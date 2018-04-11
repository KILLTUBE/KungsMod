#pragma once

#include "cg_local.h"

#define	MAX_MARK_FRAGMENTS	128
#define	MAX_MARK_POINTS		384
#define	MARK_TOTAL_TIME		10000
#define	MARK_FADE_TIME		1000

EXTERNC markPoly_t cg_markPolys[MAX_MARK_POLYS];
EXTERNC markPoly_t *cg_freeMarkPolys;
EXTERNC markPoly_t cg_activeMarkPolys;

CCALL void CG_AddMarks(void);
CCALL void CG_ImpactMark(qhandle_t markShader,const vec3_t origin,const vec3_t dir,float orientation,float red,float green,float blue,float alpha,qboolean alphaFade,float radius,qboolean temporary);
CCALL markPoly_t *CG_AllocMark(void);
CCALL void CG_FreeMarkPoly(markPoly_t *le);
CCALL void CG_InitMarkPolys(void);
