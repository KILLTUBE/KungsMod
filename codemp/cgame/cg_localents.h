#pragma once

#include "cg_local.h"

#define	MAX_LOCAL_ENTITIES	2048 // 512

EXTERNC localEntity_t *cg_freeLocalEntities;
EXTERNC localEntity_t cg_activeLocalEntities;
EXTERNC localEntity_t cg_localEntities[MAX_LOCAL_ENTITIES];

CCALL void CG_AddLocalEntities(void);
CCALL void CG_AddLine(localEntity_t *le);
CCALL void CG_AddOLine(localEntity_t *le);
CCALL void CG_AddScorePlum(localEntity_t *le);
CCALL void CG_AddRefEntity(localEntity_t *le);
CCALL void CG_AddFadeRGB(localEntity_t *le);
CCALL void CG_AddFragment(localEntity_t *le);
CCALL void CG_ReflectVelocity(localEntity_t *le,trace_t *trace);
CCALL void CG_FragmentBounceSound(localEntity_t *le,trace_t *trace);
CCALL void CG_FragmentBounceMark(localEntity_t *le,trace_t *trace);
CCALL void CG_BloodTrail(localEntity_t *le);
CCALL localEntity_t *CG_AllocLocalEntity(void);
CCALL void CG_FreeLocalEntity(localEntity_t *le);
CCALL void CG_InitLocalEntities(void);
