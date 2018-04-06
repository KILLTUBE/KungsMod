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

//B_local.h
//re-added by MCG

#include "g_local.h"
#include "b_public.h"
#include "say.h"

#include "ai.h"

#define	AI_TIMERS 0//turn on to see print-outs of AI/nav timing
//
// Navigation susbsystem
//

#define NAVF_DUCK			0x00000001
#define NAVF_JUMP			0x00000002
#define NAVF_HOLD			0x00000004
#define NAVF_SLOW			0x00000008

#define DEBUG_LEVEL_DETAIL	4
#define DEBUG_LEVEL_INFO	3
#define DEBUG_LEVEL_WARNING	2
#define DEBUG_LEVEL_ERROR	1
#define DEBUG_LEVEL_NONE	0

#define MAX_GOAL_REACHED_DIST_SQUARED	256//16 squared
#define MIN_ANGLE_ERROR 0.01f

#define MIN_ROCKET_DIST_SQUARED 16384//128*128
//
// NPC.cpp
//
// ai debug cvars
CCALL void SetNPCGlobals( gentity_t *ent );
CCALL void SaveNPCGlobals(void);
CCALL void RestoreNPCGlobals(void);
CCALL void NPC_Think ( gentity_t *self);

//NPC_reactions.cpp
CCALL void NPC_Pain(gentity_t *self, gentity_t *attacker, int damage);
CCALL void NPC_Touch( gentity_t *self, gentity_t *other, trace_t *trace );
CCALL void NPC_Use( gentity_t *self, gentity_t *other, gentity_t *activator );
CCALL float NPC_GetPainChance( gentity_t *self, int damage );

//
// NPC_misc.cpp
//
CCALL void Debug_Printf( cvar_t *cv, int level, char *fmt, ... );
CCALL void Debug_NPCPrintf( gentity_t *printNPC, cvar_t *cv, int debugLevel, char *fmt, ... );

//MCG - Begin============================================================
//NPC_ai variables - shared by NPC.cpp and the following modules
//OJKFIXME: Should probably construct these at the NPC entry points and pass as arguments to any function that needs them
typedef struct npcStatic_s {
	gentity_t		*NPC;
	gNPC_t			*NPCInfo;
	gclient_t		*client;
	usercmd_t		 ucmd;
	visibility_t	 enemyVisibility;
} npcStatic_t;
EXTERNC npcStatic_t NPCS;

//AI_Default
CCALL qboolean NPC_CheckInvestigate( int alertEventNum );
CCALL qboolean NPC_StandTrackAndShoot (gentity_t *NPC, qboolean canDuck);
CCALL void NPC_BSIdle( void );
CCALL void NPC_BSPointShoot(qboolean shoot);
CCALL void NPC_BSStandGuard (void);
CCALL void NPC_BSPatrol (void);
CCALL void NPC_BSHuntAndKill (void);
CCALL void NPC_BSStandAndShoot (void);
CCALL void NPC_BSRunAndShoot (void);
CCALL void NPC_BSWait( void );
CCALL void NPC_BSDefault( void );

//NPC_behavior
CCALL void NPC_BSAdvanceFight (void);
CCALL void NPC_BSInvestigate (void);
CCALL void NPC_BSSleep( void );
CCALL void NPC_BSFlee (void);
CCALL void NPC_BSFollowLeader (void);
CCALL void NPC_BSJump (void);
CCALL void NPC_BSRemove (void);
CCALL void NPC_BSSearch (void);
CCALL void NPC_BSSearchStart (int	homeWp, bState_t bState);
CCALL void NPC_BSWander (void);
CCALL void NPC_BSFlee( void );
CCALL void NPC_StartFlee( gentity_t *enemy, vec3_t dangerPoint, int dangerLevel, int fleeTimeMin, int fleeTimeMax );
CCALL void G_StartFlee( gentity_t *self, gentity_t *enemy, vec3_t dangerPoint, int dangerLevel, int fleeTimeMin, int fleeTimeMax );

//NPC_combat
CCALL int ChooseBestWeapon( void );
CCALL void NPC_ChangeWeapon( int newWeapon );
CCALL void ShootThink( void );
CCALL void WeaponThink( qboolean inCombat );
CCALL qboolean HaveWeapon( int weapon );
CCALL qboolean CanShoot ( gentity_t *ent, gentity_t *shooter );
CCALL void NPC_CheckPossibleEnemy( gentity_t *other, visibility_t vis );
CCALL gentity_t *NPC_PickEnemy (gentity_t *closestTo, int enemyTeam, qboolean checkVis, qboolean findPlayersFirst, qboolean findClosest);
CCALL gentity_t *NPC_CheckEnemy (qboolean findNew, qboolean tooFarOk, qboolean setEnemy ); //setEnemy = qtrue
CCALL qboolean NPC_CheckAttack (float scale);
CCALL qboolean NPC_CheckDefend (float scale);
CCALL qboolean NPC_CheckCanAttack (float attack_scale, qboolean stationary);
CCALL int NPC_AttackDebounceForWeapon (void);
CCALL qboolean EntIsGlass (gentity_t *check);
CCALL qboolean ShotThroughGlass (trace_t *tr, gentity_t *target, vec3_t spot, int mask);
CCALL qboolean ValidEnemy (gentity_t *ent);
CCALL void G_ClearEnemy (gentity_t *self);
CCALL gentity_t *NPC_PickAlly ( qboolean facingEachOther, float range, qboolean ignoreGroup, qboolean movingOnly );
CCALL void NPC_LostEnemyDecideChase(void);
CCALL float NPC_MaxDistSquaredForWeapon( void );
CCALL qboolean NPC_EvaluateShot( int hit, qboolean glassOK );
CCALL int NPC_ShotEntity( gentity_t *ent, vec3_t impactPos ); //impactedPos = NULL

//NPC_formation
CCALL qboolean NPC_SlideMoveToGoal (void);
CCALL float NPC_FindClosestTeammate (gentity_t *self);
CCALL void NPC_CalcClosestFormationSpot(gentity_t *self);
CCALL void G_MaintainFormations (gentity_t *self);
CCALL void NPC_BSFormation (void);
CCALL void NPC_CreateFormation (gentity_t *self);
CCALL void NPC_DropFormation (gentity_t *self);
CCALL void NPC_ReorderFormation (gentity_t *self);
CCALL void NPC_InsertIntoFormation (gentity_t *self);
CCALL void NPC_DeleteFromFormation (gentity_t *self);

#define COLLISION_RADIUS 32
#define NUM_POSITIONS 30

//NPC spawnflags
#define SFB_RIFLEMAN	2
#define SFB_PHASER		4

#define	SFB_CINEMATIC	32
#define	SFB_NOTSOLID	64
#define	SFB_STARTINSOLID 128

//NPC_goal
CCALL void SetGoal( gentity_t *goal, float rating );
CCALL void NPC_SetGoal( gentity_t *goal, float rating );
CCALL void NPC_ClearGoal( void );
CCALL void NPC_ReachedGoal( void );
CCALL qboolean ReachedGoal( gentity_t *goal );
CCALL gentity_t *UpdateGoal( void );
CCALL qboolean NPC_ClearPathToGoal(vec3_t dir, gentity_t *goal);
CCALL qboolean NPC_MoveToGoal( qboolean tryStraight );

//NPC_reactions

//NPC_senses
#define	ALERT_CLEAR_TIME	200
#define CHECK_PVS		1
#define CHECK_360		2
#define CHECK_FOV		4
#define CHECK_SHOOT		8
#define CHECK_VISRANGE	16
CCALL qboolean CanSee ( gentity_t *ent );
CCALL qboolean InFOV ( gentity_t *ent, gentity_t *from, int hFOV, int vFOV );
CCALL qboolean InFOV2( vec3_t origin, gentity_t *from, int hFOV, int vFOV );
CCALL qboolean InFOV3( vec3_t spot, vec3_t from, vec3_t fromAngles, int hFOV, int vFOV );
CCALL visibility_t NPC_CheckVisibility ( gentity_t *ent, int flags );
CCALL qboolean InVisrange ( gentity_t *ent );

//NPC_spawn
CCALL void NPC_Spawn ( gentity_t *ent, gentity_t *other, gentity_t *activator );

//NPC_stats
CCALL int NPC_ReactionTime ( void );
CCALL qboolean NPC_ParseParms( const char *NPCName, gentity_t *NPC );
CCALL void NPC_LoadParms( void );

//NPC_utils
EXTERNC int	teamNumbers[TEAM_NUM_TEAMS];
EXTERNC int	teamStrength[TEAM_NUM_TEAMS];
EXTERNC int	teamCounter[TEAM_NUM_TEAMS];
CCALL void CalcEntitySpot ( const gentity_t *ent, const spot_t spot, vec3_t point );
CCALL qboolean NPC_UpdateAngles ( qboolean doPitch, qboolean doYaw );
CCALL void NPC_UpdateShootAngles (vec3_t angles, qboolean doPitch, qboolean doYaw );
CCALL qboolean NPC_UpdateFiringAngles ( qboolean doPitch, qboolean doYaw );
CCALL void SetTeamNumbers (void);
CCALL qboolean G_ActivateBehavior (gentity_t *self, int bset );
CCALL void NPC_AimWiggle( vec3_t enemy_org );
CCALL void NPC_ClearLookTarget( gentity_t *self );
CCALL void NPC_SetLookTarget( gentity_t *self, int entNum, int clearTime );

//g_nav.cpp
CCALL int NAV_FindClosestWaypointForEnt (gentity_t *ent, int targWp);
CCALL qboolean NAV_CheckAhead( gentity_t *self, vec3_t end, trace_t *trace, int clipmask );

//NPC_combat
CCALL float IdealDistance ( gentity_t *self );

//g_squad
CCALL void NPC_SetSayState (gentity_t *self, gentity_t *to, int saying);

//g_utils
CCALL qboolean G_CheckInSolid (gentity_t *self, qboolean fix);

//MCG - End============================================================

// NPC.cpp
#include "NPC.h"
CCALL qboolean NPC_EnemyTooFar(gentity_t *enemy, float dist, qboolean toShoot);

// ==================================================================

//rww - special system for sync'ing bone angles between client and server.
CCALL void NPC_SetBoneAngles(gentity_t *ent, char *bone, vec3_t angles);

//rww - and another method of automatically managing surface status for the client and server at once
CCALL void NPC_SetSurfaceOnOff(gentity_t *ent, const char *surfaceName, int surfaceFlags);

CCALL qboolean NPC_ClearLOS( const vec3_t start, const vec3_t end );
CCALL qboolean NPC_ClearLOS5( const vec3_t end );
CCALL qboolean NPC_ClearLOS4( gentity_t *ent ) ;
CCALL qboolean NPC_ClearLOS3( const vec3_t start, gentity_t *ent );
CCALL qboolean NPC_ClearLOS2( gentity_t *ent, const vec3_t end );

CCALL qboolean NPC_ClearShot( gentity_t *ent );

CCALL int NPC_FindCombatPoint( const vec3_t position, const vec3_t avoidPosition, vec3_t enemyPosition, const int flags, const float avoidDist, const int ignorePoint ); //ignorePoint = -1


CCALL qboolean NPC_ReserveCombatPoint( int combatPointID );
CCALL qboolean NPC_FreeCombatPoint( int combatPointID, qboolean failed ); //failed = qfalse
CCALL qboolean NPC_SetCombatPoint( int combatPointID );

#define	CP_ANY			0			//No flags
#define	CP_COVER		0x00000001	//The enemy cannot currently shoot this position
#define CP_CLEAR		0x00000002	//This cover point has a clear shot to the enemy
#define CP_FLEE			0x00000004	//This cover point is marked as a flee point
#define CP_DUCK			0x00000008	//This cover point is marked as a duck point
#define CP_NEAREST		0x00000010	//Find the nearest combat point
#define CP_AVOID_ENEMY	0x00000020	//Avoid our enemy
#define CP_INVESTIGATE	0x00000040	//A special point worth enemy investigation if searching
#define	CP_SQUAD		0x00000080	//Squad path
#define	CP_AVOID		0x00000100	//Avoid supplied position
#define	CP_APPROACH_ENEMY 0x00000200	//Try to get closer to enemy
#define	CP_CLOSEST		0x00000400	//Take the closest combatPoint to the enemy that's available
#define	CP_FLANK		0x00000800	//Pick a combatPoint behind the enemy
#define	CP_HAS_ROUTE	0x00001000	//Pick a combatPoint that we have a route to
#define	CP_SNIPE		0x00002000	//Pick a combatPoint that is marked as a sniper spot
#define	CP_SAFE			0x00004000	//Pick a combatPoint that is not have dangerTime
#define	CP_HORZ_DIST_COLL 0x00008000	//Collect combat points within *horizontal* dist
#define	CP_NO_PVS		0x00010000	//A combat point out of the PVS of enemy pos
#define	CP_RETREAT		0x00020000	//Try to get farther from enemy

#define CPF_NONE		0
#define	CPF_DUCK		0x00000001
#define	CPF_FLEE		0x00000002
#define	CPF_INVESTIGATE	0x00000004
#define	CPF_SQUAD		0x00000008
#define	CPF_LEAN		0x00000010
#define	CPF_SNIPE		0x00000020

#define	MAX_COMBAT_POINT_CHECK	32

CCALL qboolean NPC_ValidEnemy( gentity_t *ent );
CCALL qboolean NPC_CheckEnemyExt( qboolean checkAlerts ); //checkAlerts = qfalse
CCALL qboolean NPC_FindPlayer( void );
CCALL qboolean NPC_CheckCanAttackExt( void );
CCALL int NPC_CheckAlertEvents( qboolean checkSight, qboolean checkSound, int ignoreAlert, qboolean mustHaveOwner, int minAlertLevel ); //ignoreAlert = -1, mustHaveOwner = qfalse, minAlertLevel = AEL_MINOR
CCALL qboolean NPC_CheckForDanger( int alertEvent );
CCALL void G_AlertTeam( gentity_t *victim, gentity_t *attacker, float radius, float soundDist );
CCALL int NPC_FindSquadPoint( vec3_t position );
CCALL void ClearPlayerAlertEvents( void );
CCALL qboolean G_BoundsOverlap(const vec3_t mins1, const vec3_t maxs1, const vec3_t mins2, const vec3_t maxs2);
CCALL qboolean NAV_HitNavGoal( vec3_t point, vec3_t mins, vec3_t maxs, vec3_t dest, int radius, qboolean flying );
CCALL void NPC_SetMoveGoal( gentity_t *ent, vec3_t point, int radius, qboolean isNavGoal, int combatPoint, gentity_t *targetEnt ); //isNavGoal = qfalse, combatPoint = -1, targetEnt = NULL
CCALL qboolean NAV_ClearPathToPoint(gentity_t *self, vec3_t pmins, vec3_t pmaxs, vec3_t point, int clipmask, int okToHitEnt );
CCALL void NPC_ApplyWeaponFireDelay(void);

//NPC_FaceXXX suite
CCALL qboolean NPC_FacePosition( vec3_t position, qboolean doPitch ); //doPitch = qtrue
CCALL qboolean NPC_FaceEntity( gentity_t *ent, qboolean doPitch ); //doPitch = qtrue
CCALL qboolean NPC_FaceEnemy( qboolean doPitch ); //doPitch = qtrue

#define	NIF_NONE		0x00000000
#define	NIF_FAILED		0x00000001	//failed to find a way to the goal
#define	NIF_MACRO_NAV	0x00000002	//using macro navigation
#define	NIF_COLLISION	0x00000004	//resolving collision with an entity
#define NIF_BLOCKED		0x00000008	//blocked from moving

/*
-------------------------
struct navInfo_s
-------------------------
*/

typedef struct navInfo_s
{
	gentity_t	*blocker;
	vec3_t		direction;
	vec3_t		pathDirection;
	float		distance;
	trace_t		trace;
	int			flags;
} navInfo_t;

CCALL int	NAV_MoveToGoal( gentity_t *self, navInfo_t *info );
CCALL void NAV_GetLastMove( navInfo_t *info );
CCALL qboolean NAV_AvoidCollision( gentity_t *self, gentity_t *goal, navInfo_t *info );
