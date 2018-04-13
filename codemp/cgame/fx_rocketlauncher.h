#pragma once

#include "cg_local.h"

CCALL void FX_RocketAltProjectileThink(centity_t *cent,const struct weaponInfo_s *weapon);
CCALL void FX_RocketHitPlayer(vec3_t origin,vec3_t normal,qboolean humanoid);
CCALL void FX_RocketHitWall(vec3_t origin,vec3_t normal);
CCALL void FX_RocketProjectileThink(centity_t *cent,const struct weaponInfo_s *weapon);
