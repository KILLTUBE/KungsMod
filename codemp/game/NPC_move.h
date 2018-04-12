#pragma once

#include "b_local.h"
#include "g_nav.h"
#include "anims.h"

EXTERNC navInfo_t frameNavInfo;
#if AI_TIMERS
EXTERNC int navTime;
#endif

CCALL void NPC_ApplyRoff(void);
CCALL qboolean NPC_SlideMoveToGoal(void);
CCALL qboolean NPC_MoveToGoal(qboolean tryStraight);
CCALL void G_UcmdMoveForDir(gentity_t *self,usercmd_t *cmd,vec3_t dir);
CCALL qboolean NPC_GetMoveDirectionAltRoute(vec3_t out,float *distance,qboolean tryStraight);
CCALL qboolean NAVNEW_AvoidCollision(gentity_t *self,gentity_t *goal,navInfo_t *info,qboolean setBlockedInfo,int blockedMovesLimit);
CCALL int NAVNEW_MoveToGoal(gentity_t *self,navInfo_t *info);
CCALL qboolean NPC_GetMoveDirection(vec3_t out,float *distance);
CCALL void NAV_GetLastMove(navInfo_t *info);
CCALL qboolean NPC_ClearPathToGoal(vec3_t dir,gentity_t *goal);
CCALL qboolean PM_InKnockDown(playerState_t *ps);
CCALL qboolean FlyingCreature(gentity_t *ent);
CCALL int GetTime(int lastTime);
CCALL int NAV_Steer(gentity_t *self,vec3_t dir,float distance);
CCALL qboolean G_BoundsOverlap(const vec3_t mins1,const vec3_t maxs1,const vec3_t mins2,const vec3_t maxs2);
CCALL void G_Cylinder(vec3_t start,vec3_t end,float radius,vec3_t color);
