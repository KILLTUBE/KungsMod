#pragma once

#include "b_local.h"
#include "g_nav.h"
#include "anims.h"

// todo: these defines are probably meant to be local to .c file only,
// so they should be called e.g. NPC_AI_GRENADIER_MAX_VIEW_DIST (globally)
// but thats why too long, so namespaces would probably make sense...
// but then again, i dont like hardcoded defines at all, imo should be all
// converted to cvars. And the cvar struct should have a "bool visualize", which 
// - when true - draws all the meta data via opengl
// otherwise all this shit is just guess work or hard to come up with new values

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

// i also dont like types local to a type, imo everything should be editable from everywhere
// this local bullshit is kind of producing copy paste inbred code

typedef enum
{
	LSTATE_NONE = 0,
	LSTATE_UNDERFIRE,
	LSTATE_INVESTIGATE,
} NPC_GRENADIER_LSTATE;

CCALL void NPC_BSGrenadier_Default(void);
CCALL void NPC_BSGrenadier_Attack(void);
CCALL qboolean Grenadier_EvaluateShot(int hit);
CCALL void NPC_BSGrenadier_Patrol(void);
CCALL void NPC_Grenadier_Pain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void NPC_Grenadier_PlayConfusionSound(gentity_t *self);
CCALL void Grenadier_ClearTimers(gentity_t *ent);
CCALL qboolean NPC_CheckPlayerTeamStealth(void);
CCALL qboolean FlyingCreature(gentity_t *ent);
CCALL void NPC_AimAdjust(int change);
CCALL qboolean G_ExpandPointToBBox(vec3_t point,const vec3_t mins,const vec3_t maxs,int ignore,int clipmask);
CCALL void NPC_TempLookTarget(gentity_t *self,int lookEntNum,int minLookTime,int maxLookTime);
CCALL void G_SoundOnEnt(gentity_t *ent,soundChannel_t channel,const char *soundPath);
CCALL void G_AddVoiceEvent(gentity_t *self,int event,int speakDebounceTime);
CCALL void CG_DrawAlert(vec3_t origin,float rating);
CCALL qboolean BG_SabersOff(playerState_t *ps);
