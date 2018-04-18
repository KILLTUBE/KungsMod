#ifndef DOCK_MENUS
#define DOCK_MENUS

#include "../imgui_docks/dock.h"
#include <string>
#include "../imgui/imgui_dock.h"

class DockMenus : public Dock {
public:
	DockMenus();
	virtual const char *label();
	virtual void imgui();
};

#endif