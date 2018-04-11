#pragma once

#include "cg_local.h"
#include "ui/ui_shared.h"
#include "../client/keycodes.h"

EXTERNC displayContextDef_t cgDC;

CCALL void CG_GetTeamColor(vec4_t *color);
CCALL qboolean CG_DeferMenuScript(char **args);
CCALL void CG_RunMenuScript(char **args);
CCALL void CG_ShowResponseHead(void);
CCALL int CG_ClientNumFromName(const char *p);
CCALL void CG_KeyEvent(int key,qboolean down);
CCALL void CG_EventHandling(int type);
CCALL void CG_ShowTeamMenu();
CCALL void CG_HideTeamMenu();
CCALL void CG_MouseEvent(int x,int y);
CCALL void CG_OwnerDraw(float x,float y,float w,float h,float text_x,float text_y,int ownerDraw,int ownerDrawFlags,int align,float special,float scale,vec4_t color,qhandle_t shader,int textStyle,int font);
CCALL void CG_DrawMedal(int ownerDraw,rectDef_t *rect,float scale,vec4_t color,qhandle_t shader);
CCALL void CG_DrawTeamSpectators(rectDef_t *rect,float scale,vec4_t color,qhandle_t shader);
CCALL void CG_DrawNewTeamInfo(rectDef_t *rect,float text_x,float text_y,float scale,vec4_t color,qhandle_t shader);
CCALL const char *CG_GetLocationString(const char *loc);
CCALL int MenuFontToHandle_CG(int iMenuFont);
CCALL const char *CG_GetGameStatusText(void);
CCALL const char *CG_GetKillerText(void);
CCALL qboolean CG_OwnerDrawVisible(int flags);
CCALL qboolean CG_YourTeamHasFlag(void);
CCALL qboolean CG_OtherTeamHasFlag(void);
CCALL float CG_GetValue(int ownerDraw);
CCALL qhandle_t CG_StatusHandle(int task);
CCALL int CG_GetSelectedPlayer();
