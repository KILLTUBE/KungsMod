#ifndef UI_ONLY_C_DEFINES
#define UI_ONLY_C_DEFINES

#include "ui_local.h"


// C only version of c++ tr_local.h header...
void *R_GetCommandBuffer( int bytes );
void RB_ExecuteRenderCommands( const void *data );
void R_IssuePendingRenderCommands( void );
//void R_AddDrawSurfCmd( drawSurf_t *drawSurfs, int numDrawSurfs );
void R_AddCapShadowmapCmd( int dlight, int cubeSide );
void R_AddConvolveCubemapCmd( int cubemap );
void R_AddPostProcessCmd (void);
qhandle_t R_BeginTimedBlockCmd( const char *name );
void R_EndTimedBlockCmd( qhandle_t timerHandle );
void RE_SetColor( const float *rgba );
void RE_StretchPic ( float x, float y, float w, float h, float s1, float t1, float s2, float t2, qhandle_t hShader );
void RE_RotatePic ( float x, float y, float w, float h, float s1, float t1, float s2, float t2, float a, qhandle_t hShader );
void RE_RotatePic2 ( float x, float y, float w, float h, float s1, float t1, float s2, float t2,float a, qhandle_t hShader );
void RE_BeginFrame( stereoFrame_t stereoFrame );
void RE_EndFrame( int *frontEndMsec, int *backEndMsec );
void RE_TakeVideoFrame( int width, int height, byte *captureBuffer, byte *encodeBuffer, qboolean motionJpeg );





// C only version of client.h ...
void CL_InitUI( void );
void CL_ShutdownUI( void );
int Key_GetCatcher( void );
CCALL qboolean Key_IsDown( int keynum );
void Key_SetCatcher( int catcher );
void LAN_LoadCachedServers();
void LAN_SaveServersToCache();


// C only version of qcommon.h...
CCALL int		Cmd_Argc (void);
CCALL char	*Cmd_Argv (int arg);
CCALL void	Cmd_ArgvBuffer( int arg, char *buffer, int bufferLength );
CCALL char	*Cmd_Args (void);
CCALL char	*Cmd_ArgsFrom( int arg );
CCALL void	Cmd_ArgsBuffer( char *buffer, int bufferLength );
CCALL void	Cmd_ArgsFromBuffer( int arg, char *buffer, int bufferLength );
CCALL char	*Cmd_Cmd (void);

float Cvar_VariableValue( const char *var_name );
int Cvar_VariableIntegerValue( const char *var_name );
char *Cvar_VariableString( const char *var_name );
void Cvar_VariableStringBuffer( const char *var_name, char *buffer, int bufsize );


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
CCALL void			R_DrawStretchPic		( float x, float y, float w, float h, float s1, float t1, float s2, float t2, qhandle_t hShader );
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
CCALL void			R_ShaderNameFromIndex	( char *name, int index );


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


#endif