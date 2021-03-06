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

// Simple linear memory allocator

#include "g_mem.h"

/*
  The purpose of G_Alloc is to efficiently allocate memory for objects
  typically when the game is starting up. It shouldn't be used as a general
  purpose allocator that's used when the game is running, and especially not
  from a client command! It is *by design* that memory blocks can't be
  deallocated while the game is running!

  If your mod experiences the allocation failed error often, use g_debugAlloc
  to trace down where G_Alloc is being called and to make sure it isn't used
  often while the game is running. Feel free to increase POOLSIZE for your mod!

  More information about Linear Allocators:
  http://www.altdevblogaday.com/2011/02/12/alternatives-to-malloc-and-new/
*/


static char		memoryPool[POOLSIZE];
static int		allocPoint;

void *G_Alloc( int size ) {
	char	*p;

	if ( size <= 0 ) {
		Com_Error( ERR_DROP, "G_Alloc: zero-size allocation\n", size );
		return NULL;
	}

	if ( g_debugAlloc->integer ) {
		Com_Printf( "G_Alloc of %i bytes (%i left)\n", size, POOLSIZE - allocPoint - ( ( size + 31 ) & ~31 ) );
	}

	if ( allocPoint + size > POOLSIZE ) {
		Com_Error( ERR_DROP, "G_Alloc: failed on allocation of %i bytes\n", size ); // bk010103 - was %u, but is signed
		return NULL;
	}

	p = &memoryPool[allocPoint];

	allocPoint += ( size + 31 ) & ~31;

	return p;
}

void G_InitMemory( void ) {
	allocPoint = 0;
}

void Svcmd_GameMem_f( void ) {
	float f = allocPoint;
	f /= POOLSIZE;
	f *= 100;
	Com_Printf("Game Memory Pool is %.1f%% full, %i bytes out of %i used.\n", f, allocPoint, POOLSIZE);
}
