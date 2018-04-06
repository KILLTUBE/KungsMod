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

#include "g_local.h"

#if 0
void trap_SendServerCommand( int clientNum, const char *text ) {
	if ( strlen( text ) > 1022 ) {
		G_SecurityLogPrintf( "trap_SendServerCommand( %d, ... ) length exceeds 1022.\n", clientNum );
		G_SecurityLogPrintf( "text [%s]\n", text );
		return;
	}
	Q_syscall( G_SEND_SERVER_COMMAND, clientNum, text );
}
qboolean SVSyscall_EntityContact( const vec3_t mins, const vec3_t maxs, const sharedEntity_t *ent, int capsule ) {
	if ( capsule )
		return trap_EntityContactCapsule( mins, maxs, ent );
	else
		return trap_EntityContact( mins, maxs, ent );
}

void SVSyscall_Trace( trace_t *results, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end, int passEntityNum, int contentmask, int capsule, int traceFlags, int useLod ) {
	if ( capsule )
		trap_TraceCapsule( results, start, mins, maxs, end, passEntityNum, contentmask );
	else if ( traceFlags )
		trap_G2Trace( results, start, mins, maxs, end, passEntityNum, contentmask, traceFlags, useLod );
	else
		trap_Trace( results, start, mins, maxs, end, passEntityNum, contentmask );
}

void G_Error( int errorLevel, const char *error, ... ) {
	va_list argptr;
	char text[1024];

	va_start( argptr, error );
	Q_vsnprintf( text, sizeof( text ), error, argptr );
	va_end( argptr );

	trap_Error( text );
}

void G_Printf( const char *msg, ... ) {
	va_list argptr;
	char text[4096] = {0};
	int ret;

	va_start( argptr, msg );
	ret = Q_vsnprintf( text, sizeof( text ), msg, argptr );
	va_end( argptr );

	if ( ret == -1 )
		trap_Print( "G_Printf: overflow of 4096 bytes buffer\n" );
	else
		trap_Print( text );
}

#endif