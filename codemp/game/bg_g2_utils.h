#pragma once

#include "qcommon/q_shared.h"
#include "bg_public.h"

#define	MAX_VARIANTS 8

CCALL void BG_AttachToRancor( void *ghoul2, float rancYaw, vec3_t rancOrigin, int time, qhandle_t *modelList, vec3_t modelScale, qboolean inMouth, vec3_t out_origin, vec3_t out_angles, matrix3_t out_axis );
CCALL qboolean BG_GetRootSurfNameWithVariant( void *ghoul2, const char *rootSurfName, char *returnSurfName, int returnSize );