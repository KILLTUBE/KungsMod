#include <stdio.h>
#include "../imgui/imgui.h"
#include "../imgui/imgui_dock.h"
#include "../imgui_docks/dock.h"
#include "imgui_openjk_default_docks.h"

// custom docks
#include "../imgui_docks_openjk/dock_shadereditor.h"
#include "../imgui_docks_openjk/dock_mapinfo.h"
#include "../imgui_docks_openjk/dock_perf.h"
#include "../imgui_docks_openjk/dock_controlflow.h"
#include "../imgui_docks_openjk/dock_models.h"
#include "../imgui_docks_openjk/dock_all.h"
#include "../imgui_docks_openjk/dock_quakeshaders.h"
#include "../imgui_docks_openjk/dock_opsys.h"
#include "../imgui_docks_openjk/dock_images.h"
#include "../imgui_docks_openjk/dock_menus.h"
#include "../imgui_docks_openjk/dock_fbos.h"
#include "../imgui_docks_openjk/dock_ghoul2.h"
#include "../imgui_docks_openjk/dock_anims.h"
#include "../imgui_docks_openjk/dock_frames.h"
#include "../imgui_docks_openjk/dock_clients.h"
#include "../imgui/imgui_api.h"

#include <list>
std::list<Dock *> imgui_quake_docks;

void alignTabsDefault();

CCALL int add_dock(Dock *dock) {
	imgui_quake_docks.push_back(dock);
	return 1;
}

CCALL void *imgui_get_current_dock();
bool dockRight(CDock *from, CDock *to);
CDock *findDock(char *name);

CCALL int imgui_openjk_default_docks() {
	if (imgui_quake_docks.size() == 0) {
		// the last dock is seen first when pressing F2, so lets make it an useful one
		//imgui_quake_docks.push_back(new DockMapInfo());
		//imgui_quake_docks.push_back(new DockPerf());
		imgui_quake_docks.push_back(new DockControlFlow());
		imgui_quake_docks.push_back(new DockModels());
		imgui_quake_docks.push_back(new DockAll());
		imgui_quake_docks.push_back(new DockQuakeShaders());
		imgui_quake_docks.push_back(new DockShaders());
		imgui_quake_docks.push_back(new DockImages());
		imgui_quake_docks.push_back(new DockOpsys("opsystems/matmulpoint.opsys"));
		imgui_quake_docks.push_back(new DockMenus());
		imgui_quake_docks.push_back(new DockFBOs());
		imgui_quake_docks.push_back(new DockGhoul2());
		imgui_quake_docks.push_back(new DockAnims());
		imgui_quake_docks.push_back(new DockFrames());
		imgui_quake_docks.push_back(new DockClients());
		//imgui_quake_docks.push_back(new DockExplorer());
		//imgui_quake_docks.push_back(new DockAnims());
		//imgui_quake_docks.push_back(new DockSound());
		//imgui_quake_docks.push_back(new DockVars());
		//imgui_quake_docks.push_back(new DockQuakeShaders());
		//imgui_quake_docks.push_back(new DockHuds());
		//imgui_quake_docks.push_back(new DockEntity());
		//imgui_quake_docks.push_back(new DockConfigstrings());
#ifndef EMSCRIPTEN
		//imgui_quake_docks.push_back(new DockDuktape());
		//imgui_quake_docks.push_back(new DockOpsys( "opsystems/matmulpoint.opsys" ));
#endif
	}

	for (Dock *dock : imgui_quake_docks) {
		bool closed = true;
		if (BeginDock(dock->label(), &closed, 0, dock->cdock)) {
			if (dock->cdock == NULL)
				dock->cdock = (CDock *)imgui_get_current_dock();
			dock->imgui();
		}
		EndDock();
	}

	// gotta make sure that the docks were at least drawn once, otherwise cant find them via string label
	static int first = 1;
	if (first == 2) {

		CDock *all = findDock("All");
		CDock *console = findDock("Console");
		CDock *node = findDock("Node");
		dockRight(node, console);


		// until i figure out how the dock code exactly works this must be good enough...
		// basically every step gets more successive to the aimed value (todo: rewrite dock system...)
		g_dock.getRootDock()->setPosSize(g_dock.getRootDock()->pos, g_dock.getRootDock()->size);
		console->parent->size.y = 180;
		g_dock.getRootDock()->setPosSize(g_dock.getRootDock()->pos, g_dock.getRootDock()->size);
		console->parent->size.y = 180;
		g_dock.getRootDock()->setPosSize(g_dock.getRootDock()->pos, g_dock.getRootDock()->size);
		console->parent->size.y = 180;

		first = 0;
	}
	if (first == 1) {
		alignTabsDefault();
		first = 2;
	}


	return 1;
}
