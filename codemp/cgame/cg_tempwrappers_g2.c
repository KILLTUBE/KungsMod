
#include <cgame/cg_local.h>




#if 0

CCALL void SV_G2API_ListModelSurfaces( void *ghlInfo ) {
	//re->G2API_ListSurfaces( (CGhoul2Info *)ghlInfo );
}

CCALL void SV_G2API_ListModelBones( void *ghlInfo, int frame ) {
	//re->G2API_ListBones( (CGhoul2Info *)ghlInfo, frame );
}

CCALL void SV_G2API_SetGhoul2ModelIndexes( void *ghoul2, qhandle_t *modelList, qhandle_t *skinList ) {
	//re->G2API_SetGhoul2ModelIndexes( *((CGhoul2Info_v *)ghoul2), modelList, skinList );
}

CCALL qboolean SV_G2API_HaveWeGhoul2Models( void *ghoul2) {
	//return re->G2API_HaveWeGhoul2Models( *((CGhoul2Info_v *)ghoul2) );
	assert(0);
	return qfalse;
}

CCALL qboolean SV_G2API_GetBoltMatrix( void *ghoul2, const int modelIndex, const int boltIndex, mdxaBone_t *matrix, const vec3_t angles, const vec3_t position, const int frameNum, qhandle_t *modelList, vec3_t scale ) {
	return CL_G2API_GetBoltMatrix( ghoul2, modelIndex, boltIndex, matrix, angles, position, frameNum, modelList, scale );
	assert(0);
	return qfalse;
}

CCALL qboolean SV_G2API_GetBoltMatrix_NoReconstruct( void *ghoul2, const int modelIndex, const int boltIndex, mdxaBone_t *matrix, const vec3_t angles, const vec3_t position, const int frameNum, qhandle_t *modelList, vec3_t scale ) {
	//re->G2API_BoltMatrixReconstruction( qfalse );
	//return re->G2API_GetBoltMatrix( *((CGhoul2Info_v *)ghoul2), modelIndex, boltIndex, matrix, angles, position, frameNum, modelList, scale );
		assert(0);
	return qfalse;
}

CCALL qboolean SV_G2API_GetBoltMatrix_NoRecNoRot( void *ghoul2, const int modelIndex, const int boltIndex, mdxaBone_t *matrix, const vec3_t angles, const vec3_t position, const int frameNum, qhandle_t *modelList, vec3_t scale ) {
	//CL_G2API_BoltMatrixReconstruction( qfalse );
	//CL_G2API_BoltMatrixSPMethod( qtrue );
	//return CL_G2API_GetBoltMatrix( ghoul2, modelIndex, boltIndex, matrix, angles, position, frameNum, modelList, scale );


	if ( !ghoul2 ) { 
		assert(0);
		return qfalse;
	}
	return CL_G2API_GetBoltMatrix_NoRecNoRot( ghoul2, modelIndex, boltIndex, matrix, angles, position, frameNum, modelList, scale );

	assert(0);
	return qfalse;
}

CCALL int SV_G2API_InitGhoul2Model( void **ghoul2Ptr, const char *fileName, int modelIndex, qhandle_t customSkin, qhandle_t customShader, int modelFlags, int lodBias ) {
//#ifdef _FULL_G2_LEAK_CHECKING
//		g_G2AllocServer = 1;
//#endif
//	return re->G2API_InitGhoul2Model( (CGhoul2Info_v **)ghoul2Ptr, fileName, modelIndex, customSkin, customShader, modelFlags, lodBias );
		assert(0);
	return 0;
}

CCALL qboolean SV_G2API_SetSkin( void *ghoul2, int modelIndex, qhandle_t customSkin, qhandle_t renderSkin ) {
	//CGhoul2Info_v &g2 = *((CGhoul2Info_v *)ghoul2);
	//return re->G2API_SetSkin( g2, modelIndex, customSkin, renderSkin );
		assert(0);
	return qfalse;
}

CCALL void SV_G2API_CollisionDetect( CollisionRecord_t *collRecMap, void* ghoul2, const vec3_t angles, const vec3_t position, int frameNumber, int entNum, vec3_t rayStart, vec3_t rayEnd, vec3_t scale, int traceFlags, int useLod, float fRadius ) {
	//re->G2API_CollisionDetect( collRecMap, *((CGhoul2Info_v *)ghoul2), angles, position, frameNumber, entNum, rayStart, rayEnd, scale, G2VertSpaceServer, traceFlags, useLod, fRadius );
}

CCALL void SV_G2API_CollisionDetectCache( CollisionRecord_t *collRecMap, void* ghoul2, const vec3_t angles, const vec3_t position, int frameNumber, int entNum, vec3_t rayStart, vec3_t rayEnd, vec3_t scale, int traceFlags, int useLod, float fRadius ) {
	//re->G2API_CollisionDetectCache( collRecMap, *((CGhoul2Info_v *)ghoul2), angles, position, frameNumber, entNum, rayStart, rayEnd, scale, G2VertSpaceServer, traceFlags, useLod, fRadius );
}

CCALL void SV_G2API_CleanGhoul2Models( void **ghoul2Ptr ) {
//#ifdef _FULL_G2_LEAK_CHECKING
//		g_G2AllocServer = 1;
//#endif
//	re->G2API_CleanGhoul2Models( (CGhoul2Info_v **)ghoul2Ptr );
}

CCALL qboolean SV_G2API_SetBoneAngles( void *ghoul2, int modelIndex, const char *boneName, const vec3_t angles, const int flags, const int up, const int right, const int forward, qhandle_t *modelList, int blendTime , int currentTime ) {
	return CL_G2API_SetBoneAngles( ghoul2, modelIndex, boneName, angles, flags, up, right, forward, modelList, blendTime , currentTime );
	assert(0);
	return qfalse;
}

CCALL qboolean SV_G2API_SetBoneAnim( void *ghoul2, const int modelIndex, const char *boneName, const int startFrame, const int endFrame, const int flags, const float animSpeed, const int currentTime, const float setFrame, const int blendTime ) {
	//return re->G2API_SetBoneAnim( *((CGhoul2Info_v *)ghoul2), modelIndex, boneName, startFrame, endFrame, flags, animSpeed, currentTime, setFrame, blendTime );
		assert(0);
	return qfalse;
}

CCALL qboolean SV_G2API_GetBoneAnim( void *ghoul2, const char *boneName, const int currentTime, float *currentFrame, int *startFrame, int *endFrame, int *flags, float *animSpeed, int *modelList, const int modelIndex ) {
	//CGhoul2Info_v &g2 = *((CGhoul2Info_v *)ghoul2);
	//return re->G2API_GetBoneAnim( g2, modelIndex, boneName, currentTime, currentFrame, startFrame, endFrame, flags, animSpeed, modelList );
		assert(0);
	return qfalse;
}

CCALL void SV_G2API_GetGLAName( void *ghoul2, int modelIndex, char *fillBuf ) {
	//assert( ghoul2 && "invalid g2 handle" );
	//
	//char *tmp = re->G2API_GetGLAName( *((CGhoul2Info_v *)ghoul2), modelIndex );
	//if ( tmp ) {
	//	strcpy( fillBuf, tmp );
	//}
}

CCALL int SV_G2API_CopyGhoul2Instance( void *g2From, void *g2To, int modelIndex ) {
	//return re->G2API_CopyGhoul2Instance( *((CGhoul2Info_v *)g2From), *((CGhoul2Info_v *)g2To), modelIndex );
	assert(0);
	return 0;
}

CCALL void SV_G2API_CopySpecificGhoul2Model( void *g2From, int modelFrom, void *g2To, int modelTo ) {
	//re->G2API_CopySpecificG2Model( *((CGhoul2Info_v *)g2From), modelFrom, *((CGhoul2Info_v *)g2To), modelTo );
}

CCALL void SV_G2API_DuplicateGhoul2Instance( void *g2From, void **g2To ) {
//#ifdef _FULL_G2_LEAK_CHECKING
//		g_G2AllocServer = 1;
//#endif
//	re->G2API_DuplicateGhoul2Instance( *((CGhoul2Info_v *)g2From), (CGhoul2Info_v **)g2To );
}

CCALL qboolean SV_G2API_HasGhoul2ModelOnIndex( void *ghlInfo, int modelIndex ) {
	//return re->G2API_HasGhoul2ModelOnIndex( (CGhoul2Info_v **)ghlInfo, modelIndex );
	assert(0);
	return qfalse;
}

CCALL qboolean SV_G2API_RemoveGhoul2Model( void *ghlInfo, int modelIndex ) {
//#ifdef _FULL_G2_LEAK_CHECKING
//		g_G2AllocServer = 1;
//#endif
//	return re->G2API_RemoveGhoul2Model( (CGhoul2Info_v **)ghlInfo, modelIndex );
		assert(0);
	return qfalse;
}

CCALL qboolean SV_G2API_RemoveGhoul2Models( void *ghlInfo ) {
//#ifdef _FULL_G2_LEAK_CHECKING
//	g_G2AllocServer = 1;
//#endif
//	return re->G2API_RemoveGhoul2Models( (CGhoul2Info_v **)ghlInfo );
		assert(0);
	return qfalse;
}

CCALL int SV_G2API_Ghoul2Size( void *ghlInfo ) {
	//return re->G2API_Ghoul2Size( *((CGhoul2Info_v *)ghlInfo) );
		assert(0);
	return 0;
}

CCALL int SV_G2API_AddBolt( void *ghoul2, int modelIndex, const char *boneName ) {
	//return re->G2API_AddBolt( *((CGhoul2Info_v *)ghoul2), modelIndex, boneName );
		assert(0);
	return 0;
}

CCALL void SV_G2API_SetBoltInfo( void *ghoul2, int modelIndex, int boltInfo ) {
	//re->G2API_SetBoltInfo( *((CGhoul2Info_v *)ghoul2), modelIndex, boltInfo );
}

CCALL qboolean SV_G2API_SetRootSurface( void *ghoul2, const int modelIndex, const char *surfaceName ) {
	//return re->G2API_SetRootSurface( *((CGhoul2Info_v *)ghoul2), modelIndex, surfaceName );
		assert(0);
	return qfalse;
}

CCALL qboolean SV_G2API_SetSurfaceOnOff( void *ghoul2, const char *surfaceName, const int flags ) {
	//return re->G2API_SetSurfaceOnOff( *((CGhoul2Info_v *)ghoul2), surfaceName, flags );
		assert(0);
	return qfalse;
}

CCALL qboolean SV_G2API_SetNewOrigin( void *ghoul2, const int boltIndex ) {
	//return re->G2API_SetNewOrigin( *((CGhoul2Info_v *)ghoul2), boltIndex );
		assert(0);
	return qfalse;
}

CCALL qboolean SV_G2API_DoesBoneExist( void *ghoul2, int modelIndex, const char *boneName ) {
	//CGhoul2Info_v &g2 = *((CGhoul2Info_v *)ghoul2);
	//return re->G2API_DoesBoneExist( g2, modelIndex, boneName );
		assert(0);
	return qfalse;
}

CCALL int SV_G2API_GetSurfaceRenderStatus( void *ghoul2, const int modelIndex, const char *surfaceName ) {
	//CGhoul2Info_v &g2 = *((CGhoul2Info_v *)ghoul2);
	//return re->G2API_GetSurfaceRenderStatus( g2, modelIndex, surfaceName );
		assert(0);
	return 0;
}

CCALL void SV_G2API_AbsurdSmoothing( void *ghoul2, qboolean status ) {
	//CGhoul2Info_v &g2 = *((CGhoul2Info_v *)ghoul2);
	//re->G2API_AbsurdSmoothing( g2, status );
}

CCALL void SV_G2API_SetRagDoll( void *ghoul2, sharedRagDollParams_t *params ) {
	//CRagDollParams rdParams;
	//
	//if ( !params ) {
	//	re->G2API_ResetRagDoll( *((CGhoul2Info_v *)ghoul2) );
	//	return;
	//}
	//
	//VectorCopy( params->angles, rdParams.angles );
	//VectorCopy( params->position, rdParams.position );
	//VectorCopy( params->scale, rdParams.scale );
	//VectorCopy( params->pelvisAnglesOffset, rdParams.pelvisAnglesOffset );
	//VectorCopy( params->pelvisPositionOffset, rdParams.pelvisPositionOffset );
	//
	//rdParams.fImpactStrength = params->fImpactStrength;
	//rdParams.fShotStrength = params->fShotStrength;
	//rdParams.me = params->me;
	//
	//rdParams.startFrame = params->startFrame;
	//rdParams.endFrame = params->endFrame;
	//
	//rdParams.collisionType = params->collisionType;
	//rdParams.CallRagDollBegin = params->CallRagDollBegin;
	//
	//rdParams.RagPhase = (CRagDollParams::ERagPhase)params->RagPhase;
	//rdParams.effectorsToTurnOff = (CRagDollParams::ERagEffector)params->effectorsToTurnOff;
	//
	//re->G2API_SetRagDoll( *((CGhoul2Info_v *)ghoul2), &rdParams );
}

CCALL void SV_G2API_AnimateG2Models( void *ghoul2, int time, sharedRagDollUpdateParams_t *params ) {
	//CRagDollUpdateParams rduParams;
	//
	//if ( !params )
	//	return;
	//
	//VectorCopy( params->angles, rduParams.angles );
	//VectorCopy( params->position, rduParams.position );
	//VectorCopy( params->scale, rduParams.scale );
	//VectorCopy( params->velocity, rduParams.velocity );
	//
	//rduParams.me = params->me;
	//rduParams.settleFrame = params->settleFrame;
	//
	//re->G2API_AnimateG2ModelsRag( *((CGhoul2Info_v *)ghoul2), time, &rduParams );
}

CCALL qboolean SV_G2API_RagPCJConstraint( void *ghoul2, const char *boneName, vec3_t min, vec3_t max ) {
	//return re->G2API_RagPCJConstraint( *((CGhoul2Info_v *)ghoul2), boneName, min, max );
		assert(0);
	return qfalse;
}

CCALL qboolean SV_G2API_RagPCJGradientSpeed( void *ghoul2, const char *boneName, const float speed ) {
	//return re->G2API_RagPCJGradientSpeed( *((CGhoul2Info_v *)ghoul2), boneName, speed );
		assert(0);
	return qfalse;
}

CCALL qboolean SV_G2API_RagEffectorGoal( void *ghoul2, const char *boneName, vec3_t pos ) {
	//return re->G2API_RagEffectorGoal( *((CGhoul2Info_v *)ghoul2), boneName, pos );
		assert(0);
	return qfalse;
}

CCALL qboolean SV_G2API_GetRagBonePos( void *ghoul2, const char *boneName, vec3_t pos, vec3_t entAngles, vec3_t entPos, vec3_t entScale ) {
	//return re->G2API_GetRagBonePos( *((CGhoul2Info_v *)ghoul2), boneName, pos, entAngles, entPos, entScale );
		assert(0);
	return qfalse;
}

CCALL qboolean SV_G2API_RagEffectorKick( void *ghoul2, const char *boneName, vec3_t velocity ) {
	//return re->G2API_RagEffectorKick( *((CGhoul2Info_v *)ghoul2), boneName, velocity );
		assert(0);
	return qfalse;
}

CCALL qboolean SV_G2API_RagForceSolve( void *ghoul2, qboolean force ) {
	//return re->G2API_RagForceSolve( *((CGhoul2Info_v *)ghoul2), force );
		assert(0);
	return qfalse;
}

CCALL qboolean SV_G2API_SetBoneIKState( void *ghoul2, int time, const char *boneName, int ikState, sharedSetBoneIKStateParams_t *params ) {
	//return re->G2API_SetBoneIKState( *((CGhoul2Info_v *)ghoul2), time, boneName, ikState, params );
		assert(0);
	return qfalse;
}

CCALL qboolean SV_G2API_IKMove( void *ghoul2, int time, sharedIKMoveParams_t *params ) {
	//return re->G2API_IKMove( *((CGhoul2Info_v *)ghoul2), time, params );
		assert(0);
	return qfalse;
}

CCALL qboolean SV_G2API_RemoveBone( void *ghoul2, const char *boneName, int modelIndex ) {
	//CGhoul2Info_v &g2 = *((CGhoul2Info_v *)ghoul2);
	//return re->G2API_RemoveBone( g2, modelIndex, boneName );
	return qfalse;
}

CCALL void SV_G2API_AttachInstanceToEntNum( void *ghoul2, int entityNum, qboolean server ) {
	//re->G2API_AttachInstanceToEntNum( *((CGhoul2Info_v *)ghoul2), entityNum, server );
}

CCALL void SV_G2API_ClearAttachedInstance( int entityNum ) {
	//re->G2API_ClearAttachedInstance( entityNum );
}

CCALL void SV_G2API_CleanEntAttachments( void ) {
	//re->G2API_CleanEntAttachments();
}

CCALL qboolean SV_G2API_OverrideServer( void *serverInstance ) {
	//CGhoul2Info_v &g2 = *((CGhoul2Info_v *)serverInstance);
	//return re->G2API_OverrideServerWithClientData( g2, 0 );
	return qfalse;
}

CCALL void SV_G2API_GetSurfaceName( void *ghoul2, int surfNumber, int modelIndex, char *fillBuf ) {
	//CGhoul2Info_v &g2 = *((CGhoul2Info_v *)ghoul2);
	//char *tmp = re->G2API_GetSurfaceName( g2, modelIndex, surfNumber );
	//strcpy( fillBuf, tmp );
	assert(0);
}
#endif