#pragma once

#include "b_local.h"
#include "g_nav.h"


#define VELOCITY_DECAY	0.85f
#define HUNTER_STRAFE_VEL	256
#define HUNTER_STRAFE_DIS	200
#define HUNTER_UPWARD_PUSH	32
#define HUNTER_FORWARD_BASE_SPEED	10
#define HUNTER_FORWARD_MULTIPLIER	5

#define	MIN_MELEE_RANGE		320
#define	MIN_MELEE_RANGE_SQR	( MIN_MELEE_RANGE * MIN_MELEE_RANGE )

#define MIN_DISTANCE		128
#define MIN_DISTANCE_SQR	( MIN_DISTANCE * MIN_DISTANCE )

typedef enum
{
	LSTATE_NONE = 0,
	LSTATE_BACKINGUP,
	LSTATE_SPINNING,
	LSTATE_PAIN,
	LSTATE_DROP
} ImperialProbeLState;

CCALL void NPC_BSImperialProbe_Default(void);
CCALL void ImperialProbe_Wait(void);
CCALL void ImperialProbe_Patrol(void);
CCALL void NPC_Probe_Pain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void ImperialProbe_AttackDecision(void);
CCALL void ImperialProbe_Ranged(qboolean visible,qboolean advance);
CCALL void ImperialProbe_FireBlaster(void);
CCALL void ImperialProbe_Hunt(qboolean visible,qboolean advance);
CCALL void ImperialProbe_Strafe(void);
CCALL void ImperialProbe_MaintainHeight(void);
CCALL void NPC_Probe_Precache(void);
CCALL void ImperialProbe_Idle(void);
CCALL void ImperialProbe_Idle(void);
CCALL void G_SoundOnEnt(gentity_t *ent,soundChannel_t channel,const char *soundPath);
CCALL gitem_t *BG_FindItemForAmmo(ammo_t ammo);
