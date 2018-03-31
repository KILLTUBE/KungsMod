/*
===========================================================================
Copyright (C) 1999 - 2005, Id Software, Inc.
Copyright (C) 2000 - 2013, Raven Software, Inc.
Copyright (C) 2001 - 2013, Activision, Inc.
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

CCALL void LAN_LoadCachedServers( );
CCALL void LAN_SaveServersToCache( );
CCALL void LAN_ResetPings(int source);
CCALL int LAN_AddServer(int source, const char *name, const char *address);
CCALL int LAN_AddFavAddr( const char *address );
CCALL void LAN_RemoveServer(int source, const char *addr);
CCALL int LAN_GetServerCount( int source );
CCALL void LAN_GetServerAddressString( int source, int n, char *buf, int buflen );
CCALL void LAN_GetServerInfo( int source, int n, char *buf, int buflen );
CCALL int LAN_GetServerPing( int source, int n );
CCALL int LAN_CompareServers( int source, int sortKey, int sortDir, int s1, int s2 );
CCALL int LAN_GetPingQueueCount( void );
CCALL void LAN_ClearPing( int n );
CCALL void LAN_GetPing( int n, char *buf, int buflen, int *pingtime );
CCALL void LAN_GetPingInfo( int n, char *buf, int buflen );
CCALL void LAN_MarkServerVisible(int source, int n, qboolean visible );
CCALL int LAN_ServerIsVisible(int source, int n );
CCALL qboolean LAN_UpdateVisiblePings(int source );
CCALL int LAN_GetServerStatus( const char *serverAddress, char *serverStatus, int maxLen );
