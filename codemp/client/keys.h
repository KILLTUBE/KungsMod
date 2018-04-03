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

#include "ui/keycodes.h"
#include "client/keycodes.h"

typedef struct qkey_s {
	qboolean	down;
	int			repeats; // if > 1, it is autorepeating
	char		*binding;
} qkey_t;

typedef struct keyGlobals_s {
	qboolean	anykeydown;
	qboolean	key_overstrikeMode;
	int			keyDownCount;

	qkey_t		keys[MAX_KEYS];
} keyGlobals_t;

typedef struct keyname_s {
	word		upper, lower;
	const char	*name;
	int			keynum;
	bool		menukey;
} keyname_t;

EXTERNC keyGlobals_t	kg;
EXTERNC keyname_t	keynames[MAX_KEYS];

// console
EXTERNC field_t		g_consoleField;
EXTERNC int			nextHistoryLine;	// the last line in the history buffer, not masked
EXTERNC int			historyLine;		// the line being displayed from history buffer will be <= nextHistoryLine
EXTERNC field_t		historyEditLines[COMMAND_HISTORY];

// chat
EXTERNC field_t		chatField;
EXTERNC qboolean		chat_team;
EXTERNC int			chat_playerNum;

CCALL void	Field_KeyDownEvent	( field_t *edit, int key );
CCALL void	Field_CharEvent		( field_t *edit, int ch );
CCALL void	Field_Draw			( field_t *edit, int x, int y, int width, qboolean showCursor, qboolean noColorEscape );
CCALL void	Field_BigDraw		( field_t *edit, int x, int y, int width, qboolean showCursor, qboolean noColorEscape );

CCALL void		Key_SetBinding			( int keynum, const char *binding );
CCALL char *		Key_GetBinding			( int keynum );
CCALL qboolean	Key_IsDown				( int keynum );
CCALL int			Key_StringToKeynum		( char *str );
CCALL qboolean	Key_GetOverstrikeMode	( void );
CCALL void		Key_SetOverstrikeMode	( qboolean state );
CCALL void		Key_ClearStates			( void );
CCALL int			Key_GetKey				( const char *binding );
