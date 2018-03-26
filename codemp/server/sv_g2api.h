#ifndef SV_G2API
#define SV_G2API

CCALL void SV_G2API_GetSurfaceName(void *ghoul2,int surfNumber,int modelIndex,char *fillBuf);
CCALL qboolean SV_G2API_OverrideServer(void *serverInstance);
CCALL void SV_G2API_CleanEntAttachments(void);
CCALL void SV_G2API_ClearAttachedInstance(int entityNum);
CCALL void SV_G2API_AttachInstanceToEntNum(void *ghoul2,int entityNum,qboolean server);
CCALL qboolean SV_G2API_RemoveBone(void *ghoul2,const char *boneName,int modelIndex);
CCALL qboolean SV_G2API_IKMove(void *ghoul2,int time,sharedIKMoveParams_t *params);
CCALL qboolean SV_G2API_SetBoneIKState(void *ghoul2,int time,const char *boneName,int ikState,sharedSetBoneIKStateParams_t *params);
CCALL qboolean SV_G2API_RagForceSolve(void *ghoul2,qboolean force);
CCALL qboolean SV_G2API_RagEffectorKick(void *ghoul2,const char *boneName,vec3_t velocity);
CCALL qboolean SV_G2API_GetRagBonePos(void *ghoul2,const char *boneName,vec3_t pos,vec3_t entAngles,vec3_t entPos,vec3_t entScale);
CCALL qboolean SV_G2API_RagEffectorGoal(void *ghoul2,const char *boneName,vec3_t pos);
CCALL qboolean SV_G2API_RagPCJGradientSpeed(void *ghoul2,const char *boneName,const float speed);
CCALL qboolean SV_G2API_RagPCJConstraint(void *ghoul2,const char *boneName,vec3_t min,vec3_t max);
CCALL void SV_G2API_AnimateG2Models(void *ghoul2,int time,sharedRagDollUpdateParams_t *params);
CCALL void SV_G2API_SetRagDoll(void *ghoul2,sharedRagDollParams_t *params);
CCALL void SV_G2API_AbsurdSmoothing(void *ghoul2,qboolean status);
CCALL int SV_G2API_GetSurfaceRenderStatus(void *ghoul2,const int modelIndex,const char *surfaceName);
CCALL qboolean SV_G2API_DoesBoneExist(void *ghoul2,int modelIndex,const char *boneName);
CCALL qboolean SV_G2API_SetNewOrigin(void *ghoul2,const int boltIndex);
CCALL qboolean SV_G2API_SetSurfaceOnOff(void *ghoul2,const char *surfaceName,const int flags);
CCALL qboolean SV_G2API_SetRootSurface(void *ghoul2,const int modelIndex,const char *surfaceName);
CCALL void SV_G2API_SetBoltInfo(void *ghoul2,int modelIndex,int boltInfo);
CCALL int SV_G2API_AddBolt(void *ghoul2,int modelIndex,const char *boneName);
CCALL int SV_G2API_Ghoul2Size(void *ghlInfo);
CCALL qboolean SV_G2API_RemoveGhoul2Models(void *ghlInfo);
CCALL qboolean SV_G2API_RemoveGhoul2Model(void *ghlInfo,int modelIndex);
CCALL qboolean SV_G2API_HasGhoul2ModelOnIndex(void *ghlInfo,int modelIndex);
CCALL void SV_G2API_DuplicateGhoul2Instance(void *g2From,void **g2To);
CCALL void SV_G2API_CopySpecificGhoul2Model(void *g2From,int modelFrom,void *g2To,int modelTo);
CCALL int SV_G2API_CopyGhoul2Instance(void *g2From,void *g2To,int modelIndex);
CCALL void SV_G2API_GetGLAName(void *ghoul2,int modelIndex,char *fillBuf);
CCALL qboolean SV_G2API_GetBoneAnim(void *ghoul2,const char *boneName,const int currentTime,float *currentFrame,int *startFrame,int *endFrame,int *flags,float *animSpeed,int *modelList,const int modelIndex);
CCALL qboolean SV_G2API_SetBoneAnim(void *ghoul2,const int modelIndex,const char *boneName,const int startFrame,const int endFrame,const int flags,const float animSpeed,const int currentTime,const float setFrame,const int blendTime);
CCALL qboolean SV_G2API_SetBoneAngles(void *ghoul2,int modelIndex,const char *boneName,const vec3_t angles,const int flags,const int up,const int right,const int forward,qhandle_t *modelList,int blendTime,int currentTime);
CCALL void SV_G2API_CleanGhoul2Models(void **ghoul2Ptr);
CCALL void SV_G2API_CollisionDetectCache(CollisionRecord_t *collRecMap,void *ghoul2,const vec3_t angles,const vec3_t position,int frameNumber,int entNum,vec3_t rayStart,vec3_t rayEnd,vec3_t scale,int traceFlags,int useLod,float fRadius);
CCALL void SV_G2API_CollisionDetect(CollisionRecord_t *collRecMap,void *ghoul2,const vec3_t angles,const vec3_t position,int frameNumber,int entNum,vec3_t rayStart,vec3_t rayEnd,vec3_t scale,int traceFlags,int useLod,float fRadius);
CCALL qboolean SV_G2API_SetSkin(void *ghoul2,int modelIndex,qhandle_t customSkin,qhandle_t renderSkin);
CCALL int SV_G2API_InitGhoul2Model(void **ghoul2Ptr,const char *fileName,int modelIndex,qhandle_t customSkin,qhandle_t customShader,int modelFlags,int lodBias);
CCALL qboolean SV_G2API_GetBoltMatrix_NoRecNoRot(void *ghoul2,const int modelIndex,const int boltIndex,mdxaBone_t *matrix,const vec3_t angles,const vec3_t position,const int frameNum,qhandle_t *modelList,vec3_t scale);
CCALL qboolean SV_G2API_GetBoltMatrix_NoReconstruct(void *ghoul2,const int modelIndex,const int boltIndex,mdxaBone_t *matrix,const vec3_t angles,const vec3_t position,const int frameNum,qhandle_t *modelList,vec3_t scale);
CCALL qboolean SV_G2API_GetBoltMatrix(void *ghoul2,const int modelIndex,const int boltIndex,mdxaBone_t *matrix,const vec3_t angles,const vec3_t position,const int frameNum,qhandle_t *modelList,vec3_t scale);
CCALL qboolean SV_G2API_HaveWeGhoul2Models(void *ghoul2);
CCALL void SV_G2API_SetGhoul2ModelIndexes(void *ghoul2,qhandle_t *modelList,qhandle_t *skinList);
CCALL void SV_G2API_ListModelBones(void *ghlInfo,int frame);

#endif