#include "cg_local.h"
#include "qcommon/q_shared.h"
#include "ghoul2/G2.h"
#include "../game/bg_g2_utils.h"

EXTERNC int CG_BMS_END;
EXTERNC int CG_BMS_MID;
EXTERNC int CG_BMS_START;
EXTERNC char *forceHolocronModels[];
EXTERNC int cgSiegeEntityRender;

CCALL void CG_Cube(vec3_t mins,vec3_t maxs,vec3_t color,float alpha);
CCALL void CG_ROFF_NotetrackCallback(centity_t *cent,const char *notetrack);
CCALL void CG_AddPacketEntities(qboolean isPortal);
CCALL void CG_ManualEntityRender(centity_t *cent);
CCALL void CG_G2Animated(centity_t *cent);
CCALL void CG_CalcEntityLerpPositions(centity_t *cent);
CCALL void CG_AdjustPositionForMover(const vec3_t in,int moverNum,int fromTime,int toTime,vec3_t out);
CCALL void CG_Beam(centity_t *cent);
CCALL void CG_PlayDoorSound(centity_t *cent,int type);
CCALL void CG_PlayDoorLoopSound(centity_t *cent);
CCALL void CG_CreateDistortionTrailPart(centity_t *cent,float scale,vec3_t pos);
CCALL qboolean CG_GreyItem(int type,int tag,int plSide);
CCALL void CG_G2ServerBoneAngles(centity_t *cent);
CCALL void CG_AddBracketedEnt(centity_t *cent);
CCALL void CG_AddRadarEnt(centity_t *cent);
CCALL void CG_Disintegration(centity_t *cent,refEntity_t *ent);
CCALL void ScaleModelAxis(refEntity_t *ent);
CCALL void G2_BoltToGhoul2Model(centity_t *cent,refEntity_t *ent);
CCALL void CG_CreateBBRefEnts(entityState_t *s1,vec3_t origin);
CCALL void CG_SetGhoul2Info(refEntity_t *ent,centity_t *cent);
CCALL void CG_Special(centity_t *cent);
CCALL void FX_DrawPortableShield(centity_t *cent);
CCALL localEntity_t *FX_AddOrientedLine(vec3_t start,vec3_t end,vec3_t normal,float stScale,float scale,float dscale,float startalpha,float endalpha,float killTime,qhandle_t shader);
CCALL void CG_S_UpdateLoopingSounds(int entityNum);
CCALL void CG_S_StopLoopingSound(int entityNum,sfxHandle_t sfx);
CCALL void CG_S_AddRealLoopingSound(int entityNum,const vec3_t origin,const vec3_t velocity,sfxHandle_t sfx);
CCALL void CG_S_AddLoopingSound(int entityNum,const vec3_t origin,const vec3_t velocity,sfxHandle_t sfx);
CCALL void CG_SetEntitySoundPosition(centity_t *cent);
CCALL void CG_PositionRotatedEntityOnTag(refEntity_t *entity,const refEntity_t *parent,qhandle_t parentModel,char *tagName);
CCALL void CG_PositionEntityOnTag(refEntity_t *entity,const refEntity_t *parent,qhandle_t parentModel,char *tagName);
CCALL qboolean CG_InFighter(void);
