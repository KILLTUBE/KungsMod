#pragma once


#include "b_local.h"

EXTERNC int eventClearTime;

CCALL void SP_target_interest(gentity_t *self);
CCALL int G_FindLocalInterestPoint(gentity_t *self);
CCALL float NPC_GetVFOVPercentage(vec3_t spot,vec3_t from,vec3_t facing,float vFOV);
CCALL float NPC_GetHFOVPercentage(vec3_t spot,vec3_t from,vec3_t facing,float hFOV);
CCALL qboolean G_ClearLOS4(gentity_t *self,gentity_t *ent);
CCALL qboolean G_ClearLOS3(gentity_t *self,const vec3_t start,gentity_t *ent);
CCALL qboolean G_ClearLOS2(gentity_t *self,gentity_t *ent,const vec3_t end);
CCALL qboolean G_ClearLOS(gentity_t *self,const vec3_t start,const vec3_t end);
CCALL void ClearPlayerAlertEvents(void);
CCALL void AddSightEvent(gentity_t *owner,vec3_t position,float radius,alertEventLevel_e alertLevel,float addLight);
CCALL void AddSoundEvent(gentity_t *owner,vec3_t position,float radius,alertEventLevel_e alertLevel,qboolean needLOS);
CCALL qboolean RemoveOldestAlert(void);
CCALL qboolean RemoveOldestAlert(void);
CCALL qboolean NPC_CheckForDanger(int alertEvent);
CCALL qboolean G_CheckForDanger(gentity_t *self,int alertEvent);
CCALL int NPC_CheckAlertEvents(qboolean checkSight,qboolean checkSound,int ignoreAlert,qboolean mustHaveOwner,int minAlertLevel);
CCALL int G_CheckAlertEvents(gentity_t *self,qboolean checkSight,qboolean checkSound,float maxSeeDist,float maxHearDist,int ignoreAlert,qboolean mustHaveOwner,int minAlertLevel);
CCALL float G_GetLightLevel(vec3_t pos,vec3_t fromDir);
CCALL qboolean G_ClearLOS5(gentity_t *self,const vec3_t end);
CCALL visibility_t NPC_CheckVisibility(gentity_t *ent,int flags);
CCALL qboolean InVisrange(gentity_t *ent);
CCALL qboolean InFOV(gentity_t *ent,gentity_t *from,int hFOV,int vFOV);
CCALL qboolean InFOV2(vec3_t origin,gentity_t *from,int hFOV,int vFOV);
CCALL qboolean InFOV3(vec3_t spot,vec3_t from,vec3_t fromAngles,int hFOV,int vFOV);
CCALL qboolean InFront(vec3_t spot,vec3_t from,vec3_t fromAngles,float threshHold);
CCALL qboolean CanSee(gentity_t *ent);
CCALL qboolean G_ClearLineOfSight(const vec3_t point1,const vec3_t point2,int ignore,int clipmask);

