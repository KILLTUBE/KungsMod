#pragma once

#include "cg_local.h"

CCALL void FX_BowcasterAltProjectileThink(centity_t *cent,const struct weaponInfo_s *weapon);
CCALL void FX_BowcasterHitPlayer(vec3_t origin,vec3_t normal,qboolean humanoid);
CCALL void FX_BowcasterHitWall(vec3_t origin,vec3_t normal);
CCALL void FX_BowcasterProjectileThink(centity_t *cent,const struct weaponInfo_s *weapon);
