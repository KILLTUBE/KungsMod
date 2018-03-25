#ifndef COMPOSE_LIB
#define COMPOSE_LIB

#include <qcommon/q_shared.h>
#include <sys/sys_public.h>
#include <qcommon/MiniHeap.h>

void				FS_FreeFile						( void *buffer );
void				FS_FreeFileList					( char **fileList );
int					FS_Read							( void *buffer, int len, fileHandle_t f );
long				FS_ReadFile						( const char *qpath, void **buffer );
void				FS_FCloseFile					( fileHandle_t f );
long				FS_FOpenFileRead				( const char *qpath, fileHandle_t *file, qboolean uniqueFILE );
fileHandle_t		FS_FOpenFileWrite				( const char *qpath, qboolean safe );
int					FS_FOpenFileByMode				( const char *qpath, fileHandle_t *f, fsMode_t mode );
qboolean			FS_FileExists					( const char *file );
int					FS_FileIsInPAK					( const char *filename );
char **				FS_ListFiles					( const char *directory, const char *extension, int *numfiles );
int					FS_Write						( const void *buffer, int len, fileHandle_t f );
void				FS_WriteFile					( const char *qpath, const void *buffer, int size );


void				CM_DrawDebugSurface				( void (*drawPoly)( int color, int numPoints, float *points ) );
bool				CM_CullWorldBox					( const cplane_t *frustrum, const vec3pair_t bounds );
byte*				CM_ClusterPVS					( int cluster );
int					CM_PointContents				( const vec3_t p, clipHandle_t model );
void				S_RestartMusic					( void );
qboolean			SND_RegisterAudio_LevelLoadEnd	( qboolean bDeleteEverythingNotUsedThisLevel );
e_status			CIN_RunCinematic				( int handle );
int					CIN_PlayCinematic				( const char *arg0, int xpos, int ypos, int width, int height, int bits, const char *psAudioFile /* = NULL */ );
void				CIN_UploadCinematic				( int handle );

// window handling
window_t		WIN_Init		( const windowDesc_t *desc, glconfig_t *glConfig );
void			WIN_SetGamma	( glconfig_t *glConfig, byte red[256], byte green[256], byte blue[256] );
void			WIN_Present		( window_t *window );
void            WIN_Shutdown	( void );

// OpenGL-specific
void *			GL_GetProcAddress			( const char *name );
qboolean		GL_ExtensionSupported		( const char *extension );

CMiniHeap *			GetG2VertSpaceServer		( void );

// Persistent data store
bool			PD_Store						( const char *name, const void *data, size_t size );
const void *	PD_Load							( const char *name, size_t *size );

// ============= NOT IN MP BEYOND THIS POINT
void				SV_Trace							( trace_t *results, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end, const int passEntityNum, const int contentmask, const EG2_Collision eG2TraceType, const int useLod );

#endif