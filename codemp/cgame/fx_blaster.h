#pragma once

#include "cg_local.h"

CCALL void FX_BlasterWeaponHitPlayer(vec3_t origin,vec3_t normal,qboolean humanoid);
CCALL void FX_BlasterWeaponHitWall(vec3_t origin,vec3_t normal);
CCALL void FX_BlasterAltFireThink(centity_t *cent,const struct weaponInfo_s *weapon);
CCALL void FX_BlasterProjectileThink(centity_t *cent,const struct weaponInfo_s *weapon);
