#include "dock_shadereditor.h"

#include "../imgui_docks/dock_console.h"
//#include <renderergl2/tr_model_kung.h>
#include "rd-warzone/tr_glsl.h"
#include <imgui/MagicFile.cpp/magicfile.h>

DockShaders::DockShaders() {}

const char *DockShaders::label() {
	return "shaders";
}

bool IsKeyPressedMap(ImGuiKey key, bool repeat = true);

int GLSL_MyCompileGPUShader(GLuint program, GLuint *prevShader, const GLchar *buffer, int size, GLenum shaderType) {
	GLint           compiled;
	GLuint          shader;
	shader = qglCreateShader(shaderType);
	qglShaderSource(shader, 1, (const GLchar **)&buffer, &size);
	// compile shader
	qglCompileShader(shader);
	// check if shader compiled
	qglGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if(!compiled) {
		//GLSL_PrintLog(shader, GLSL_PRINTLOG_SHADER_SOURCE, qfalse);
		//GLSL_PrintLog(shader, GLSL_PRINTLOG_SHADER_INFO, qfalse);
		//imgui_log("Couldn't compile shader");
		return 0;
	}
	//if (*prevShader) {
	//	qglDetachShader(program, *prevShader);
	//	qglDeleteShader(*prevShader);
	//}
	qglAttachShader(program, shader);
	*prevShader = shader;
	return 1;
}

void DockShaders::recompileShader() {
		int newProgram = qglCreateProgram();
		int retVert = GLSL_MyCompileGPUShader(newProgram, &shader->vertexShader, shader->vertexText, strlen(shader->vertexText), GL_VERTEX_SHADER);
		if (retVert == 0) {
			imgui_log("Couldn't compile Vertex shader\n");
			return;
		}
		int retFrag = GLSL_MyCompileGPUShader(newProgram, &shader->fragmentShader, shader->fragText, strlen(shader->fragText), GL_FRAGMENT_SHADER);
		if (retFrag == 0) {
			imgui_log("Couldn't compile Fragment shader\n");
			return;
		}
		// if both shaders compiled, link them and resetup all the quake stuff
		shader->program = newProgram;
		GLSL_BindAttributeLocations(shader, shader->attribs);
		int retLink = GLSL_LinkProgramSafe(newProgram);
		GLSL_BindAttributeLocations(shader, shader->attribs);
		GLSL_InitUniforms(shader);
		imgui_log("ret compile shader:  retVert=%d retFrag=%d retLink=%d\n", retVert, retFrag, retLink);
}

//void DockShaders::recompileFragmentShader() {
//		int newProgram = qglCreateProgram();
//		int ret = GLSL_CompileGPUShader(shader->program, &shader->fragmentShader, shader->fragText, strlen(shader->fragText), GL_FRAGMENT_SHADER);
//		if (ret)
//			GLSL_LinkProgram(shader->program);
//		imgui_log("ret compile shader:  %d\n", ret);
//}

void DockShaders::imgui() {


	#define NUM_SHADERS 256
	int num_shaders = shaders_next_id;
	//shaderProgram_t *shaders[NUM_SHADERS];
	char items[NUM_SHADERS][256];
	char *items_[NUM_SHADERS]; // just a pointer list

	
	//for (int i=0; i<32; i++)
	//	shaders[i] = tr.genericShader + i;
	//for (int i=0; i<64; i++)
	//	shaders[i + 32] = tr.lightallShader + i;
	//shaders[32+64] = &tr.textureColorShader;
	

	for (int i=0; i<num_shaders; i++) {
		//shaderProgram_t *shader = tr.genericShader + i;
		shaderProgram_t *shader = shaders[i];
		if (shader == NULL)
			continue;
		sprintf(items[i], "shaders[%d] %s prog=%d vert=%d frag=%d usagecount=%d", i, shader->name, shader->program, shader->vertexShader, shader->fragmentShader, shader->usageCount);
		items_[i] = items[i];
	}

	ImGui::Combo("shader", &currentItem, (const char **)items_, num_shaders);
	ImGui::DragInt("currentItem", &currentItem);
	

	if (currentItem <= 0)
		currentItem = 0;
	if (currentItem >= num_shaders)
		currentItem = num_shaders - 1;

	shader = shaders[currentItem];
	if (ImGui::Button("Recompile Shader")) {
		recompileShader();
	}

	//ImGui::NewLine();

	ImVec2 winsize = ImGui::GetWindowSize();
	winsize -= ImVec2(30,30); // border crap

	ImVec2 startpos = ImGui::GetCursorPos();

	float heightLeft = winsize.y - startpos.y;
	
	ImVec2 vertPosStart = ImVec2(startpos);
	ImVec2 vertPosSize = ImVec2(winsize.x / 2, heightLeft);
	//ImVec2 size;
	//size.x = ImGui::GetWindowSize();
	ImGui::SetCursorPos(vertPosStart);
	ImGui::InputTextMultiline("##vert", shader->vertexText, sizeof(shader->vertexText), vertPosSize, ImGuiInputTextFlags_AllowTabInput);

	if (ImGui::IsItemActive() && ImGui::GetIO().KeyCtrl && IsKeyPressedMap(ImGuiKey_Enter, 0)) {
		recompileShader();
	}

	ImVec2 fragPosStart = ImVec2(startpos) + ImVec2(winsize.x / 2 + 15, 0);
	ImVec2 fragPosSize = ImVec2(winsize.x / 2, heightLeft);
	//ImVec2 size;
	//size.x = ImGui::GetWindowSize();
	ImGui::SetCursorPos(fragPosStart);
	ImGui::InputTextMultiline("##frag", shader->fragText, sizeof(shader->fragText), fragPosSize, ImGuiInputTextFlags_AllowTabInput);
	
	if (ImGui::IsItemActive() && ImGui::GetIO().KeyCtrl && IsKeyPressedMap(ImGuiKey_Enter, 0)) {
		recompileShader();
	}

}