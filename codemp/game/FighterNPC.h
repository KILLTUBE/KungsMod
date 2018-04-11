#pragma once

#include "bg_public.h"
#include "bg_vehicles.h"
#include "g_local.h"
#include "cgame/cg_local.h"


#define FIGHTER_MIN_TAKEOFF_FRACTION 0.7f

EXTERNC vec3_t playerMaxs;
EXTERNC vec3_t playerMins;

CCALL void G_CreateFighterNPC(Vehicle_t **pVeh,const char *strType);
CCALL void G_AllocateVehicleObject(Vehicle_t **pVeh);
CCALL void G_SetFighterVehicleFunctions(vehicleInfo_t *pVehInfo);
CCALL void AttachRidersGeneric(Vehicle_t *pVeh);
CCALL void FighterPitchClamp(Vehicle_t *pVeh,playerState_t *riderPS,playerState_t *parentPS,int curTime);
#if defined(VEH_CONTROL_SCHEME_4)
CCALL void FighterPitchAdjust(Vehicle_t *pVeh,playerState_t *riderPS,playerState_t *parentPS);
#endif
#if !(defined(VEH_CONTROL_SCHEME_4))
CCALL void FighterPitchAdjust(Vehicle_t *pVeh,playerState_t *riderPS,playerState_t *parentPS);
#endif
#if defined(VEH_CONTROL_SCHEME_4)
CCALL void FighterYawAdjust(Vehicle_t *pVeh,playerState_t *riderPS,playerState_t *parentPS);
#endif
#if !(defined(VEH_CONTROL_SCHEME_4))
CCALL void FighterYawAdjust(Vehicle_t *pVeh,playerState_t *riderPS,playerState_t *parentPS);
#endif
#if defined(VEH_CONTROL_SCHEME_4)
CCALL void FighterRollAdjust(Vehicle_t *pVeh,playerState_t *riderPS,playerState_t *parentPS);
#endif
CCALL void BG_VehicleTurnRateForSpeed(Vehicle_t *pVeh,float speed,float *mPitchOverride,float *mYawOverride);
CCALL qboolean FighterSuspended(Vehicle_t *pVeh,playerState_t *parentPS);
CCALL qboolean FighterIsLaunching(Vehicle_t *pVeh,playerState_t *parentPS);
CCALL qboolean FighterIsLanding(Vehicle_t *pVeh,playerState_t *parentPS);
CCALL qboolean FighterIsLanded(Vehicle_t *pVeh,playerState_t *parentPS);
CCALL qboolean FighterOverValidLandingSurface(Vehicle_t *pVeh);
CCALL qboolean FighterIsInSpace(gentity_t *gParent);
CCALL qboolean BG_FighterUpdate(Vehicle_t *pVeh,const usercmd_t *pUcmd,vec3_t trMins,vec3_t trMaxs,float gravity,void(*traceFunc)(trace_t *results,const vec3_t start,const vec3_t lmins,const vec3_t lmaxs,const vec3_t end,int passEntityNum,int contentMask));
CCALL int BG_GetTime(void);
CCALL void BG_SetAnim(playerState_t *ps,animation_t *animations,int setAnimParts,int anim,int setAnimFlags);
CCALL qboolean BG_UnrestrainedPitchRoll(playerState_t *ps,Vehicle_t *pVeh);
CCALL void G_VehicleTrace(trace_t *results,const vec3_t start,const vec3_t tMins,const vec3_t tMaxs,const vec3_t end,int passEntityNum,int contentmask);
CCALL int PM_AnimLength(int index,animNumber_t anim);
CCALL void ChangeWeapon(gentity_t *ent,int newWeapon);
CCALL float DotToSpot(vec3_t spot,vec3_t from,vec3_t fromAngles);
