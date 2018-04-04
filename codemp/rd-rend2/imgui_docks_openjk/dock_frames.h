#pragma once

#include "../imgui_docks/dock.h"
#include <string>
#include "../imgui/imgui_dock.h"

class DockFrames : public Dock {
public:
	DockFrames();
	virtual const char *label();
	virtual void imgui();
};
