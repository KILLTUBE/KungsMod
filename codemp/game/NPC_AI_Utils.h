#pragma once

#include "b_local.h"
#include "g_nav.h"
#include "NPC_AI_Utils.h"

#define	MAX_RADIUS_ENTS		128
#define	DEFAULT_RADIUS		45
#define	MAX_RADIUS_ENTS		128

CCALL gentity_t *AI_DistributeAttack(gentity_t *attacker,gentity_t *enemy,team_t team,int threshold);
CCALL qboolean AI_CheckEnemyCollision(gentity_t *ent,qboolean takeEnemy);
CCALL qboolean AI_GroupContainsEntNum(AIGroupInfo_t *group,int entNum);
CCALL void AI_UpdateGroups(void);
CCALL qboolean AI_RefreshGroup(AIGroupInfo_t *group);
CCALL void AI_GroupUpdateSquadstates(AIGroupInfo_t *group,gentity_t *member,int newSquadState);
CCALL void AI_GroupUpdateClearShotTime(AIGroupInfo_t *group);
CCALL void AI_GroupUpdateEnemyLastSeen(AIGroupInfo_t *group,vec3_t spot);
CCALL void AI_GroupMemberKilled(gentity_t *self);
CCALL void ST_StartFlee(gentity_t *self,gentity_t *enemy,vec3_t dangerPoint,int dangerLevel,int minTime,int maxTime);
CCALL void ST_MarkToCover(gentity_t *self);
CCALL void ST_AggressionAdjust(gentity_t *self,int change);
CCALL void AI_DeleteSelfFromGroup(gentity_t *self);
CCALL void AI_DeleteGroupMember(AIGroupInfo_t *group,int memberNum);
CCALL void AI_SetNewGroupCommander(AIGroupInfo_t *group);
CCALL void AI_GetGroup(gentity_t *self);
CCALL qboolean AI_ValidateNoEnemyGroupMember(AIGroupInfo_t *group,gentity_t *member);
CCALL qboolean AI_GetNextEmptyGroup(gentity_t *self);
CCALL qboolean AI_TryJoinPreviousGroup(gentity_t *self);
CCALL void AI_InsertGroupMember(AIGroupInfo_t *group,gentity_t *member);
CCALL qboolean AI_FindSelfInPreviousGroup(gentity_t *self);
CCALL void AI_SortGroupByPathCostToEnemy(AIGroupInfo_t *group);
CCALL void AI_SetClosestBuddy(AIGroupInfo_t *group);
CCALL int AI_GetGroupSize2(gentity_t *ent,int radius);
CCALL int AI_GetGroupSize(vec3_t origin,int radius,team_t playerTeam,gentity_t *avoid);
CCALL void G_TestLine(vec3_t start,vec3_t end,int color,int time);
CCALL qboolean AI_ValidateGroupMember(AIGroupInfo_t *group,gentity_t *member);