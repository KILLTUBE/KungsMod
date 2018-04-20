/*
===========================================================================
Copyright (C) 2013 - 2015, OpenJK contributors

This file is part of the OpenJK source code.

OpenJK is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License version 2 as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, see <http://www.gnu.org/licenses/>.
===========================================================================
*/

#include "qcommon/RoffSystem.h"
#include "qcommon/stringed_ingame.h"
#include "qcommon/timing.h"
#include "client.h"
#include "cl_lan.h"
#include "botlib/botlib.h"
#include "snd_ambient.h"
#include "FXExport.h"
#include "FxUtil.h"

extern IHeapAllocator *G2VertSpaceClient;
extern botlib_export_t *botlib_export;

// ui interface
static vm_t *uivm; // ui vm, valid for legacy and new api


CCALL void UI_Init( qboolean inGameLoad );
CCALL void UI_Shutdown( void );
CCALL void UI_KeyEvent( int key, qboolean down );
CCALL void UI_MouseEvent( int dx, int dy );
CCALL void UI_Refresh( int realtime );
CCALL qboolean Menus_AnyFullScreenVisible( void );
CCALL void UI_SetActiveMenu( uiMenuCommand_t menu );
CCALL qboolean UI_ConsoleCommand( int realTime );
CCALL void UI_DrawConnectScreen( qboolean overlay );
CCALL void Menu_Reset(void);





void UIVM_Init( qboolean inGameLoad ) {
	VMSwap v( uivm );
	UI_Init( inGameLoad );
}

void UIVM_Shutdown( void ) {
	VMSwap v( uivm );
	UI_Shutdown();
	Menu_Reset();
}

void UIVM_KeyEvent( int key, qboolean down ) {
	VMSwap v( uivm );
	UI_KeyEvent( key, down );
}

void UIVM_MouseEvent( int dx, int dy ) {
	VMSwap v( uivm );
	UI_MouseEvent( dx, dy );
}

void UIVM_Refresh( int realtime ) {
	VMSwap v( uivm );
	UI_Refresh( realtime );
}

qboolean UIVM_IsFullscreen( void ) {
	VMSwap v( uivm );
	return Menus_AnyFullScreenVisible();
}

void UIVM_SetActiveMenu( uiMenuCommand_t menu ) {
	VMSwap v( uivm );
	UI_SetActiveMenu( menu );
}

qboolean UIVM_ConsoleCommand( int realTime ) {
	VMSwap v( uivm );
	return UI_ConsoleCommand( realTime );
}
void UIVM_DrawConnectScreen( qboolean overlay ) {
	VMSwap v( uivm );
	UI_DrawConnectScreen( overlay );
}





static int CL_Milliseconds( void ) {
	return Sys_Milliseconds();
}

static void CL_Cvar_Get( const char *var_name, const char *value, uint32_t flags ) {
	Cvar_Register( NULL, var_name, value, flags );
}

CCALL void CL_GetClientState( uiClientState_t *state ) {
	state->connectPacketCount = clc.connectPacketCount;
	state->connState = cls.state;
	Q_strncpyz( state->servername, cls.servername, sizeof( state->servername ) );
	Q_strncpyz( state->updateInfoString, cls.updateInfoString, sizeof( state->updateInfoString ) );
	Q_strncpyz( state->messageString, clc.serverMessage, sizeof( state->messageString ) );
	state->clientNum = cl.snap.ps.clientNum;
}

CCALL void UI_GetClipboardData( char *buf, int buflen ) {
	char	*cbd, *c;

	c = cbd = Sys_GetClipboardData();
	if ( !cbd ) {
		*buf = 0;
		return;
	}

	for ( int i = 0, end = buflen - 1; *c && i < end; i++ )
	{
		uint32_t utf32 = ConvertUTF8ToUTF32( c, &c );
		buf[i] = ConvertUTF32ToExpectedCharset( utf32 );
	}

	Z_Free( cbd );
}

CCALL int GetConfigString(int index, char *buf, int size)
{
	int		offset;

	if (index < 0 || index >= MAX_CONFIGSTRINGS)
		return qfalse;

	offset = cl.gameState.stringOffsets[index];
	if (!offset) {
		if( size ) {
			buf[0] = 0;
		}
		return qfalse;
	}

	Q_strncpyz( buf, cl.gameState.stringData+offset, size);

	return qtrue;
}

CCALL void Key_GetBindingBuf( int keynum, char *buf, int buflen ) {
	char	*value;

	value = Key_GetBinding( keynum );
	if ( value ) {
		Q_strncpyz( buf, value, buflen );
	}
	else {
		*buf = 0;
	}
}

CCALL void Key_KeynumToStringBuf( int keynum, char *buf, int buflen )
{
	const char *psKeyName = Key_KeynumToString( keynum/*, qtrue */);

	// see if there's a more friendly (or localised) name...
	//
	const char *psKeyNameFriendly = SE_GetString( va("KEYNAMES_KEYNAME_%s",psKeyName) );

	Q_strncpyz( buf, (psKeyNameFriendly && psKeyNameFriendly[0]) ? psKeyNameFriendly : psKeyName, buflen );
}

CCALL void CL_SE_GetLanguageName( const int languageIndex, char *buffer ) {
	Q_strncpyz( buffer, SE_GetLanguageName( languageIndex ), 128 );
}

//CCALL qboolean CL_SE_GetStringTextString( const char *text, char *buffer, int bufferLength ) {
//	assert( text && buffer );
//	Q_strncpyz( buffer, SE_GetString( text ), bufferLength );
//	return qtrue;
//}

static void CL_R_ShaderNameFromIndex( char *name, int index ) {
	const char *retMem = R_ShaderNameFromIndex( index );
	if ( retMem )
		strcpy( name, retMem );
	else
		name[0] = '\0';
}


/*

static void CL_G2API_ListModelSurfaces( void *ghlInfo ) {
	if ( !ghlInfo ) {
		return;
	}

	G2API_ListSurfaces( (CGhoul2Info *)ghlInfo );
}

static void CL_G2API_ListModelBones( void *ghlInfo, int frame ) {
	if ( !ghlInfo ) {
		return;
	}

	G2API_ListBones( (CGhoul2Info *)ghlInfo, frame );
}

static void CL_G2API_SetGhoul2ModelIndexes( void *ghoul2, qhandle_t *modelList, qhandle_t *skinList ) {
	if ( !ghoul2 ) {
		return;
	}

	G2API_SetGhoul2ModelIndexes( *((CGhoul2Info_v *)ghoul2), modelList, skinList );
}

static qboolean CL_G2API_HaveWeGhoul2Models( void *ghoul2) {
	if ( !ghoul2 ) {
		return qfalse;
	}

	return G2API_HaveWeGhoul2Models( *((CGhoul2Info_v *)ghoul2) );
}

static qboolean CL_G2API_GetBoltMatrix( void *ghoul2, const int modelIndex, const int boltIndex, mdxaBone_t *matrix, const vec3_t angles, const vec3_t position, const int frameNum, qhandle_t *modelList, vec3_t scale ) {
	if ( !ghoul2 ) {
		return qfalse;
	
	}
	return G2API_GetBoltMatrix( *((CGhoul2Info_v *)ghoul2), modelIndex, boltIndex, matrix, angles, position, frameNum, modelList, scale );
}

static qboolean CL_G2API_GetBoltMatrix_NoReconstruct( void *ghoul2, const int modelIndex, const int boltIndex, mdxaBone_t *matrix, const vec3_t angles, const vec3_t position, const int frameNum, qhandle_t *modelList, vec3_t scale ) {
	if ( !ghoul2 ) {
		return qfalse;
	}

	G2API_BoltMatrixReconstruction( qfalse );
	return G2API_GetBoltMatrix( *((CGhoul2Info_v *)ghoul2), modelIndex, boltIndex, matrix, angles, position, frameNum, modelList, scale );
}

static qboolean CL_G2API_GetBoltMatrix_NoRecNoRot( void *ghoul2, const int modelIndex, const int boltIndex, mdxaBone_t *matrix, const vec3_t angles, const vec3_t position, const int frameNum, qhandle_t *modelList, vec3_t scale ) {
	if ( !ghoul2 ) {
		return qfalse;
	}

	G2API_BoltMatrixSPMethod( qtrue );
	return G2API_GetBoltMatrix( *((CGhoul2Info_v *)ghoul2), modelIndex, boltIndex, matrix, angles, position, frameNum, modelList, scale );
}

static int CL_G2API_InitGhoul2Model( void **ghoul2Ptr, const char *fileName, int modelIndex, qhandle_t customSkin, qhandle_t customShader, int modelFlags, int lodBias ) {
	if ( !ghoul2Ptr ) {
		return 0;
	}

#ifdef _FULL_G2_LEAK_CHECKING
		g_G2AllocServer = 0;
#endif
	return G2API_InitGhoul2Model( (CGhoul2Info_v **)ghoul2Ptr, fileName, modelIndex, customSkin, customShader, modelFlags, lodBias );
}

static qboolean CL_G2API_SetSkin( void *ghoul2, int modelIndex, qhandle_t customSkin, qhandle_t renderSkin ) {
	if ( !ghoul2 ) {
		return qfalse;
	}

	CGhoul2Info_v &g2 = *((CGhoul2Info_v *)ghoul2);
	return G2API_SetSkin( g2, modelIndex, customSkin, renderSkin );
}

static void CL_G2API_CollisionDetect(
	CollisionRecord_t *collRecMap,
	void* ghoul2,
	const vec3_t angles,
	const vec3_t position,
	int frameNumber,
	int entNum,
	vec3_t rayStart,
	vec3_t rayEnd,
	vec3_t scale,
	int traceFlags,
	int useLod,
	float fRadius )
{
	if ( !ghoul2 ) {
		return;
	}

	G2API_CollisionDetect(
		collRecMap,
		*((CGhoul2Info_v *)ghoul2),
		angles,
		position,
		frameNumber,
		entNum,
		rayStart,
		rayEnd,
		scale,
		G2VertSpaceClient,
		traceFlags,
		useLod,
		fRadius);
}

static void CL_G2API_CollisionDetectCache(
	CollisionRecord_t *collRecMap,
	void* ghoul2,
	const vec3_t angles,
	const vec3_t position,
	int frameNumber,
	int entNum,
	vec3_t rayStart,
	vec3_t rayEnd,
	vec3_t scale,
	int traceFlags,
	int useLod,
	float fRadius)
{
	if ( !ghoul2 ) {
		return;
	}

	G2API_CollisionDetectCache(
		collRecMap,
		*((CGhoul2Info_v *)ghoul2),
		angles,
		position,
		frameNumber,
		entNum,
		rayStart,
		rayEnd,
		scale,
		G2VertSpaceClient,
		traceFlags,
		useLod,
		fRadius);
}

static void CL_G2API_CleanGhoul2Models( void **ghoul2Ptr ) {
	if ( !ghoul2Ptr ) {
		return;
	}

#ifdef _FULL_G2_LEAK_CHECKING
		g_G2AllocServer = 0;
#endif
	G2API_CleanGhoul2Models( (CGhoul2Info_v **)ghoul2Ptr );
}

static qboolean CL_G2API_SetBoneAngles(
	void *ghoul2,
	int modelIndex,
	const char *boneName,
	const vec3_t angles,
	const int flags,
	const int up,
	const int right,
	const int forward,
	qhandle_t *modelList,
	int blendTime ,
	int currentTime)
{
	if ( !ghoul2 ) {
		return qfalse;
	}

	return G2API_SetBoneAngles(
		*((CGhoul2Info_v *)ghoul2),
		modelIndex,
		boneName,
		angles,
		flags,
		(const Eorientations)up,
		(const Eorientations)right,
		(const Eorientations)forward,
		modelList,
		blendTime,
		currentTime);
}

static qboolean CL_G2API_SetBoneAnim(
	void *ghoul2,
	const int modelIndex,
	const char *boneName,
	const int startFrame,
	const int endFrame,
	const int flags,
	const float animSpeed,
	const int currentTime,
	const float setFrame,
	const int blendTime)
{
	if ( !ghoul2 ) {
		return qfalse;
	}

	return G2API_SetBoneAnim(
		*((CGhoul2Info_v *)ghoul2),
		modelIndex,
		boneName,
		startFrame,
		endFrame,
		flags,
		animSpeed,
		currentTime,
		setFrame,
		blendTime);
}

static qboolean CL_G2API_GetBoneAnim(
	void *ghoul2,
	const char *boneName,
	const int currentTime,
	float *currentFrame,
	int *startFrame,
	int *endFrame,
	int *flags,
	float *animSpeed,
	int *modelList,
	const int modelIndex)
{
	if ( !ghoul2 ) {
		return qfalse;
	}

	CGhoul2Info_v &g2 = *((CGhoul2Info_v *)ghoul2);
	return G2API_GetBoneAnim(
		g2,
		modelIndex,
		boneName,
		currentTime,
		currentFrame,
		startFrame,
		endFrame,
		flags,
		animSpeed,
		modelList);
}

static qboolean CL_G2API_GetBoneFrame(
	void *ghoul2,
	const char *boneName,
	const int currentTime,
	float *currentFrame,
	int *modelList,
	const int modelIndex)
{
	if ( !ghoul2 ) {
		return qfalse;
	}

	CGhoul2Info_v &g2 = *((CGhoul2Info_v *)ghoul2);
	int iDontCare1 = 0, iDontCare2 = 0, iDontCare3 = 0;
	float fDontCare1 = 0;

	return G2API_GetBoneAnim(
		g2,
		modelIndex,
		boneName,
		currentTime,
		currentFrame,
		&iDontCare1,
		&iDontCare2,
		&iDontCare3,
		&fDontCare1,
		modelList);
}

static void CL_G2API_GetGLAName( void *ghoul2, int modelIndex, char *fillBuf ) {
	if ( !ghoul2 ) {
		return;
	}

	char *tmp = G2API_GetGLAName( *((CGhoul2Info_v *)ghoul2), modelIndex );
	strcpy( fillBuf, tmp );
}

static int CL_G2API_CopyGhoul2Instance( void *g2From, void *g2To, int modelIndex ) {
	if ( !g2From || !g2To ) {
		return 0;
	}

	return G2API_CopyGhoul2Instance( *((CGhoul2Info_v *)g2From), *((CGhoul2Info_v *)g2To), modelIndex );
}

static void CL_G2API_CopySpecificGhoul2Model( void *g2From, int modelFrom, void *g2To, int modelTo ) {
	if ( !g2From || !g2To ) {
		return;
	}

	G2API_CopySpecificG2Model( *((CGhoul2Info_v *)g2From), modelFrom, *((CGhoul2Info_v *)g2To), modelTo );
}

static void CL_G2API_DuplicateGhoul2Instance( void *g2From, void **g2To ) {
	if ( !g2From || !g2To ) {
		return;
	}

#ifdef _FULL_G2_LEAK_CHECKING
		g_G2AllocServer = 0;
#endif
	G2API_DuplicateGhoul2Instance( *((CGhoul2Info_v *)g2From), (CGhoul2Info_v **)g2To );
}

CCALL qboolean CL_G2API_HasGhoul2ModelOnIndex( void *ghlInfo, int modelIndex ) {
	if ( !ghlInfo ) {
		return qfalse;
	}

	return G2API_HasGhoul2ModelOnIndex( (CGhoul2Info_v **)ghlInfo, modelIndex );
}

CCALL qboolean CL_G2API_RemoveGhoul2Model( void *ghlInfo, int modelIndex ) {
	if ( !ghlInfo ) {
		return qfalse;
	}

#ifdef _FULL_G2_LEAK_CHECKING
		g_G2AllocServer = 0;
#endif
	return G2API_RemoveGhoul2Model( (CGhoul2Info_v **)ghlInfo, modelIndex );
}

CCALL int CL_G2API_AddBolt( void *ghoul2, int modelIndex, const char *boneName ) {
	if ( !ghoul2 ) {
		return -1;
	}

	return G2API_AddBolt( *((CGhoul2Info_v *)ghoul2), modelIndex, boneName );
}

static void CL_G2API_SetBoltInfo( void *ghoul2, int modelIndex, int boltInfo ) {
	if ( !ghoul2 ) {
		return;
	}

	G2API_SetBoltInfo( *((CGhoul2Info_v *)ghoul2), modelIndex, boltInfo );
}

static qboolean CL_G2API_SetRootSurface( void *ghoul2, const int modelIndex, const char *surfaceName ) {
	if ( !ghoul2 ) {
		return qfalse;
	}

	return G2API_SetRootSurface( *((CGhoul2Info_v *)ghoul2), modelIndex, surfaceName );
}

static qboolean CL_G2API_SetSurfaceOnOff( void *ghoul2, const char *surfaceName, const int flags ) {
	if ( !ghoul2 ) {
		return qfalse;
	}

	return G2API_SetSurfaceOnOff( *((CGhoul2Info_v *)ghoul2), surfaceName, flags );
}

static qboolean CL_G2API_SetNewOrigin( void *ghoul2, const int boltIndex ) {
	if ( !ghoul2 ) {
		return qfalse;
	}

	return G2API_SetNewOrigin( *((CGhoul2Info_v *)ghoul2), boltIndex );
}

static int CL_G2API_GetTime( void ) {
	return G2API_GetTime( 0 );
}

CCALL void CL_G2API_SetTime( int time, int clock ) {
	G2API_SetTime( time, clock );
}

static void CL_G2API_SetRagDoll( void *ghoul2, sharedRagDollParams_t *params ) {
	if ( !ghoul2 ) {
		return;
	}

	CRagDollParams rdParams;

	if ( !params ) {
		G2API_ResetRagDoll( *((CGhoul2Info_v *)ghoul2) );
		return;
	}

	VectorCopy( params->angles, rdParams.angles );
	VectorCopy( params->position, rdParams.position );
	VectorCopy( params->scale, rdParams.scale );
	VectorCopy( params->pelvisAnglesOffset, rdParams.pelvisAnglesOffset );
	VectorCopy( params->pelvisPositionOffset, rdParams.pelvisPositionOffset );

	rdParams.fImpactStrength = params->fImpactStrength;
	rdParams.fShotStrength = params->fShotStrength;
	rdParams.me = params->me;

	rdParams.startFrame = params->startFrame;
	rdParams.endFrame = params->endFrame;

	rdParams.collisionType = params->collisionType;
	rdParams.CallRagDollBegin = params->CallRagDollBegin;

	rdParams.RagPhase = (CRagDollParams::ERagPhase)params->RagPhase;
	rdParams.effectorsToTurnOff = (CRagDollParams::ERagEffector)params->effectorsToTurnOff;

	G2API_SetRagDoll( *((CGhoul2Info_v *)ghoul2), &rdParams );
}

static void CL_G2API_AnimateG2Models( void *ghoul2, int time, sharedRagDollUpdateParams_t *params ) {
	if ( !ghoul2 ) {
		return;
	}

	CRagDollUpdateParams rduParams;

	if ( !params )
		return;

	VectorCopy( params->angles, rduParams.angles );
	VectorCopy( params->position, rduParams.position );
	VectorCopy( params->scale, rduParams.scale );
	VectorCopy( params->velocity, rduParams.velocity );

	rduParams.me = params->me;
	rduParams.settleFrame = params->settleFrame;

	G2API_AnimateG2ModelsRag( *((CGhoul2Info_v *)ghoul2), time, &rduParams );
}

static qboolean CL_G2API_SetBoneIKState( void *ghoul2, int time, const char *boneName, int ikState, sharedSetBoneIKStateParams_t *params ) {
	if ( !ghoul2 ) {
		return qfalse;
	}

	return G2API_SetBoneIKState( *((CGhoul2Info_v *)ghoul2), time, boneName, ikState, params );
}

static qboolean CL_G2API_IKMove( void *ghoul2, int time, sharedIKMoveParams_t *params ) {
	if ( !ghoul2 ) {
		return qfalse;
	}

	return G2API_IKMove( *((CGhoul2Info_v *)ghoul2), time, params );
}

static void CL_G2API_GetSurfaceName( void *ghoul2, int surfNumber, int modelIndex, char *fillBuf ) {
	if ( !ghoul2 ) {
		return;
	}

	CGhoul2Info_v &g2 = *((CGhoul2Info_v *)ghoul2);
	char *tmp = G2API_GetSurfaceName( g2, modelIndex, surfNumber );
	strcpy( fillBuf, tmp );
}

*/

static void CL_Key_SetCatcher( int catcher ) {
	// Don't allow the ui module to close the console
	Key_SetCatcher( catcher | ( Key_GetCatcher( ) & KEYCATCH_CONSOLE ) );
}

static void UIVM_Cvar_Set( const char *var_name, const char *value ) {
	Cvar_VM_Set( var_name, value, VM_UI );
}

static void UIVM_Cvar_SetValue( const char *var_name, float value ) {
	Cvar_VM_SetValue( var_name, value, VM_UI );
}

static void CL_AddUICommand( const char *cmdName ) {
	Cmd_AddCommand( cmdName, NULL );
}

static void UIVM_Cmd_RemoveCommand( const char *cmd_name ) {
	Cmd_VM_RemoveCommand( cmd_name, VM_UI );
}




CCALL int  PC_AddGlobalDefine(char *string);
CCALL int  PC_FreeSourceHandle(int handle);
CCALL int  PC_LoadGlobalDefines(const char* filename );
CCALL int  PC_LoadSourceHandle(const char *filename);
CCALL int  PC_ReadTokenHandle(int handle, pc_token_t *pc_token);
CCALL void PC_RemoveAllGlobalDefines( void );
CCALL int  PC_SourceFileAndLine(int handle, char *filename, int *line);

CCALL unsigned int R_AnyLanguage_ReadCharFromString( const char *psText, int *piAdvanceCount, qboolean *pbIsTrailingPunctuation ) {
	return AnyLanguage_ReadCharFromString(psText, piAdvanceCount, pbIsTrailingPunctuation);
}


CCALL void		G2_ListModelSurfaces			( void *ghlInfo ) {
	CL_G2API_ListModelSurfaces(ghlInfo);
}
CCALL void		G2_ListModelBones				( void *ghlInfo, int frame ) {
	CL_G2API_ListModelBones(ghlInfo, frame);
}
CCALL void		G2_SetGhoul2ModelIndexes		( void *ghoul2, qhandle_t *modelList, qhandle_t *skinList ) {
	CL_G2API_SetGhoul2ModelIndexes(ghoul2, modelList, skinList);
}
CCALL qboolean	G2_HaveWeGhoul2Models			( void *ghoul2 ) {
	return CL_G2API_HaveWeGhoul2Models(ghoul2);
}





CCALL qboolean		G2API_GetBoltMatrix					( void *ghoul2, const int modelIndex, const int boltIndex, mdxaBone_t *matrix, const vec3_t angles, const vec3_t position, const int frameNum, qhandle_t *modelList, vec3_t scale ) {
	return CL_G2API_GetBoltMatrix(ghoul2, modelIndex, boltIndex, matrix, angles, position, frameNum, modelList, scale);
}
CCALL qboolean		G2API_GetBoltMatrix_NoReconstruct	( void *ghoul2, const int modelIndex, const int boltIndex, mdxaBone_t *matrix, const vec3_t angles, const vec3_t position, const int frameNum, qhandle_t *modelList, vec3_t scale ) {
	return CL_G2API_GetBoltMatrix_NoReconstruct(ghoul2, modelIndex, boltIndex, matrix, angles, position, frameNum, modelList, scale);
}
CCALL qboolean		G2API_GetBoltMatrix_NoRecNoRot		( void *ghoul2, const int modelIndex, const int boltIndex, mdxaBone_t *matrix, const vec3_t angles, const vec3_t position, const int frameNum, qhandle_t *modelList, vec3_t scale ) {
	return CL_G2API_GetBoltMatrix_NoRecNoRot(ghoul2, modelIndex, boltIndex, matrix, angles, position, frameNum, modelList, scale);
}
CCALL int			G2API_InitGhoul2Model				( void **ghoul2Ptr, const char *fileName, int modelIndex, qhandle_t customSkin, qhandle_t customShader, int modelFlags, int lodBias ) {
	return CL_G2API_InitGhoul2Model(ghoul2Ptr, fileName, modelIndex, customSkin, customShader, modelFlags, lodBias);
}
CCALL void			G2API_CollisionDetect				( CollisionRecord_t *collRecMap, void* ghoul2, const vec3_t angles, const vec3_t position, int frameNumber, int entNum, vec3_t rayStart, vec3_t rayEnd, vec3_t scale, int traceFlags, int useLod, float fRadius ) {
	CL_G2API_CollisionDetect(collRecMap, ghoul2, angles, position, frameNumber, entNum, rayStart, rayEnd, scale, traceFlags, useLod, fRadius);
}
CCALL void			G2API_CollisionDetectCache			( CollisionRecord_t *collRecMap, void* ghoul2, const vec3_t angles, const vec3_t position, int frameNumber, int entNum, vec3_t rayStart, vec3_t rayEnd, vec3_t scale, int traceFlags, int useLod, float fRadius ) {
	CL_G2API_CollisionDetectCache(collRecMap, ghoul2, angles, position, frameNumber, entNum, rayStart, rayEnd, scale, traceFlags, useLod, fRadius);
}
CCALL qboolean		G2API_SetSkin						( void *ghoul2, int modelIndex, qhandle_t customSkin, qhandle_t renderSkin ) {
	return CL_G2API_SetSkin(ghoul2, modelIndex, customSkin, renderSkin);
}
CCALL void			G2API_CleanGhoul2Models				( void **ghoul2Ptr ) {
	CL_G2API_CleanGhoul2Models(ghoul2Ptr);
}

CCALL qboolean G2API_HasGhoul2ModelOnIndex( void *ghlInfo, int modelIndex ) {
	return CL_G2API_HasGhoul2ModelOnIndex(ghlInfo, modelIndex);
}

CCALL int G2API_AddBolt( void *ghoul2, int modelIndex, const char *boneName ) {
	return CL_G2API_AddBolt(ghoul2, modelIndex, boneName);
}

CCALL qboolean G2API_RemoveGhoul2Model( void *ghlInfo, int modelIndex ) {
	return CL_G2API_RemoveGhoul2Model(ghlInfo, modelIndex);
}

CCALL qboolean G2API_AttachG2Model( void *ghoul2From, int modelIndexFrom, void *ghoul2To, int toBoltIndex, int toModel ) {
	return CL_G2API_AttachG2Model(ghoul2From, modelIndexFrom, ghoul2To, toBoltIndex, toModel);
}

CCALL void	Cmd_ExecuteText	( int exec_when, const char *text ) {
	Cbuf_ExecuteText(exec_when, text);
}

void CL_BindUI( void ) {
	uivm = VM_Create( VM_UI );
}

void CL_UnbindUI( void ) {
	UIVM_Shutdown();
	VM_Free( uivm );
	uivm = NULL;
}
