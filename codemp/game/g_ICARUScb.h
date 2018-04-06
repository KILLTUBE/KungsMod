/*
===========================================================================
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

CCALL int Q3_PlaySound( int taskID, int entID, const char *name, const char *channel );
CCALL qboolean Q3_Set( int taskID, int entID, const char *type_name, const char *data );
CCALL void Q3_Lerp2Pos( int taskID, int entID, vec3_t origin, vec3_t angles, float duration );
CCALL void Q3_Lerp2Origin( int taskID, int entID, vec3_t origin, float duration );
CCALL void Q3_Lerp2Angles( int taskID, int entID, vec3_t angles, float duration );
CCALL int Q3_GetTag( int entID, const char *name, int lookup, vec3_t info );
CCALL void Q3_Lerp2Start( int entID, int taskID, float duration );
CCALL void Q3_Lerp2End( int entID, int taskID, float duration );
CCALL void Q3_Use( int entID, const char *target );
CCALL void Q3_Kill( int entID, const char *name );
CCALL void Q3_Remove( int entID, const char *name );
CCALL void Q3_Play( int taskID, int entID, const char *type, const char *name );
CCALL int Q3_GetFloat( int entID, int type, const char *name, float *value );
CCALL int Q3_GetVector( int entID, int type, const char *name, vec3_t value );
CCALL int Q3_GetString( int entID, int type, const char *name, char **value );
