/*
===========================================================================
Copyright (C) 1999 - 2005, Id Software, Inc.
Copyright (C) 2000 - 2013, Raven Software, Inc.
Copyright (C) 2001 - 2013, Activision, Inc.
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

// qcommon.h -- definitions common between client and server, but not game.or ref modules

#include "qcommon/q_shared.h"
#include "sys/sys_public.h"
#include "include_ccall.h"

//============================================================================

//
// msg.c
//
typedef struct msg_s {
	qboolean	allowoverflow;	// if false, do a Com_Error
	qboolean	overflowed;		// set to true if the buffer size failed (with allowoverflow set)
	qboolean	oob;			// set to true if the buffer size failed (with allowoverflow set)
	byte	*data;
	int		maxsize;
	int		cursize;
	int		readcount;
	int		bit;				// for bitwise reads and writes
} msg_t;

void MSG_Init (msg_t *buf, byte *data, int length);
void MSG_InitOOB( msg_t *buf, byte *data, int length );
void MSG_Clear (msg_t *buf);
void MSG_WriteData (msg_t *buf, const void *data, int length);
void MSG_Bitstream( msg_t *buf );

struct usercmd_s;
struct entityState_s;
struct playerState_s;

void MSG_WriteBits( msg_t *msg, int value, int bits );

void MSG_WriteChar (msg_t *sb, int c);
void MSG_WriteByte (msg_t *sb, int c);
void MSG_WriteShort (msg_t *sb, int c);
void MSG_WriteLong (msg_t *sb, int c);
void MSG_WriteFloat (msg_t *sb, float f);
void MSG_WriteString (msg_t *sb, const char *s);
void MSG_WriteBigString (msg_t *sb, const char *s);
void MSG_WriteAngle16 (msg_t *sb, float f);

void	MSG_BeginReading (msg_t *sb);
void	MSG_BeginReadingOOB(msg_t *sb);

int		MSG_ReadBits( msg_t *msg, int bits );

int		MSG_ReadChar (msg_t *sb);
int		MSG_ReadByte (msg_t *sb);
int		MSG_ReadShort (msg_t *sb);
int		MSG_ReadLong (msg_t *sb);
float	MSG_ReadFloat (msg_t *sb);
char	*MSG_ReadString (msg_t *sb);
char	*MSG_ReadBigString (msg_t *sb);
char	*MSG_ReadStringLine (msg_t *sb);
float	MSG_ReadAngle16 (msg_t *sb);
void	MSG_ReadData (msg_t *sb, void *buffer, int size);


void MSG_WriteDeltaUsercmdKey( msg_t *msg, int key, usercmd_t *from, usercmd_t *to );
void MSG_ReadDeltaUsercmdKey( msg_t *msg, int key, usercmd_t *from, usercmd_t *to );

void MSG_WriteDeltaEntity( msg_t *msg, struct entityState_s *from, struct entityState_s *to
						   , qboolean force );
void MSG_ReadDeltaEntity( msg_t *msg, entityState_t *from, entityState_t *to,
						 int number );

#ifdef _ONEBIT_COMBO
void MSG_WriteDeltaPlayerstate( msg_t *msg, struct playerState_s *from, struct playerState_s *to, int *bitComboDelta, int *bitNumDelta, qboolean isVehiclePS = qfalse );
#else
void MSG_WriteDeltaPlayerstate( msg_t *msg, struct playerState_s *from, struct playerState_s *to, qboolean isVehiclePS = qfalse );
#endif
void MSG_ReadDeltaPlayerstate( msg_t *msg, struct playerState_s *from, struct playerState_s *to, qboolean isVehiclePS = qfalse );

#ifndef FINAL_BUILD
void MSG_ReportChangeVectors_f( void );
#endif

//============================================================================

/*
==============================================================

NET

==============================================================
*/

#define NET_ENABLEV4		0x01

#define	PACKET_BACKUP	32	// number of old messages that must be kept on client and
							// server for delta comrpession and ping estimation
#define	PACKET_MASK		(PACKET_BACKUP-1)

#define	MAX_PACKET_USERCMDS		32		// max number of usercmd_t in a packet

#define	MAX_SNAPSHOT_ENTITIES	256

#define	PORT_ANY			-1

#define	MAX_RELIABLE_COMMANDS	128			// max string commands buffered for restransmit

typedef enum {
	NS_CLIENT,
	NS_SERVER
} netsrc_t;

CCALL void		NET_Init( void );
CCALL void		NET_Shutdown( void );
CCALL void		NET_Restart_f( void );
CCALL void		NET_Config( qboolean enableNetworking );
CCALL void		NET_SendPacket (netsrc_t sock, int length, const void *data, netadr_t to);
CCALL void		NET_OutOfBandPrint( netsrc_t net_socket, netadr_t adr, const char *format, ...);
CCALL void		NET_OutOfBandData( netsrc_t sock, netadr_t adr, byte *format, int len );
CCALL qboolean	NET_CompareAdr (netadr_t a, netadr_t b);
CCALL qboolean	NET_CompareBaseAdrMask( netadr_t a, netadr_t b, int netmask );
CCALL qboolean	NET_CompareBaseAdr (netadr_t a, netadr_t b);
CCALL qboolean	NET_IsLocalAddress (netadr_t adr);
CCALL const char	*NET_AdrToString (netadr_t a);
CCALL qboolean	NET_StringToAdr ( const char *s, netadr_t *a);
CCALL qboolean	NET_GetLoopPacket (netsrc_t sock, netadr_t *net_from, msg_t *net_message);
CCALL void		NET_Sleep(int msec);
CCALL void		Sys_SendPacket( int length, const void *data, netadr_t to );
CCALL qboolean	Sys_StringToAdr( const char *s, netadr_t *a ); //Does NOT parse port numbers, only base addresses.
CCALL qboolean	Sys_IsLANAddress (netadr_t adr);
CCALL void		Sys_ShowIP(void);


#define	MAX_MSGLEN				49152		// max length of a message, which may
											// be fragmented into multiple packets

//rww - 6/28/02 - Changed from 16384 to match sof2's. This does seem rather huge, but I guess it doesn't really hurt anything.

#define MAX_DOWNLOAD_WINDOW			8		// max of eight download frames
#define MAX_DOWNLOAD_BLKSIZE		2048	// 2048 byte block chunks


/*
Netchan handles packet fragmentation and out of order / duplicate suppression
*/

typedef struct netchan_s {
	netsrc_t	sock;

	int			dropped;			// between last packet and previous

	netadr_t	remoteAddress;
	int			qport;				// qport value to write when transmitting

	// sequencing variables
	int			incomingSequence;
	int			outgoingSequence;

	// incoming fragment assembly buffer
	int			fragmentSequence;
	int			fragmentLength;
	byte		fragmentBuffer[MAX_MSGLEN];

	// outgoing fragment buffer
	// we need to space out the sending of large fragmented messages
	qboolean	unsentFragments;
	int			unsentFragmentStart;
	int			unsentLength;
	byte		unsentBuffer[MAX_MSGLEN];
} netchan_t;

void Netchan_Init( int qport );
void Netchan_Setup( netsrc_t sock, netchan_t *chan, netadr_t adr, int qport );

void Netchan_Transmit( netchan_t *chan, int length, const byte *data );
void Netchan_TransmitNextFragment( netchan_t *chan );

qboolean Netchan_Process( netchan_t *chan, msg_t *msg );


/*
==============================================================

PROTOCOL

==============================================================
*/

#define	PROTOCOL_VERSION	26

#define	UPDATE_SERVER_NAME			"updatejk3.ravensoft.com"
#define MASTER_SERVER_NAME			"masterjk3.ravensoft.com"

#define JKHUB_MASTER_SERVER_NAME	"master.jkhub.org"
#define JKHUB_UPDATE_SERVER_NAME	"update.jkhub.org"

#define	PORT_MASTER			29060
#define	PORT_UPDATE			29061
#define	PORT_SERVER			29070	//...+9 more for multiple servers
#define	NUM_SERVER_PORTS	4		// broadcast scan this many ports after PORT_SERVER so a single machine can run multiple servers

// the svc_strings[] array in cl_parse.c should mirror this
//
// server to client
//
enum svc_ops_e {
	svc_bad,
	svc_nop,
	svc_gamestate,
	svc_configstring,			// [short] [string] only in gamestate messages
	svc_baseline,				// only in gamestate messages
	svc_serverCommand,			// [string] to be executed by client game module
	svc_download,				// [short] size [size bytes]
	svc_snapshot,
	svc_setgame,
	svc_mapchange,
	svc_EOF
};


//
// client to server
//
enum clc_ops_e {
	clc_bad,
	clc_nop,
	clc_move,				// [[usercmd_t]
	clc_moveNoDelta,		// [[usercmd_t]
	clc_clientCommand,		// [string] message
	clc_EOF
};

/*
==============================================================

VIRTUAL MACHINE

==============================================================
*/

typedef enum vmSlots_e {
	VM_GAME=0,
	VM_CGAME,
	VM_UI,
	MAX_VM
} vmSlots_t;

typedef struct vm_s {
	vmSlots_t	slot; // VM_GAME, VM_CGAME, VM_UI
    char		name[MAX_QPATH];
	void		*dllHandle;
	qboolean	isLegacy; // uses the legacy syscall/vm_call api, is set by VM_CreateLegacy

	// fill the import/export tables
	void *		(*GetModuleAPI)( int apiVersion, ... );

	// legacy stuff
	struct {
		VMMainProc* main; // module vmMain
		intptr_t	(QDECL *syscall)( intptr_t *parms );	// engine syscall handler
	} legacy;
} vm_t;

EXTERNC	 vm_t *currentVM;

CCALL qboolean isGame();
CCALL qboolean isCGame();
CCALL qboolean isUI();

class VMSwap {
private:
	VMSwap();
	vm_t *oldVM;
public:
	VMSwap( vm_t *newVM ) : oldVM( currentVM ) { currentVM = newVM; };
	~VMSwap() { if ( oldVM ) currentVM = oldVM; };
};

extern const char *vmStrs[MAX_VM];

typedef enum {
	TRAP_MEMSET = 100,
	TRAP_MEMCPY,
	TRAP_STRNCPY,
	TRAP_SIN,
	TRAP_COS,
	TRAP_ATAN2,
	TRAP_SQRT,
	TRAP_MATRIXMULTIPLY,
	TRAP_ANGLEVECTORS,
	TRAP_PERPENDICULARVECTOR,
	TRAP_FLOOR,
	TRAP_CEIL,

	TRAP_TESTPRINTINT,
	TRAP_TESTPRINTFLOAT,

	TRAP_ACOS,
	TRAP_ASIN
} sharedTraps_t;

CCALL void			VM_Init( void );
CCALL vm_t			*VM_CreateLegacy( vmSlots_t vmSlot, intptr_t (*systemCalls)(intptr_t *) );
CCALL vm_t			*VM_Create( vmSlots_t vmSlot );
CCALL void			 VM_Free( vm_t *vm );
CCALL void			 VM_Clear(void);
CCALL vm_t			*VM_Restart( vm_t *vm );
CCALL intptr_t QDECL	 VM_Call( vm_t *vm, int callNum, intptr_t arg0 = 0, intptr_t arg1 = 0, intptr_t arg2 = 0, intptr_t arg3 = 0, intptr_t arg4 = 0, intptr_t arg5 = 0, intptr_t arg6 = 0, intptr_t arg7 = 0, intptr_t arg8 = 0, intptr_t arg9 = 0, intptr_t arg10 = 0, intptr_t arg11 = 0 );
CCALL void			 VM_Shifted_Alloc( void **ptr, int size );
CCALL void			 VM_Shifted_Free( void **ptr );
CCALL void			*VM_ArgPtr( intptr_t intValue );
CCALL void			*VM_ExplicitArgPtr( vm_t *vm, intptr_t intValue );
CCALL float			_vmf( intptr_t x );

#define	VMA(x) VM_ArgPtr( args[x] )
#define	VMF(x) _vmf( args[x] )

/*
==============================================================

CMD

Command text buffering and command execution

==============================================================
*/

/*

Any number of commands can be added in a frame, from several different sources.
Most commands come from either keybindings or console line input, but entire text
files can be execed.

*/

CCALL void Cbuf_Init (void);
// allocates an initial text buffer that will grow as needed

CCALL void Cbuf_AddText( const char *text );
// Adds command text at the end of the buffer, does NOT add a final \n

CCALL void Cbuf_ExecuteText( int exec_when, const char *text );
// this can be used in place of either Cbuf_AddText or Cbuf_InsertText

CCALL void Cbuf_Execute (void);
// Pulls off \n terminated lines of text from the command buffer and sends
// them through Cmd_ExecuteString.  Stops when the buffer is empty.
// Normally called once per frame, but may be explicitly invoked.
// Do not call inside a command function, or current args will be destroyed.

//===========================================================================

/*

Command execution takes a null terminated string, breaks it into tokens,
then searches for a command or variable that matches the first token.

*/

typedef void (*xcommand_t) (void);

typedef void ( *callbackFunc_t )( const char *s );

CCALL void	Cmd_Init (void);

CCALL void	Cmd_AddCommand( const char *cmd_name, xcommand_t function, const char *cmd_desc=NULL );
// called by the init functions of other parts of the program to
// register commands and functions to call for them.
// The cmd_name is referenced later, so it should not be in temp memory
// if function is NULL, the command will be forwarded to the server
// as a clc_clientCommand instead of executed locally

CCALL void	Cmd_RemoveCommand( const char *cmd_name );
CCALL void	Cmd_VM_RemoveCommand( const char *cmd_name, vmSlots_t vmslot );
typedef void (*completionFunc_t)( char *args, int argNum );

typedef struct cmdList_s
{
	const char *name;
	const char *description;
	xcommand_t func;
	completionFunc_t complete;
} cmdList_t;

CCALL void Cmd_AddCommandList( const cmdList_t *cmdList );
CCALL void Cmd_RemoveCommandList( const cmdList_t *cmdList );

CCALL void	Cmd_CommandCompletion( callbackFunc_t callback );
// callback with each valid string
CCALL void Cmd_SetCommandCompletionFunc( const char *command, completionFunc_t complete );
CCALL void Cmd_CompleteArgument( const char *command, char *args, int argNum );
CCALL void Cmd_CompleteCfgName( char *args, int argNum );

CCALL int		Cmd_Argc (void);
CCALL char	*Cmd_Argv (int arg);
CCALL void	Cmd_ArgvBuffer( int arg, char *buffer, int bufferLength );
CCALL char	*Cmd_Args (void);
CCALL char	*Cmd_ArgsFrom( int arg );
CCALL void	Cmd_ArgsBuffer( char *buffer, int bufferLength );
CCALL void	Cmd_ArgsFromBuffer( int arg, char *buffer, int bufferLength );
CCALL char	*Cmd_Cmd (void);
CCALL void	Cmd_Args_Sanitize( size_t length = MAX_CVAR_VALUE_STRING, const char *strip = "\n\r;", const char *repl = "   " );
// The functions that execute commands get their parameters with these
// functions. Cmd_Argv () will return an empty string, not a NULL
// if arg > argc, so string operations are allways safe.

CCALL void	Cmd_TokenizeString( const char *text );
CCALL void	Cmd_TokenizeStringIgnoreQuotes( const char *text_in );
// Takes a null terminated string.  Does not need to be /n terminated.
// breaks the string up into arg tokens.

CCALL void	Cmd_ExecuteString( const char *text );
// Parses a single line of text into arguments and tries to execute it
// as if it was typed at the console


/*
==============================================================

CVAR

==============================================================
*/

/*

cvar_t variables are used to hold scalar or string variables that can be changed
or displayed at the console or prog code as well as accessed directly
in C code.

The user can access cvars from the console in three ways:
r_draworder			prints the current value
r_draworder 0		sets the current value to 0
set r_draworder 0	as above, but creates the cvar if not present

Cvars are restricted from having the same names as commands to keep this
interface from being ambiguous.

The are also occasionally used to communicated information between different
modules of the program.

*/

CCALL cvar_t *Cvar_Get( const char *var_name, const char *value, uint32_t flags, const char *var_desc=NULL );
// creates the variable if it doesn't exist, or returns the existing one
// if it exists, the value will not be changed, but flags will be ORed in
// that allows variables to be unarchived without needing bitflags
// if value is "", the value will not override a previously set value.

CCALL void	Cvar_Register( cvar_t *vmCvar, const char *varName, const char *defaultValue, uint32_t flags );
// basically a slightly modified Cvar_Get for the interpreted modules

CCALL void	Cvar_Update( cvar_t *vmCvar );
// updates an interpreted modules' version of a cvar

CCALL cvar_t	*Cvar_Set2(const char *var_name, const char *value, uint32_t defaultFlags, qboolean force);
//

CCALL cvar_t	*Cvar_Set( const char *var_name, const char *value );
// will create the variable with no flags if it doesn't exist

CCALL cvar_t	*Cvar_SetSafe( const char *var_name, const char *value );
// same as Cvar_Set, but doesn't force setting the value (respects CVAR_ROM, etc)

CCALL cvar_t	*Cvar_User_Set( const char *var_name, const char *value );
// same as Cvar_SetSafe, but defaults to CVAR_USER_CREATED

CCALL void	Cvar_Server_Set( const char *var_name, const char *value );
CCALL void	Cvar_VM_Set( const char *var_name, const char *value, vmSlots_t vmslot );
// sometimes we set variables from an untrusted source: fail if flags & CVAR_PROTECTED

CCALL cvar_t *Cvar_SetValue( const char *var_name, float value );
CCALL void	Cvar_User_SetValue( const char *var_name, float value );
CCALL void	Cvar_VM_SetValue( const char *var_name, float value, vmSlots_t vmslot );
// expands value to a string and calls Cvar_Set/Cvar_User_Set/Cvar_VM_Set

CCALL float	Cvar_VariableValue( const char *var_name );
CCALL int		Cvar_VariableIntegerValue( const char *var_name );
// returns 0 if not defined or non numeric

CCALL char	*Cvar_VariableString( const char *var_name );
CCALL void	Cvar_VariableStringBuffer( const char *var_name, char *buffer, int bufsize );
// returns an empty string if not defined

CCALL uint32_t	Cvar_Flags(const char *var_name);
// returns CVAR_NONEXISTENT if cvar doesn't exist or the flags of that particular CVAR.

CCALL void	Cvar_CommandCompletion( callbackFunc_t callback );
// callback with each valid string

CCALL void 	Cvar_Reset( const char *var_name );
CCALL void 	Cvar_ForceReset( const char *var_name );

CCALL void	Cvar_SetCheatState( void );
// reset all testing vars to a safe value

CCALL qboolean Cvar_Command( void );
// called by Cmd_ExecuteString when Cmd_Argv(0) doesn't match a known
// command.  Returns true if the command was a variable reference that
// was handled. (print or change)

CCALL void 	Cvar_WriteVariables( fileHandle_t f );
// writes lines containing "set variable value" for all variables
// with the archive flag set to true.

CCALL cvar_t *Cvar_Unset(cvar_t *cv);

CCALL void	Cvar_Init( void );

CCALL char	*Cvar_InfoString( int bit );
CCALL char	*Cvar_InfoString_Big( int bit );
// returns an info string containing all the cvars that have the given bit set
// in their flags ( CVAR_USERINFO, CVAR_SERVERINFO, CVAR_SYSTEMINFO, etc )
CCALL void	Cvar_InfoStringBuffer( int bit, char *buff, int buffsize );
CCALL void Cvar_CheckRange( cvar_t *cv, float minVal, float maxVal, qboolean shouldBeIntegral );

CCALL void	Cvar_Restart(qboolean unsetVM);
CCALL void	Cvar_Restart_f( void );

CCALL void Cvar_CompleteCvarName( char *args, int argNum );

extern uint32_t cvar_modifiedFlags;
// whenever a cvar is modifed, its flags will be OR'd into this, so
// a single check can determine if any CVAR_USERINFO, CVAR_SERVERINFO,
// etc, variables have been modified since the last check.  The bit
// can then be cleared to allow another change detection.

/*
==============================================================

FILESYSTEM

No stdio calls should be used by any part of the game, because
we need to deal with all sorts of directory and seperator char
issues.
==============================================================
*/

// referenced flags
// these are in loop specific order so don't change the order
#define FS_GENERAL_REF	0x01
#define FS_UI_REF		0x02
#define FS_CGAME_REF	0x04
#define FS_GAME_REF		0x08
// number of id paks that will never be autodownloaded from base
#define NUM_ID_PAKS		9

#define	MAX_FILE_HANDLES	64

#ifdef DEDICATED
#	define Q3CONFIG_CFG PRODUCT_NAME "_server.cfg"
#else
#	define Q3CONFIG_CFG PRODUCT_NAME ".cfg"
#endif
#include "files.h"

/*
==============================================================

Edit fields and command line history/completion

==============================================================
*/

#define CONSOLE_PROMPT_CHAR ']'
#define	MAX_EDIT_LINE		256
#define COMMAND_HISTORY		32

typedef struct field_s {
	int		cursor;
	int		scroll;
	int		widthInChars;
	char	buffer[MAX_EDIT_LINE];
} field_t;

CCALL void Field_Clear( field_t *edit );
CCALL void Field_AutoComplete( field_t *edit );
CCALL void Field_CompleteKeyname( void );
CCALL void Field_CompleteFilename( const char *dir, const char *ext, qboolean stripExt, qboolean allowNonPureFilesOnDisk );
CCALL void Field_CompleteCommand( char *cmd, qboolean doCommands, qboolean doCvars );

/*
==============================================================

MISC

==============================================================
*/

#define RoundUp(N, M) ((N) + ((unsigned int)(M)) - (((unsigned int)(N)) % ((unsigned int)(M))))
#define RoundDown(N, M) ((N) - (((unsigned int)(N)) % ((unsigned int)(M))))

CCALL char		*CopyString( const char *in );
CCALL void		Info_Print( const char *s );
CCALL void		Com_BeginRedirect (char *buffer, int buffersize, void (*flush)(char *));
CCALL void		Com_EndRedirect( void );
CCALL void 		Com_Printf( const char *fmt, ... );
CCALL void 		Com_DPrintf( const char *fmt, ... );
CCALL void		Com_OPrintf( const char *fmt, ...); // Outputs to the VC / Windows Debug window (only in debug compile)
CCALL void 		Com_Error( int code, const char *fmt, ... );
CCALL void 		Com_Quit_f( void );
CCALL int		Com_EventLoop( void );
CCALL int		Com_Milliseconds( void );	// will be journaled properly
CCALL uint32_t	Com_BlockChecksum( const void *buffer, int length );
CCALL char		*Com_MD5File(const char *filename, int length, const char *prefix, int prefix_len);
CCALL int      Com_HashKey(char *string, int maxlen);
CCALL int			Com_Filter(char *filter, char *name, int casesensitive);
CCALL int			Com_FilterPath(char *filter, char *name, int casesensitive);
CCALL int			Com_RealTime(qtime_t *qtime);
CCALL qboolean	Com_SafeMode( void );
CCALL void		Com_RunAndTimeServerPacket(netadr_t *evFrom, msg_t *buf);
CCALL void		Com_StartupVariable( const char *match );
// checks for and removes command line "+set var arg" constructs
// if match is NULL, all set commands will be executed, otherwise
// only a set with the exact name.  Only used during startup.


EXTERNC		cvar_t	*com_developer;
EXTERNC		cvar_t	*com_dedicated;
EXTERNC		cvar_t	*com_speeds;
EXTERNC		cvar_t	*com_timescale;
EXTERNC		cvar_t	*com_sv_running;
EXTERNC		cvar_t	*com_cl_running;
EXTERNC		cvar_t	*com_version;
EXTERNC		cvar_t	*com_buildScript;		// for building release pak files
EXTERNC		cvar_t	*com_journal;
EXTERNC		cvar_t	*com_cameraMode;
EXTERNC		cvar_t	*com_homepath;

EXTERNC cvar_t *bg_showevents;

#ifndef _WIN32
EXTERNC		cvar_t	*com_ansiColor;
#endif

EXTERNC	cvar_t	*com_optvehtrace;

#ifdef G2_PERFORMANCE_ANALYSIS
EXTERNC		cvar_t	*com_G2Report;
#endif

EXTERNC		cvar_t	*com_affinity;
EXTERNC		cvar_t	*com_busyWait;

// both client and server must agree to pause
EXTERNC		cvar_t	*cl_paused;
EXTERNC		cvar_t	*sv_paused;

// com_speeds times
EXTERNC		int		time_game;
EXTERNC		int		time_frontend;
EXTERNC		int		time_backend;		// renderer backend time

EXTERNC		int		com_frameTime;

EXTERNC		qboolean	com_errorEntered;


EXTERNC		fileHandle_t	logfile;
EXTERNC		fileHandle_t	com_journalFile;
EXTERNC		fileHandle_t	com_journalDataFile;

/*
typedef enum {
	TAG_FREE,
	TAG_GENERAL,
	TAG_BOTLIB,
	TAG_RENDERER,
	TAG_SMALL,
	TAG_STATIC
} memtag_t;
*/

/*

--- low memory ----
server vm
server clipmap
---mark---
renderer initialization (shaders, etc)
UI vm
cgame vm
renderer map
renderer models

---free---

temp file loading
--- high memory ---

*/

#if defined(_DEBUG) && !defined(BSPC)
	#define DEBUG_ZONE_ALLOCS
#endif

/*
#ifdef DEBUG_ZONE_ALLOCS
	#define Z_TagMalloc(size, tag)			Z_TagMallocDebug(size, tag, #size, __FILE__, __LINE__)
	#define Z_Malloc(size)					Z_MallocDebug(size, #size, __FILE__, __LINE__)
	#define S_Malloc(size)					S_MallocDebug(size, #size, __FILE__, __LINE__)
	void *Z_TagMallocDebug( int size, int tag, char *label, char *file, int line );	// NOT 0 filled memory
	void *Z_MallocDebug( int size, char *label, char *file, int line );			// returns 0 filled memory
	void *S_MallocDebug( int size, char *label, char *file, int line );			// returns 0 filled memory
#else
	void *Z_TagMalloc( int size, int tag );	// NOT 0 filled memory
	void *Z_Malloc( int size );			// returns 0 filled memory
	void *S_Malloc( int size );			// NOT 0 filled memory only for small allocations
#endif
void Z_Free( void *ptr );
void Z_FreeTags( int tag );
int Z_AvailableMemory( void );
void Z_LogHeap( void );
*/

// later on I'll re-implement __FILE__, __LINE__ etc, but for now...
//
#ifdef DEBUG_ZONE_ALLOCS
void *Z_Malloc  ( int iSize, memtag_t eTag, qboolean bZeroit = qfalse, int iAlign = 4);	// return memory NOT zero-filled by default
void *S_Malloc	( int iSize );					// NOT 0 filled memory only for small allocations
#else
void *Z_Malloc  ( int iSize, memtag_t eTag, qboolean bZeroit = qfalse, int iAlign = 4);	// return memory NOT zero-filled by default
void *S_Malloc	( int iSize );					// NOT 0 filled memory only for small allocations
#endif
CCALL void  Z_MorphMallocTag( void *pvBuffer, memtag_t eDesiredTag );
CCALL void  Z_Validate( void );
CCALL int   Z_MemSize	( memtag_t eTag );
CCALL void  Z_TagFree	( memtag_t eTag );
CCALL void  Z_Free	( void *ptr );
CCALL int	  Z_Size	( void *pvAddress);
CCALL void Com_InitZoneMemory(void);
CCALL void Com_InitZoneMemoryVars(void);
CCALL void Com_InitHunkMemory(void);
CCALL void Com_ShutdownZoneMemory(void);
CCALL void Com_ShutdownHunkMemory(void);
CCALL void Hunk_Clear( void );
CCALL void Hunk_ClearToMark( void );
CCALL void Hunk_SetMark( void );
CCALL qboolean Hunk_CheckMark( void );
CCALL void Hunk_ClearTempMemory( void );
CCALL void *Hunk_AllocateTempMemory( int size );
CCALL void Hunk_FreeTempMemory( void *buf );
CCALL int	Hunk_MemoryRemaining( void );
CCALL void Hunk_Log( void);
CCALL void Hunk_Trash( void );

CCALL void Com_TouchMemory( void );

// commandLine should not include the executable name (argv[0])
CCALL void Com_Init( char *commandLine );
CCALL void Com_Frame( void );
CCALL void Com_Shutdown( void );


/*
==============================================================

CLIENT / SERVER SYSTEMS

==============================================================
*/

//
// client interface
//
CCALL void CL_InitKeyCommands( void );
// the keyboard binding interface must be setup before execing
// config files, but the rest of client startup will happen later

CCALL void CL_Init( void );
CCALL void CL_Disconnect( qboolean showMainMenu );
CCALL void CL_Shutdown( void );
CCALL void CL_Frame( int msec );
CCALL qboolean CL_GameCommand( void );
CCALL void CL_KeyEvent (int key, qboolean down, unsigned time);

CCALL void CL_CharEvent( int key );
// char events are for field typing, not game control

CCALL void CL_MouseEvent( int dx, int dy, int time );

CCALL void CL_JoystickEvent( int axis, int value, int time );

CCALL void CL_PacketEvent( netadr_t from, msg_t *msg );

CCALL void CL_ConsolePrint( const char *text );

CCALL void CL_MapLoading( void );
// do a screen update before starting to load a map
// when the server is going to load a new map, the entire hunk
// will be cleared, so the client must shutdown cgame, ui, and
// the renderer

CCALL void	CL_ForwardCommandToServer( const char *string );
// adds the current command line as a clc_clientCommand to the client message.
// things like godmode, noclip, etc, are commands directed to the server,
// so when they are typed in at the console, they will need to be forwarded.

CCALL void CL_ShutdownAll( qboolean shutdownRef );
// shutdown all the client stuff

CCALL void CL_FlushMemory( void );
// dump all memory on an error

CCALL void CL_StartHunkUsers( void );
// start all the client stuff using the hunk

qboolean CL_ConnectedToRemoteServer( void );
// returns qtrue if connected to a server

void Key_KeynameCompletion ( void(*callback)( const char *s ) );
// for keyname autocompletion

void Key_WriteBindings( fileHandle_t f );
// for writing the config files

void S_ClearSoundBuffer( void );
// call before filesystem access

CCALL void SCR_DebugGraph (float value, int color);	// FIXME: move logging to common?

// AVI files have the start of pixel lines 4 byte-aligned
#define AVI_LINE_PADDING 4


//
// server interface
//
CCALL void SV_Init( void );
CCALL void SV_Shutdown( char *finalmsg );
CCALL void SV_Frame( int msec );
CCALL void SV_PacketEvent( netadr_t from, msg_t *msg );
CCALL int SV_FrameMsec( void );
CCALL qboolean SV_GameCommand( void );


//
// UI interface
//
CCALL qboolean UI_GameCommand( void );

/* This is based on the Adaptive Huffman algorithm described in Sayood's Data
 * Compression book.  The ranks are not actually stored, but implicitly defined
 * by the location of a node within a doubly-linked list */

#define NYT HMAX					/* NYT = Not Yet Transmitted */
#define INTERNAL_NODE (HMAX+1)

typedef struct nodetype {
	struct	nodetype *left, *right, *parent; /* tree structure */
	struct	nodetype *next, *prev; /* doubly-linked list */
	struct	nodetype **head; /* highest ranked node in block */
	int		weight;
	int		symbol;
} node_t;

#define HMAX 256 /* Maximum symbol */

typedef struct huff_s {
	int			blocNode;
	int			blocPtrs;

	node_t*		tree;
	node_t*		lhead;
	node_t*		ltail;
	node_t*		loc[HMAX+1];
	node_t**	freelist;

	node_t		nodeList[768];
	node_t*		nodePtrs[768];
} huff_t;

typedef struct huffman_s {
	huff_t		compressor;
	huff_t		decompressor;
} huffman_t;

CCALL void	Huff_Compress(msg_t *buf, int offset);
CCALL void	Huff_Decompress(msg_t *buf, int offset);
CCALL void	Huff_Init(huffman_t *huff);
CCALL void	Huff_addRef(huff_t* huff, byte ch);
CCALL int		Huff_Receive (node_t *node, int *ch, byte *fin);
CCALL void	Huff_transmit (huff_t *huff, int ch, byte *fout);
CCALL void	Huff_offsetReceive (node_t *node, int *ch, byte *fin, int *offset);
CCALL void	Huff_offsetTransmit (huff_t *huff, int ch, byte *fout, int *offset);
CCALL void	Huff_putBit( int bit, byte *fout, int *offset);
CCALL int		Huff_getBit( byte *fout, int *offset);

extern huffman_t clientHuffTables;

#define	SV_ENCODE_START		4
#define SV_DECODE_START		12
#define	CL_ENCODE_START		12
#define CL_DECODE_START		4

inline int Round(float value)
{
	return((int)floorf(value + 0.5f));
}

// Persistent data store API
bool PD_Store ( const char *name, const void *data, size_t size );
const void *PD_Load ( const char *name, size_t *size );

uint32_t ConvertUTF8ToUTF32( char *utf8CurrentChar, char **utf8NextChar );

#include "sys/sys_public.h"

template <class T>
T *AllocHunk(int count = 1) {
	return (T *)Hunk_Alloc( count * sizeof( T ), h_high );
}

template <class T>
T *AllocZone(memtag_t mt, int count = 1) {
	return (T *)Z_Malloc( count * sizeof( T ), mt, qtrue );
}