#ifndef Z_MEMMAN_PC
#define Z_MEMMAN_PC

void Z_Details_f(void);
void CIN_CloseAllVideos();


// This handles zone memory allocation.
// It is a wrapper around malloc with a tag id and a magic number at the start

#define ZONE_MAGIC			0x21436587

typedef struct zoneHeader_s
{
		int					iMagic;
		memtag_t			eTag;
		int					iSize;
struct	zoneHeader_s		*pNext;
struct	zoneHeader_s		*pPrev;
} zoneHeader_t;

typedef struct
{
	int iMagic;

} zoneTail_t;

static inline zoneTail_t *ZoneTailFromHeader(zoneHeader_t *pHeader)
{
	return (zoneTail_t*) ( (char*)pHeader + sizeof(*pHeader) + pHeader->iSize );
}

#ifdef DETAILED_ZONE_DEBUG_CODE
map <void*,int> mapAllocatedZones;
#endif


typedef struct zoneStats_s
{
	int		iCount;
	int		iCurrent;
	int		iPeak;

	// I'm keeping these updated on the fly, since it's quicker for cache-pool
	//	purposes rather than recalculating each time...
	//
	int		iSizesPerTag [TAG_COUNT];
	int		iCountsPerTag[TAG_COUNT];

} zoneStats_t;

typedef struct zone_s
{
	zoneStats_t				Stats;
	zoneHeader_t			Header;
} zone_t;

extern cvar_t	*com_validateZone;
extern zone_t	TheZone;


// Scans through the linked list of mallocs and makes sure no data has been overwritten

void Z_Validate(void);



// static mem blocks to reduce a lot of small zone overhead
//
#pragma pack(push)
#pragma pack(1)
typedef struct StaticZeroMem_s {
	zoneHeader_t	Header;
//	byte mem[0];
	zoneTail_t		Tail;
} StaticZeroMem_t;

typedef struct StaticMem_s {
	zoneHeader_t	Header;
	byte mem[2];
	zoneTail_t		Tail;
} StaticMem_t;
#pragma pack(pop)

/*
StaticZeroMem_t gZeroMalloc  =
	{ {ZONE_MAGIC, TAG_STATIC,0,NULL,NULL},{ZONE_MAGIC}};
StaticMem_t gEmptyString =
	{ {ZONE_MAGIC, TAG_STATIC,2,NULL,NULL},{'\0','\0'},{ZONE_MAGIC}};
StaticMem_t gNumberString[] = {
	{ {ZONE_MAGIC, TAG_STATIC,2,NULL,NULL},{'0','\0'},{ZONE_MAGIC}},
	{ {ZONE_MAGIC, TAG_STATIC,2,NULL,NULL},{'1','\0'},{ZONE_MAGIC}},
	{ {ZONE_MAGIC, TAG_STATIC,2,NULL,NULL},{'2','\0'},{ZONE_MAGIC}},
	{ {ZONE_MAGIC, TAG_STATIC,2,NULL,NULL},{'3','\0'},{ZONE_MAGIC}},
	{ {ZONE_MAGIC, TAG_STATIC,2,NULL,NULL},{'4','\0'},{ZONE_MAGIC}},
	{ {ZONE_MAGIC, TAG_STATIC,2,NULL,NULL},{'5','\0'},{ZONE_MAGIC}},
	{ {ZONE_MAGIC, TAG_STATIC,2,NULL,NULL},{'6','\0'},{ZONE_MAGIC}},
	{ {ZONE_MAGIC, TAG_STATIC,2,NULL,NULL},{'7','\0'},{ZONE_MAGIC}},
	{ {ZONE_MAGIC, TAG_STATIC,2,NULL,NULL},{'8','\0'},{ZONE_MAGIC}},
	{ {ZONE_MAGIC, TAG_STATIC,2,NULL,NULL},{'9','\0'},{ZONE_MAGIC}},
};
*/

extern qboolean gbMemFreeupOccured;
void *Z_Malloc(int iSize, memtag_t eTag, qboolean bZeroit /* = qfalse */, int iUnusedAlign /* = 4 */);

// Special wrapper around Z_Malloc for better separation between the main engine
// code and the bundled minizip library.

extern "C" Q_EXPORT void* openjk_minizip_malloc(int size);
extern "C" Q_EXPORT void openjk_minizip_free(void* to_free);

void *openjk_minizip_malloc(int size);

void openjk_minizip_free(void *to_free);

// used during model cacheing to save an extra malloc, lets us morph the disk-load buffer then
//	just not fs_freefile() it afterwards.
//
void Z_MorphMallocTag( void *pvAddress, memtag_t eDesiredTag );

static void Zone_FreeBlock(zoneHeader_t *pMemory);

// stats-query function to ask how big a malloc is...
//
int Z_Size(void *pvAddress);


// Frees a block of memory...
//
void Z_Free(void *pvAddress);


int Z_MemSize(memtag_t eTag);

// Frees all blocks with the specified tag...
//
void Z_TagFree(memtag_t eTag);


void *S_Malloc( int iSize );


#ifdef _DEBUG
void Z_MemRecoverTest_f(void);
#endif



// Gives a summary of the zone memory usage

void Z_Stats_f(void);

// Gives a detailed breakdown of the memory blocks in the zone

void Z_Details_f(void);

// Shuts down the zone memory system and frees up all memory
void Com_ShutdownZoneMemory(void);

// Initialises the zone memory system

void Com_InitZoneMemory( void );

void Com_InitZoneMemoryVars( void );



/*
========================
CopyString

 NOTE:	never write over the memory CopyString returns because
		memory from a memstatic_t might be returned
========================
*/
char *CopyString( const char *in );

/*
===============
Com_TouchMemory

Touch all known used data to make sure it is paged in
===============
*/
void Com_TouchMemory( void );



CCALL qboolean Com_TheHunkMarkHasBeenMade(void);

/*
=================
Com_InitHunkMemory
=================
*/
void Com_InitHunkMemory( void );

void Com_ShutdownHunkMemory(void);

/*
====================
Hunk_MemoryRemaining
====================
*/
CCALL int	Hunk_MemoryRemaining( void );

/*
===================
Hunk_SetMark

The server calls this after the level and game VM have been loaded
===================
*/
void Hunk_SetMark( void );

/*
=================
Hunk_ClearToMark

The client calls this before starting a vid_restart or snd_restart
=================
*/
void Hunk_ClearToMark( void );

/*
=================
Hunk_CheckMark
=================
*/
qboolean Hunk_CheckMark( void );

void CL_ShutdownCGame( void );
void CL_ShutdownUI( void );
CCALL void SV_ShutdownGameProgsVoid( void );

/*
=================
Hunk_Clear

The server calls this before shutting down or loading a new map
=================
*/
CCALL void R_HunkClearCrap(void);
#ifdef _FULL_G2_LEAK_CHECKING
void G2_DEBUG_ReportLeaks(void);
#endif

void Hunk_Clear( void );

/*
=================
Hunk_Alloc

Allocate permanent (until the hunk is cleared) memory
=================
*/
void *Hunk_Alloc( int size, ha_pref preference );

/*
=================
Hunk_AllocateTempMemory

This is used by the file loading system.
Multiple files can be loaded in temporary memory.
When the files-in-use count reaches zero, all temp memory will be deleted
=================
*/
void *Hunk_AllocateTempMemory( int size );


/*
==================
Hunk_FreeTempMemory
==================
*/
void Hunk_FreeTempMemory( void *buf );


/*
=================
Hunk_ClearTempMemory

The temp space is no longer needed.  If we have left more
touched but unused memory on this side, have future
permanent allocs use this side.
=================
*/
void Hunk_ClearTempMemory( void );

#endif