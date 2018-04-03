#ifndef DOCK_FBOS
#define DOCK_FBOS

#include "../imgui_docks/dock.h"
#include <string>
#include "../imgui/imgui_dock.h"

class DockFBOs : public Dock {
public:
	DockFBOs();
	virtual const char *label();
	virtual void imgui();
};

#endif