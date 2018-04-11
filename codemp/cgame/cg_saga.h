#pragma once

#include "cg_local.h"
#include "game/bg_saga.h"

EXTERNC siegeExtended_t cg_siegeExtendedData[MAX_CLIENTS];
EXTERNC int cgSiegeTeam2PlShader;
EXTERNC int cgSiegeTeam1PlShader;
EXTERNC int team2Timed;
EXTERNC int team1Timed;
EXTERNC int cgSiegeRoundTime;
EXTERNC int cgSiegeRoundState;

CCALL void CG_ParseSiegeExtendedData(void);
CCALL void CG_ParseSiegeExtendedDataEntry(const char *conStr);
CCALL void CG_SiegeObjectiveCompleted(centity_t *ent,int won,int objectivenum);
CCALL int CG_SiegeGetObjectiveFinal(int team,int objective);
CCALL void CG_SiegeGetObjectiveDescription(int team,int objective,char *buffer);
CCALL void CG_SiegeRoundOver(centity_t *ent,int won);
CCALL void CG_ParseSiegeObjectiveStatus(const char *str);
CCALL void CG_SetSiegeTimerCvar(int msec);
CCALL void CG_InitSiegeMode(void);
CCALL void CG_PrecachePlayersForSiegeTeam(int team);
CCALL void CG_PrecacheSiegeObjectiveAssetsForTeam(int myTeam);
CCALL void CG_SiegeBriefingDisplay(int team,int dontshow);
CCALL void CG_SiegeBriefingDisplay(int team,int dontshow);
CCALL void CG_DrawSiegeMessageNonMenu(const char *str);
CCALL void CG_DrawSiegeMessage(const char *str,int objectiveScreen);
CCALL void CG_LoadCISounds(clientInfo_t *ci,qboolean modelloaded);