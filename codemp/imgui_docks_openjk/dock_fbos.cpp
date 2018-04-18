#include "dock_fbos.h"
#include "../imgui_docks/dock_console.h"
#include "../imgui_openjk/gluecode.h"
#include "rd-rend2/tr_local.h"

DockFBOs::DockFBOs() {}

const char *DockFBOs::label() {
	return "FBOs";
}

CCALL void FBO_CreateBuffer(FBO_t *fbo, int format, int index, int multisample);
CCALL void FBO_SetupDrawBuffers();

float viewport_tmp[4] = {0.0};
void R_CreateBuiltinImages( void );

void DockFBOs::imgui() {
	
	ImGui::PushItemWidth(150);
	
		
	if (ImGui::Button("FBO_Init(void)")) {
		FBO_Init();
	}

	if (ImGui::Button("R_CreateBuiltinImages( void )")) {
		R_CreateBuiltinImages();
	}

	ImGui::DragFloat4("viewport_tmp", viewport_tmp);

	for (int i=0; i<tr.numFBOs; i++) {
		FBO_t *fbo = tr.fbos[i];
		ImGui::PushID(fbo);

		ImGui::Text("FBO[%d] name=%s frameBuffer=%d depthBuffer=%d colorbuffers=%d,%d,%d,%d,%d,%d",
			i,
			fbo->name,
			fbo->frameBuffer,
			fbo->depthBuffer,
			fbo->colorBuffers[0],
			fbo->colorBuffers[1],
			fbo->colorBuffers[2],
			fbo->colorBuffers[3],
			fbo->colorBuffers[4],
			fbo->colorBuffers[5]
		);
		
		

		ImGui::DragInt("w", &fbo->width);
		ImGui::DragInt("h", &fbo->height);

		
		if (ImGui::Button("Update _render")) {

			int hdrFormat = GL_RGBA8;
			if (r_hdr->integer) {
				hdrFormat = GL_RGB16F;
			}

			//qglDeleteFramebuffers(1, &fbo->frameBuffer);
			qglGenFramebuffers(1, &fbo->frameBuffer);

			FBO_Bind(NULL);
			//qglBindFramebuffer(GL_FRAMEBUFFER, fbo->frameBuffer);
			glState.currentFBO = fbo;
			int multisample = 0; // idk
			FBO_CreateBuffer(fbo, hdrFormat, 0, multisample);
			FBO_CreateBuffer(fbo, hdrFormat, 1, multisample);
			FBO_CreateBuffer(fbo, GL_DEPTH_COMPONENT24, 0, multisample);
			glState.currentFBO = fbo;
			FBO_Bind(fbo);
			FBO_SetupDrawBuffers();
			tr.renderFbo = fbo;
			FBO_Bind(fbo);
		}
		
		if (ImGui::Button("Update depth")) {

			int hdrFormat = GL_RGBA8;
			if (r_hdr->integer) {
				hdrFormat = GL_RGB16F;
			}

			FBO_Bind(fbo);
			int multisample = 4; // idk
			//FBO_CreateBuffer(fbo, hdrFormat, 0, multisample);
			//FBO_CreateBuffer(fbo, hdrFormat, 1, multisample);
			FBO_CreateBuffer(fbo, GL_DEPTH_COMPONENT24, 0, multisample);
			FBO_SetupDrawBuffers();		
		}
		if (ImGui::Button("Update multisample=0")) {

			int hdrFormat = GL_RGBA8;
			if (r_hdr->integer) {
				hdrFormat = GL_RGB16F;
			}

			FBO_Bind(fbo);
			int multisample = 0; // idk
			FBO_CreateBuffer(fbo, hdrFormat, 0, multisample);
			FBO_CreateBuffer(fbo, hdrFormat, 1, multisample);
			//FBO_CreateBuffer(fbo, GL_DEPTH_COMPONENT24, 0, multisample);
			FBO_SetupDrawBuffers();		
		}
		
		ImGui::PopID();
	}
	ImGui::PopItemWidth();

	// 
	//if (ImGui::Button("UI_LoadMenus jampingame.txt")) {
	//	UI_LoadMenus("ui/jampingame.txt", qfalse);
	//}
	//if (ImGui::Button("UI_LoadMenus jampmenus.txt")) {
	//	UI_LoadMenus("ui/jampmenus.txt", qfalse);
	//}

}