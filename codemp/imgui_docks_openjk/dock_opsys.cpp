#include "dock_opsys.h"
#include "../include_imgui.h"
#include "../include_console.h"
#include "../opsys/opsys.h"
#include "rd-rend2/compose_images.h"

OpSystem *opsys_root = NULL;

DockOpsys::DockOpsys(std::string filename) {
#ifndef EMSCRIPTEN
	opsys_root = new OpSystem( (char *) filename.c_str() );
#endif
}

const char *DockOpsys::label() {
	return opsys_root->name;
}

void DockOpsys::imgui() {
#ifndef EMSCRIPTEN
	opsys_root->update();
	opsys_root->editor->DoFrame();
	resetImageChanges();
	//ImGui::Button("DockOpsys...");
#endif
}