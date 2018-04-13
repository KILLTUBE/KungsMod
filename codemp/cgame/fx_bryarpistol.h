#pragma once

#include "cg_local.h"
#include "fx_local.h"

CCALL void FX_ConcAltShot(vec3_t start,vec3_t end);
CCALL void FX_ConcussionProjectileThink(centity_t *cent,const struct weaponInfo_s *weapon);
CCALL void FX_ConcussionHitPlayer(vec3_t origin,vec3_t normal,qboolean humanoid);
CCALL void FX_ConcussionHitWall(vec3_t origin,vec3_t normal);
CCALL void FX_TurretHitPlayer(vec3_t origin,vec3_t normal,qboolean humanoid);
CCALL void FX_TurretHitWall(vec3_t origin,vec3_t normal);
CCALL void FX_TurretProjectileThink(centity_t *cent,const struct weaponInfo_s *weapon);
CCALL void FX_BryarAltHitPlayer(vec3_t origin,vec3_t normal,qboolean humanoid);
CCALL void FX_BryarAltHitWall(vec3_t origin,vec3_t normal,int power);
CCALL void FX_BryarAltProjectileThink(centity_t *cent,const struct weaponInfo_s *weapon);
CCALL void FX_BryarHitPlayer(vec3_t origin,vec3_t normal,qboolean humanoid);
CCALL void FX_BryarHitWall(vec3_t origin,vec3_t normal);
CCALL void FX_BryarProjectileThink(centity_t *cent,const struct weaponInfo_s *weapon);
