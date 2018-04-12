#pragma once

#include "g_local.h"
#include "bg_public.h"
#include "bg_vehicles.h"

#define	STRAFERAM_DURATION	8
#define	STRAFERAM_ANGLE		8

EXTERNC vec3_t playerMaxs;
EXTERNC vec3_t playerMins;

CCALL void G_CreateSpeederNPC(Vehicle_t **pVeh,const char *strType);
CCALL void G_AllocateVehicleObject(Vehicle_t **pVeh);
CCALL void G_SetSpeederVehicleFunctions(vehicleInfo_t *pVehInfo);
CCALL void AttachRidersGeneric(Vehicle_t *pVeh);
CCALL void AnimateRiders(Vehicle_t *pVeh);
CCALL void AnimateVehicle(Vehicle_t *pVeh);
CCALL void ProcessOrientCommands(Vehicle_t *pVeh);
CCALL void AnimalProcessOri(Vehicle_t *pVeh);
CCALL qboolean Update(Vehicle_t *pVeh,const usercmd_t *pUcmd);
CCALL qboolean VEH_StartStrafeRam(Vehicle_t *pVeh,qboolean Right,int Duration);
CCALL qboolean BG_SabersOff(playerState_t *ps);
CCALL int BG_GetTime(void);
CCALL void BG_SetAnim(playerState_t *ps,animation_t *animations,int setAnimParts,int anim,int setAnimFlags);
CCALL int PM_AnimLength(int index,animNumber_t anim);
CCALL int PM_AnimLength(int index,animNumber_t anim);
CCALL void ChangeWeapon(gentity_t *ent,int newWeapon);
CCALL float DotToSpot(vec3_t spot,vec3_t from,vec3_t fromAngles);
