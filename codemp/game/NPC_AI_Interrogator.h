#pragma once

#include "b_local.h"
#include "g_nav.h"

#define VELOCITY_DECAY	0.85f
#define HUNTER_UPWARD_PUSH	2
#define HUNTER_STRAFE_VEL	32
#define HUNTER_STRAFE_DIS	200
#define HUNTER_FORWARD_BASE_SPEED	10
#define HUNTER_FORWARD_MULTIPLIER	2
#define MIN_DISTANCE		64

typedef enum
{
LSTATE_BLADESTOP=0,
LSTATE_BLADEUP,
LSTATE_BLADEDOWN,
} InterrogatorLState;

CCALL void NPC_BSInterrogator_Default(void);
CCALL void Interrogator_Attack(void);
CCALL void Interrogator_Melee(qboolean visible,qboolean advance);
CCALL void Interrogator_Hunt(qboolean visible,qboolean advance);
CCALL void Interrogator_Strafe(void);
CCALL void Interrogator_MaintainHeight(void);
CCALL void Interrogator_PartsMove(void);
CCALL void Interrogator_die(gentity_t *self,gentity_t *inflictor,gentity_t *attacker,int damage,int mod,int dFlags,int hitLoc);
CCALL void NPC_Interrogator_Precache(gentity_t *self);
CCALL void G_SoundOnEnt(gentity_t *ent,soundChannel_t channel,const char *soundPath);
CCALL void DeathFX(gentity_t *ent);
CCALL void Interrogator_Idle(void);
CCALL void Interrogator_Idle(void);
