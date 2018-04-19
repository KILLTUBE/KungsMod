#ifndef IMGUI_API_H
#define IMGUI_API_H

#include "../ccall/ccall.h"
#include "imgui_default_docks.h"

struct imgui_globals_s {
	int mouse_left;
	int mouse_top;
	int screen_width;
	int screen_height;
	unsigned int global_ticks;
};

extern struct imgui_globals_s imguidata;
EXTERNC int imgui_ready;
typedef int kungbool; // just for having type safety among all compilers

ICAPI void ICDECL imgui_set_mousepos(int left, int top);
ICAPI void ICDECL imgui_set_widthheight(int width, int height);
ICAPI void ICDECL imgui_mouse_set_button(int button, kungbool state);
ICAPI void ICDECL imgui_mouse_wheel(float wheelDelta);
ICAPI void ICDECL imgui_on_key(int key, kungbool state);
ICAPI void ICDECL imgui_on_shift(kungbool state);
ICAPI void ICDECL imgui_on_ctrl (kungbool state);
ICAPI void ICDECL imgui_on_alt  (kungbool state);
ICAPI void ICDECL imgui_set_ticks(unsigned int ticks);
ICAPI void ICDECL imgui_on_key_text(int key);
ICAPI void ICDECL imgui_on_text(char *text);

ICAPI void ICDECL imgui_init();
ICAPI void ICDECL imgui_new_frame();
ICAPI void ICDECL imgui_end_frame();
ICAPI void ICDECL imgui_render();

#endif