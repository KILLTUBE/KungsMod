#pragma once

#include "../qcommon/q_shared.h"

CCALL void UI_DrawRect(float x,float y,float width,float height,const float *color);
CCALL void UI_DrawTopBottom(float x,float y,float w,float h);
CCALL void UI_DrawSides(float x,float y,float w,float h);
CCALL void UI_FillRect(float x,float y,float width,float height,const float *color);
CCALL void UI_DrawHandlePic(float x,float y,float w,float h,qhandle_t hShader);
CCALL qboolean UI_ConsoleCommand(int realTime);
CCALL int cmdcmp_ui(const void *a,const void *b);
CCALL char *UI_Cvar_VariableString(const char *name);