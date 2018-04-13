#pragma once

#include "cg_local.h"
#include "fx_local.h"
#include "../client/client.h"
#include "../client/FxPrimitives.h"

CCALL void FX_DisruptorHitPlayer(vec3_t origin,vec3_t normal,qboolean humanoid);
CCALL void FX_DisruptorHitWall(vec3_t origin,vec3_t normal);
CCALL void FX_DisruptorAltHit(vec3_t origin,vec3_t normal);
CCALL void FX_DisruptorAltMiss(vec3_t origin,vec3_t normal);
CCALL void FX_DisruptorAltShot(vec3_t start,vec3_t end,qboolean fullCharge);
CCALL void FX_DisruptorMainShot(vec3_t start,vec3_t end);
