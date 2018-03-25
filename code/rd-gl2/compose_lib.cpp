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