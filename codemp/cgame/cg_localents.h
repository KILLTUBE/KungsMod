/* This file was automatically generated.  Do not edit! */
void CG_AddLocalEntities(void);
void CG_AddLine(localEntity_t *le);
void CG_AddOLine(localEntity_t *le);
void CG_AddScorePlum(localEntity_t *le);
void CG_AddRefEntity(localEntity_t *le);
void CG_AddFadeRGB(localEntity_t *le);
void CG_AddFragment(localEntity_t *le);
void CG_ReflectVelocity(localEntity_t *le,trace_t *trace);
void CG_FragmentBounceSound(localEntity_t *le,trace_t *trace);
void CG_FragmentBounceMark(localEntity_t *le,trace_t *trace);
void CG_BloodTrail(localEntity_t *le);
localEntity_t *CG_AllocLocalEntity(void);
void CG_FreeLocalEntity(localEntity_t *le);
void CG_InitLocalEntities(void);
extern localEntity_t *cg_freeLocalEntities;
extern localEntity_t cg_activeLocalEntities;
extern localEntity_t cg_localEntities[MAX_LOCAL_ENTITIES];
