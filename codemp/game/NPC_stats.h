#pragma once

#include "b_local.h"
#include "b_public.h"
#include "anims.h"
#include "ghoul2/G2.h"


#define MAX_NPC_DATA_SIZE 0x40000

EXTERNC char npcParseBuffer[MAX_NPC_DATA_SIZE];
EXTERNC char NPCParms[MAX_NPC_DATA_SIZE];
EXTERNC char *ClassNames[CLASS_NUM_CLASSES];
EXTERNC char *TeamNames[TEAM_NUM_TEAMS];
EXTERNC stringID_table_t FPTable[];
EXTERNC stringID_table_t WPTable[];
EXTERNC stringID_table_t BSETTable[];
EXTERNC stringID_table_t BSTable[];
EXTERNC stringID_table_t ClassTable[];
EXTERNC stringID_table_t TeamTable[];
EXTERNC qboolean NPCsPrecached;

CCALL void NPC_LoadParms(void);
CCALL qboolean NPC_ParseParms(const char *NPCName,gentity_t *NPC);
CCALL void SetupGameGhoul2Model(gentity_t *ent,char *modelname,char *skinName);
CCALL void NPC_Precache(gentity_t *spawner);
CCALL void NPC_PrecacheWeapons(team_t playerTeam,int spawnflags,char *NPCtype);
CCALL int NPC_WeaponsForTeam(team_t team,int spawnflags,const char *NPC_type);
CCALL void NPC_PrecacheAnimationCFG(const char *NPC_type);
CCALL qboolean G_ParseAnimFileSet(const char *filename,const char *animCFG,int *animFileIndex);
#if defined(CONVENIENT_ANIMATION_FILE_DEBUG_THING)
CCALL void SpewDebugStuffToFile(animation_t *anims);
#endif
CCALL saber_colors_t TranslateSaberColor(const char *name);
CCALL qboolean BG_ParseLiteral(const char **data,const char *string);
CCALL int NPC_ReactionTime(void);
CCALL void WP_RemoveSaber(saberInfo_t *sabers,int saberNum);
CCALL qboolean WP_SaberParseParms(const char *SaberName,saberInfo_t *saber);
