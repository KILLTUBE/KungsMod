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

// bg_local.h -- local definitions for the bg (both games) files

#define	MIN_WALK_NORMAL	0.7f		// can't walk on very steep slopes

#define	TIMER_LAND		130
#define	TIMER_GESTURE	(34*66+50)

#define	OVERCLIP		1.001f

// all of the locals will be zeroed before each
// pmove, just to make damn sure we don't have
// any differences when running on client or server
typedef struct
{
	vec3_t		forward, right, up;
	float		frametime;

	int			msec;

	qboolean	walking;
	qboolean	groundPlane;
	trace_t		groundTrace;

	float		impactSpeed;

	vec3_t		previous_origin;
	vec3_t		previous_velocity;
	int			previous_waterlevel;
} pml_t;


EXTERNC	pml_t		pml;

// movement parameters
EXTERNC	float	pm_stopspeed;
EXTERNC	float	pm_duckScale;
EXTERNC	float	pm_swimScale;
EXTERNC	float	pm_wadeScale;
EXTERNC	float	pm_accelerate;
EXTERNC	float	pm_airaccelerate;
EXTERNC	float	pm_wateraccelerate;
EXTERNC	float	pm_flyaccelerate;
EXTERNC	float	pm_friction;
EXTERNC	float	pm_waterfriction;
EXTERNC	float	pm_flightfriction;
EXTERNC	int		c_pmove;
EXTERNC int forcePowerNeeded[NUM_FORCE_POWER_LEVELS][NUM_FORCE_POWERS];

//PM anim utility functions:
CCALL qboolean PM_SaberInParry( int move );
CCALL qboolean PM_SaberInKnockaway( int move );
CCALL qboolean PM_SaberInReflect( int move );
CCALL qboolean PM_SaberInStart( int move );
CCALL qboolean PM_InSaberAnim( int anim );
CCALL qboolean PM_InKnockDown( playerState_t *ps );
CCALL qboolean PM_PainAnim( int anim );
CCALL qboolean PM_JumpingAnim( int anim );
CCALL qboolean PM_LandingAnim( int anim );
CCALL qboolean PM_SpinningAnim( int anim );
CCALL qboolean PM_InOnGroundAnim ( int anim );
CCALL qboolean PM_InRollComplete( playerState_t *ps, int anim );
CCALL int PM_AnimLength( int index, animNumber_t anim );
CCALL int PM_GetSaberStance(void);
CCALL float PM_GroundDistance(void);
CCALL qboolean PM_SomeoneInFront(trace_t *tr);
CCALL saberMoveName_t PM_SaberFlipOverAttackMove(void);
CCALL saberMoveName_t PM_SaberJumpAttackMove( void );
CCALL void PM_ClipVelocity( vec3_t in, vec3_t normal, vec3_t out, float overbounce );
CCALL void PM_AddTouchEnt( int entityNum );
CCALL void PM_AddEvent( int newEvent );
CCALL qboolean	PM_SlideMove( qboolean gravity );
CCALL void		PM_StepSlideMove( qboolean gravity );
CCALL void PM_StartTorsoAnim( int anim );
CCALL void PM_ContinueLegsAnim( int anim );
CCALL void PM_ForceLegsAnim( int anim );
CCALL void PM_BeginWeaponChange( int weapon );
CCALL void PM_FinishWeaponChange( void );
CCALL void PM_SetAnim(int setAnimParts,int anim,int setAnimFlags);
CCALL void PM_WeaponLightsaber(void);
CCALL void PM_SetSaberMove(short newMove);
CCALL void PM_SetForceJumpZStart(float value);
CCALL void BG_CycleInven(playerState_t *ps, int direction);

