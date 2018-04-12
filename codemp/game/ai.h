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

//Distance ratings
typedef enum
{
	DIST_MELEE,
	DIST_LONG,
} distance_e;

//Attack types
typedef enum
{
	ATTACK_MELEE,
	ATTACK_RANGE,
} attack_e;

enum
{
	SQUAD_IDLE,					//No target found, waiting
	SQUAD_STAND_AND_SHOOT,		//Standing in position and shoot (no cover)
	SQUAD_RETREAT,				//Running away from combat
	SQUAD_COVER,				//Under protective cover
	SQUAD_TRANSITION,			//Moving between points, not firing
	SQUAD_POINT,				//On point, laying down suppressive fire
	SQUAD_SCOUT,				//Poking out to draw enemy
	NUM_SQUAD_STATES,
};

//sigh... had to move in here for groupInfo
typedef enum //# rank_e
{
	RANK_CIVILIAN,
	RANK_CREWMAN,
	RANK_ENSIGN,
	RANK_LT_JG,
	RANK_LT,
	RANK_LT_COMM,
	RANK_COMMANDER,
	RANK_CAPTAIN
} rank_t;

CCALL qboolean NPC_CheckPlayerTeamStealth( void );

//AI_GRENADIER
CCALL void NPC_BSGrenadier_Default( void );

//AI_SNIPER
CCALL void NPC_BSSniper_Default( void );

//AI_STORMTROOPER
CCALL void NPC_BSST_Investigate( void );
CCALL void NPC_BSST_Default( void );
CCALL void NPC_BSST_Sleep( void );

//AI_JEDI
CCALL void NPC_BSJedi_Investigate( void );
CCALL void NPC_BSJedi_Default( void );
CCALL void NPC_BSJedi_FollowLeader( void );

// AI_DROID
CCALL void NPC_BSDroid_Default( void );

// AI_ImperialProbe
CCALL void NPC_BSImperialProbe_Default( void );

// AI_atst
CCALL void NPC_BSATST_Default( void );

CCALL void NPC_BSInterrogator_Default( void );

// AI Mark 1
CCALL void NPC_BSMark1_Default( void );

// AI Mark 2
CCALL void NPC_BSMark2_Default( void );

CCALL void NPC_BSMineMonster_Default( void );
CCALL void NPC_BSHowler_Default( void );
CCALL void NPC_BSRancor_Default( void );

//Utilities
//Group AI
#define	MAX_FRAME_GROUPS	32
// !!!!!!!!!! LOADSAVE-affecting structure !!!!!!!!!!
typedef struct AIGroupMember_s
{
	int	number;
	int waypoint;
	int pathCostToEnemy;
	int	closestBuddy;
} AIGroupMember_t;

#define MAX_GROUP_MEMBERS 32
// !!!!!!!!!! LOADSAVE-affecting structure !!!!!!!!!!
typedef struct AIGroupInfo_s
{
	int			numGroup;
	qboolean	processed;
	team_t		team;
	gentity_t	*enemy;
	int			enemyWP;
	int			speechDebounceTime;
	int			lastClearShotTime;
	int			lastSeenEnemyTime;
	int			morale;
	int			moraleAdjust;
	int			moraleDebounce;
	int			memberValidateTime;
	int			activeMemberNum;
	gentity_t	*commander;
	vec3_t		enemyLastSeenPos;
	int			numState[ NUM_SQUAD_STATES ];
	AIGroupMember_t member[ MAX_GROUP_MEMBERS ];
} AIGroupInfo_t;

CCALL int	AI_GetGroupSize( vec3_t origin, int radius, team_t playerTeam, gentity_t *avoid );
CCALL int AI_GetGroupSize2( gentity_t *ent, int radius );
CCALL void AI_GetGroup( gentity_t *self );
CCALL qboolean AI_CheckEnemyCollision( gentity_t *ent, qboolean takeEnemy );
CCALL gentity_t *AI_DistributeAttack( gentity_t *attacker, gentity_t *enemy, team_t team, int threshold );
