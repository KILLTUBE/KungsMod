void CG_InitMarkPolys();
void CG_FreeMarkPoly( markPoly_t *le );
markPoly_t *CG_AllocMark();
void CG_ImpactMark( qhandle_t markShader, const vec3_t origin, const vec3_t dir, float orientation, float red, float green, float blue, float alpha, qboolean alphaFade, float radius, qboolean temporary );
void CG_AddMarks();
