#pragma once

#include "b_local.h"
#include "g_nav.h"
#include "anims.h"


#define	MAX_VIEW_DIST		1024
#define MAX_VIEW_SPEED		250
#define	MAX_LIGHT_INTENSITY 255
#define	MIN_LIGHT_THRESHOLD	0.1
#define	ST_MIN_LIGHT_THRESHOLD 30
#define	ST_MAX_LIGHT_THRESHOLD 180
#define	DISTANCE_THRESHOLD	0.075f

#define	DISTANCE_SCALE		0.35f	//These first three get your base detection rating, ideally add up to 1
#define	FOV_SCALE			0.40f	//
#define	LIGHT_SCALE			0.25f	//

#define	SPEED_SCALE			0.25f	//These next two are bonuses
#define	TURNING_SCALE		0.25f	//

#define	REALIZE_THRESHOLD	0.6f
#define CAUTIOUS_THRESHOLD	( REALIZE_THRESHOLD * 0.75 )

#define	MAX_CHECK_THRESHOLD	1

typedef enum
{
	LSTATE_NONE = 0,
	LSTATE_UNDERFIRE,
	LSTATE_INVESTIGATE,
} StormtrooperState;

typedef enum
{
	SPEECH_CHASE,
	SPEECH_CONFUSED,
	SPEECH_COVER,
	SPEECH_DETECTED,
	SPEECH_GIVEUP,
	SPEECH_LOOK,
	SPEECH_LOST,
	SPEECH_OUTFLANK,
	SPEECH_ESCAPING,
	SPEECH_SIGHT,
	SPEECH_SOUND,
	SPEECH_SUSPICIOUS,
	SPEECH_YELL,
	SPEECH_PUSHED
} StormtrooperSpeech;

EXTERNC int groupSpeechDebounceTime[TEAM_NUM_TEAMS];

CCALL void NPC_BSST_Default(void);
CCALL void NPC_BSST_Attack(void);
CCALL void ST_Commander(void);
CCALL int ST_GetCPFlags(void);
CCALL void ST_TransferTimers(gentity_t *self,gentity_t *other);
CCALL void ST_HuntEnemy(gentity_t *self);
CCALL int ST_ApproachEnemy(gentity_t *self);
CCALL void ST_TrackEnemy(gentity_t *self,vec3_t enemyPos);
CCALL void ST_ResolveBlockedShot(int hit);
CCALL void NPC_BSST_Patrol(void);
CCALL void NPC_BSST_Investigate(void);
CCALL qboolean NPC_CheckEnemyStealth(gentity_t *target);
CCALL void NPC_BSST_Sleep(void);
CCALL void ST_TransferMoveGoal(gentity_t *self,gentity_t *other);
CCALL void ST_TransferMoveGoal(gentity_t *self,gentity_t *other);
CCALL void NPC_ST_StoreMovementSpeech(int speech,float chance);
CCALL void NPC_ST_SayMovementSpeech(void);
CCALL void NPC_ST_Pain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void ST_StartFlee(gentity_t *self,gentity_t *enemy,vec3_t dangerPoint,int dangerLevel,int minTime,int maxTime);
CCALL void ST_MarkToCover(gentity_t *self);
CCALL void ST_ClearTimers(gentity_t *ent);
CCALL void ST_AggressionAdjust(gentity_t *self,int change);
CCALL qboolean NPC_CheckPlayerTeamStealth(void);
CCALL qboolean NPC_CheckPlayerTeamStealth(void);
CCALL qboolean FlyingCreature(gentity_t *ent);
CCALL void NPC_AimAdjust(int change);
CCALL int GetTime(int lastTime);
CCALL void NPC_CheckGetNewWeapon(void);
CCALL void ChangeWeapon(gentity_t *ent,int newWeapon);
CCALL qboolean G_ExpandPointToBBox(vec3_t point,const vec3_t mins,const vec3_t maxs,int ignore,int clipmask);
CCALL void NPC_TempLookTarget(gentity_t *self,int lookEntNum,int minLookTime,int maxLookTime);
CCALL void AI_GroupUpdateClearShotTime(AIGroupInfo_t *group);
CCALL void AI_GroupUpdateEnemyLastSeen(AIGroupInfo_t *group,vec3_t spot);
CCALL qboolean AI_GroupContainsEntNum(AIGroupInfo_t *group,int entNum);
CCALL void AI_GroupUpdateSquadstates(AIGroupInfo_t *group,gentity_t *member,int newSquadState);
CCALL void G_AddVoiceEvent(gentity_t *self,int event,int speakDebounceTime);
