#pragma once

#include "b_local.h"
#include "g_nav.h"

#define VELOCITY_DECAY	0.85f
#define REMOTE_STRAFE_VEL	256
#define REMOTE_STRAFE_DIS	200
#define REMOTE_UPWARD_PUSH	32

#define REMOTE_FORWARD_BASE_SPEED	10
#define REMOTE_FORWARD_MULTIPLIER	5

#define	MIN_MELEE_RANGE		320
#define	MIN_MELEE_RANGE_SQR	( MIN_MELEE_RANGE * MIN_MELEE_RANGE )

#define MIN_DISTANCE		80
#define MIN_DISTANCE_SQR	( MIN_DISTANCE * MIN_DISTANCE )

typedef enum
{
	LSTATE_NONE = 0,
} RemoteLState;

CCALL void NPC_BSRemote_Default(void);
CCALL void Remote_Patrol(void);
CCALL void Remote_Attack(void);
CCALL void Remote_Ranged(qboolean visible,qboolean advance,qboolean retreat);
CCALL void Remote_Fire(void);
CCALL void Remote_Hunt(qboolean visible,qboolean advance,qboolean retreat);
CCALL void Remote_MaintainHeight(void);
CCALL void NPC_Remote_Pain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void NPC_Remote_Precache(void);
CCALL void Remote_Idle(void);
CCALL void Remote_Idle(void);
CCALL void Remote_Strafe(void);
CCALL void Remote_Strafe(void);
CCALL qboolean NPC_GetMoveDirection( vec3_t out, float *distance );
