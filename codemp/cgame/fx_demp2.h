#pragma once

#include "cg_local.h"

CCALL void FX_DEMP2_AltDetonate(vec3_t org,float size);
CCALL void FX_DEMP2_AltBeam(vec3_t start,vec3_t end,vec3_t normal,vec3_t targ1,vec3_t targ2);
CCALL void FX_DEMP2_HitPlayer(vec3_t origin,vec3_t normal,qboolean humanoid);
CCALL void FX_DEMP2_HitWall(vec3_t origin,vec3_t normal);
CCALL void FX_DEMP2_ProjectileThink(centity_t *cent,const struct weaponInfo_s *weapon);
