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

#include "g_local.h"

//
// Cvar callbacks
//

/*
static void CVU_Derpity( void ) {
	// ...
}
*/


//
// Cvar table
//

//typedef struct cvarTable_s {
//	cvar_t	*vmCvar;
//	char		*cvarName;
//	char		*defaultString;
//	void		(*update)( void );
//	uint32_t	cvarFlags;
//	qboolean	trackChange; // announce if value changes
//} cvarTable_t;

#define XCVAR_DECL
	#include "g_xcvar.h"
#undef XCVAR_DECL

//#include "client/client.h"
cvar_t *Cvar_Get( const char *var_name, const char *var_value, uint32_t flags, const char *var_desc );

void G_RegisterCvars( void ) {

	#define XCVAR_LIST
		#include "g_xcvar.h"
	#undef XCVAR_LIST
	//g_gravity = Cvar_Get("g_gravity", "800", 0, "desc");

	//for ( i=0, cv=gameCvarTable; i<gameCvarTableSize; i++, cv++ ) {
	//	Cvar_Register( cv->vmCvar, cv->cvarName, cv->defaultString, cv->cvarFlags );
	//	if ( cv->update )
	//		cv->update();
	//}
}

void G_UpdateCvars( void ) {
	//size_t i = 0;
	//const cvarTable_t *cv = NULL;

	//for ( i=0, cv=gameCvarTable; i<gameCvarTableSize; i++, cv++ ) {
	//	if ( cv->vmCvar ) {
	//		int modCount = cv->vmCvar->modificationCount;
	//		Cvar_Update( cv->vmCvar );
	//		if ( cv->vmCvar->modificationCount != modCount ) {
	//			if ( cv->update )
	//				cv->update();
	//

	// trackChange is quite nice, need to embed that in main cvar system, along with typed cvars etc. + imgui interface

	//			if ( cv->trackChange )
	//				SV_GameSendServerCommand( -1, va("print \"Server: %s changed to %s\n\"", cv->cvarName, cv->vmCvar->string ) );
	//		}
	//	}
	//}
}
