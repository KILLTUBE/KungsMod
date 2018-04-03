#pragma once

#include "../qcommon/q_shared.h"

EXTERNC int ui_numBots;

CCALL char *UI_GetBotNameByNumber(int num);
CCALL int UI_GetNumBots();
CCALL char *UI_GetBotInfoByName(const char *name);
CCALL char *UI_GetBotInfoByNumber(int num);
CCALL void UI_LoadBots(void);
CCALL void UI_LoadBotsFromFile(char *filename);
CCALL void UI_LoadArenas(void);
CCALL int UI_ParseInfos(char *buf,int max,char *infos[]);
