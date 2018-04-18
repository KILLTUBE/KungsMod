#pragma once

#include "../imgui_docks/dock.h"
#include <string>
#include "../imgui/imgui_dock.h"

class DockClients : public Dock {
public:
	DockClients();
	virtual const char *label();
	virtual void imgui();
};
