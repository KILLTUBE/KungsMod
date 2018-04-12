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

#include "qcommon/qfiles.h"

#define NUM_FORCE_STAR_IMAGES  9
#define FORCE_NONJEDI	0
#define FORCE_JEDI		1

EXTERNC int uiForceSide;
EXTERNC int uiJediNonJedi;
EXTERNC int uiForceRank;
EXTERNC int uiMaxRank;
EXTERNC int uiForceUsed;
EXTERNC int uiForceAvailable;
EXTERNC qboolean gTouchedForce;
EXTERNC qboolean uiForcePowersDisabled[NUM_FORCE_POWERS];
EXTERNC int uiForcePowersRank[NUM_FORCE_POWERS];
EXTERNC int uiForcePowerDarkLight[NUM_FORCE_POWERS];
EXTERNC int uiSaberColorShaders[NUM_SABER_COLORS];
// Dots above or equal to a given rank carry a certain color.

CCALL void UI_InitForceShaders(void);
CCALL void UI_ReadLegalForce(void);
CCALL void UI_DrawTotalForceStars(rectDef_t *rect, float scale, vec4_t color, int textStyle);
CCALL void UI_DrawForceStars(rectDef_t *rect, float scale, vec4_t color, int textStyle, int findex, int val, int min, int max) ;
CCALL void UI_UpdateClientForcePowers(const char *teamArg);
CCALL void UI_SaveForceTemplate();
CCALL void UI_UpdateForcePowers();
CCALL qboolean UI_SkinColor_HandleKey(int flags, float *special, int key, int num, int min, int max, int type);
CCALL qboolean UI_ForceSide_HandleKey(int flags, float *special, int key, int num, int min, int max, int type);
CCALL qboolean UI_JediNonJedi_HandleKey(int flags, float *special, int key, int num, int min, int max, int type);
CCALL qboolean UI_ForceMaxRank_HandleKey(int flags, float *special, int key, int num, int min, int max, int type);
CCALL qboolean UI_ForcePowerRank_HandleKey(int flags, float *special, int key, int num, int min, int max, int type);
CCALL void UI_ForceConfigHandle( int oldindex, int newindex );
CCALL void UpdateForceUsed();