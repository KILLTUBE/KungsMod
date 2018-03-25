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

#include "../server/exe_headers.h"

// tr_subs.cpp - common function replacements for modular renderer
#include "tr_local.h"

//void QDECL Com_Printf(const char *msg, ...)
//{
//	va_list         argptr;
//	char            text[1024];
//
//	va_start(argptr, msg);
//	Q_vsnprintf(text, sizeof(text), msg, argptr);
//	va_end(argptr);
//
//	R_Printf(PRINT_ALL, "%s", text);
//}
//
//void QDECL Com_Error(int level, const char *error, ...)
//{
//	va_list         argptr;
//	char            text[1024];
//
//	va_start(argptr, error);
//	Q_vsnprintf(text, sizeof(text), error, argptr);
//	va_end(argptr);
//
//	R_Error(level, "%s", text);
//}

/*
================
Com_DPrintf

DLL glue
================
*/
//void Com_DPrintf(const char *format, ...)
//{
//	va_list         argptr;
//	char            text[1024];
//
//	va_start(argptr, format);
//	Q_vsnprintf(text, sizeof(text), format, argptr);
//	va_end(argptr);
//
//	R_Printf(PRINT_DEVELOPER, "%s", text);
//}

// HUNK

//int Hunk_MemoryRemaining( void ) {
//	return ri.Hunk_MemoryRemaining();
//}

// ZONE
#if 1 //SP
void *R_Malloc(int iSize, memtag_t eTag, qboolean bZeroit) {
	return Malloc(iSize, eTag, bZeroit, 4);
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
	return Malloc(iSize, TAG_HUNKALLOC, bZeroit, 4);
}

#else // UniqueOne's Version

void *R_Malloc(int iSize, memtag_t eTag, qboolean bZeroit) {
#ifndef __USE_MALLOC__
	return ri.Malloc(iSize, eTag, qtrue/*bZeroit*/, 4);
#else
	void *mem = malloc(iSize);

	//if (bZeroit)
	{
		memset(mem, 0, iSize);
	}

	return mem;
#endif
}

void R_Free(void *ptr) {
#ifndef __USE_MALLOC__
	ri.Z_Free(ptr);
#else
	free(ptr);
#endif
}

int R_MemSize(memtag_t eTag) {
	return ri.Z_MemSize(eTag);
}

void R_MorphMallocTag(void *pvBuffer, memtag_t eDesiredTag) {
#ifndef __USE_MALLOC__
	ri.Z_MorphMallocTag(pvBuffer, eDesiredTag);
#endif
}

void *R_Hunk_Alloc(int iSize, qboolean bZeroit) {
#ifndef __USE_MALLOC__
	return ri.Malloc(iSize, TAG_HUNKALLOC, qtrue/*bZeroit*/, 4);
#else
	return R_Malloc(iSize, TAG_HUNKALLOC, bZeroit);
#endif
}
#endif