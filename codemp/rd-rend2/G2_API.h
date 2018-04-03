#ifndef G2_API_H
#define G2_API_H

#include "../qcommon/qcommon.h"
#include "../ghoul2/g2_local.h"

extern qboolean gG2_GBMUseSPMethod;
extern qboolean gG2_GBMNoReconstruct;

/* This file was automatically generated.  Do not edit! */
const char *G2API_GetModelName(CGhoul2Info_v&ghoul2,int modelIndex);
qboolean G2API_IsGhoul2InfovValid(CGhoul2Info_v&ghoul2);
#if defined(G2_PERFORMANCE_ANALYSIS)
extern int G2Time_G2_SetupModelPointers;
extern timing_c G2PerformanceTimer_G2_SetupModelPointers;
#endif
#if defined(_G2_GORE)
void G2API_AddSkinGore(CGhoul2Info_v&ghoul2,SSkinGoreData&gore);
extern IHeapAllocator *G2VertSpaceServer;
int G2_DecideTraceLod(CGhoul2Info&ghoul2,int useLod);
int G2API_Ghoul2Size(CGhoul2Info_v&ghoul2);
int G2API_GetNumGoreMarks(CGhoul2Info_v&ghoul2,int modelIndex);
void ResetGoreTag();
#endif
qboolean G2API_SkinlessModel(CGhoul2Info_v&ghoul2,int modelIndex);
void G2API_LoadSaveCodeDestructGhoul2Info(CGhoul2Info_v&ghoul2);
void G2API_FreeSaveBuffer(char *buffer);
void G2API_LoadGhoul2Models(CGhoul2Info_v&ghoul2,char *buffer);
qboolean G2API_SaveGhoul2Models(CGhoul2Info_v&ghoul2,char **buffer,int *size);
int G2API_GetBoneIndex(CGhoul2Info *ghlInfo,const char *boneName);
qboolean G2API_SetNewOrigin(CGhoul2Info_v&ghoul2,const int boltIndex);
char *G2API_GetGLAName(CGhoul2Info_v&ghoul2,int modelIndex);
int G2API_GetSurfaceIndex(CGhoul2Info *ghlInfo,const char *surfaceName);
char *G2API_GetSurfaceName(CGhoul2Info_v&ghoul2,int modelIndex,int surfNumber);
void G2API_DuplicateGhoul2Instance(CGhoul2Info_v&g2From,CGhoul2Info_v **g2To);
void G2API_CopySpecificG2Model(CGhoul2Info_v&ghoul2From,int modelFrom,CGhoul2Info_v&ghoul2To,int modelTo);
int G2API_CopyGhoul2Instance(CGhoul2Info_v&g2From,CGhoul2Info_v&g2To,int modelIndex);
void G2API_GiveMeVectorFromMatrix(mdxaBone_t *boltMatrix,Eorientations flags,vec3_t vec);
int G2API_GetGhoul2ModelFlags(CGhoul2Info *ghlInfo);
qboolean G2API_SetGhoul2ModelFlags(CGhoul2Info *ghlInfo,const int flags);
void G2API_CollisionDetect(CollisionRecord_t *collRecMap,CGhoul2Info_v&ghoul2,const vec3_t angles,const vec3_t position,int frameNumber,int entNum,vec3_t rayStart,vec3_t rayEnd,vec3_t scale,IHeapAllocator *G2VertSpace,int traceFlags,int useLod,float fRadius);
void G2API_CollisionDetectCache(CollisionRecord_t *collRecMap,CGhoul2Info_v&ghoul2,const vec3_t angles,const vec3_t position,int frameNumber,int entNum,vec3_t rayStart,vec3_t rayEnd,vec3_t scale,IHeapAllocator *G2VertSpace,int traceFlags,int useLod,float fRadius);
qboolean G2API_GetAnimFileName(CGhoul2Info *ghlInfo,char **filename);
char *G2API_GetAnimFileNameIndex(qhandle_t modelIndex);
void G2API_SetGhoul2ModelIndexes(CGhoul2Info_v&ghoul2,qhandle_t *modelList,qhandle_t *skinList);
qboolean G2API_HaveWeGhoul2Models(CGhoul2Info_v&ghoul2);
void G2API_ListBones(CGhoul2Info *ghlInfo,int frame);
void G2API_ListSurfaces(CGhoul2Info *ghlInfo);
qboolean G2API_GetBoltMatrix(CGhoul2Info_v&ghoul2,const int modelIndex,const int boltIndex,mdxaBone_t *matrix,const vec3_t angles,const vec3_t position,const int frameNum,qhandle_t *modelList,vec3_t scale);
void G2_GetBoneMatrixLow(CGhoul2Info&ghoul2,int boneNum,const vec3_t scale,mdxaBone_t&retMatrix,mdxaBone_t *&retBasepose,mdxaBone_t *&retBaseposeInv);
void G2_GetBoltMatrixLow(CGhoul2Info&ghoul2,int boltNum,const vec3_t scale,mdxaBone_t&retMatrix);
bool G2_NeedsRecalc(CGhoul2Info *ghlInfo,int frameNum);
qboolean G2API_GetBoltMatrix_SPMethod(CGhoul2Info_v&ghoul2,const int modelIndex,const int boltIndex,mdxaBone_t *matrix,const vec3_t angles,const vec3_t position,const int frameNum,qhandle_t *modelList,const vec3_t scale);
qboolean G2API_AttachEnt(int *boltInfo,CGhoul2Info_v&ghoul2,int modelIndex,int toBoltIndex,int entNum,int toModelNum);
qboolean G2API_DetachG2Model(CGhoul2Info *ghlInfo);
void G2API_SetBoltInfo(CGhoul2Info_v&ghoul2,int modelIndex,int boltInfo);
qboolean G2API_AttachG2Model(CGhoul2Info_v&ghoul2From,int modelFrom,CGhoul2Info_v&ghoul2To,int toBoltIndex,int toModel);
int G2API_AddBoltSurfNum(CGhoul2Info *ghlInfo,const int surfIndex);
int G2API_AddBolt(CGhoul2Info_v&ghoul2,const int modelIndex,const char *boneName);
qboolean G2API_RemoveBolt(CGhoul2Info *ghlInfo,const int index);
qboolean G2API_IKMove(CGhoul2Info_v&ghoul2,int time,sharedIKMoveParams_t *params);
qboolean G2_IKMove(CGhoul2Info_v&ghoul2,int time,sharedIKMoveParams_t *params);
qboolean G2API_SetBoneIKState(CGhoul2Info_v&ghoul2,int time,const char *boneName,int ikState,sharedSetBoneIKStateParams_t *params);
qboolean G2_SetBoneIKState(CGhoul2Info_v&ghoul2,int time,const char *boneName,int ikState,sharedSetBoneIKStateParams_t *params);
qboolean G2API_RagForceSolve(CGhoul2Info_v&ghoul2,qboolean force);
qboolean G2API_RagEffectorKick(CGhoul2Info_v&ghoul2,const char *boneName,vec3_t velocity);
qboolean G2API_GetRagBonePos(CGhoul2Info_v&ghoul2,const char *boneName,vec3_t pos,vec3_t entAngles,vec3_t entPos,vec3_t entScale);
qboolean G2API_RagEffectorGoal(CGhoul2Info_v&ghoul2,const char *boneName,vec3_t pos);
qboolean G2API_RagPCJGradientSpeed(CGhoul2Info_v&ghoul2,const char *boneName,const float speed);
qboolean G2API_RagPCJConstraint(CGhoul2Info_v&ghoul2,const char *boneName,vec3_t min,vec3_t max);
int G2_Find_Bone_Rag(CGhoul2Info *ghlInfo,boneInfo_v&blist,const char *boneName);
void G2API_AnimateG2ModelsRag(CGhoul2Info_v&ghoul2,int AcurrentTime,CRagDollUpdateParams *params);
#if defined(_DEBUG)
extern int ragTraceCount;
extern int ragSSCount;
extern int ragTraceTime;
#endif
qboolean G2API_RemoveBone(CGhoul2Info_v&ghoul2,int modelIndex,const char *boneName);
void G2API_ResetRagDoll(CGhoul2Info_v&ghoul2);
void G2_ResetRagDoll(CGhoul2Info_v&ghoul2V);
void G2API_SetRagDoll(CGhoul2Info_v&ghoul2,CRagDollParams *parms);
void G2_SetRagDoll(CGhoul2Info_v&ghoul2V,CRagDollParams *parms);
void G2API_AbsurdSmoothing(CGhoul2Info_v&ghoul2,qboolean status);
qboolean G2API_StopBoneAngles(CGhoul2Info *ghlInfo,const char *boneName);
qboolean G2API_StopBoneAnglesIndex(CGhoul2Info *ghlInfo,const int index);
qboolean G2API_SetBoneAnglesMatrix(CGhoul2Info *ghlInfo,const char *boneName,const mdxaBone_t&matrix,const int flags,qhandle_t *modelList,int blendTime,int currentTime);
qboolean G2API_SetBoneAnglesMatrixIndex(CGhoul2Info *ghlInfo,const int index,const mdxaBone_t&matrix,const int flags,qhandle_t *modelList,int blendTime,int currentTime);
qboolean G2API_SetBoneAngles(CGhoul2Info_v&ghoul2,const int modelIndex,const char *boneName,const vec3_t angles,const int flags,const Eorientations up,const Eorientations left,const Eorientations forward,qhandle_t *modelList,int blendTime,int currentTime);
qboolean G2API_SetBoneAnglesIndex(CGhoul2Info *ghlInfo,const int index,const vec3_t angles,const int flags,const Eorientations yaw,const Eorientations pitch,const Eorientations roll,qhandle_t *modelList,int blendTime,int currentTime);
qboolean G2API_StopBoneAnim(CGhoul2Info *ghlInfo,const char *boneName);
qboolean G2API_StopBoneAnimIndex(CGhoul2Info *ghlInfo,const int index);
qboolean G2API_IsPaused(CGhoul2Info *ghlInfo,const char *boneName);
qboolean G2API_PauseBoneAnim(CGhoul2Info *ghlInfo,const char *boneName,const int currentTime);
qboolean G2API_GetAnimRange(CGhoul2Info *ghlInfo,const char *boneName,int *startFrame,int *endFrame);
qboolean G2API_GetBoneAnim(CGhoul2Info_v&ghoul2,int modelIndex,const char *boneName,const int currentTime,float *currentFrame,int *startFrame,int *endFrame,int *flags,float *animSpeed,int *modelList);
qboolean G2API_SetBoneAnim(CGhoul2Info_v&ghoul2,const int modelIndex,const char *boneName,const int AstartFrame,const int AendFrame,const int flags,const float animSpeed,const int currentTime,const float AsetFrame,const int blendTime);
qboolean G2API_SetBoneAnimIndex(CGhoul2Info *ghlInfo,const int index,const int AstartFrame,const int AendFrame,const int flags,const float animSpeed,const int currentTime,const float AsetFrame,const int blendTime);
qboolean G2API_DoesBoneExist(CGhoul2Info_v&ghoul2,int modelIndex,const char *boneName);
qboolean G2API_RemoveGhoul2Models(CGhoul2Info_v **ghlRemove);
qboolean G2API_RemoveGhoul2Model(CGhoul2Info_v **ghlRemove,const int modelIndex);
qboolean G2API_HasGhoul2ModelOnIndex(CGhoul2Info_v **ghlRemove,const int modelIndex);
int G2API_GetSurfaceRenderStatus(CGhoul2Info_v&ghoul2,int modelIndex,const char *surfaceName);
int G2API_GetParentSurface(CGhoul2Info *ghlInfo,const int index);
qboolean G2API_RemoveSurface(CGhoul2Info *ghlInfo,const int index);
int G2API_AddSurface(CGhoul2Info *ghlInfo,int surfaceNumber,int polyNumber,float BarycentricI,float BarycentricJ,int lod);
qboolean G2API_SetRootSurface(CGhoul2Info_v&ghoul2,const int modelIndex,const char *surfaceName);
int G2API_GetSurfaceOnOff(CGhoul2Info *ghlInfo,const char *surfaceName);
qboolean G2API_SetSurfaceOnOff(CGhoul2Info_v&ghoul2,const char *surfaceName,const int flags);
qboolean G2API_SetShader(CGhoul2Info *ghlInfo,qhandle_t customShader);
qboolean G2API_SetSkin(CGhoul2Info_v&ghoul2,int modelIndex,qhandle_t customSkin,qhandle_t renderSkin);
void G2_SetSurfaceOnOffFromSkin(CGhoul2Info *ghlInfo,qhandle_t renderSkin);
qboolean G2API_SetLodBias(CGhoul2Info *ghlInfo,int lodBias);
int G2API_InitGhoul2Model(CGhoul2Info_v **ghoul2Ptr,const char *fileName,int modelIndex,qhandle_t customSkin,qhandle_t customShader,int modelFlags,int lodBias);
void CL_InitRef(void);
qhandle_t G2API_PrecacheGhoul2Model(const char *fileName);
qboolean G2_ShouldRegisterServer(void);
#if defined(_G2_GORE)
void G2API_ClearSkinGore(CGhoul2Info_v&ghoul2);
#endif
void G2API_CleanGhoul2Models(CGhoul2Info_v **ghoul2Ptr);
void Ghoul2InfoArray_Free(void);
void SaveGhoul2InfoArray();
void RestoreGhoul2InfoArray();
IGhoul2InfoArray&TheGhoul2InfoArray();
qboolean G2API_OverrideServerWithClientData(CGhoul2Info_v&ghoul2,int modelIndex);
#if defined(_G2_LISTEN_SERVER_OPT)
void CopyBoneCache(CBoneCache *to,CBoneCache *from);
#endif
void G2API_CleanEntAttachments(void);
void G2API_ClearAttachedInstance(int entityNum);
void G2API_AttachInstanceToEntNum(CGhoul2Info_v&ghoul2,int entityNum,qboolean server);
#if defined(_G2_LISTEN_SERVER_OPT)
extern CGhoul2Info_v *g2ClientAttachments[MAX_GENTITIES];
#endif
int G2API_GetTime(int argTime);
void G2API_SetTime(int currentTime,int clock);
qboolean G2_TestModelPointers(CGhoul2Info *ghlInfo);
qboolean G2_TestModelPointers(CGhoul2Info *ghlInfo);
qboolean G2_SetupModelPointers(CGhoul2Info *ghlInfo);
qboolean G2_SetupModelPointers(CGhoul2Info_v&ghoul2);
qboolean G2_SetupModelPointers(CGhoul2Info *ghlInfo);
qboolean G2_SetupModelPointers(CGhoul2Info_v&ghoul2);
#if defined(_FULL_G2_LEAK_CHECKING)
void G2_DEBUG_RemovePtrFromTracker(CGhoul2Info_v *g2);
void G2_DEBUG_ShovePtrInTracker(CGhoul2Info_v *g2);
void G2_DEBUG_ReportLeaks(void);
void G2_DEBUG_InitPtrTracker(void);
extern int g_G2AllocServer;
extern int g_G2ClientAlloc;
extern int g_G2ServerAlloc;
extern int g_Ghoul2Allocations;
#endif
void G2API_BoltMatrixReconstruction( qboolean reconstruct );
void G2API_BoltMatrixSPMethod( qboolean spMethod );

#endif