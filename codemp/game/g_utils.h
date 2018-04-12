#pragma once

#include "../game/g_local.h"

#define MAX_SHADER_REMAPS 128
#define MAX_G2_KILL_QUEUE 256
#define USE_DISTANCE	64.0f

typedef struct shaderRemap_s {
  char oldShader[MAX_QPATH];
  char newShader[MAX_QPATH];
  float timeOffset;
} shaderRemap_t;

EXTERNC shaderRemap_t remappedShaders[MAX_SHADER_REMAPS];
EXTERNC int remapCount;
EXTERNC qboolean gSiegeRoundBegun;
EXTERNC int gG2KillNum;
EXTERNC int gG2KillIndex[MAX_G2_KILL_QUEUE];
EXTERNC gclient_t *gClPtrs[MAX_GENTITIES];

CCALL float ShortestLineSegBewteen2LineSegs(vec3_t start1,vec3_t end1,vec3_t start2,vec3_t end2,vec3_t close_pnt1,vec3_t close_pnt2);
CCALL qboolean G_FindClosestPointOnLineSegment(const vec3_t start,const vec3_t end,const vec3_t from,vec3_t result);
CCALL qboolean G_ExpandPointToBBox(vec3_t point,const vec3_t mins,const vec3_t maxs,int ignore,int clipmask);
CCALL void G_SpeechEvent(gentity_t *self,int event);
CCALL void G_ROFF_NotetrackCallback(gentity_t *cent,const char *notetrack);
CCALL int DebugLine(vec3_t start,vec3_t end,int color);
CCALL qboolean G_CheckInSolid(gentity_t *self,qboolean fix);
CCALL qboolean G_ClearTrace(vec3_t start,vec3_t mins,vec3_t maxs,vec3_t end,int ignore,int clipmask);
CCALL void G_SetAngles(gentity_t *ent,vec3_t angles);
CCALL qboolean G_BoxInBounds(vec3_t point,vec3_t mins,vec3_t maxs,vec3_t boundsMins,vec3_t boundsMaxs);
CCALL qboolean G_PointInBounds(vec3_t point,vec3_t mins,vec3_t maxs);
CCALL void TryUse(gentity_t *ent);
CCALL qboolean TryHeal(gentity_t *ent,gentity_t *target);
CCALL int G_CanUseDispOn(gentity_t *ent,int dispType);
CCALL void G_UseDispenserOn(gentity_t *ent,int dispType,gentity_t *target);
CCALL qboolean ValidUseTarget(gentity_t *ent);
CCALL void G_SoundOnEnt(gentity_t *ent, soundChannel_t channel,const char *soundPath);
CCALL void G_EntitySound(gentity_t *ent,int channel,int soundIndex);
CCALL void G_SoundAtLoc(vec3_t loc,int channel,int soundIndex);
CCALL void G_Sound(gentity_t *ent,int channel,int soundIndex);
CCALL void G_MuteSound(int entnum,int channel);
CCALL gentity_t *G_ScreenShake(vec3_t org,gentity_t *target,float intensity,int duration,qboolean global);
CCALL gentity_t *G_PlayEffectID(const int fxID,vec3_t org,vec3_t ang);
CCALL gentity_t *G_PlayEffect(int fxID,vec3_t org,vec3_t ang);
CCALL void G_AddEvent(gentity_t *ent,int event,int eventParm);
CCALL void G_AddPredictableEvent(gentity_t *ent,int event,int eventParm);
CCALL void G_KillBox(gentity_t *ent);
CCALL void G_ScaleNetHealth(gentity_t *self);
CCALL gentity_t *G_SoundTempEntity(vec3_t origin,int event,int channel);
CCALL void G_SetOrigin(gentity_t *ent,vec3_t origin);
CCALL gentity_t *G_TempEntity(vec3_t origin,int event);
CCALL void G_FreeEntity(gentity_t *ed);
CCALL void G_KillG2Queue(int entNum);
CCALL void G_SendG2KillQueue(void);
CCALL qboolean G_EntitiesFree(void);
CCALL gentity_t *G_Spawn(void);
CCALL void G_InitGentity(gentity_t *e);
CCALL void G_SetMovedir(vec3_t angles,vec3_t movedir);
CCALL char *vtos(const vec3_t v);
CCALL float *tv(float x,float y,float z);
CCALL void G_UseTargets(gentity_t *ent,gentity_t *activator);
CCALL void G_UseTargets2(gentity_t *ent,gentity_t *activator,const char *string);
CCALL void GlobalUse(gentity_t *self,gentity_t *other,gentity_t *activator);
CCALL gentity_t *G_PickTarget(char *targetname);
CCALL void G_SetAnim(gentity_t *ent,usercmd_t *ucmd,int setAnimParts,int anim,int setAnimFlags,int blendTime);
CCALL void BG_SetAnim(playerState_t *ps,animation_t *animations,int setAnimParts,int anim,int setAnimFlags,int blendTime);
CCALL void G_CleanAllFakeClients(void);
CCALL void G_CreateFakeClient(int entNum,gclient_t **cl);
CCALL void G_FreeVehicleObject(Vehicle_t *pVeh);
CCALL void G_AllocateVehicleObject(Vehicle_t **pVeh);
CCALL void G_FreeFakeClient(gclient_t **cl);
CCALL void G_Throw(gentity_t *targ,vec3_t newDir,float push);
CCALL int G_RadiusList(vec3_t origin,float radius,gentity_t *ignore,qboolean takeDamage,gentity_t *ent_list[MAX_GENTITIES]);
CCALL gentity_t *G_Find(gentity_t *from,int fieldofs,const char *match);
CCALL void G_TeamCommand(team_t team,char *cmd);
CCALL qboolean G_PlayerHasCustomSkeleton(gentity_t *ent);
CCALL int G_BSPIndex(const char *name);
CCALL int G_EffectIndex(const char *name);
CCALL int G_SoundSetIndex(const char *name);
CCALL int G_SoundIndex(const char *name);
CCALL int G_IconIndex(const char *name);
CCALL int G_ModelIndex(const char *name);
CCALL int G_BoneIndex(const char *name);
CCALL const char *BuildShaderStateConfig(void);
CCALL void AddRemap(const char *oldShader,const char *newShader,float timeOffset);
