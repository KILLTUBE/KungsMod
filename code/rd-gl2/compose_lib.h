#ifndef COMPOSE_LIB
#define COMPOSE_LIB

#include <qcommon/q_shared.h>

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

#endif