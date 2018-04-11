#pragma once

#include "cg_local.h"

#define MAX_LOADING_PLAYER_ICONS	16
#define MAX_LOADING_ITEM_ICONS		26
#define UI_INFOFONT (UI_BIGFONT)

CCALL void CG_DrawInformation(void);
CCALL void CG_LoadingClient(int clientNum);
CCALL void CG_LoadingItem(int itemNum);
CCALL void CG_LoadingString(const char *s);
CCALL void CG_LoadBar(void);
CCALL void CG_LoadBar(void);
