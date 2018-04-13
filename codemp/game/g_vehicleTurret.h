#pragma once

#include "bg_vehicles.h"
#include "b_local.h"
#include "ghoul2/G2.h"

CCALL void VEH_TurretThink(Vehicle_t *pVeh,gentity_t *parent,int turretNum);
CCALL void VEH_TurretObeyPassengerControl(Vehicle_t *pVeh,gentity_t *parent,int turretNum);
CCALL qboolean VEH_TurretAim(Vehicle_t *pVeh,gentity_t *parent,gentity_t *turretEnemy,turretStats_t *turretStats,vehWeaponInfo_t *vehWeapon,int turretNum,int curMuzzle,vec3_t desiredAngles);
CCALL void VEH_TurretAnglesToEnemy(Vehicle_t *pVeh,int curMuzzle,float fSpeed,gentity_t *turretEnemy,qboolean bAILead,vec3_t desiredAngles);
CCALL void VEH_TurretCheckFire(Vehicle_t *pVeh,gentity_t *parent,turretStats_t *turretStats,vehWeaponInfo_t *vehWeapon,int turretNum,int curMuzzle);
CCALL void G_VehMuzzleFireFX(gentity_t *ent,gentity_t *broadcaster,int muzzlesFired);
CCALL gentity_t *WP_FireVehicleWeapon(gentity_t *ent,vec3_t start,vec3_t dir,vehWeaponInfo_t *vehWeapon,qboolean alt_fire,qboolean isTurretWeap);
CCALL void WP_CalcVehMuzzle(gentity_t *ent,int muzzleNum);
CCALL void G_SetEnemy(gentity_t *self,gentity_t *enemy);
