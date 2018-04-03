#ifndef CG_TEMPWRAPPERS
#define CG_TEMPWRAPPERS

//#include <client/client.h>
#include "../game/g_local.h"
#include <cgame/cg_local.h>

CCALL sfxHandle_t	S_RegisterSound( const char *name);

CCALL qhandle_t		R_RegisterFont						( const char *fontName );
CCALL qhandle_t		R_RegisterModel						( const char *name );
CCALL qhandle_t		R_RegisterShader					( const char *name );
CCALL qhandle_t		R_RegisterShaderNoMip				( const char *name );
CCALL qhandle_t		R_RegisterSkin						( const char *name );
CCALL int				FX_RegisterEffect					( const char *file );

CCALL qhandle_t SV_R_RegisterSkin( const char *name );

CCALL void CG_GetVehicleCamPos( vec3_t camPos );
//CCALL void NPC_SetAnim(gentity_t *ent, int setAnimParts, int anim, int setAnimFlags);

// for UI stuff
CCALL const char *String_Alloc(const char *p);

CCALL int G_ModelIndex( const char *name );

CCALL int G_EffectIndex( const char *name );

CCALL void G_SetSharedVehicleFunctions( vehicleInfo_t *pVehInfo );

CCALL void	Cmd_ArgsBuffer( char *buffer, int bufferLength );




CCALL void CG_Init( int serverMessageNum, int serverCommandSequence, int clientNum );
CCALL void CG_Shutdown( void );
CCALL qboolean CG_ConsoleCommand( void );
CCALL void CG_DrawActiveFrame( int serverTime, stereoFrame_t stereoView, qboolean demoPlayback );
CCALL int CG_CrosshairPlayer( void );
CCALL int CG_LastAttacker( void );
CCALL void CG_KeyEvent(int key, qboolean down);
CCALL void _CG_MouseEvent( int x, int y );
CCALL void CG_EventHandling(int type);
CCALL int C_PointContents( void );
CCALL void C_GetLerpOrigin( void );
CCALL void C_GetLerpData( void );
CCALL void C_Trace( void );
CCALL void C_G2Trace( void );
CCALL void C_G2Mark( void );
CCALL int CG_RagCallback(int callType);
CCALL qboolean CG_IncomingConsoleCommand( void );
CCALL qboolean CG_NoUseableForce(void);
CCALL void CG_GetOrigin( int entID, vec3_t out );
CCALL void CG_GetAngles( int entID, vec3_t out );
CCALL trajectory_t *CG_GetOriginTrajectory( int entID );
CCALL trajectory_t *CG_GetAngleTrajectory( int entID );
CCALL void _CG_ROFF_NotetrackCallback( int entID, const char *notetrack );
CCALL void CG_MapChange( void );
CCALL void CG_AutomapInput( void );
CCALL void CG_MiscEnt( void );
CCALL void CG_FX_CameraShake( void );

CCALL void Cvar_VariableStringBuffer( const char *var_name, char *buffer, int bufsize );
CCALL cvar_t *Cvar_Get( const char *var_name, const char *var_value, uint32_t flags, const char *var_desc );
CCALL void CL_AddCgameCommand( const char *cmdName );
CCALL void CGVM_Cmd_RemoveCommand( const char *cmd_name );
CCALL void CL_AddReliableCommand2( const char *cmd );

CCALL void Cbuf_AddText( const char *text );
CCALL void SCR_UpdateScreen( void );
CCALL clipHandle_t	CM_InlineModel( int index );
CCALL void CL_CM_LoadMap( const char *mapname, qboolean subBSP );
CCALL void CM_TransformedBoxTrace( trace_t *trace, const vec3_t start, const vec3_t end,
						  const vec3_t mins, const vec3_t maxs,
						  clipHandle_t model, int brushmask,
						  const vec3_t origin, const vec3_t angles, int capsule );
CCALL int	CM_TransformedPointContents( const vec3_t p, clipHandle_t model, const vec3_t origin, const vec3_t angles);
CCALL int S_AddLocalSet( const char *name, vec3_t listener_origin, vec3_t origin, int entID, int time );
CCALL void S_AddLoopingSound( int entityNum, const vec3_t origin, const vec3_t velocity, sfxHandle_t sfxHandle );
CCALL void S_ClearLoopingSounds( void );


CCALL void CIN_DrawCinematic (int handle);
CCALL int CIN_PlayCinematic( const char *arg, int x, int y, int w, int h, int systemBits );
CCALL e_status CIN_RunCinematic (int handle);
CCALL void CIN_SetExtents (int handle, int x, int y, int w, int h);
CCALL e_status CIN_StopCinematic(int handle);

CCALL void CGFX_AddLine( vec3_t start, vec3_t end, float size1, float size2, float sizeParm, float alpha1, float alpha2, float alphaParm, vec3_t sRGB, vec3_t eRGB, float rgbParm, int killTime, qhandle_t shader, int flags );
CCALL void CGFX_AddPoly( addpolyArgStruct_t *p );
CCALL void CGFX_AddBezier( addbezierArgStruct_t *b );
CCALL void CGFX_AddPrimitive( effectTrailArgStruct_t *e );
CCALL void CGFX_AddSprite( addspriteArgStruct_t *s );
CCALL void CGFX_AddElectricity( addElectricityArgStruct_t *p );
CCALL int	FX_RegisterEffect(const char *file);
CCALL void FX_PlayEffect( const char *file, vec3_t org, vec3_t fwd, int vol, int rad );
CCALL void FX_PlayEffectID( int id, vec3_t org, vec3_t fwd, int vol, int rad, qboolean isPortal );
CCALL void FX_PlayEntityEffectID( int id, vec3_t org, matrix3_t axis, const int boltInfo, const int entNum, int vol, int rad );


CCALL int	FX_RegisterEffect(const char *file);
CCALL void FX_PlayEffect( const char *file, vec3_t org, vec3_t fwd, int vol, int rad );		// builds arbitrary perp. right vector, does a cross product to define up
CCALL void FX_PlayEffectID( int id, vec3_t org, vec3_t fwd, int vol, int rad, qboolean isPortal);		// builds arbitrary perp. right vector, does a cross product to define up
CCALL void FX_PlayEntityEffectID( int id, vec3_t org, matrix3_t axis, const int boltInfo, const int entNum, int vol, int rad );
//CCALL void FX_PlayBoltedEffectID( int id, vec3_t org, const int boltInfo, CGhoul2Info_v *ghoul2, int iLooptime, qboolean isRelative );
CCALL void FX_AddScheduledEffects( qboolean portal );
CCALL void		FX_Draw2DEffects ( float screenXScale, float screenYScale );
CCALL int			FX_InitSystem( refdef_t* refdef );	// called in CG_Init to purge the fx system.
CCALL void		FX_SetRefDefFromCGame( refdef_t* refdef );
CCALL qboolean	FX_FreeSystem( void );	// ditches all active effects;
CCALL void		FX_AdjustTime( int time );
CCALL void FX_SetRefDef(refdef_t *refdef);


CCALL qboolean CL_ROFF_Clean( void );
CCALL void CL_ROFF_UpdateEntities( void );
CCALL int CL_ROFF_Cache( char *file );
CCALL qboolean CL_ROFF_Play( int entID, int roffID, qboolean doTranslation );
CCALL qboolean CL_ROFF_Purge_Ent( int entID );

CCALL void CL_GetCurrentSnapshotNumber( int *snapshotNumber, int *serverTime );
CCALL int CL_GetCurrentCmdNumber( void );
CCALL void CL_SetClientForceAngle( int time, vec3_t angle );
CCALL void CL_PrecisionTimerStart( void **p );
CCALL int CL_PrecisionTimerEnd( void *p );
CCALL void CL_RMG_Init( int /* terrainID */, const char * /* terrainInfo */ );
CCALL qboolean CGFX_PlayBoltedEffectID( int id, vec3_t org, void *ghoul2, const int boltNum, const int entNum, const int modelNum, int iLooptime, qboolean isRelative );
CCALL qboolean CL_SE_GetStringTextString( const char *text, char *buffer, int bufferLength );
CCALL qboolean CL_GetDefaultState(int index, entityState_t *state);
CCALL void CL_GetGameState( gameState_t *gs );
CCALL void CL_GetGlconfig( glconfig_t *glconfig );
CCALL qboolean CL_GetServerCommand( int serverCommandNumber );
CCALL qboolean CL_GetSnapshot( int snapshotNumber, snapshot_t *snapshot );
CCALL qboolean CL_GetUserCmd( int cmdNumber, usercmd_t *ucmd );
CCALL void CL_OpenUIMenu( int menuID );
CCALL void CL_SetClientForceAngle( int time, vec3_t angle );
CCALL void _CL_SetUserCmdValue( int stateValue, float sensitivityScale, float mPitchOverride, float mYawOverride, float mSensitivityOverride, int fpSel, int invenSel, qboolean fighterControls );

CCALL void CL_InitUI( void );
CCALL void CL_ShutdownUI( void );
CCALL int Key_GetCatcher( void );
CCALL void Key_SetCatcher( int catcher );
CCALL void LAN_LoadCachedServers();
CCALL void LAN_SaveServersToCache();

CCALL int	Hunk_MemoryRemaining( void );
CCALL void RegisterSharedMemory( char *memory );
CCALL void VM_Shifted_Alloc( void **ptr, int size );
CCALL void VM_Shifted_Free( void **ptr );
CCALL int CL_Milliseconds( void );
CCALL int Com_RealTime(qtime_t *qtime);
CCALL void CL_PrecisionTimerStart( void **p );
CCALL int CL_PrecisionTimerEnd( void *p );
CCALL void	Cvar_Register( cvar_t *vmCvar, const char *varName, const char *defaultValue, uint32_t flags );
CCALL void CGVM_Cvar_Set( const char *var_name, const char *value );
CCALL void	Cvar_Update( cvar_t *vmCvar );

CCALL void AS_Init( void );
CCALL void AS_Free( void );
CCALL void AS_ParseSets( void );
CCALL void AS_AddPrecacheEntry( const char *name );
CCALL void S_UpdateAmbientSet ( const char *name, vec3_t origin );
CCALL int S_AddLocalSet( const char *name, vec3_t listener_origin, vec3_t origin, int entID, int time );
CCALL sfxHandle_t	AS_GetBModelSound( const char *name, int stage );
CCALL void S_AddLoopingSound( int entityNum, const vec3_t origin, const vec3_t velocity, sfxHandle_t sfxHandle );
CCALL void S_ClearLoopingSounds( void );
CCALL int CL_S_GetVoiceVolume( int entID );
CCALL void S_MuteSound(int entityNum, int entchannel);
CCALL sfxHandle_t	S_RegisterSound( const char *name);
CCALL void S_Respatialize( int entityNum, const vec3_t head, matrix3_t axis, int inwater );
CCALL void CL_S_Shutup( qboolean shutup );
CCALL void S_StartBackgroundTrack( const char *intro, const char *loop, qboolean bCalledByCGameStart );
CCALL void S_StartLocalSound( sfxHandle_t sfxHandle, int channelNum );
CCALL void S_StartSound(const vec3_t origin, int entityNum, int entchannel, sfxHandle_t sfxHandle );
CCALL void S_StopBackgroundTrack( void );
CCALL void S_StopLoopingSound( int entityNum );
CCALL void S_UpdateEntityPosition( int entityNum, const vec3_t origin );
CCALL void S_UpdateAmbientSet ( const char *name, vec3_t origin );

CCALL void AS_AddPrecacheEntry( const char *name );
CCALL sfxHandle_t AS_GetBModelSound( const char *name, int stage );
CCALL void AS_ParseSets( void );

CCALL clipHandle_t	CM_InlineModel( int index );
CCALL void CL_CM_LoadMap( const char *mapname, qboolean subBSP );
CCALL int CM_PointContents( const vec3_t p, clipHandle_t model );
CCALL int CL_CM_RegisterTerrain( const char *config );
CCALL clipHandle_t CM_TempBoxModel( const vec3_t mins, const vec3_t maxs, int capsule );
CCALL void CM_BoxTrace( trace_t *results, const vec3_t start, const vec3_t end,
						  const vec3_t mins, const vec3_t maxs,
						  clipHandle_t model, int brushmask, int capsule );
CCALL int	CM_TransformedPointContents( const vec3_t p, clipHandle_t model, const vec3_t origin, const vec3_t angles);
CCALL void CM_TransformedBoxTrace( trace_t *trace, const vec3_t start, const vec3_t end,
						  const vec3_t mins, const vec3_t maxs,
						  clipHandle_t model, int brushmask,
						  const vec3_t origin, const vec3_t angles, int capsule );


CCALL void R_BeginFrame( stereoFrame_t stereoFrame );
CCALL void R_EndFrame( int *frontEndMsec, int *backEndMsec );

CCALL int C_GetLevel( void );
CCALL qboolean C_Models_LevelLoadEnd( qboolean deleteUnusedByLevel );
CCALL qboolean C_Images_LevelLoadEnd();

CCALL void R_KeyEvent(int key, int state);
CCALL void R_CharEvent(int key);
CCALL void R_MouseWheelEvent(float dir);
CCALL void R_MouseClickEvent(int key, int state);

CCALL void R_HunkClearCrap(void);
CCALL void R_InitShaders( qboolean server );

CCALL void R_TakeVideoFrame( int width, int height, byte *captureBuffer, byte *encodeBuffer, qboolean motionJpeg );
CCALL void R_SVModelInit( void );
CCALL void	R_InitSkins( void );
CCALL void R_Shutdown( qboolean destroyWindow, qboolean restarting );
CCALL void R_BeginRegistration( glconfig_t *glconfigOut );
CCALL qhandle_t R_RegisterModel( const char *name );
CCALL qhandle_t R_RegisterServerModel( const char *name );
CCALL qhandle_t R_RegisterSkin( const char *name );
CCALL qhandle_t R_RegisterServerSkin( const char *name );
CCALL qhandle_t R_RegisterShader( const char *name );
CCALL qhandle_t R_RegisterShaderNoMip( const char *name );
CCALL const char *R_ShaderNameFromIndex(int index);
CCALL void R_LoadWorldMap( const char *name );
CCALL void R_SetWorldVisData( const byte *vis );
CCALL void R_EndRegistration( void );
CCALL int R_MarkFragments( int numPoints, const vec3_t *points, const vec3_t projection, int maxPoints, vec3_t pointBuffer, int maxFragments, markFragment_t *fragmentBuffer );
CCALL int R_LerpTag( orientation_t *tag, qhandle_t handle, int startFrame, int endFrame, float frac, const char *tagName );
CCALL void R_ModelBounds( qhandle_t handle, vec3_t mins, vec3_t maxs );
CCALL void R_RotatePic ( float x, float y, float w, float h, float s1, float t1, float s2, float t2,float a, qhandle_t hShader );
CCALL void R_RotatePic2 ( float x, float y, float w, float h, float s1, float t1, float s2, float t2,float a, qhandle_t hShader );
CCALL void R_ClearScene( void );

CCALL void R_ClearDecals( void );
CCALL void R_InitDecals( void );
CCALL void R_FreeDecal( int type, int index );

#define DECAL_POLY
typedef struct decalPoly_s 
{
	int					time;
	int					fadetime;
	qhandle_t			shader;
	float				color[4];
	poly_t				poly;
	// define from tr_decals.cpp
#define	MAX_VERTS_ON_DECAL_POLY	10
	polyVert_t			verts[MAX_VERTS_ON_DECAL_POLY];
} decalPoly_t;


CCALL decalPoly_t* R_AllocDecal( int type );

CCALL void R_AddRefEntityToScene( const refEntity_t *ent );
CCALL void R_AddMiniRefEntityToScene( const miniRefEntity_t *miniRefEnt );
CCALL void R_AddPolysToScene( qhandle_t hShader, int numVerts, const polyVert_t *verts, int numPolys );
CCALL void R_AddDecalToScene( qhandle_t decalShader, const vec3_t origin, const vec3_t dir, float orientation, float red, float green, float blue, float alpha, qboolean alphaFade, float radius, qboolean temporary );
CCALL int R_LightForPoint( vec3_t point, vec3_t ambientLight, vec3_t directedLight, vec3_t lightDir );
CCALL void R_AddLightToScene( const vec3_t org, float intensity, float r, float g, float b );
CCALL void R_AddAdditiveLightToScene( const vec3_t org, float intensity, float r, float g, float b );
CCALL void R_RenderScene( const refdef_t *fd );
CCALL void	R_SetColor( const float *rgba );
CCALL void R_StretchPic ( float x, float y, float w, float h, float s1, float t1, float s2, float t2, qhandle_t hShader );
CCALL void R_StretchRaw (int x, int y, int w, int h, int cols, int rows, const byte *data, int client, qboolean dirty);
CCALL void R_UploadCinematic (int cols, int rows, const byte *data, int client, qboolean dirty);
CCALL int R_RegisterFont(const char *psName);
CCALL int R_Font_StrLenPixels( const char *psText, const int iFontHandle, const float fScale );
CCALL int R_Font_StrLenChars(const char *psText);
CCALL int R_Font_HeightPixels(const int iFontHandle, const float fScale);
CCALL void R_Font_DrawString(int ox, int oy, const char *psText, const float *rgba, const int iFontHandle, int iMaxPixelWidth, const float fScale);
CCALL qboolean Language_IsAsian(void);
CCALL qboolean Language_UsesSpaces(void);
CCALL unsigned int AnyLanguage_ReadCharFromString( const char *psText, int *piAdvanceCount, qboolean *pbIsTrailingPunctuation /* = NULL */);
CCALL void R_RemapShader(const char *shaderName, const char *newShaderName, const char *timeOffset);
CCALL qboolean R_GetEntityToken( char *buffer, int size );
CCALL qboolean R_inPVS( const vec3_t p1, const vec3_t p2, byte *mask );
CCALL void R_GetLightStyle(int style, color4ub_t color);
CCALL void R_SetLightStyle(int style, int color);
CCALL void R_GetBModelVerts (int bModel, vec3_t *vec, float *normal);
CCALL void R_SetRangedFog ( float range );
CCALL void R_SetRefractionProperties ( float distortionAlpha, float distortionStretch, qboolean distortionPrePost, qboolean distortionNegate );
CCALL float R_GetDistanceCull( void );
CCALL void R_GetRealRes( int *w, int *h );
CCALL qboolean stub_InitializeWireframeAutomap();
CCALL void stub_R_AddWeatherZone ( vec3_t mins, vec3_t maxs );
CCALL void stub_R_WorldEffectCommand ( const char *cmd );
CCALL void C_LevelLoadBegin(const char *psMapName, ForceReload_e eForceReload);
CCALL void C_LevelLoadEnd( void );
CCALL void Key_SetOverstrikeMode( qboolean state );
CCALL qboolean Key_GetOverstrikeMode( void );
CCALL void Key_SetBinding( int keynum, const char *binding );
CCALL void Key_GetBindingBuf( int keynum, char *buf, int buflen );
CCALL void Key_KeynumToStringBuf( int keynum, char *buf, int buflen );
CCALL void	Cmd_ExecuteText	( int exec_when, const char *text );
CCALL void R_AutomapElevationAdjustment(float newHeight);



CCALL void CL_G2API_ListModelSurfaces( void *ghlInfo );
CCALL void CL_G2API_ListModelBones( void *ghlInfo, int frame ) ;
CCALL void CL_G2API_SetGhoul2ModelIndexes( void *ghoul2, qhandle_t *modelList, qhandle_t *skinList );
CCALL qboolean CL_G2API_HaveWeGhoul2Models( void *ghoul2);
CCALL qboolean CL_G2API_GetBoltMatrix( void *ghoul2, const int modelIndex, const int boltIndex, mdxaBone_t *matrix, const vec3_t angles, const vec3_t position, const int frameNum, qhandle_t *modelList, vec3_t scale );
CCALL qboolean CL_G2API_GetBoltMatrix_NoReconstruct( void *ghoul2, const int modelIndex, const int boltIndex, mdxaBone_t *matrix, const vec3_t angles, const vec3_t position, const int frameNum, qhandle_t *modelList, vec3_t scale );
CCALL qboolean CL_G2API_GetBoltMatrix_NoRecNoRot( void *ghoul2, const int modelIndex, const int boltIndex, mdxaBone_t *matrix, const vec3_t angles, const vec3_t position, const int frameNum, qhandle_t *modelList, vec3_t scale );
CCALL int CL_G2API_InitGhoul2Model( void **ghoul2Ptr, const char *fileName, int modelIndex, qhandle_t customSkin, qhandle_t customShader, int modelFlags, int lodBias );
CCALL qboolean CL_G2API_SetSkin( void *ghoul2, int modelIndex, qhandle_t customSkin, qhandle_t renderSkin ) ;
CCALL void CL_G2API_CollisionDetect( CollisionRecord_t *collRecMap, void* ghoul2, const vec3_t angles, const vec3_t position, int frameNumber, int entNum, vec3_t rayStart, vec3_t rayEnd, vec3_t scale, int traceFlags, int useLod, float fRadius ) ;
CCALL void CL_G2API_CollisionDetectCache( CollisionRecord_t *collRecMap, void* ghoul2, const vec3_t angles, const vec3_t position, int frameNumber, int entNum, vec3_t rayStart, vec3_t rayEnd, vec3_t scale, int traceFlags, int useLod, float fRadius );
CCALL void CL_G2API_CleanGhoul2Models( void **ghoul2Ptr ) ;
CCALL qboolean CL_G2API_SetBoneAngles( void *ghoul2, int modelIndex, const char *boneName, const vec3_t angles, const int flags, const int up, const int right, const int forward, qhandle_t *modelList, int blendTime , int currentTime );
CCALL qboolean CL_G2API_SetBoneAnim( void *ghoul2, const int modelIndex, const char *boneName, const int startFrame, const int endFrame, const int flags, const float animSpeed, const int currentTime, const float setFrame, const int blendTime );
CCALL qboolean CL_G2API_GetBoneAnim( void *ghoul2, const char *boneName, const int currentTime, float *currentFrame, int *startFrame, int *endFrame, int *flags, float *animSpeed, int *modelList, const int modelIndex );
CCALL qboolean CL_G2API_GetBoneFrame( void *ghoul2, const char *boneName, const int currentTime, float *currentFrame, int *modelList, const int modelIndex );
CCALL void CL_G2API_GetGLAName( void *ghoul2, int modelIndex, char *fillBuf );
CCALL int CL_G2API_CopyGhoul2Instance( void *g2From, void *g2To, int modelIndex ) ;
CCALL void CL_G2API_CopySpecificGhoul2Model( void *g2From, int modelFrom, void *g2To, int modelTo );
CCALL void CL_G2API_DuplicateGhoul2Instance( void *g2From, void **g2To );
CCALL qboolean CL_G2API_HasGhoul2ModelOnIndex( void *ghlInfo, int modelIndex );
CCALL qboolean CL_G2API_RemoveGhoul2Model( void *ghlInfo, int modelIndex );
CCALL qboolean CL_G2API_SkinlessModel( void *ghlInfo, int modelIndex );
CCALL int CL_G2API_GetNumGoreMarks( void *ghlInfo, int modelIndex );
CCALL void CL_G2API_AddSkinGore( void *ghlInfo, SSkinGoreData *gore ) ;
CCALL void CL_G2API_ClearSkinGore( void *ghlInfo );
CCALL int CL_G2API_Ghoul2Size( void *ghlInfo );
CCALL int CL_G2API_AddBolt( void *ghoul2, int modelIndex, const char *boneName ) ;
CCALL qboolean CL_G2API_AttachEnt( int *boltInfo, void *ghlInfoTo, int toBoltIndex, int entNum, int toModelNum ) ;
CCALL void CL_G2API_SetBoltInfo( void *ghoul2, int modelIndex, int boltInfo );
CCALL qboolean CL_G2API_SetRootSurface( void *ghoul2, const int modelIndex, const char *surfaceName );
CCALL qboolean CL_G2API_SetSurfaceOnOff( void *ghoul2, const char *surfaceName, const int flags ) ;
CCALL qboolean CL_G2API_SetNewOrigin( void *ghoul2, const int boltIndex );
CCALL qboolean CL_G2API_DoesBoneExist( void *ghoul2, int modelIndex, const char *boneName );
CCALL int CL_G2API_GetSurfaceRenderStatus( void *ghoul2, const int modelIndex, const char *surfaceName );
CCALL int CL_G2API_GetTime( void );
CCALL void CL_G2API_SetTime( int time, int clock );
CCALL void CL_G2API_AbsurdSmoothing( void *ghoul2, qboolean status );
CCALL void CL_G2API_SetRagDoll( void *ghoul2, sharedRagDollParams_t *params );
CCALL void CL_G2API_AnimateG2Models( void *ghoul2, int time, sharedRagDollUpdateParams_t *params );
CCALL qboolean CL_G2API_RagPCJConstraint( void *ghoul2, const char *boneName, vec3_t min, vec3_t max );
CCALL qboolean CL_G2API_RagPCJGradientSpeed( void *ghoul2, const char *boneName, const float speed );
CCALL qboolean CL_G2API_RagEffectorGoal( void *ghoul2, const char *boneName, vec3_t pos );
CCALL qboolean CL_G2API_GetRagBonePos( void *ghoul2, const char *boneName, vec3_t pos, vec3_t entAngles, vec3_t entPos, vec3_t entScale );
CCALL qboolean CL_G2API_RagEffectorKick( void *ghoul2, const char *boneName, vec3_t velocity );
CCALL qboolean CL_G2API_RagForceSolve( void *ghoul2, qboolean force );
CCALL qboolean CL_G2API_SetBoneIKState( void *ghoul2, int time, const char *boneName, int ikState, sharedSetBoneIKStateParams_t *params );
CCALL qboolean CL_G2API_IKMove( void *ghoul2, int time, sharedIKMoveParams_t *params );
CCALL qboolean CL_G2API_RemoveBone( void *ghoul2, const char *boneName, int modelIndex );
CCALL void CL_G2API_AttachInstanceToEntNum( void *ghoul2, int entityNum, qboolean server );
CCALL void CL_G2API_ClearAttachedInstance( int entityNum );
CCALL void CL_G2API_CleanEntAttachments( void );
CCALL qboolean CL_G2API_OverrideServer( void *serverInstance );
CCALL void CL_G2API_GetSurfaceName( void *ghoul2, int surfNumber, int modelIndex, char *fillBuf );
CCALL qboolean CL_G2API_AttachG2Model( void *ghoul2From, int modelIndexFrom, void *ghoul2To, int toBoltIndex, int toModel );


CCALL int  BOTLIB_AddGlobalDefine(char *string);
CCALL int  BOTLIB_FreeSourceHandle(int handle);
CCALL int  BOTLIB_LoadGlobalDefines(const char* filename );
CCALL int  BOTLIB_LoadSourceHandle(const char *filename);
CCALL int  BOTLIB_ReadTokenHandle(int handle, pc_token_t *pc_token);
CCALL void BOTLIB_RemoveAllGlobalDefines( void );
CCALL int  BOTLIB_SourceFileAndLine(int handle, char *filename, int *line);


#endif

