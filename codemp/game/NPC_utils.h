#pragma once

#include "b_local.h"
#include "icarus/Q3_Interface.h"
#include "ghoul2/G2.h"

#define	VALID_ATTACK_CONE	2.0f	//Degrees

//rww - and another method of automatically managing surface status for the client and server at once
#define TURN_ON				0x00000000
#define TURN_OFF			0x00000100

#define	MAX_RADIUS_ENTS			256	//NOTE: This can cause entities to be lost
#define NEAR_DEFAULT_RADIUS		256

EXTERNC int teamCounter[TEAM_NUM_TEAMS];
EXTERNC int teamStrength[TEAM_NUM_TEAMS];
EXTERNC int teamNumbers[TEAM_NUM_TEAMS];
EXTERNC stringID_table_t BSETTable[];
EXTERNC stringID_table_t BSTable[];

CCALL int NPC_GetEntsNearBolt(int *radiusEnts,float radius,int boltIndex,vec3_t boltOrg);
CCALL float NPC_EnemyRangeFromBolt(int boltIndex);
CCALL float NPC_EntRangeFromBolt(gentity_t *targEnt,int boltIndex);
CCALL void G_GetBoltPosition(gentity_t *self,int boltIndex,vec3_t pos,int modelIndex);
CCALL void NPC_CheckCharmed(void);
CCALL void G_AddVoiceEvent(gentity_t *self,int event,int speakDebounceTime);
CCALL qboolean NPC_CheckLookTarget(gentity_t *self);
CCALL void NPC_SetLookTarget(gentity_t *self,int entNum,int clearTime);
CCALL void NPC_ClearLookTarget(gentity_t *self);
CCALL qboolean NPC_CheckCanAttackExt(void);
CCALL qboolean NPC_FaceEnemy(qboolean doPitch);
CCALL qboolean NPC_FaceEntity(gentity_t *ent,qboolean doPitch);
CCALL qboolean NPC_FacePosition(vec3_t position,qboolean doPitch);
CCALL qboolean NPC_CheckEnemyExt(qboolean checkAlerts);
CCALL qboolean NPC_FindEnemy(qboolean checkAlerts);
CCALL qboolean NPC_FindPlayer(void);
CCALL gentity_t *NPC_PickEnemyExt(qboolean checkAlerts);
CCALL int NPC_FindNearestEnemy(gentity_t *ent);
CCALL qboolean NPC_TargetVisible(gentity_t *ent);
CCALL qboolean NPC_ValidEnemy(gentity_t *ent);
CCALL qboolean NPC_ClearLOS2(gentity_t *ent,const vec3_t end);
CCALL qboolean NPC_ClearLOS3(const vec3_t start,gentity_t *ent);
CCALL qboolean NPC_ClearLOS4(gentity_t *ent);
CCALL qboolean NPC_ClearLOS5(const vec3_t end);
CCALL qboolean NPC_ClearLOS(const vec3_t start,const vec3_t end);
CCALL qboolean NPC_SomeoneLookingAtMe(gentity_t *ent);
CCALL void NPC_SetSurfaceOnOff(gentity_t *ent,const char *surfaceName,int surfaceFlags);
CCALL void NPC_SetBoneAngles(gentity_t *ent,char *bone,vec3_t angles);
CCALL qboolean G_ActivateBehavior(gentity_t *self,int bset);
CCALL void SetTeamNumbers(void);
CCALL void NPC_UpdateShootAngles(vec3_t angles,qboolean doPitch,qboolean doYaw);
CCALL qboolean NPC_UpdateFiringAngles(qboolean doPitch,qboolean doYaw);
CCALL void NPC_AimWiggle(vec3_t enemy_org);
CCALL qboolean NPC_UpdateAngles(qboolean doPitch,qboolean doYaw);
CCALL void CalcEntitySpot(const gentity_t *ent,const spot_t spot,vec3_t point);
CCALL void G_DebugPrint(int level,const char *format,...);
