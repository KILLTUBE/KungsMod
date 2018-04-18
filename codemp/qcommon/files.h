#ifndef FILES_H
#define FILES_H
#include "include_ccall.h"
//#include "q_shared.h"
//#include "qcommon.h"
//#include "minizip/unzip.h"

// gnah, was caused by C/C++ mixing... still gotta convert everything to C++ :S
// ripped from q_shared.h, for some reason it doesnt include atm...
//typedef int32_t qhandle_t, thandle_t, fxHandle_t, sfxHandle_t, fileHandle_t, clipHandle_t;
//#define	MAX_OSPATH			256		// max length of a filesystem pathname

#define MAX_ZPATH			256
#define	MAX_SEARCH_PATHS	4096
#define MAX_FILEHASH_SIZE	1024

typedef struct fileInPack_s {
	char					*name;		// name of the file
	unsigned long			pos;		// file info position in zip
	unsigned long			len;		// uncompress file size
	struct	fileInPack_s*	next;		// next file in the hash
} fileInPack_t;



typedef struct directory_s {
	char		path[MAX_OSPATH];		// c:\jediacademy\gamedata
	char		fullpath[MAX_OSPATH];	// c:\jediacademy\gamedata\base
	char		gamedir[MAX_OSPATH];	// base
} directory_t;


CCALL qboolean FS_WriteToTemporaryFile(const void *data,size_t dataLength,char **tempFilePath);
#if defined(MACOS_X)
bool FS_LoadMachOBundle(const char *name);
#endif
CCALL const char *FS_GetCurrentGameDir(qboolean emptybase);
//void FS_FilenameCompletion(const char *dir,const char *ext,qboolean stripExt,callbackFunc_t callback,qboolean allowNonPureFilesOnDisk);
fileHandle_t FS_FOpenFileWrite( const char *filename, qboolean safe );
CCALL int FS_FOpenFileByMode(const char *qpath,fileHandle_t *f,fsMode_t mode);
CCALL qboolean FS_ConditionalRestart(int checksumFeed);
CCALL void FS_InitFilesystem(void);
CCALL void FS_PureServerSetReferencedPaks(const char *pakSums,const char *pakNames);
CCALL void FS_Restart(int checksumFeed);
CCALL void FS_PureServerSetLoadedPaks(const char *pakSums,const char *pakNames);
CCALL void FS_ClearPakReferences(int flags);
CCALL const char *FS_ReferencedPakNames(void);
CCALL const char *FS_ReferencedPakPureChecksums(void);
CCALL const char *FS_ReferencedPakChecksums(void);
CCALL const char *FS_LoadedPakPureChecksums(void);
CCALL const char *FS_LoadedPakNames(void);
CCALL const char *FS_LoadedPakChecksums(void);
CCALL void FS_Startup(const char *gameName);
CCALL void FS_UpdateGamedir(void);
CCALL void FS_Shutdown(qboolean closemfp);
CCALL qboolean FS_ComparePaks(char *neededpaks,int len,qboolean dlstring);
CCALL qboolean FS_CheckDirTraversal(const char *checkdir);
CCALL qboolean FS_idPak(char *pak,char *base);
CCALL void FS_Which_f(void);
CCALL void FS_TouchFile_f(void);
CCALL void FS_Path_f(void);
CCALL void FS_NewDir_f(void);
CCALL void FS_SortFileList(char **filelist,int numfiles);
CCALL int FS_PathCmp(const char *s1,const char *s2);
CCALL void FS_ConvertPath(char *s);
CCALL void FS_Dir_f(void);
//CCALL const char *SE_GetString(const char *psPackageAndStringReference);
CCALL int FS_GetModList(char *listbuf,int bufsize);
CCALL int FS_GetFileList(const char *path,const char *extension,char *listbuf,int bufsize);
CCALL char **FS_ListFiles(const char *path,const char *extension,int *numfiles);
CCALL char **FS_ListFilteredFiles(const char *path,const char *extension,char *filter,int *numfiles);
CCALL qboolean FS_CompareZipChecksum(const char *zipfile);
//void FS_FreePak(pack_t *thepak);
CCALL void FS_WriteFile(const char *qpath,const void *buffer,int size);
CCALL void FS_FreeFile(void *buffer);
CCALL void FS_Flush(fileHandle_t f);
CCALL long FS_ReadFile(const char *qpath,void **buffer);
CCALL int FS_FileIsInPAK(const char *filename,int *pChecksum);
CCALL int FS_FTell(fileHandle_t f);
CCALL int FS_Seek(fileHandle_t f,long offset,int origin);
CCALL void QDECL FS_Printf(fileHandle_t h,const char *fmt,...);
CCALL int FS_Write(const void *buffer,int len,fileHandle_t h);
CCALL int FS_Read(void *buffer,int len,fileHandle_t f);
CCALL qboolean FS_FindPureDLL(const char *name);
CCALL long FS_FOpenFileRead(const char *filename,fileHandle_t *file,qboolean uniqueFILE);
extern qboolean com_fullyInitialized;
//bool FS_FileCacheable(const char *const filename);
#if defined(_WIN32)
//bool Sys_FileOutOfDate(LPCSTR psFinalFileName,LPCSTR psDataFileName);
//bool Sys_GetFileTime(LPCSTR psFileName,FILETIME&ft);
#endif
CCALL qboolean FS_IsDemoExt(const char *filename,int namelen);
CCALL qboolean FS_IsExt(const char *filename,const char *ext,int namelen);
CCALL qboolean FS_FilenameCompare(const char *s1,const char *s2);
CCALL fileHandle_t FS_FOpenFileAppend(const char *filename);
//fileHandle_t FS_FOpenFileWrite(const char *filename,qboolean safe);
CCALL void FS_FCloseFile(fileHandle_t f);
CCALL void FS_Rename(const char *from,const char *to);
CCALL void FS_SV_Rename(const char *from,const char *to,qboolean safe);
CCALL int FS_SV_FOpenFileRead(const char *filename,fileHandle_t *fp);
//fileHandle_t FS_SV_FOpenFileWrite(const char *filename);
CCALL qboolean FS_SV_FileExists(const char *file);
CCALL qboolean FS_FileExists(const char *file);
CCALL qboolean FS_FileInPathExists(const char *testpath);
CCALL void FS_HomeRmdir(const char *homePath,qboolean recursive);
CCALL void FS_FreeFileList(char **fileList);
CCALL void FS_Rmdir(const char *osPath,qboolean recursive);
CCALL void FS_HomeRemove(const char *homePath);
CCALL void FS_Remove(const char *osPath);
CCALL void FS_CopyFile(char *fromOSPath,char *toOSPath);
CCALL qboolean FS_CreatePath(char *OSPath);
CCALL char *FS_BuildOSPath(const char *qpath);
CCALL char *FS_BuildOSPath2(const char *base,const char *game,const char *qpath);
CCALL void FS_ReplaceSeparators(char *path);
CCALL int FS_filelength(fileHandle_t f);
CCALL long FS_fplength(FILE *h);
CCALL void FS_ForceFlush(fileHandle_t f);
//qboolean FS_PakIsPure(pack_t *pack);
qboolean FS_Initialized(void);
#if defined(FS_MISSING)
extern FILE *missingFiles;
#endif
extern char lastValidGame[MAX_OSPATH];
extern char lastValidBase[MAX_OSPATH];
CCALL const char *FS_GetCurrentGameDir(qboolean emptybase);
fileHandle_t FS_SV_FOpenFileWrite( const char *filename );

#endif