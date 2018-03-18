#include "../imgui/imgui.h"
#include "../imgui/imgui_dock.h"
#include <stdio.h>
#include "../imgui_docks/dock.h"
#include "../imgui_openjk/imgui_openjk_default_docks.h"
//#include "../imgui_docks_openjk/dock_shadereditor.h"

#include <list>
std::list<Dock *> imgui_quake_docks;
CCALL int imgui_openjk_default_docks() {
	if (imgui_quake_docks.size() == 0) {
		//imgui_quake_docks.push_back(new DockShaders());
		//imgui_quake_docks.push_back(new DockExplorer());
		//imgui_quake_docks.push_back(new DockModels());
		//imgui_quake_docks.push_back(new DockAnims());
		//imgui_quake_docks.push_back(new DockSound());
		//imgui_quake_docks.push_back(new DockVars());
		//imgui_quake_docks.push_back(new DockQuakeShaders());
		//imgui_quake_docks.push_back(new DockHuds());
		//imgui_quake_docks.push_back(new DockImages());
		//imgui_quake_docks.push_back(new DockEntity());
		//imgui_quake_docks.push_back(new DockConfigstrings());
		#ifndef EMSCRIPTEN
		//imgui_quake_docks.push_back(new DockDuktape());
		//imgui_quake_docks.push_back(new DockOpsys( "opsystems/matmulpoint.opsys" ));
		#endif
	}
	for (Dock *dock : imgui_quake_docks) {
		bool closed = true;
		if (BeginDock(dock->label(), &closed)) {
			dock->imgui();
		}
		EndDock();
	}
	return 1;
}
