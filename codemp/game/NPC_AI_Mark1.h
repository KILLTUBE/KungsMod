#pragma once

#include "b_local.h"
#include "g_nav.h"

#define	MIN_MELEE_RANGE				320
#define	MIN_MELEE_RANGE_SQR			( MIN_MELEE_RANGE * MIN_MELEE_RANGE )

#define MIN_DISTANCE				128
#define MIN_DISTANCE_SQR			( MIN_DISTANCE * MIN_DISTANCE )

#define TURN_OFF					0x00000100

#define LEFT_ARM_HEALTH				40
#define RIGHT_ARM_HEALTH			40
#define AMMO_POD_HEALTH				40

#define	BOWCASTER_VELOCITY			1300
#define	BOWCASTER_NPC_DAMAGE_EASY	12
#define	BOWCASTER_NPC_DAMAGE_NORMAL	24
#define	BOWCASTER_NPC_DAMAGE_HARD	36
#define BOWCASTER_SIZE				2
#define BOWCASTER_SPLASH_DAMAGE		0
#define BOWCASTER_SPLASH_RADIUS		0

//Local state enums
typedef enum
{
	LSTATE_NONE = 0,
	LSTATE_ASLEEP,
	LSTATE_WAKEUP,
	LSTATE_FIRED0,
	LSTATE_FIRED1,
	LSTATE_FIRED2,
	LSTATE_FIRED3,
	LSTATE_FIRED4,
} Mark1LState;

CCALL void NPC_BSMark1_Default(void);
CCALL void Mark1_Patrol(void);
CCALL void Mark1_AttackDecision(void);
CCALL void Mark1_RocketAttack(qboolean advance);
CCALL void Mark1_FireRocket(void);
CCALL void Mark1_FireBlaster(void);
CCALL void Mark1_Hunt(void);
CCALL void NPC_Mark1_Pain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void Mark1_dying(gentity_t *self);
CCALL void Mark1_die(gentity_t *self,gentity_t *inflictor,gentity_t *attacker,int damage,int mod,int dFlags,int hitLoc);
CCALL void Mark1Dead_FireBlaster(void);
CCALL void Mark1Dead_FireRocket(void);
CCALL void Mark1_Idle(void);
CCALL void NPC_Mark1_Part_Explode(gentity_t *self,int bolt);
CCALL void NPC_Mark1_Precache(void);
CCALL gitem_t *BG_FindItemForAmmo(ammo_t ammo);
CCALL void DeathFX(gentity_t *ent);
CCALL void Mark1_BlasterAttack(qboolean advance);
CCALL void Mark1_BlasterAttack(qboolean advance);
CCALL qboolean NPC_CheckPlayerTeamStealth(void);
