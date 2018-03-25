/*
===========================================================================
Copyright (C) 2010 James Canete (use.less01@gmail.com)

This file is part of Quake III Arena source code.

Quake III Arena source code is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

Quake III Arena source code is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Quake III Arena source code; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
===========================================================================
*/
// tr_subs.c - common function replacements for modular renderer

#include "../rd-rend2/tr_local.h"



// HUNK
//void *Hunk_AllocateTempMemory( int size ) {
//	return ri.Hunk_AllocateTempMemory( size );
//}
//
//void Hunk_FreeTempMemory( void *buf ) {
//	ri.Hunk_FreeTempMemory( buf );
//}
//
//void *Hunk_Alloc( int size, ha_pref preference ) {
//	return ri.Hunk_Alloc( size, preference );
//}
//
//int Hunk_MemoryRemaining( void ) {
//	return ri.Hunk_MemoryRemaining();
//}

//// ZONE
//void *Z_Malloc( int iSize, memtag_t eTag, qboolean bZeroit, int iAlign ) {
//	return ri.Z_Malloc( iSize, eTag, bZeroit, iAlign );
//}
//
//void Z_Free( void *ptr ) {
//	ri.Z_Free( ptr );
//}
//
//int Z_MemSize( memtag_t eTag ) {
//	return ri.Z_MemSize( eTag );
//}
//
//void Z_MorphMallocTag( void *pvBuffer, memtag_t eDesiredTag ) {
//	ri.Z_MorphMallocTag( pvBuffer, eDesiredTag );
//}


void *R_Malloc(int iSize, memtag_t eTag, qboolean bZeroit) {
	return ri.Z_Malloc(iSize, eTag, bZeroit, 4);
}

void R_Free(void *ptr) {
	Z_Free(ptr);
}

int R_MemSize(memtag_t eTag) {
	return Z_MemSize(eTag);
}

void R_MorphMallocTag(void *pvBuffer, memtag_t eDesiredTag) {
	Z_MorphMallocTag(pvBuffer, eDesiredTag);
}

void *R_Hunk_Alloc(int iSize, qboolean bZeroit) {
	return ri.Z_Malloc(iSize, TAG_TEMP_HUNKALLOC, bZeroit, 4);
}







	GoreTextureCoordinates::GoreTextureCoordinates()
	{
		int i;
		for (i=0;i<MAX_LODS;i++)
		{
			tex[i]=0;
		}
	}
	GoreTextureCoordinates::~GoreTextureCoordinates()
	{
		int i;
		for (i=0;i<MAX_LODS;i++)
		{
			if ( tex[i] )
			{
				extern void R_Free(void *pvAddress);
				R_Free(tex[i]);
				tex[i] = 0;
			}
		}
	}