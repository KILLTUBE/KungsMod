#ifndef DOCK_QUAKESHADERS
#define DOCK_QUAKESHADERS

#include "../imgui_docks/dock.h"
#include <string>

class DockQuakeShaders : public Dock {
public:
	DockQuakeShaders();
	virtual const char *label();
	virtual void imgui();
};

#endif