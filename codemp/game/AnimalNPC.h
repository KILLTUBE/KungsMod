#pragma once

#include "g_local.h"
#include "bg_public.h"
#include "bg_vehicles.h"
#include "../game/bg_misc.h"

EXTERNC vec3_t playerMaxs;
EXTERNC vec3_t playerMins;

CCALL void G_CreateAnimalNPC(Vehicle_t **pVeh,const char *strAnimalType);
CCALL void G_AllocateVehicleObject(Vehicle_t **pVeh);
CCALL void G_SetAnimalVehicleFunctions(vehicleInfo_t *pVehInfo);
CCALL void AttachRidersGeneric(Vehicle_t *pVeh);
CCALL void AnimalProcessOri(Vehicle_t *pVeh);
CCALL void G_VehicleTrace(trace_t *results,const vec3_t start,const vec3_t tMins,const vec3_t tMaxs,const vec3_t end,int passEntityNum,int contentmask);
CCALL void G_Knockdown(gentity_t *self,gentity_t *attacker,const vec3_t pushDir,float strength,qboolean breakSaberLock);
CCALL void Vehicle_SetAnim(gentity_t *ent,int setAnimParts,int anim,int setAnimFlags,int iBlend);
CCALL int PM_AnimLength(int index,animNumber_t anim);
CCALL float DotToSpot(vec3_t spot,vec3_t from,vec3_t fromAngles);
