#pragma once

#include "b_local.h"

// todo: replace all defines to cvars and calculate SQR for cvars automatically
// e.g. howler_min_distance->valueSquared

// These define the working combat range for these suckers
#define MIN_DISTANCE		54
#define MIN_DISTANCE_SQR	( MIN_DISTANCE * MIN_DISTANCE )

#define MAX_DISTANCE		128
#define MAX_DISTANCE_SQR	( MAX_DISTANCE * MAX_DISTANCE )

#define LSTATE_CLEAR		0
#define LSTATE_WAITING		1

CCALL void NPC_BSHowler_Default(void);
CCALL void NPC_Howler_Pain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void Howler_Combat(void);
CCALL void Howler_Attack(void);
CCALL void Howler_TryDamage(gentity_t *enemy,int damage);
CCALL void Howler_Move(qboolean visible);
CCALL void Howler_Patrol(void);
CCALL void Howler_Idle(void);
CCALL void NPC_Howler_Precache(void);
