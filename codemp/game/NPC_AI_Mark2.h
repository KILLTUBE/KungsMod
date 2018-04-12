#pragma once

#include "b_local.h"
#include "g_nav.h"

#define AMMO_POD_HEALTH				1
#define TURN_OFF					0x00000100

#define VELOCITY_DECAY		0.25
#define MAX_DISTANCE		256
#define MAX_DISTANCE_SQR	( MAX_DISTANCE * MAX_DISTANCE )
#define MIN_DISTANCE		24
#define MIN_DISTANCE_SQR	( MIN_DISTANCE * MIN_DISTANCE )

typedef enum
{
	LSTATE_NONE = 0,
	LSTATE_DROPPINGDOWN,
	LSTATE_DOWN,
	LSTATE_RISINGUP,
} Mark2LState;

CCALL void NPC_BSMark2_Default(void);
CCALL void Mark2_Idle(void);
CCALL void Mark2_Patrol(void);
CCALL void Mark2_AttackDecision(void);
CCALL void Mark2_BlasterAttack(qboolean advance);
CCALL void Mark2_FireBlaster(qboolean advance);
CCALL void Mark2_Hunt(void);
CCALL void NPC_Mark2_Pain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void NPC_Mark2_Part_Explode(gentity_t *self,int bolt);
CCALL void NPC_Mark2_Precache(void);
CCALL gitem_t *BG_FindItemForAmmo(ammo_t ammo);
