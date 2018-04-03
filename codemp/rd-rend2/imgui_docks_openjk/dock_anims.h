#pragma once

#include "../imgui_docks/dock.h"
#include <string>
#include "../imgui/imgui_dock.h"

class DockAnims : public Dock {
public:
	DockAnims();
	virtual const char *label();
	virtual void imgui();
};
