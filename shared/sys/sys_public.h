/*
===========================================================================
Copyright (C) 2005 - 2015, ioquake3 contributors
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

#include "qcommon/q_shared.h"

#define MAXPRINTMSG 4096

typedef enum netadrtype_s
{
	NA_BAD = 0,					// an address lookup failed
	NA_BOT,
	NA_LOOPBACK,
	NA_BROADCAST,
	NA_IP
} netadrtype_t;

typedef struct netadr_s
{
	netadrtype_t	type;

	byte		ip[4];
	uint16_t	port;
} netadr_t;

/*
==============================================================

NON-PORTABLE SYSTEM SERVICES

==============================================================
*/

typedef enum {
	AXIS_SIDE,
	AXIS_FORWARD,
	AXIS_UP,
	AXIS_ROLL,
	AXIS_YAW,
	AXIS_PITCH,
	MAX_JOYSTICK_AXIS
} joystickAxis_t;

typedef enum {
  // bk001129 - make sure SE_NONE is zero
	SE_NONE = 0,	// evTime is still valid
	SE_KEY,		// evValue is a key code, evValue2 is the down flag
	SE_CHAR,	// evValue is an ascii char
	SE_MOUSE,	// evValue and evValue2 are reletive signed x / y moves
	SE_JOYSTICK_AXIS,	// evValue is an axis number and evValue2 is the current state (-127 to 127)
	SE_CONSOLE,	// evPtr is a char*
	SE_MAX
} sysEventType_t;

typedef struct sysEvent_s {
	int				evTime;
	sysEventType_t	evType;
	int				evValue, evValue2;
	int				evPtrLength;	// bytes of data pointed to by evPtr, for journaling
	void			*evPtr;			// this must be manually freed if not NULL
} sysEvent_t;

extern cvar_t *com_minimized;
extern cvar_t *com_unfocused;
extern cvar_t *com_maxfps;
extern cvar_t *com_maxfpsMinimized;
extern cvar_t *com_maxfpsUnfocused;

CCALL sysEvent_t	Sys_GetEvent( void );
CCALL void	Sys_Init (void);

// general development dll loading for virtual machine testing
typedef void *GetGameAPIProc( void  *);
typedef intptr_t QDECL VMMainProc( int, intptr_t, intptr_t, intptr_t, intptr_t, intptr_t, intptr_t, intptr_t, intptr_t, intptr_t, intptr_t, intptr_t, intptr_t );
typedef intptr_t QDECL SystemCallProc( intptr_t, ... );
typedef void * QDECL GetModuleAPIProc( int, ... );

CCALL void	*Sys_LoadSPGameDll( const char *name, GetGameAPIProc **GetGameAPI );
CCALL void	*Sys_LoadDll(const char *name, qboolean useSystemLib);
CCALL void	*Sys_LoadLegacyGameDll( const char *name, VMMainProc **vmMain, SystemCallProc *systemcalls );
CCALL void	*Sys_LoadGameDll( const char *name, GetModuleAPIProc **moduleAPI );
CCALL void	Sys_UnloadDll( void *dllHandle );
CCALL char	*Sys_GetCurrentUser( void );
CCALL void	Sys_Error( const char *error, ... );
CCALL void	Sys_Quit (void);
CCALL char	*Sys_GetClipboardData( void );	// note that this isn't journaled...
CCALL void	Sys_Print( const char *msg );

// Sys_Milliseconds should only be used for profiling purposes,
// any game related timing information should come from event timestamps
CCALL int		Sys_Milliseconds (bool baseTime = false);
CCALL int		Sys_Milliseconds2(void);
CCALL void	Sys_Sleep( int msec );
CCALL void	Sys_SnapVector( float *v );
CCALL bool Sys_RandomBytes( byte *string, int len );
CCALL void	Sys_SetErrorText( const char *text );
CCALL void	Sys_SendPacket( int length, const void *data, netadr_t to );
CCALL qboolean	Sys_StringToAdr( const char *s, netadr_t *a ); //Does NOT parse port numbers, only base addresses.
CCALL qboolean	Sys_IsLANAddress (netadr_t adr);
CCALL void		Sys_ShowIP(void);
CCALL qboolean	Sys_Mkdir( const char *path );
CCALL char	*Sys_Cwd( void );
CCALL void	Sys_SetDefaultInstallPath(const char *path);
CCALL char	*Sys_DefaultInstallPath(void);
CCALL char	*Sys_DefaultHomePath(void);
CCALL const char *Sys_Dirname( char *path );
CCALL const char *Sys_Basename( char *path );
CCALL bool Sys_PathCmp( const char *path1, const char *path2 );
CCALL char **Sys_ListFiles( const char *directory, const char *extension, char *filter, int *numfiles, qboolean wantsubs );
CCALL void	Sys_FreeFileList( char **fileList ); //rwwRMG - changed to fileList to not conflict with list type
CCALL time_t Sys_FileTime( const char *path );
CCALL qboolean Sys_LowPhysicalMemory();
CCALL void Sys_SetProcessorAffinity( void );

typedef enum graphicsApi_e
{
	GRAPHICS_API_GENERIC,

	// Only OpenGL needs special treatment..
	GRAPHICS_API_OPENGL,
} graphicsApi_t;

// Graphics API
typedef struct window_s
{
	void *handle; // OS-dependent window handle
	graphicsApi_t api;
} window_t;

typedef enum glProfile_e
{
	GLPROFILE_COMPATIBILITY,
	GLPROFILE_CORE,
	GLPROFILE_ES,
} glProfile_t;

typedef enum glContextFlag_e
{
	GLCONTEXT_DEBUG = (1 << 1),
} glContextFlag_t;

typedef struct windowDesc_s
{
	graphicsApi_t api;

	// Only used if api == GRAPHICS_API_OPENGL
	struct gl_
	{
		int majorVersion;
		int minorVersion;
		glProfile_t profile;
		uint32_t contextFlags;
	} gl;
} windowDesc_t;

typedef struct glconfig_s glconfig_t;
CCALL window_t	WIN_Init( const windowDesc_t *desc, glconfig_t *glConfig );
CCALL void		WIN_Present( window_t *window );
CCALL void		WIN_SetGamma( glconfig_t *glConfig, byte red[256], byte green[256], byte blue[256] );
CCALL void		WIN_Shutdown( void );
CCALL void *		WIN_GL_GetProcAddress( const char *proc );
CCALL qboolean	WIN_GL_ExtensionSupported( const char *extension );

uint8_t ConvertUTF32ToExpectedCharset( uint32_t utf32 );
