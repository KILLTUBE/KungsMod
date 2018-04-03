#ifndef UI_ONLY_C_DEFINES
#define UI_ONLY_C_DEFINES

#include "ui_local.h"


// C only version of c++ tr_local.h header...
CCALL void *R_GetCommandBuffer( int bytes );
CCALL void RB_ExecuteRenderCommands( const void *data );
CCALL void R_IssuePendingRenderCommands( void );
//void R_AddDrawSurfCmd( drawSurf_t *drawSurfs, int numDrawSurfs );
CCALL void R_AddCapShadowmapCmd( int dlight, int cubeSide );
CCALL void R_AddConvolveCubemapCmd( int cubemap );
CCALL void R_AddPostProcessCmd (void);
CCALL qhandle_t R_BeginTimedBlockCmd( const char *name );
CCALL void R_EndTimedBlockCmd( qhandle_t timerHandle );
CCALL void R_SetColor( const float *rgba );
CCALL void R_StretchPic ( float x, float y, float w, float h, float s1, float t1, float s2, float t2, qhandle_t hShader );
CCALL void R_RotatePic ( float x, float y, float w, float h, float s1, float t1, float s2, float t2, float a, qhandle_t hShader );
CCALL void R_RotatePic2 ( float x, float y, float w, float h, float s1, float t1, float s2, float t2,float a, qhandle_t hShader );
CCALL void R_BeginFrame( stereoFrame_t stereoFrame );
CCALL void R_EndFrame( int *frontEndMsec, int *backEndMsec );
CCALL void R_TakeVideoFrame( int width, int height, byte *captureBuffer, byte *encodeBuffer, qboolean motionJpeg );





// C only version of client.h ...
CCALL void CL_InitUI( void );
CCALL void CL_ShutdownUI( void );
CCALL int Key_GetCatcher( void );
CCALL qboolean Key_IsDown( int keynum );
CCALL void Key_SetCatcher( int catcher );
CCALL void LAN_LoadCachedServers();
CCALL void LAN_SaveServersToCache();
CCALL void Key_ClearStates( void );


// C only version of qcommon.h...
CCALL int		Cmd_Argc (void);
CCALL char	*Cmd_Argv (int arg);
CCALL void	Cmd_ArgvBuffer( int arg, char *buffer, int bufferLength );
CCALL char	*Cmd_Args (void);
CCALL char	*Cmd_ArgsFrom( int arg );
CCALL void	Cmd_ArgsBuffer( char *buffer, int bufferLength );
CCALL void	Cmd_ArgsFromBuffer( int arg, char *buffer, int bufferLength );
CCALL char	*Cmd_Cmd (void);

CCALL float Cvar_VariableValue( const char *var_name );
CCALL int Cvar_VariableIntegerValue( const char *var_name );
CCALL char *Cvar_VariableString( const char *var_name );
CCALL void Cvar_VariableStringBuffer( const char *var_name, char *buffer, int bufsize );


CCALL cvar_t *Cvar_SetValue( const char *var_name, float value);

CCALL int				PC_AddGlobalDefine					( char *define );
CCALL int				PC_FreeSource						( int handle );
CCALL int				PC_LoadGlobalDefines					( const char* filename );
CCALL int				PC_LoadSource						( const char *filename );
CCALL int				PC_ReadToken							( int handle, pc_token_t *pc_token );
CCALL void			PC_RemoveAllGlobalDefines			( void );
CCALL int				PC_SourceFileAndLine					( int handle, char *filename, int *line );


CCALL qboolean CL_SE_GetStringTextString( const char *text, char *buffer, int bufferLength );


CCALL void UI_SaberLoadParms( void );
CCALL void UI_CacheSaberGlowGraphics( void );
CCALL void UI_SaberDrawBlades( itemDef_t *item, vec3_t origin, vec3_t angles );

EXTERNC qboolean	ui_saber_parms_parsed;

CCALL unsigned int R_AnyLanguage_ReadCharFromString( const char *psText, int *piAdvanceCount, qboolean *pbIsTrailingPunctuation );

CCALL qboolean	 R_Language_IsAsian					( void );
CCALL qboolean	 R_Language_UsesSpaces				( void );
CCALL unsigned int R_AnyLanguage_ReadCharFromString	( const char *psText, int *piAdvanceCount, qboolean *pbIsTrailingPunctuation );




CCALL void			R_AddLightToScene		( const vec3_t org, float intensity, float r, float g, float b );
CCALL void			R_AddPolysToScene		( qhandle_t hShader, int numVerts, const polyVert_t *verts, int num );
CCALL void			R_AddRefEntityToScene	( const refEntity_t *re );
CCALL void			R_ClearScene			( void );
CCALL void			R_StretchPic		( float x, float y, float w, float h, float s1, float t1, float s2, float t2, qhandle_t hShader );
CCALL int			R_Font_StrLenPixels		( const char *text, const int iFontIndex, const float scale );
CCALL int			R_Font_StrLenChars		( const char *text );
CCALL int			R_Font_HeightPixels		( const int iFontIndex, const float scale );
CCALL void			R_Font_DrawString		( int ox, int oy, const char *text, const float *rgba, const int setIndex, int iCharLimit, const float scale );
CCALL int			R_LerpTag				( orientation_t *tag, clipHandle_t mod, int startFrame, int endFrame, float frac, const char *tagName );
CCALL void			R_ModelBounds			( clipHandle_t model, vec3_t mins, vec3_t maxs );
CCALL qhandle_t		R_RegisterModel			( const char *name );
CCALL qhandle_t		R_RegisterSkin			( const char *name );
CCALL qhandle_t		R_RegisterShaderNoMip	( const char *name );
CCALL qhandle_t		R_RegisterFont			( const char *fontName );
CCALL void			R_RemapShader			( const char *oldShader, const char *newShader, const char *timeOffset );
CCALL void			R_RenderScene			( const refdef_t *fd );
CCALL void			R_SetColor				( const float *rgba );
//CCALL void			R_ShaderNameFromIndex	( char *name, int index );


CCALL void		G2_ListModelSurfaces			( void *ghlInfo );
CCALL void		G2_ListModelBones				( void *ghlInfo, int frame );
CCALL void		G2_SetGhoul2ModelIndexes		( void *ghoul2, qhandle_t *modelList, qhandle_t *skinList );
CCALL qboolean	G2_HaveWeGhoul2Models			( void *ghoul2 );

CCALL qboolean		G2API_GetBoltMatrix					( void *ghoul2, const int modelIndex, const int boltIndex, mdxaBone_t *matrix, const vec3_t angles, const vec3_t position, const int frameNum, qhandle_t *modelList, vec3_t scale );
CCALL qboolean		G2API_GetBoltMatrix_NoReconstruct	( void *ghoul2, const int modelIndex, const int boltIndex, mdxaBone_t *matrix, const vec3_t angles, const vec3_t position, const int frameNum, qhandle_t *modelList, vec3_t scale );
CCALL qboolean		G2API_GetBoltMatrix_NoRecNoRot		( void *ghoul2, const int modelIndex, const int boltIndex, mdxaBone_t *matrix, const vec3_t angles, const vec3_t position, const int frameNum, qhandle_t *modelList, vec3_t scale );
CCALL int			G2API_InitGhoul2Model				( void **ghoul2Ptr, const char *fileName, int modelIndex, qhandle_t customSkin, qhandle_t customShader, int modelFlags, int lodBias );
CCALL void			G2API_CollisionDetect				( CollisionRecord_t *collRecMap, void* ghoul2, const vec3_t angles, const vec3_t position, int frameNumber, int entNum, vec3_t rayStart, vec3_t rayEnd, vec3_t scale, int traceFlags, int useLod, float fRadius );
CCALL void			G2API_CollisionDetectCache			( CollisionRecord_t *collRecMap, void* ghoul2, const vec3_t angles, const vec3_t position, int frameNumber, int entNum, vec3_t rayStart, vec3_t rayEnd, vec3_t scale, int traceFlags, int useLod, float fRadius );
CCALL qboolean		G2API_SetSkin						( void *ghoul2, int modelIndex, qhandle_t customSkin, qhandle_t renderSkin );
CCALL void			G2API_CleanGhoul2Models				( void **ghoul2Ptr );

CCALL qboolean G2API_HasGhoul2ModelOnIndex( void *ghlInfo, int modelIndex );
CCALL int G2API_AddBolt( void *ghoul2, int modelIndex, const char *boneName );
CCALL qboolean G2API_RemoveGhoul2Model( void *ghlInfo, int modelIndex );
CCALL qboolean G2API_AttachG2Model( void *ghoul2From, int modelIndexFrom, void *ghoul2To, int toBoltIndex, int toModel );

CCALL void CL_G2API_SetTime( int time, int clock );

CCALL cvar_t *Cvar_Set( const char *var_name, const char *value);
CCALL cvar_t *Cvar_Get( const char *var_name, const char *var_value, uint32_t flags, const char *var_desc );

CCALL void	Cbuf_ExecuteText	( int exec_when, const char *text );
CCALL void	Cmd_ExecuteText	( int exec_when, const char *text );

CCALL int		FS_FOpenFileByMode( const char *qpath, fileHandle_t *f, fsMode_t mode );
CCALL void FS_FCloseFile( fileHandle_t f );
CCALL int FS_Write( const void *buffer, int len, fileHandle_t h );
CCALL int FS_Read( void *buffer, int len, fileHandle_t f );
CCALL int	FS_GetFileList(  const char *path, const char *extension, char *listbuf, int bufsize );



CCALL int GetConfigString(int index, char *buf, int size);
CCALL void CL_GetClientState( uiClientState_t *state );
CCALL void	Cvar_Register( cvar_t *vmCvar, const char *varName, const char *defaultValue, uint32_t flags );

CCALL sfxHandle_t	S_RegisterSound( const char *name);
CCALL void S_StartLocalSound( sfxHandle_t sfxHandle, int channelNum );
CCALL void S_StartBackgroundTrack( const char *intro, const char *loop, qboolean bCalledByCGameStart );
CCALL void S_StopBackgroundTrack( void );

CCALL int SE_GetNumLanguages(void);

CCALL void CL_GetGlconfig( glconfig_t *config );

CCALL void Key_SetOverstrikeMode( qboolean state );
CCALL qboolean Key_GetOverstrikeMode( void );
CCALL void Key_SetBinding( int keynum, const char *binding );
CCALL void Key_GetBindingBuf( int keynum, char *buf, int buflen );
CCALL void Key_KeynumToStringBuf( int keynum, char *buf, int buflen );

CCALL int Com_RealTime(qtime_t *qtime);

#include "client/cl_lan.h"

#endif