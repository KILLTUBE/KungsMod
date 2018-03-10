#ifndef DOCK_H
#define DOCK_H


// creating a new dock: add it to imgui_api.cpp line 457, like: docks.push_back(new DockExplorer());
#ifdef __cplusplus

class Dock {
public:
	virtual const char *label();
	virtual void imgui();
};

#endif

#endif