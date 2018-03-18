#include "imgui/imgui_api.h"
#include "tr_local.h"
#include "imgui/include_imgui.h"
#include "imgui_openjk/imgui_openjk_default_docks.h"

void RE_KeyEvent(int key, int state) {
	ImGuiIO& io = ImGui::GetIO();
	if (key >= 0 && key <= 256)
		io.KeysDown[key] = state;
}

void RE_CharEvent(int key) {
	// basically just this: https://github.com/ocornut/imgui/blob/69e700f8694f89707b7aec91551f4a9546684040/examples/directx9_example/imgui_impl_dx9.cpp#L273
	// with a round trip from client.exe to renderer.dll
	// You can also use ToAscii()+GetKeyboardState() to retrieve characters.
	if (key > 0 && key < 0x10000) {
		ImGuiIO& io = ImGui::GetIO();
		io.AddInputCharacter((unsigned short)key);
	}
}

void RE_MouseWheelEvent(float dir) {
	imgui_mouse_wheel(dir);
}

void RE_MouseClickEvent(int key, int state) {
	if (key >= 0 && key <= 4)
		imgui_mouse_set_button(key, state);
}

void RE_RenderImGui() {
	float width = glConfig.vidWidth;
	float height = glConfig.vidHeight;

	if (!(ri.Key_GetCatcher() & KEYCATCH_IMGUI))
		return;

	// copy over all keys to imgui
	ImGuiIO& io = ImGui::GetIO();
	//for (int i=0; i<MAX_KEYS; i++)
	//	io.KeysDown[i] = keyStatus[i];

	// Read keyboard modifiers inputs
	io.KeyCtrl = (GetKeyState(VK_CONTROL) & 0x8000) != 0;
	io.KeyShift = (GetKeyState(VK_SHIFT) & 0x8000) != 0;
	io.KeyAlt = (GetKeyState(VK_MENU) & 0x8000) != 0;
	io.KeySuper = false;

	float x = -1;
	float y = -1;


#if 0//defined(__GNUC__) || defined(MACOS_X)
	vec2_t ratio;
	ratio[0] = (float)glConfig.vidWidth / (float)SCREEN_WIDTH;
	ratio[1] = (float)glConfig.vidHeight / (float)SCREEN_HEIGHT;
	x = mouseStatus[0] * ratio[0];
	y = mouseStatus[1] * ratio[1];
#else
	POINT p;
	if (GetCursorPos(&p)) {//cursor position now in p.x and p.y
						   //HANDLE hwnd = GetCurrentProcess();
		HWND hwnd = GetActiveWindow();
		if (ScreenToClient(hwnd, &p)) {
			//p.x and p.y are now relative to hwnd's client area
			x = p.x;
			y = p.y;
		}
	}
#endif

	imgui_set_mousepos((int)x, (int)y);
	imgui_set_widthheight(width, height);
	//imgui_mouse_set_button(0, keyStatus[A_MOUSE1]);
	//imgui_mouse_set_button(1, keyStatus[A_MOUSE2]);
	//imgui_mouse_set_button(2, keyStatus[A_MOUSE3]);

	/*
	* VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
	* 0x40 : unassigned
	* VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
	*/
#if 0
	for (int i = A_CAP_A; i <= A_CAP_Z; i++)
	{
		if (keyStatus[i])
		{
			int vkNum = (i - A_CAP_A) + 0x30;
			nk_input_char(&GUI_ctx, vkNum);
		}
		else if (keyStatus[i - 32])
		{
			int vkNum = (i - A_LOW_A) + 0x30;
			nk_input_char(&GUI_ctx, vkNum);
		}
	}

	for (int i = A_0; i <= A_9; i++)
	{
		if (keyStatus[i])
		{
			int vkNum = (i - A_0) + 0x41;
			nk_input_char(&GUI_ctx, vkNum);
		}
	}
#endif

	//FBO_Bind(tr.renderGUIFbo);
	FBO_Bind(NULL);
	GL_SetDefaultState();
	GL_State(GLS_DEPTHTEST_DISABLE | GLS_SRCBLEND_SRC_ALPHA | GLS_DSTBLEND_ONE_MINUS_SRC_ALPHA);
	GL_Cull(CT_TWO_SIDED);
	qglColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	qglClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//qglClear(GL_COLOR_BUFFER_BIT);

	static int first = 1;
	if (first) {
		imgui_init();
		first = 0;
	}

	imgui_new_frame();
	imgui_render();
	imgui_openjk_default_docks();
	imgui_end_frame();

	/* default OpenGL state */
	//qglUseProgram(0);
	//qglBindBuffer(GL_ARRAY_BUFFER, 0);
	//qglBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//qglBindVertexArray(tr.globalVao);
	tr.globalVao;
	//FBO_Bind(glState.previousFBO);
	// todo: make it a proper DSA function and save it in glState aswell
	// for some reason a map loading is resetting tr.globalVao, so imgui only works in the start menu...
	qglBindVertexArray(1);
	//FBO_Bind(NULL);
	R_BindNullVBO();
	R_BindNullIBO();
	//glState.current = -123;
	GLSL_BindNullProgram();
	GL_SetDefaultState();
}


