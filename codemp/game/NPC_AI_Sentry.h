#pragma once

#include "b_local.h"
#include "g_nav.h"

#define MIN_DISTANCE		256
#define MIN_DISTANCE_SQR	( MIN_DISTANCE * MIN_DISTANCE )

#define SENTRY_FORWARD_BASE_SPEED	10
#define SENTRY_FORWARD_MULTIPLIER	5

#define SENTRY_VELOCITY_DECAY	0.85f
#define SENTRY_STRAFE_VEL		256
#define SENTRY_STRAFE_DIS		200
#define SENTRY_UPWARD_PUSH		32
#define SENTRY_HOVER_HEIGHT		24

typedef enum
{
	LSTATE_NONE = 0,
	LSTATE_ASLEEP,
	LSTATE_WAKEUP,
	LSTATE_ACTIVE,
	LSTATE_POWERING_UP,
	LSTATE_ATTACKING,
} SentryLState;

CCALL void NPC_BSSentry_Default(void);
CCALL void NPC_Sentry_Patrol(void);
CCALL qboolean NPC_CheckPlayerTeamStealth(void);
CCALL void Sentry_AttackDecision(void);
CCALL void Sentry_RangedAttack(qboolean visible,qboolean advance);
CCALL void Sentry_Hunt(qboolean visible,qboolean advance);
CCALL void Sentry_Strafe(void);
CCALL void Sentry_Idle(void);
CCALL void Sentry_MaintainHeight(void);
CCALL void Sentry_Fire(void);
CCALL void NPC_Sentry_Pain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void sentry_use(gentity_t *self,gentity_t *other,gentity_t *activator);
CCALL void NPC_Sentry_Precache(void);
CCALL void G_SoundOnEnt(gentity_t *ent,soundChannel_t channel,const char *soundPath);
CCALL gitem_t *BG_FindItemForAmmo(ammo_t ammo);
CCALL qboolean NPC_GetMoveDirection( vec3_t out, float *distance );