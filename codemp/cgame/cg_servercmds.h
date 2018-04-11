
#pragma once

#include "cg_local.h"
#include "ui/menudef.h"
#include "ghoul2/G2.h"
#include "ui/ui_public.h"

#define SCORE_OFFSET (14)
#define TEAMINFO_OFFSET (6)

EXTERNC const char *cg_customDuelSoundNames[MAX_CUSTOM_DUEL_SOUNDS];
EXTERNC const char *cg_customJediSoundNames[MAX_CUSTOM_JEDI_SOUNDS];
EXTERNC const char *cg_customExtraSoundNames[MAX_CUSTOM_EXTRA_SOUNDS];
EXTERNC const char *cg_customCombatSoundNames[MAX_CUSTOM_COMBAT_SOUNDS];
EXTERNC char *cg_customSoundNames[MAX_CUSTOM_SOUNDS];
EXTERNC int cg_siegeWinTeam;
EXTERNC int cg_beatingSiegeTime;
EXTERNC int cgSiegeRoundTime;
EXTERNC int cgSiegeRoundState;

CCALL void CG_ExecuteNewServerCommands(int latestSequence);
CCALL int svcmdcmp_cg(const void *a,const void *b);
CCALL void CG_ChatBox_AddString(char *chatStr);
CCALL void CG_ParseSiegeExtendedData(void);
CCALL void CG_SiegeBriefingDisplay(int team,int dontshow);
CCALL void CG_CheckSVStringEdRef(char *buf,const char *str);
CCALL void CG_KillCEntityInstances(void);
CCALL void CG_KillCEntityG2(int entNum);
CCALL void CG_ParseSiegeState(const char *str);
CCALL void CG_ParseWeatherEffect(const char *str);
CCALL void CG_ParseSiegeObjectiveStatus(const char *str);
CCALL void SetDuelistHealthsFromConfigString(const char *str);
CCALL void CG_CacheG2AnimInfo(char *modelName);
CCALL int CG_HandleAppendedSkin(char *modelName);
CCALL void CG_HandleNPCSounds(centity_t *cent);
CCALL void CG_PrecacheNPCSounds(const char *str);
CCALL void SetCustomSoundForType(clientInfo_t *ci,int setType,int index,sfxHandle_t sfx);
CCALL void CG_ShaderStateChanged(void);
CCALL void CG_SetConfigValues(void);
CCALL void CG_ParseServerinfo(void);
