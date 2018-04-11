#pragma once

#include "qcommon/q_shared.h"
#include "g_local.h"
#include "bg_vehicles.h"

//try to break surfaces off the ship on impact
#define TURN_ON				0x00000000
#define TURN_OFF			0x00000100

CCALL void G_SetSharedVehicleFunctions(vehicleInfo_t *pVehInfo);
CCALL qboolean AddPassenger(Vehicle_t *pVeh);
CCALL void _SetParent(Vehicle_t *pVeh,bgEntity_t *pParentEntity);
CCALL void G_FlyVehicleSurfaceDestruction(gentity_t *veh,trace_t *trace,int magnitude,qboolean force);
CCALL qboolean G_FlyVehicleDestroySurface(gentity_t *veh,int surface);
CCALL void G_VehicleSetDamageLocFlags(gentity_t *veh,int impactDir,int deathPoint);
CCALL void G_SetVehDamageFlags(gentity_t *veh,int shipSurf,int damageLevel);
CCALL int G_ShipSurfaceForSurfName(const char *surfaceName);
CCALL void NPC_SetSurfaceOnOff(gentity_t *ent,const char *surfaceName,int surfaceFlags);
CCALL int G_FlyVehicleImpactDir(gentity_t *veh,trace_t *trace);
CCALL void AttachRidersGeneric(Vehicle_t *pVeh);
CCALL void G_VehicleDamageBoxSizing(Vehicle_t *pVeh);
CCALL void G_VehicleDamageBoxSizing(Vehicle_t *pVeh);
CCALL qboolean Initialize(Vehicle_t *pVeh);
CCALL void ChangeWeapon(gentity_t *ent,int newWeapon);
CCALL void RegisterAssets(Vehicle_t *pVeh);
CCALL qboolean Inhabited(Vehicle_t *pVeh);
CCALL qboolean EjectAll(Vehicle_t *pVeh);
CCALL qboolean Eject(Vehicle_t *pVeh,bgEntity_t *pEnt,qboolean forceEject);
CCALL void G_EjectDroidUnit(Vehicle_t *pVeh,qboolean kill);
CCALL qboolean VEH_TryEject(Vehicle_t *pVeh,gentity_t *parent,gentity_t *ent,int ejectDir,vec3_t vExitPos);
CCALL void SetPilot(Vehicle_t *pVeh,bgEntity_t *pPilot);
CCALL qboolean Board(Vehicle_t *pVeh,bgEntity_t *pEnt);
#if defined(VEH_CONTROL_SCHEME_4)
CCALL void FighterStorePilotViewAngles(Vehicle_t *pVeh,bgEntity_t *parent);
#endif
CCALL qboolean ValidateBoard(Vehicle_t *pVeh,bgEntity_t *pEnt);
CCALL void Animate(Vehicle_t *pVeh);
CCALL void G_AttachToVehicle(gentity_t *pEnt,usercmd_t **ucmd);
CCALL void G_VehicleSpawn(gentity_t *self);
CCALL float G_CanJumpToEnemyVeh(Vehicle_t *pVeh,const usercmd_t *pUcmd);
CCALL Vehicle_t *G_IsRidingVehicle(gentity_t *pEnt);
CCALL void G_VehicleTrace(trace_t *results,const vec3_t start,const vec3_t tMins,const vec3_t tMaxs,const vec3_t end,int passEntityNum,int contentmask);
CCALL void Vehicle_SetAnim(gentity_t *ent,int setAnimParts,int anim,int setAnimFlags,int iBlend);
CCALL qboolean BG_UnrestrainedPitchRoll(playerState_t *ps,Vehicle_t *pVeh);
CCALL void VEH_TurretThink(Vehicle_t *pVeh,gentity_t *parent,int turretNum);
CCALL void G_VehUpdateShields(gentity_t *targ);
CCALL void G_VehUpdateShields(gentity_t *targ);
CCALL void BG_SetTorsoAnimTimer(playerState_t *ps,int time);
CCALL void BG_SetLegsAnimTimer(playerState_t *ps,int time);
CCALL void BG_SetAnim(playerState_t *ps,animation_t *animations,int setAnimParts,int anim,int setAnimFlags,int blendTime);
CCALL void NPC_SetAnim(gentity_t *ent,int setAnimParts,int anim,int setAnimFlags);
CCALL gentity_t *NPC_Spawn_Do(gentity_t *ent);
