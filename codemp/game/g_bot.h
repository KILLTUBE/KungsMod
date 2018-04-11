#pragma once

#include "g_local.h"

#define BOT_BEGIN_DELAY_BASE		2000
#define BOT_BEGIN_DELAY_INCREMENT	1500
#define BOT_SPAWN_QUEUE_DEPTH	16
#define MAX_MAPS 256
#define MAPSBUFSIZE (MAX_MAPS * 64)

static struct botSpawnQueue_s {
	int		clientNum;
	int		spawnTime;
} botSpawnQueue[BOT_SPAWN_QUEUE_DEPTH];

CCALL void G_InitBots(void);
CCALL void LoadPath_ThisLevel(void);
CCALL char *G_GetBotInfoByNumber(int num);
CCALL void Svcmd_BotList_f(void);
CCALL void Svcmd_AddBot_f(void);
CCALL char *G_GetBotInfoByName(const char *name);
CCALL qboolean G_BotConnect(int clientNum,qboolean restart);
CCALL void G_RemoveQueuedBotBegin(int clientNum);
CCALL void G_CheckBotSpawn(void);
CCALL void G_CheckMinimumPlayers(void);
CCALL int G_CountBotPlayers(int team);
CCALL int G_CountHumanPlayers(int team);
CCALL int G_RemoveRandomBot(int team);
CCALL void G_AddRandomBot(int team);
CCALL const char *G_GetArenaInfoByMap(const char *map);
CCALL void G_LoadArenas(void);
CCALL const char *G_RefreshNextMap(int gametype,qboolean forced);
CCALL qboolean G_DoesMapSupportGametype(const char *mapname,int gametype);
CCALL int G_GetMapTypeBits(char *type);
CCALL void G_LoadArenasFromFile(char *filename);
CCALL int G_ParseInfos(char *buf,int max,char *infos[]);
CCALL float trap_Cvar_VariableValue(const char *var_name);
