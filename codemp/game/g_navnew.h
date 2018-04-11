#pragma once

#include "b_local.h"
#include "g_nav.h"
#include "server/sv_nav.h"

CCALL int NAVNEW_MoveToGoal(gentity_t *self,navInfo_t *info);
CCALL qboolean NAVNEW_TestNodeConnectionBlocked(int wp1,int wp2,gentity_t *ignoreEnt,int goalEntNum,qboolean checkWorld,qboolean checkEnts);
CCALL qboolean NAVNEW_AvoidCollision(gentity_t *self,gentity_t *goal,navInfo_t *info,qboolean setBlockedInfo,int blockedMovesLimit);
CCALL qboolean NAVNEW_ResolveEntityCollision(gentity_t *self,gentity_t *blocker,vec3_t movedir,vec3_t pathDir,qboolean setBlockedInfo);
CCALL void CalcTeamDoorCenter(gentity_t *ent,vec3_t center);
CCALL qboolean NAVNEW_CheckDoubleBlock(gentity_t *self,gentity_t *blocker,vec3_t blocked_dir);
CCALL qboolean NAVNEW_Bypass(gentity_t *self,gentity_t *blocker,vec3_t blocked_dir,float blocked_dist,vec3_t movedir,qboolean setBlockedInfo);
CCALL qboolean NAVNEW_SidestepBlocker(gentity_t *self,gentity_t *blocker,vec3_t blocked_dir,float blocked_dist,vec3_t movedir,vec3_t right);
CCALL qboolean NAVNEW_DanceWithBlocker(gentity_t *self,gentity_t *blocker,vec3_t movedir,vec3_t right);
CCALL void NAVNEW_PushBlocker(gentity_t *self,gentity_t *blocker,vec3_t right,qboolean setBlockedInfo);
CCALL int NAVNEW_ClearPathBetweenPoints(vec3_t start,vec3_t end,vec3_t mins,vec3_t maxs,int ignore,int clipmask);
CCALL void NPC_SetBlocked(gentity_t *self,gentity_t *blocker);
CCALL void NPC_ClearBlocked(gentity_t *self);
CCALL qboolean NAV_CheckNodeFailedForEnt(gentity_t *ent,int nodeNum);
CCALL void TAG_ShowTags(int flags);
CCALL void G_DrawCombatPoint(vec3_t origin,int type);
CCALL void G_DrawNode(vec3_t origin,int type);
CCALL void G_DrawEdge(vec3_t start,vec3_t end,int type);
CCALL void G_CubeOutline(vec3_t mins,vec3_t maxs,int time,unsigned int color,float alpha);
CCALL void G_Cube(vec3_t mins,vec3_t maxs,vec3_t color,float alpha);
CCALL void G_Line(vec3_t start,vec3_t end,vec3_t color,float alpha);
CCALL qboolean NAV_TestForBlocked(gentity_t *self,gentity_t *goal,gentity_t *blocker,float distance,int *flags);
CCALL qboolean NAV_CheckAhead(gentity_t *self,vec3_t end,trace_t *trace,int clipmask);
