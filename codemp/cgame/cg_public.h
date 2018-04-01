/*
===========================================================================
Copyright (C) 1999 - 2005, Id Software, Inc.
Copyright (C) 2000 - 2013, Raven Software, Inc.
Copyright (C) 2001 - 2013, Activision, Inc.
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

#pragma once

#define	CGAME_API_VERSION		2

#define	CMD_BACKUP			64
#define	CMD_MASK			(CMD_BACKUP - 1)
// allow a lot of command backups for very fast systems
// multiple commands may be combined into a single packet, so this
// needs to be larger than PACKET_BACKUP


#define	MAX_ENTITIES_IN_SNAPSHOT	256

// snapshots are a view of the server at a given time

// Snapshots are generated at regular time intervals by the server,
// but they may not be sent if a client's rate level is exceeded, or
// they may be dropped by the network.
typedef struct snapshot_s {
	int				snapFlags;			// SNAPFLAG_RATE_DELAYED, etc
	int				ping;

	int				serverTime;		// server time the message is valid for (in msec)

	byte			areamask[MAX_MAP_AREA_BYTES];		// portalarea visibility bits

	playerState_t	ps;						// complete information about the current player at this time
	playerState_t	vps; //vehicle I'm riding's playerstate (if applicable) -rww

	int				numEntities;			// all of the entities that need to be presented
	entityState_t	entities[MAX_ENTITIES_IN_SNAPSHOT];	// at the time of this snapshot

	int				numServerCommands;		// text based server commands to execute when this
	int				serverCommandSequence;	// snapshot becomes current
} snapshot_t;

typedef enum cgameEvent_e {
	CGAME_EVENT_NONE=0,
	CGAME_EVENT_TEAMMENU,
	CGAME_EVENT_SCOREBOARD,
	CGAME_EVENT_EDITHUD
} cgameEvent_t;

typedef struct autoMapInput_s {
	float		up;
	float		down;
	float		yaw;
	float		pitch;
	qboolean	goToDefaults;
} autoMapInput_t;

// CG_POINT_CONTENTS
typedef struct TCGPointContents_s {
	vec3_t		mPoint;			// input
	int			mPassEntityNum;	// input
} TCGPointContents;

// CG_GET_BOLT_POS
typedef struct TCGGetBoltData_s {
	vec3_t		mOrigin;		// output
	vec3_t		mAngles;		// output
	vec3_t		mScale;			// output
	int			mEntityNum;		// input
} TCGGetBoltData;

// CG_IMPACT_MARK
typedef struct TCGImpactMark_s {
	int		mHandle;
	vec3_t	mPoint;
	vec3_t	mAngle;
	float	mRotation;
	float	mRed;
	float	mGreen;
	float	mBlue;
	float	mAlphaStart;
	float	mSizeStart;
} TCGImpactMark;

// CG_GET_LERP_ORIGIN
// CG_GET_LERP_ANGLES
// CG_GET_MODEL_SCALE
typedef struct TCGVectorData_s {
	int			mEntityNum;		// input
	vec3_t		mPoint;			// output
} TCGVectorData;

// CG_TRACE/CG_G2TRACE
typedef struct TCGTrace_s {
	trace_t mResult;					// output
	vec3_t	mStart, mMins, mMaxs, mEnd;	// input
	int		mSkipNumber, mMask;			// input
} TCGTrace;

// CG_G2MARK
typedef struct TCGG2Mark_s {
	int			shader;
	float		size;
	vec3_t		start, dir;
} TCGG2Mark;

// CG_INCOMING_CONSOLE_COMMAND
typedef struct TCGIncomingConsoleCommand_s {
	char conCommand[1024];
} TCGIncomingConsoleCommand;

// CG_FX_CAMERASHAKE
typedef struct TCGCameraShake_s {
	vec3_t	mOrigin;					// input
	float	mIntensity;					// input
	int		mRadius;					// input
	int		mTime;						// input
} TCGCameraShake;

// CG_MISC_ENT
typedef struct TCGMiscEnt_s {
	char	mModel[MAX_QPATH];			// input
	vec3_t	mOrigin, mAngles, mScale;	// input
} TCGMiscEnt;

typedef struct TCGPositionOnBolt_s {
	refEntity_t		ent;				// output
	void			*ghoul2;			// input
	int				modelIndex;			// input
	int				boltIndex;			// input
	vec3_t			origin;				// input
	vec3_t			angles;				// input
	vec3_t			modelScale;			// input
} TCGPositionOnBolt;

//ragdoll callback structs -rww
#define RAG_CALLBACK_NONE				0
#define RAG_CALLBACK_DEBUGBOX			1
typedef struct ragCallbackDebugBox_s {
	vec3_t			mins;
	vec3_t			maxs;
	int				duration;
} ragCallbackDebugBox_t;

#define RAG_CALLBACK_DEBUGLINE			2
typedef struct ragCallbackDebugLine_s {
	vec3_t			start;
	vec3_t			end;
	int				time;
	int				color;
	int				radius;
} ragCallbackDebugLine_t;

#define RAG_CALLBACK_BONESNAP			3
typedef struct ragCallbackBoneSnap_s {
	char			boneName[128]; //name of the bone in question
	int				entNum; //index of entity who owns the bone in question
} ragCallbackBoneSnap_t;

#define RAG_CALLBACK_BONEIMPACT			4
typedef struct ragCallbackBoneImpact_s {
	char			boneName[128]; //name of the bone in question
	int				entNum; //index of entity who owns the bone in question
} ragCallbackBoneImpact_t;

#define RAG_CALLBACK_BONEINSOLID		5
typedef struct ragCallbackBoneInSolid_s {
	vec3_t			bonePos; //world coordinate position of the bone
	int				entNum; //index of entity who owns the bone in question
	int				solidCount; //higher the count, the longer we've been in solid (the worse off we are)
} ragCallbackBoneInSolid_t;

#define RAG_CALLBACK_TRACELINE			6
typedef struct ragCallbackTraceLine_s {
	trace_t			tr;
	vec3_t			start;
	vec3_t			end;
	vec3_t			mins;
	vec3_t			maxs;
	int				ignore;
	int				mask;
} ragCallbackTraceLine_t;

#define	MAX_CG_SHARED_BUFFER_SIZE		2048

typedef struct cgameImport_s {
	// common

	int				(*MemoryRemaining)						( void );
	void			(*RegisterSharedMemory)					( char *memory );
	void			(*TrueMalloc)							( void **ptr, int size );
	void			(*TrueFree)								( void **ptr );

	// timing
	int				(*Milliseconds)							( void );
	int				(*RealTime)								( qtime_t *qtime );
	void			(*PrecisionTimerStart)					( void **timer );
	int				(*PrecisionTimerEnd)					( void *timer );

	// cvar
	void			(*Cvar_Register)						( cvar_t *vmCvar, const char *varName, const char *defaultValue, uint32_t flags );
	void			(*Cvar_Set)								( const char *var_name, const char *value );
	void			(*Cvar_Update)							( cvar_t *vmCvar );
	void			(*Cvar_VariableStringBuffer)			( const char *var_name, char *buffer, int bufsize );

	cvar_t *(*GetRealCvar)(const char *var_name, const char *var_value, uint32_t flags, const char *var_desc);

	// command
	void			(*AddCommand)							( const char *cmd_name );
	int				(*Cmd_Argc)								( void );
	void			(*Cmd_Args)								( char *buffer, int bufferLength );
	void			(*Cmd_Argv)								( int arg, char *buffer, int bufferLength );
	void			(*RemoveCommand)						( const char *cmd_name );
	void			(*SendClientCommand)					( const char *cmd );
	void			(*SendConsoleCommand)					( const char *text );

	// filesystem
	void			(*FS_Close)								( fileHandle_t f );
	int				(*FS_GetFileList)						( const char *path, const char *extension, char *listbuf, int bufsize );
	int				(*FS_Open)								( const char *qpath, fileHandle_t *f, fsMode_t mode );
	int				(*FS_Read)								( void *buffer, int len, fileHandle_t f );
	int				(*FS_Write)								( const void *buffer, int len, fileHandle_t f );

	// screen
	void			(*UpdateScreen)							( void );

	// clip model
	clipHandle_t	(*CM_InlineModel)						( int index );
	void			(*CM_LoadMap)							( const char *mapname, qboolean subBSP );
	int				(*CM_NumInlineModels)					( void );
	int				(*CM_PointContents)						( const vec3_t p, clipHandle_t model );
	int				(*CM_RegisterTerrain)					( const char *config );
	clipHandle_t	(*CM_TempModel)							( const vec3_t mins, const vec3_t maxs, int capsule );
	void			(*CM_Trace)								( trace_t *results, const vec3_t start, const vec3_t end, const vec3_t mins, const vec3_t maxs, clipHandle_t model, int brushmask, int capsule );
	int				(*CM_TransformedPointContents)			( const vec3_t p, clipHandle_t model, const vec3_t origin, const vec3_t angles );
	void			(*CM_TransformedTrace)					( trace_t *results, const vec3_t start, const vec3_t end, const vec3_t mins, const vec3_t maxs, clipHandle_t model, int brushmask, const vec3_t origin, const vec3_t angles, int capsule );
	void			(*RMG_Init)								( int terrainID, const char *terrainInfo );

	// sound
	int				(*S_AddLocalSet)						( const char *name, vec3_t listener_origin, vec3_t origin, int entID, int time );
	void			(*S_AddLoopingSound)					( int entityNum, const vec3_t origin, const vec3_t velocity, sfxHandle_t sfx );
	void			(*S_ClearLoopingSounds)					( void );
	int				(*S_GetVoiceVolume)						( int entID );
	void			(*S_MuteSound)							( int entityNum, int entchannel );
	sfxHandle_t		(*S_RegisterSound)						( const char *sample );
	void			(*S_Respatialize)						( int entityNum, const vec3_t origin, matrix3_t axis, int inwater );
	void			(*S_Shutup)								( qboolean shutup );
	void			(*S_StartBackgroundTrack)				( const char *intro, const char *loop, qboolean bReturnWithoutStarting );
	void			(*S_StartLocalSound)					( sfxHandle_t sfx, int channelNum );
	void			(*S_StartSound)							( const vec3_t origin, int entnum, int entchannel, sfxHandle_t sfx );
	void			(*S_StopBackgroundTrack)				( void );
	void			(*S_StopLoopingSound)					( int entityNum );
	void			(*S_UpdateEntityPosition)				( int entityNum, const vec3_t origin );
	void			(*S_UpdateAmbientSet)					( const char *name, vec3_t origin ) ;

	// ambient sound
	void			(*AS_AddPrecacheEntry)					( const char *name );
	sfxHandle_t		(*AS_GetBModelSound)					( const char *name, int stage );
	void			(*AS_ParseSets)							( void );

	// renderer
	void			(*R_AddAdditiveLightToScene)			( const vec3_t org, float intensity, float r, float g, float b );
	void			(*R_AddDecalToScene)					( qhandle_t shader, const vec3_t origin, const vec3_t dir, float orientation, float r, float g, float b, float a, qboolean alphaFade, float radius, qboolean temporary );
	void			(*R_AddLightToScene)					( const vec3_t org, float intensity, float r, float g, float b );
	void			(*R_AddPolysToScene)					( qhandle_t hShader , int numVerts, const polyVert_t *verts, int num );
	void			(*R_AddRefEntityToScene)				( const refEntity_t *re );
	unsigned int	(*R_AnyLanguage_ReadCharFromString)		( const char *psText, int *piAdvanceCount, qboolean *pbIsTrailingPunctuation );
	void			(*R_AutomapElevationAdjustment)			( float newHeight );
	void			(*R_ClearDecals)						( void );
	void			(*R_ClearScene)							( void );
	void			(*R_StretchPic)						( float x, float y, float w, float h, float s1, float t1, float s2, float t2, qhandle_t hShader );	// 0 = white
	void			(*R_RotatePic)						( float x, float y, float w, float h, float s1, float t1, float s2, float t2, float a1, qhandle_t hShader );	// 0 = white
	void			(*R_RotatePic2)						( float x, float y, float w, float h, float s1, float t1, float s2, float t2, float a1, qhandle_t hShader );	// 0 = white
	void			(*R_Font_DrawString)					( int ox, int oy, const char *text, const float *rgba, const int setIndex, int iCharLimit, const float scale );
	int				(*R_Font_HeightPixels)					( const int iFontIndex, const float scale );
	int				(*R_Font_StrLenChars)					( const char *text );
	int				(*R_Font_StrLenPixels)					( const char *text, const int iFontIndex, const float scale );
	void			(*R_GetBModelVerts)						( int bmodelIndex, vec3_t *vec, vec3_t normal );
	float			(*R_GetDistanceCull)					( void );
	qboolean		(*R_GetEntityToken)						( char *buffer, int size );
	void			(*R_GetLightStyle)						( int style, color4ub_t color );
	void			(*R_GetRealRes)							( int *w, int *h );
	qboolean		(*R_InitializeWireframeAutomap)			( void );
	qboolean		(*R_inPVS)								( const vec3_t p1, const vec3_t p2, byte *mask );
	qboolean		(*R_Language_IsAsian)					( void );
	qboolean		(*R_Language_UsesSpaces)				( void );
	int				(*R_LerpTag)							( orientation_t *tag,  qhandle_t model, int startFrame, int endFrame, float frac, const char *tagName );
	int				(*R_LightForPoint)						( vec3_t point, vec3_t ambientLight, vec3_t directedLight, vec3_t lightDir );
	void			(*R_LoadWorld)							( const char *name );
	int				(*R_MarkFragments)						( int numPoints, const vec3_t *points, const vec3_t projection, int maxPoints, vec3_t pointBuffer, int maxFragments, markFragment_t *fragmentBuffer );
	void			(*R_ModelBounds)						( qhandle_t model, vec3_t mins, vec3_t maxs );
	qhandle_t		(*R_RegisterFont)						( const char *fontName );
	qhandle_t		(*R_RegisterModel)						( const char *name );
	qhandle_t		(*R_RegisterShader)						( const char *name );
	qhandle_t		(*R_RegisterShaderNoMip)				( const char *name );
	qhandle_t		(*R_RegisterSkin)						( const char *name );
	void			(*R_RemapShader)						( const char *oldShader, const char *newShader, const char *offsetTime );
	void			(*R_RenderScene)						( const refdef_t *fd );
	void			(*R_SetColor)							( const float *rgba );	// NULL = 1,1,1,1
	void			(*R_SetLightStyle)						( int style, int color );
	void			(*R_SetRangedFog)						( float range );
	void			(*R_SetRefractionProperties)			( float distortionAlpha, float distortionStretch, qboolean distortionPrePost, qboolean distortionNegate );
	void			(*R_WorldEffectCommand)					( const char *cmd );
	void			(*R_InitRendererTerrain)				( const char *info );
	void			(*WE_AddWeatherZone)					( vec3_t mins, vec3_t maxs );

	// client
	void			(*GetCurrentSnapshotNumber)				( int *snapshotNumber, int *serverTime );
	int				(*GetCurrentCmdNumber)					( void );
	qboolean		(*GetDefaultState)						( int index, entityState_t *state );
	void			(*GetGameState)							( gameState_t *gs );
	void			(*GetGlconfig)							( glconfig_t *glconfig );
	qboolean		(*GetServerCommand)						( int serverCommandNumber );
	qboolean		(*GetSnapshot)							( int snapshotNumber, snapshot_t *snapshot );
	qboolean		(*GetUserCmd)							( int cmdNumber, usercmd_t *ucmd );
	void			(*OpenUIMenu)							( int menu );
	void			(*SetClientForceAngle)					( int time, vec3_t angle );
	void			(*SetUserCmdValue)						( int stateValue, float sensitivityScale, float mPitchOverride, float mYawOverride, float mSensitivityOverride, int fpSel, int invenSel, qboolean fighterControls );

	// keys
	int				(*Key_GetCatcher)						( void );
	int				(*Key_GetKey)							( const char *binding );
	qboolean		(*Key_IsDown)							( int keynum );
	void			(*Key_SetCatcher)						( int catcher );

	// preprocessor (botlib_export->PC_***)
	int				(*PC_AddGlobalDefine)					( char *string );
	int				(*PC_FreeSource)						( int handle );
	int				(*PC_LoadGlobalDefines)					( const char *filename );
	int				(*PC_LoadSource)						( const char *filename );
	int				(*PC_ReadToken)							( int handle, pc_token_t *pc_token );
	void			(*PC_RemoveAllGlobalDefines)			( void );
	int				(*PC_SourceFileAndLine)					( int handle, char *filename, int *line );

	// cinematics
	void			(*CIN_DrawCinematic)					( int handle );
	int				(*CIN_PlayCinematic)					( const char *arg, int x, int y, int w, int h, int systemBits );
	e_status		(*CIN_RunCinematic)						( int handle );
	void			(*CIN_SetExtents)						( int handle, int x, int y, int w, int h );
	e_status		(*CIN_StopCinematic)					( int handle );

	// FX
	void			(*FX_AddLine)							( vec3_t start, vec3_t end, float size1, float size2, float sizeParm, float alpha1, float alpha2, float alphaParm, vec3_t sRGB, vec3_t eRGB, float rgbParm, int killTime, qhandle_t shader, int flags );
	int				(*FX_RegisterEffect)					( const char *file );
	void			(*FX_PlayEffect)						( const char *file, vec3_t org, vec3_t fwd, int vol, int rad );
	void			(*FX_PlayEffectID)						( int id, vec3_t org, vec3_t fwd, int vol, int rad, qboolean isPortal );
	void			(*FX_PlayEntityEffectID)				( int id, vec3_t org, matrix3_t axis, const int boltInfo, const int entNum, int vol, int rad );
	qboolean		(*FX_PlayBoltedEffectID)				( int id, vec3_t org, void *pGhoul2, const int boltNum, const int entNum, const int modelNum, int iLooptime, qboolean isRelative );
	void			(*FX_AddScheduledEffects)				( qboolean portal );
	int				(*FX_InitSystem)						( refdef_t *refdef );
	void			(*FX_SetRefDef)							( refdef_t *refdef );
	qboolean		(*FX_FreeSystem)						( void );
	void			(*FX_AdjustTime)						( int time );
	void			(*FX_Draw2DEffects)						( float screenXScale, float screenYScale );
	void			(*FX_AddPoly)							( addpolyArgStruct_t *p );
	void			(*FX_AddBezier)							( addbezierArgStruct_t *p );
	void			(*FX_AddPrimitive)						( effectTrailArgStruct_t *p );
	void			(*FX_AddSprite)							( addspriteArgStruct_t *p );
	void			(*FX_AddElectricity)					( addElectricityArgStruct_t *p );

	// stringed
	qboolean		(*SE_GetStringTextString)				( const char *text, char *buffer, int bufferLength );

	// roff
	qboolean		(*ROFF_Clean)							( void );
	void			(*ROFF_UpdateEntities)					( void );
	int				(*ROFF_Cache)							( char *file );
	qboolean		(*ROFF_Play)							( int entID, int roffID, qboolean doTranslation );
	qboolean		(*ROFF_Purge_Ent)						( int entID );

	// ghoul2
	void			(*G2_ListModelSurfaces)					( void *ghlInfo );
	void			(*G2_ListModelBones)					( void *ghlInfo, int frame );
	void			(*G2_SetGhoul2ModelIndexes)				( void *ghoul2, qhandle_t *modelList, qhandle_t *skinList );
	qboolean		(*G2_HaveWeGhoul2Models)				( void *ghoul2 );
	qboolean		(*G2API_GetBoltMatrix)					( void *ghoul2, const int modelIndex, const int boltIndex, mdxaBone_t *matrix, const vec3_t angles, const vec3_t position, const int frameNum, qhandle_t *modelList, vec3_t scale );
	qboolean		(*G2API_GetBoltMatrix_NoReconstruct)	( void *ghoul2, const int modelIndex, const int boltIndex, mdxaBone_t *matrix, const vec3_t angles, const vec3_t position, const int frameNum, qhandle_t *modelList, vec3_t scale );
	qboolean		(*G2API_GetBoltMatrix_NoRecNoRot)		( void *ghoul2, const int modelIndex, const int boltIndex, mdxaBone_t *matrix, const vec3_t angles, const vec3_t position, const int frameNum, qhandle_t *modelList, vec3_t scale );
	int				(*G2API_InitGhoul2Model)				( void **ghoul2Ptr, const char *fileName, int modelIndex, qhandle_t customSkin, qhandle_t customShader, int modelFlags, int lodBias );
	qboolean		(*G2API_SetSkin)						( void *ghoul2, int modelIndex, qhandle_t customSkin, qhandle_t renderSkin );
	void			(*G2API_CollisionDetect)				( CollisionRecord_t *collRecMap, void* ghoul2, const vec3_t angles, const vec3_t position, int frameNumber, int entNum, vec3_t rayStart, vec3_t rayEnd, vec3_t scale, int traceFlags, int useLod, float fRadius );
	void			(*G2API_CollisionDetectCache)			( CollisionRecord_t *collRecMap, void* ghoul2, const vec3_t angles, const vec3_t position,int frameNumber, int entNum, vec3_t rayStart, vec3_t rayEnd, vec3_t scale, int traceFlags, int useLod, float fRadius );
	void			(*G2API_CleanGhoul2Models)				( void **ghoul2Ptr );
	qboolean		(*G2API_SetBoneAngles)					( void *ghoul2, int modelIndex, const char *boneName, const vec3_t angles, const int flags, const int up, const int right, const int forward, qhandle_t *modelList, int blendTime , int currentTime );
	qboolean		(*G2API_SetBoneAnim)					( void *ghoul2, const int modelIndex, const char *boneName, const int startFrame, const int endFrame, const int flags, const float animSpeed, const int currentTime, const float setFrame, const int blendTime );
	qboolean		(*G2API_GetBoneAnim)					( void *ghoul2, const char *boneName, const int currentTime, float *currentFrame, int *startFrame, int *endFrame, int *flags, float *animSpeed, int *modelList, const int modelIndex );
	qboolean		(*G2API_GetBoneFrame)					( void *ghoul2, const char *boneName, const int currentTime, float *currentFrame, int *modelList, const int modelIndex );
	void			(*G2API_GetGLAName)						( void *ghoul2, int modelIndex, char *fillBuf );
	int				(*G2API_CopyGhoul2Instance)				( void *g2From, void *g2To, int modelIndex );
	void			(*G2API_CopySpecificGhoul2Model)		( void *g2From, int modelFrom, void *g2To, int modelTo );
	void			(*G2API_DuplicateGhoul2Instance)		( void *g2From, void **g2To );
	qboolean		(*G2API_HasGhoul2ModelOnIndex)			( void *ghlInfo, int modelIndex );
	qboolean		(*G2API_RemoveGhoul2Model)				( void *ghlInfo, int modelIndex );
	qboolean		(*G2API_SkinlessModel)					( void *ghlInfo, int modelIndex );
	int				(*G2API_GetNumGoreMarks)				( void *ghlInfo, int modelIndex );
	void			(*G2API_AddSkinGore)					( void *ghlInfo, SSkinGoreData *gore );
	void			(*G2API_ClearSkinGore)					( void *ghlInfo );
	int				(*G2API_Ghoul2Size)						( void *ghlInfo );
	int				(*G2API_AddBolt)						( void *ghoul2, int modelIndex, const char *boneName );
	qboolean		(*G2API_AttachEnt)						( int *boltInfo, void *ghlInfoTo, int toBoltIndex, int entNum, int toModelNum );
	void			(*G2API_SetBoltInfo)					( void *ghoul2, int modelIndex, int boltInfo );
	qboolean		(*G2API_SetRootSurface)					( void *ghoul2, const int modelIndex, const char *surfaceName );
	qboolean		(*G2API_SetSurfaceOnOff)				( void *ghoul2, const char *surfaceName, const int flags );
	qboolean		(*G2API_SetNewOrigin)					( void *ghoul2, const int boltIndex );
	qboolean		(*G2API_DoesBoneExist)					( void *ghoul2, int modelIndex, const char *boneName );
	int				(*G2API_GetSurfaceRenderStatus)			( void *ghoul2, const int modelIndex, const char *surfaceName );
	int				(*G2API_GetTime)						( void );
	void			(*G2API_SetTime)						( int time, int clock );
	void			(*G2API_AbsurdSmoothing)				( void *ghoul2, qboolean status );
	void			(*G2API_SetRagDoll)						( void *ghoul2, sharedRagDollParams_t *params );
	void			(*G2API_AnimateG2Models)				( void *ghoul2, int time, sharedRagDollUpdateParams_t *params );
	qboolean		(*G2API_RagPCJConstraint)				( void *ghoul2, const char *boneName, vec3_t min, vec3_t max );
	qboolean		(*G2API_RagPCJGradientSpeed)			( void *ghoul2, const char *boneName, const float speed );
	qboolean		(*G2API_RagEffectorGoal)				( void *ghoul2, const char *boneName, vec3_t pos );
	qboolean		(*G2API_GetRagBonePos)					( void *ghoul2, const char *boneName, vec3_t pos, vec3_t entAngles, vec3_t entPos, vec3_t entScale );
	qboolean		(*G2API_RagEffectorKick)				( void *ghoul2, const char *boneName, vec3_t velocity );
	qboolean		(*G2API_RagForceSolve)					( void *ghoul2, qboolean force );
	qboolean		(*G2API_SetBoneIKState)					( void *ghoul2, int time, const char *boneName, int ikState, sharedSetBoneIKStateParams_t *params );
	qboolean		(*G2API_IKMove)							( void *ghoul2, int time, sharedIKMoveParams_t *params );
	qboolean		(*G2API_RemoveBone)						( void *ghoul2, const char *boneName, int modelIndex );
	void			(*G2API_AttachInstanceToEntNum)			( void *ghoul2, int entityNum, qboolean server );
	void			(*G2API_ClearAttachedInstance)			( int entityNum );
	void			(*G2API_CleanEntAttachments)			( void );
	qboolean		(*G2API_OverrideServer)					( void *serverInstance );
	void			(*G2API_GetSurfaceName)					( void *ghoul2, int surfNumber, int modelIndex, char *fillBuf );

	struct {
		float			(*R_Font_StrLenPixels)					( const char *text, const int iFontIndex, const float scale );
	} ext;
} cgameImport_t;

//linking of cgame library
typedef void (QDECL *GetCGameAPI_t)( int apiVersion, cgameImport_t *import );
