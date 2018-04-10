/* This file was automatically generated.  Do not edit! */
void CG_AddMarks(void);
void CG_ImpactMark(qhandle_t markShader,const vec3_t origin,const vec3_t dir,float orientation,float red,float green,float blue,float alpha,qboolean alphaFade,float radius,qboolean temporary);
markPoly_t *CG_AllocMark(void);
void CG_FreeMarkPoly(markPoly_t *le);
void CG_InitMarkPolys(void);
extern markPoly_t cg_markPolys[MAX_MARK_POLYS];
extern markPoly_t *cg_freeMarkPolys;
extern markPoly_t cg_activeMarkPolys;
