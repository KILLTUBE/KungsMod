#include "compose_lib.h"

#include "tr_local.h"

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

#if 1
int					SV_PointContents				( const vec3_t p, clipHandle_t model ) {
	return ri.SV_PointContents(p, model);
}

qboolean			CM_DeleteCachedMap				( qboolean bGuaranteedOkToDelete ) {
	return ri.CM_DeleteCachedMap(bGuaranteedOkToDelete);
}

qboolean			CL_IsRunningInGameCinematic		( void ) {
	return ri.CL_IsRunningInGameCinematic();
}

void*				gpvCachedMapDiskImage			( void ) {
	return ri.gpvCachedMapDiskImage();
}

char*				gsCachedMapDiskImage			( void ) {
	return ri.gsCachedMapDiskImage();
}

qboolean			*gbUsingCachedMapDataRightNow	( void ) {
	return ri.gbUsingCachedMapDataRightNow();
}

qboolean			*gbAlreadyDoingLoad				( void ) {
	return ri.gbAlreadyDoingLoad();
}

int					func_com_frameTime					( void ) {
	return ri.com_frameTime();
}

int					Key_GetCatcher					() {
	return ri.Key_GetCatcher();
}

const char			*Clipboard_Get					() {
	return ri.Clipboard_Get();
}

void				Clipboard_Set					(const char *text) {
	return ri.Clipboard_Set(text);
}

#endif


#if 1


int					Milliseconds					( void ) {
	return ri.Milliseconds();
}

void				Hunk_ClearToMark				( void ) {
	ri.Hunk_ClearToMark();
}

void*				Malloc							( int iSize, memtag_t eTag, qboolean zeroIt, int iAlign ) {
	return ri.Malloc(iSize, eTag, zeroIt, iAlign);
}

int					Z_Free							( void *memory ) {
	return ri.Z_Free(memory);
}

int					Z_MemSize						( memtag_t eTag ) {
	return ri.Z_MemSize(eTag);
}

void				Z_MorphMallocTag				( void *pvBuffer, memtag_t eDesiredTag ) {
	ri.Z_MorphMallocTag(pvBuffer, eDesiredTag);
}

void				Cmd_ExecuteString				( const char *text ) {
	ri.Cmd_ExecuteString(text);
}

int					Cmd_Argc						( void ) {
	return ri.Cmd_Argc();
}

char *				Cmd_Argv						( int arg ) {
	return ri.Cmd_Argv(arg);
}

void				Cmd_ArgsBuffer					( char *buffer, int bufferLength ) {
	ri.Cmd_ArgsBuffer(buffer, bufferLength);
}

void				Cmd_AddCommand					( const char *cmd_name, xcommand_t function ) {
	ri.Cmd_AddCommand(cmd_name, function);
}

void				Cmd_RemoveCommand				( const char *cmd_name ) {
	ri.Cmd_RemoveCommand(cmd_name);
}

void				Cvar_Set						( const char *var_name, const char *value ) {
	ri.Cvar_Set(var_name, value);
}

cvar_t *			Cvar_Get						( const char *var_name, const char *value, int flags ) {
	return ri.Cvar_Get(var_name, value, flags);
}

void				Cvar_SetValue					( const char *name, float value ) {
	ri.Cvar_SetValue(name, value);
}

void				Cvar_CheckRange					( cvar_t *cv, float minVal, float maxVal, qboolean shouldBeIntegral ) {
	ri.Cvar_CheckRange(cv, minVal, maxVal, shouldBeIntegral);
}

void				Cvar_VariableStringBuffer		( const char *var_name, char *buffer, int bufsize ) {
	ri.Cvar_VariableStringBuffer(var_name, buffer, bufsize);
}

char *				Cvar_VariableString				( const char *var_name ) {
	return ri.Cvar_VariableString(var_name);
}

float				Cvar_VariableValue				( const char *var_name ) {
	return ri.Cvar_VariableValue(var_name);
}

int					Cvar_VariableIntegerValue		( const char *var_name ) {
	return ri.Cvar_VariableIntegerValue(var_name);
}

qboolean			LowPhysicalMemory				( void ) {
	return ri.LowPhysicalMemory();
}

const char*			SE_GetString					( const char *reference ) {
	return ri.SE_GetString(reference);
}

#endif

ojk::ISavedGame* get_saved_game() {
	return ri.get_saved_game();
}

void R_Printf(int printLevel, const char *fmt, ...) {
	char buf[4096];
	va_list args;
	va_start (args, fmt);
	vsnprintf(buf, sizeof(buf), fmt, args);
	va_end(args);
	ri.Printf(printLevel, buf);
}

void R_Error(int errorLevel, const char *fmt, ...) {
	char buf[4096];
	va_list args;
	va_start (args, fmt);
	vsnprintf(buf, sizeof(buf), fmt, args);
	va_end(args);
	ri.Error(errorLevel, buf);
}