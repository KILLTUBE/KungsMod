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

#include "qcommon/qcommon.h"

CCALL void 		IN_Init( void *windowData );
CCALL void 		IN_Frame( void );
CCALL void 		IN_Shutdown( void );
CCALL void 		IN_Restart( void );
CCALL void		Sys_PlatformInit( void );
CCALL void		Sys_PlatformExit( void );
CCALL qboolean	Sys_GetPacket( netadr_t *net_from, msg_t *net_message );
CCALL char		*Sys_ConsoleInput( void );
CCALL void 		Sys_QueEvent( int time, sysEventType_t type, int value, int value2, int ptrLength, void *ptr );
CCALL void		Sys_SigHandler( int signal );
#ifndef _WIN32
CCALL void		Sys_AnsiColorPrint( const char *msg );
#endif

struct UnpackDLLResult
{
	bool succeeded;
	char *tempDLLPath;
};

CCALL UnpackDLLResult Sys_UnpackDLL( const char *name );
CCALL bool Sys_DLLNeedsUnpacking();
