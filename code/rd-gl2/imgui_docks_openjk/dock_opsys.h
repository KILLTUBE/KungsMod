#ifndef DOCK_OPSYS
#define DOCK_OPSYS

#include "../imgui_docks/dock.h"
#include <string>

class DockOpsys : public Dock {
public:
	std::string filename;
	DockOpsys(std::string filename);
	virtual const char *label();
	virtual void imgui();
};

#endif