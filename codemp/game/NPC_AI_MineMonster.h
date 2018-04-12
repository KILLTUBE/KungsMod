#pragma once

#include "b_local.h"

// These define the working combat range for these suckers
#define MIN_DISTANCE		54
#define MIN_DISTANCE_SQR	( MIN_DISTANCE * MIN_DISTANCE )

#define MAX_DISTANCE		128
#define MAX_DISTANCE_SQR	( MAX_DISTANCE * MAX_DISTANCE )

#define LSTATE_CLEAR		0
#define LSTATE_WAITING		1

CCALL void NPC_BSMineMonster_Default(void);
CCALL void NPC_MineMonster_Pain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void MineMonster_Combat(void);
CCALL void MineMonster_Attack(void);
CCALL void MineMonster_TryDamage(gentity_t *enemy,int damage);
CCALL void MineMonster_Move(qboolean visible);
CCALL void MineMonster_Patrol(void);
CCALL void MineMonster_Idle(void);
CCALL void NPC_MineMonster_Precache(void);
