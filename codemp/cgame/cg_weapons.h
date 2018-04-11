#pragma once

#include "cg_local.h"
#include "fx_local.h"

CCALL void CG_CheckPlayerG2Weapons(playerState_t *ps,centity_t *cent);
CCALL void CG_CopyG2WeaponInstance(centity_t *cent,int weaponNum,void *toGhoul2);
CCALL void *CG_G2WeaponInstance(centity_t *cent,int weapon);
CCALL void CG_ShutDownG2Weapons(void);
CCALL void CG_InitG2Weapons(void);
CCALL qboolean CG_CalcMuzzlePoint(int entityNum,vec3_t muzzle);
CCALL void CG_MissileHitPlayer(int weapon,vec3_t origin,vec3_t dir,int entityNum,qboolean altFire);
CCALL void CG_MissileHitWall(int weapon,int clientNum,vec3_t origin,vec3_t dir,impactSound_t soundType,qboolean altFire,int charge);
CCALL qboolean CG_VehicleWeaponImpact(centity_t *cent);
CCALL void CG_FireWeapon(centity_t *cent,qboolean altFire);
CCALL void CG_GetClientWeaponMuzzleBoltPoint(int clIndex,vec3_t to);
CCALL void CG_OutOfAmmoChange(int oldWeapon);
CCALL void CG_WeaponClean_f(void);
CCALL void CG_Weapon_f(void);
CCALL void CG_PrevWeapon_f(void);
CCALL void CG_NextWeapon_f(void);
CCALL void CG_DrawWeaponSelect(void);
CCALL qboolean CG_WeaponCheck(int weap);
CCALL void CG_DrawIconBackground(void);
CCALL void CG_AddViewWeapon(playerState_t *ps);
CCALL void CG_AddPlayerWeapon(refEntity_t *parent,playerState_t *ps,centity_t *cent,int team,vec3_t newAngles,qboolean thirdPerson);
CCALL void CG_RegisterItemVisuals(int itemNum);
CCALL void CG_SetGhoul2InfoRef(refEntity_t *ent,refEntity_t *s1);
