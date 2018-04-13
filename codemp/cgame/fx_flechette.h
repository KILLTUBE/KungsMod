#pragma once

#include "cg_local.h"

CCALL void FX_FlechetteAltProjectileThink(centity_t *cent,const struct weaponInfo_s *weapon);
CCALL void FX_FlechetteWeaponHitPlayer(vec3_t origin,vec3_t normal,qboolean humanoid);
CCALL void FX_FlechetteWeaponHitWall(vec3_t origin,vec3_t normal);
CCALL void FX_FlechetteProjectileThink(centity_t *cent,const struct weaponInfo_s *weapon);
