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

CCALL qhandle_t SV_RE_RegisterSkin( const char *name );

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


#endif