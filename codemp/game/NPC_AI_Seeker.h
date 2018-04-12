#pragma once

#include "b_local.h"
#include "g_nav.h"

#define VELOCITY_DECAY		0.7f

#define	MIN_MELEE_RANGE		320
#define	MIN_MELEE_RANGE_SQR	( MIN_MELEE_RANGE * MIN_MELEE_RANGE )

#define MIN_DISTANCE		80
#define MIN_DISTANCE_SQR	( MIN_DISTANCE * MIN_DISTANCE )

#define SEEKER_STRAFE_VEL	100
#define SEEKER_STRAFE_DIS	200
#define SEEKER_UPWARD_PUSH	32

#define SEEKER_FORWARD_BASE_SPEED	10
#define SEEKER_FORWARD_MULTIPLIER	2

#define SEEKER_SEEK_RADIUS			1024

CCALL void NPC_BSSeeker_Default(void);
CCALL void Seeker_FollowOwner(void);
CCALL void Seeker_FindEnemy(void);
CCALL void Seeker_Attack(void);
CCALL void Seeker_Ranged(qboolean visible,qboolean advance);
CCALL void Seeker_Fire(void);
CCALL void Seeker_Hunt(qboolean visible,qboolean advance);
CCALL void Seeker_MaintainHeight(void);
CCALL void NPC_Seeker_Pain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void NPC_Seeker_Precache(void);
CCALL void Seeker_Strafe(void);
CCALL void Seeker_Strafe(void);
CCALL void Boba_FireDecide(void);
CCALL qboolean NPC_GetMoveDirection( vec3_t out, float *distance );