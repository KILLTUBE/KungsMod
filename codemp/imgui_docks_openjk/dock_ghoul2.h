#pragma once

#include "../imgui_docks/dock.h"
#include <string>
#include "../imgui/imgui_dock.h"

class DockGhoul2 : public Dock {
public:
	DockGhoul2();
	virtual const char *label();
	virtual void imgui();
};
