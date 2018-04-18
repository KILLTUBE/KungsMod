
#include "dock_menus.h"
#include "../imgui_docks/dock_console.h"
#include "../imgui_openjk/gluecode.h"

extern "C" {
#include "ui/ui_local.h"
}

DockMenus::DockMenus() {}


const char *DockMenus::label() {
	return "Menus";
}


EXTERNC menuDef_t Menus[MAX_MENUS];      // defined menus
EXTERNC int menuCount;               // how many

void DockMenus::imgui() {
	for (int i=0; i<menuCount; i++) {
	
		menuDef_t *menu = Menus + i;


		ImGui::Text("menu[%d] name=%s",
			i,
			menu->window.name
		);
		
	}

	// 
	if (ImGui::Button("UI_LoadMenus jampingame.txt")) {
		UI_LoadMenus("ui/jampingame.txt", qfalse);
	}
	if (ImGui::Button("UI_LoadMenus jampmenus.txt")) {
		UI_LoadMenus("ui/jampmenus.txt", qfalse);
	}

}