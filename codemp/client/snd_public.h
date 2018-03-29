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

#include "qcommon/qcommon.h"

CCALL void S_Init( void );
CCALL void S_Shutdown( void );

// if origin is NULL, the sound will be dynamically sourced from the entity
CCALL void S_AddAmbientLoopingSound( const vec3_t origin, unsigned char volume, sfxHandle_t sfxHandle );
CCALL void S_StartAmbientSound( const vec3_t origin, int entityNum, unsigned char volume, sfxHandle_t sfxHandle );
CCALL void S_MuteSound(int entityNum, int entchannel);
CCALL void S_StartSound( const vec3_t origin, int entnum, int entchannel, sfxHandle_t sfx );
CCALL void S_StartLocalSound( sfxHandle_t sfx, int channelNum );
CCALL void S_StartLocalLoopingSound( sfxHandle_t sfx);

CCALL void S_UnCacheDynamicMusic( void );
CCALL void S_RestartMusic( void );
CCALL void S_StartBackgroundTrack( const char *intro, const char *loop, qboolean bCalledByCGameStart );
CCALL void S_StopBackgroundTrack( void );
CCALL float S_GetSampleLengthInMilliSeconds( sfxHandle_t sfxHandle);

// cinematics and voice-over-network will send raw samples
// 1.0 volume will be direct output of source samples
CCALL void S_RawSamples( int samples, int rate, int width, int channels, const byte *data, float volume, int bFirstOrOnlyUpdateThisFrame );
// stop all sounds
CCALL void S_StopSounds(void);	// from snd_dma.cpp
// stop all sounds and the background track
CCALL void S_StopAllSounds( void );

// scan all MP3s in the sound dir and add maxvol info if necessary.
CCALL void S_MP3_CalcVols_f( void );

// all continuous looping sounds must be added before calling S_Update
CCALL void S_ClearLoopingSounds( void );
CCALL void S_StopLoopingSound( int entityNum );
CCALL void S_AddLoopingSound( int entityNum, const vec3_t origin, const vec3_t velocity, sfxHandle_t sfx );

// recompute the reletive volumes for all running sounds
// relative to the given entityNum / orientation
CCALL void S_Respatialize( int entityNum, const vec3_t head, matrix3_t axis, int inwater );

// let the sound system know where an entity currently is
CCALL void S_UpdateEntityPosition( int entityNum, const vec3_t origin );

CCALL void S_Update( void );

CCALL void S_DisableSounds( void );

CCALL void S_BeginRegistration( void );

// RegisterSound will allways return a valid sample, even if it
// has to create a placeholder.  This prevents continuous filesystem
// checks for missing files
CCALL sfxHandle_t	S_RegisterSound( const char *sample );

extern qboolean s_shutUp;

CCALL void S_FreeAllSFXMem(void);
