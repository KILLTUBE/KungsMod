#pragma once

#include "b_local.h"
#include "g_nav.h"
#include "anims.h"


#define	SPF_NO_HIDE			2

#define	MAX_VIEW_DIST		1024
#define MAX_VIEW_SPEED		250
#define	MAX_LIGHT_INTENSITY 255
#define	MIN_LIGHT_THRESHOLD	0.1

#define	DISTANCE_SCALE		0.25f
#define	DISTANCE_THRESHOLD	0.075f
#define	SPEED_SCALE			0.25f
#define	FOV_SCALE			0.5f
#define	LIGHT_SCALE			0.25f

#define	REALIZE_THRESHOLD	0.6f
#define CAUTIOUS_THRESHOLD	( REALIZE_THRESHOLD * 0.75 )

typedef enum
{
	LSTATE_NONE = 0,
	LSTATE_UNDERFIRE,
	LSTATE_INVESTIGATE,
} SniperState;

CCALL void NPC_BSSniper_Default(void);
CCALL void NPC_BSSniper_Attack(void);
CCALL void Sniper_StartHide(void);
CCALL void Sniper_UpdateEnemyPos(void);
CCALL void Sniper_FaceEnemy(void);
CCALL qboolean Sniper_EvaluateShot(int hit);
CCALL void NPC_BSSniper_Patrol(void);
CCALL void NPC_Sniper_Pain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void NPC_Sniper_PlayConfusionSound(gentity_t *self);
CCALL void Sniper_ClearTimers(gentity_t *ent);
CCALL qboolean NPC_CheckPlayerTeamStealth(void);
CCALL qboolean FlyingCreature(gentity_t *ent);
CCALL qboolean G_ExpandPointToBBox(vec3_t point,const vec3_t mins,const vec3_t maxs,int ignore,int clipmask);
CCALL void NPC_TempLookTarget(gentity_t *self,int lookEntNum,int minLookTime,int maxLookTime);
CCALL void G_AddVoiceEvent(gentity_t *self,int event,int speakDebounceTime);
CCALL void G_SoundOnEnt(gentity_t *ent,soundChannel_t channel,const char *soundPath);
CCALL void G_SoundOnEnt(gentity_t *ent,soundChannel_t channel,const char *soundPath);
