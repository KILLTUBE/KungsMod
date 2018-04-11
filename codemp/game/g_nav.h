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

#include "b_local.h"
#include "server/sv_nav.h"


//This file is shared by the exe nav code.
//If you modify it without recompiling the exe with new code, there could be issues.

#define	WAYPOINT_NONE	-1

#define MAX_STORED_WAYPOINTS	512//???
#define MAX_WAYPOINT_REACHED_DIST_SQUARED	1024	//32 squared
#define	MAX_COLL_AVOID_DIST					128
#define	NAVGOAL_USE_RADIUS					16384	//Used to force the waypoint_navgoals with a manually set radius to actually do a DistanceSquared check, not just bounds overlap

#define	MIN_STOP_DIST 64
#define	MIN_BLOCKED_SPEECH_TIME	4000
#define	MIN_DOOR_BLOCK_DIST			16
#define	MIN_DOOR_BLOCK_DIST_SQR		( MIN_DOOR_BLOCK_DIST * MIN_DOOR_BLOCK_DIST )
#define	SHOVE_SPEED	200
#define SHOVE_LIFT	10
#define	MAX_RADIUS_CHECK	1024
#define	YAW_ITERATIONS	16


// Engine has its own copy of these (navigator.h)

#if /* _GAME &&*/ 1
	//rww - Rest of defines here are also shared in exe, do not modify.
	#define	__NEWCOLLECT	1

	#define _HARD_CONNECT	1

	//Node flags
	#define	NF_ANY			0
	//#define	NF_CLEAR_LOS	0x00000001
	#define NF_CLEAR_PATH	0x00000002
	#define NF_RECALC		0x00000004

	//Edge flags
	#define	EFLAG_NONE		0
	#define EFLAG_BLOCKED	0x00000001
	#define EFLAG_FAILED	0x00000002

	//Miscellaneous defines
	#define	NODE_NONE		-1
	#define	NAV_HEADER_ID	'JNV5'
	#define	NODE_HEADER_ID	'NODE'

	//this stuff is local and can be modified, don't even show it to the engine.
	EXTERNC	qboolean navCalculatePaths;
	EXTERNC	qboolean NAVDEBUG_showNodes;
	EXTERNC	qboolean NAVDEBUG_showRadius;
	EXTERNC	qboolean NAVDEBUG_showEdges;
	EXTERNC	qboolean NAVDEBUG_showTestPath;
	EXTERNC	qboolean NAVDEBUG_showEnemyPath;
	EXTERNC	qboolean NAVDEBUG_showCombatPoints;
	EXTERNC	qboolean NAVDEBUG_showNavGoals;
	EXTERNC	qboolean NAVDEBUG_showCollision;
	EXTERNC	int	 NAVDEBUG_curGoal;

#endif


#if !defined(FINAL_BUILD)
CCALL qboolean NAV_WaypointsTooFar(gentity_t *wp1,gentity_t *wp2);
EXTERNC char fatalErrorString[4096];
EXTERNC char *fatalErrorPointer;
EXTERNC int fatalErrors;
#endif
EXTERNC int NAVDEBUG_curGoal;
EXTERNC qboolean NAVDEBUG_showTestPath;
EXTERNC qboolean NAVDEBUG_showRadius;
EXTERNC qboolean NAVDEBUG_showEdges;
EXTERNC qboolean NAVDEBUG_showCombatPoints;
EXTERNC qboolean NAVDEBUG_showNavGoals;
EXTERNC qboolean NAVDEBUG_showNodes;
EXTERNC qboolean navCalculatePaths;
EXTERNC qboolean NAVDEBUG_showEnemyPath;
EXTERNC vec3_t NPCDEBUG_RED;
EXTERNC qboolean NAVDEBUG_showCollision;




CCALL void NAV_FindPlayerWaypoint(int clNum);
CCALL void NAV_ShowDebugInfo(void);
CCALL void NAV_Shutdown(void);
CCALL void NAV_CalculatePaths(const char *filename,int checksum);
CCALL int NAV_GetStoredWaypoint(char *targetname);
CCALL void NAV_ClearStoredWaypoints(void);
CCALL void Svcmd_Nav_f(void);
CCALL void SP_waypoint_navgoal_1(gentity_t *ent);
CCALL void SP_waypoint_navgoal_2(gentity_t *ent);
CCALL void SP_waypoint_navgoal_4(gentity_t *ent);
CCALL void SP_waypoint_navgoal_8(gentity_t *ent);
CCALL void SP_waypoint_navgoal(gentity_t *ent);
CCALL void SP_waypoint_small(gentity_t *ent);
CCALL void SP_waypoint(gentity_t *ent);
CCALL unsigned int waypoint_getRadius(gentity_t *ent);
CCALL unsigned int waypoint_testDirection(vec3_t origin,float yaw,unsigned int minDist);
CCALL int NAV_MoveToGoal(gentity_t *self,navInfo_t *info);
CCALL qboolean NAV_MicroError(vec3_t start,vec3_t end);
CCALL int NAV_GetNearestNode(gentity_t *self,int lastNode);
CCALL int NAV_TestBestNode(gentity_t *self,int startID,int endID,qboolean failEdge);
CCALL qboolean NAV_AvoidCollision(gentity_t *self,gentity_t *goal,navInfo_t *info);
CCALL qboolean NAV_TestForBlocked(gentity_t *self,gentity_t *goal,gentity_t *blocker,float distance,int *flags);
CCALL qboolean NAV_ResolveEntityCollision(gentity_t *self,gentity_t *blocker,vec3_t movedir,vec3_t pathDir);
CCALL qboolean NAV_StackedCanyon(gentity_t *self,gentity_t *blocker,vec3_t pathDir);
CCALL qboolean NAV_TrueCollision(gentity_t *self,gentity_t *blocker,vec3_t movedir,vec3_t blocked_dir);
CCALL qboolean NAV_ResolveBlock(gentity_t *self,gentity_t *blocker,vec3_t blocked_dir);
CCALL qboolean NAV_MoveBlocker(gentity_t *self,vec3_t shove_dir);
CCALL qboolean NAV_Bypass(gentity_t *self,gentity_t *blocker,vec3_t blocked_dir,float blocked_dist,vec3_t movedir);
CCALL int NAV_Steer(gentity_t *self,vec3_t dir,float distance);
CCALL void NAV_SetBlockedInfo(gentity_t *self,int entId);
CCALL void NAV_ClearBlockedInfo(gentity_t *self);
CCALL int NAV_FindClosestWaypointForPoint2(vec3_t point);
CCALL int NAV_FindClosestWaypointForPoint(gentity_t *ent,vec3_t point);
CCALL int NAV_FindClosestWaypointForEnt(gentity_t *ent,int targWp);
CCALL qboolean NAV_ClearPathToPoint(gentity_t *self,vec3_t pmins,vec3_t pmaxs,vec3_t point,int clipmask,int okToHitEntNum);
CCALL qboolean NAV_HitNavGoal(vec3_t point,vec3_t mins,vec3_t maxs,vec3_t dest,int radius,qboolean flying);
CCALL void NPC_SetMoveGoal(gentity_t *ent,vec3_t point,int radius,qboolean isNavGoal,int combatPoint,gentity_t *targetEnt);
CCALL void NPC_Blocked(gentity_t *self,gentity_t *blocker);
CCALL void NAV_StoreWaypoint(gentity_t *ent);
CCALL void NAV_StoreWaypoint(gentity_t *ent);
CCALL qboolean NAV_CheckAhead(gentity_t *self,vec3_t end,trace_t *trace,int clipmask);
CCALL qboolean NAV_CheckAhead(gentity_t *self,vec3_t end,trace_t *trace,int clipmask);
CCALL qboolean FlyingCreature(gentity_t *ent);
CCALL void TAG_ShowTags(int flags);
CCALL void G_DrawCombatPoint(vec3_t origin,int type);
CCALL void G_DrawNode(vec3_t origin,int type);
CCALL void G_DrawEdge(vec3_t start,vec3_t end,int type);
CCALL void G_CubeOutline(vec3_t mins,vec3_t maxs,int time,unsigned int color,float alpha);
CCALL void G_Cube(vec3_t mins,vec3_t maxs,vec3_t color,float alpha);
CCALL void G_Line(vec3_t start,vec3_t end,vec3_t color,float alpha);
CCALL qboolean G_FindClosestPointOnLineSegment(const vec3_t start,const vec3_t end,const vec3_t from,vec3_t result);
CCALL qboolean G_EntIsRemovableUsable(int entNum);
CCALL qboolean G_EntIsBreakable(int entityNum);
CCALL qboolean G_EntIsDoor(int entityNum);
CCALL qboolean G_EntIsUnlockedDoor(int entityNum);