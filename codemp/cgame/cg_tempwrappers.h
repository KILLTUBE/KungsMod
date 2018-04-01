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


#endif