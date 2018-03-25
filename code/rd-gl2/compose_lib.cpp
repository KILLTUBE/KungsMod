#include "compose_lib.h"

#include <tr_local.h>

#if 1

void				FS_FreeFile						( void *buffer ) {
	ri.FS_FreeFile(buffer);
}

void				FS_FreeFileList					( char **fileList ) {
	ri.FS_FreeFileList(fileList);
}

int					FS_Read							( void *buffer, int len, fileHandle_t f ) {
	return ri.FS_Read(buffer, len, f);
}

long				FS_ReadFile						( const char *qpath, void **buffer ) {
	return ri.FS_ReadFile(qpath, buffer);
}

void				FS_FCloseFile					( fileHandle_t f ) {
	ri.FS_FCloseFile(f);
}

long				FS_FOpenFileRead				( const char *qpath, fileHandle_t *file, qboolean uniqueFILE ) {
	return ri.FS_FOpenFileRead(qpath, file, uniqueFILE);
}

fileHandle_t		FS_FOpenFileWrite				( const char *qpath, qboolean safe ) {
	return ri.FS_FOpenFileWrite(qpath, safe);
}

int					FS_FOpenFileByMode				( const char *qpath, fileHandle_t *f, fsMode_t mode ) {
	return ri.FS_FOpenFileByMode(qpath, f, mode);
}

qboolean			FS_FileExists					( const char *file ) {
	return ri.FS_FileExists(file);
}

int					FS_FileIsInPAK					( const char *filename ) {
	return ri.FS_FileIsInPAK(filename);
}

char **				FS_ListFiles					( const char *directory, const char *extension, int *numfiles ) {
	return ri.FS_ListFiles(directory, extension, numfiles);
}

int					FS_Write						( const void *buffer, int len, fileHandle_t f ) {
	return ri.FS_Write(buffer, len, f);
}

void				FS_WriteFile					( const char *qpath, const void *buffer, int size ) {
	ri.FS_WriteFile(qpath, buffer, size);
}
#endif


#if 1

void		CM_DrawDebugSurface				( void (*drawPoly)( int color, int numPoints, float *points ) ) {
	ri.CM_DrawDebugSurface(drawPoly);
}

bool		CM_CullWorldBox					( const cplane_t *frustrum, const vec3pair_t bounds ) {
	return ri.CM_CullWorldBox(frustrum, bounds);
}

byte*		CM_ClusterPVS					( int cluster ) {
	return ri.CM_ClusterPVS(cluster);
}

int			CM_PointContents					( const vec3_t p, clipHandle_t model ) {
	return ri.CM_PointContents(p, model);
}

void		S_RestartMusic					( void ) {
	ri.S_RestartMusic();
}

qboolean	SND_RegisterAudio_LevelLoadEnd	( qboolean bDeleteEverythingNotUsedThisLevel ) {
	return ri.SND_RegisterAudio_LevelLoadEnd(bDeleteEverythingNotUsedThisLevel);
}

e_status	CIN_RunCinematic					( int handle ) {
	return ri.CIN_RunCinematic(handle);
}

int			CIN_PlayCinematic				( const char *arg0, int xpos, int ypos, int width, int height, int bits, const char *psAudioFile /* = NULL */ ) {
	return ri.CIN_PlayCinematic(arg0, xpos, ypos, width, height, bits, psAudioFile);
}

void		CIN_UploadCinematic				( int handle ) {
	return ri.CIN_UploadCinematic(handle);
}


// window handling
window_t		WIN_Init                        ( const windowDesc_t *desc, glconfig_t *glConfig ) {
	return ri.WIN_Init(desc, glConfig);
}

void			WIN_SetGamma					( glconfig_t *glConfig, byte red[256], byte green[256], byte blue[256] ) {
	ri.WIN_SetGamma(glConfig, red, green, blue);
}

void			WIN_Present						( window_t *window ) {
	ri.WIN_Present(window);
}

void            WIN_Shutdown                    ( void ) {
	ri.WIN_Shutdown();
}


// OpenGL-specific
void *			GL_GetProcAddress				( const char *name ) {
	return ri.GL_GetProcAddress(name);
}

qboolean		GL_ExtensionSupported			( const char *extension ) {
	return ri.GL_ExtensionSupported(extension);
}

CMiniHeap *		GetG2VertSpaceServer			( void ) {
	return ri.GetG2VertSpaceServer();
}


// Persistent data store
bool			PD_Store							( const char *name, const void *data, size_t size ) {
	return ri.PD_Store(name, data, size);
}

const void *	PD_Load							( const char *name, size_t *size ) {
	return ri.PD_Load(name, size);
}


// ============= NOT IN MP BEYOND THIS POINT
void				SV_Trace						( trace_t *results, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end, const int passEntityNum, const int contentmask, const EG2_Collision eG2TraceType, const int useLod ) {
	ri.SV_Trace(results, start, mins, maxs, end, passEntityNum, contentmask, eG2TraceType, useLod);
}

#endif