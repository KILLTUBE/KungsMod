#pragma once

#include "cg_local.h"

CCALL void FX_RepeaterAltHitPlayer(vec3_t origin,vec3_t normal,qboolean humanoid);
CCALL void FX_RepeaterAltHitWall(vec3_t origin,vec3_t normal);
CCALL void FX_RepeaterAltProjectileThink(centity_t *cent,const struct weaponInfo_s *weapon);
CCALL void FX_RepeaterHitPlayer(vec3_t origin,vec3_t normal,qboolean humanoid);
CCALL void FX_RepeaterHitWall(vec3_t origin,vec3_t normal);
CCALL void FX_RepeaterProjectileThink(centity_t *cent,const struct weaponInfo_s *weapon);
