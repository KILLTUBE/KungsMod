#ifndef IMGUIQUAKE_DOCK_IMAGES
#define IMGUIQUAKE_DOCK_IMAGES

#include "../imgui_docks/dock.h"
#include <string>

class DockImages : public Dock {
public:
	DockImages();
	virtual const char *label();
	virtual void imgui();
};

#endif