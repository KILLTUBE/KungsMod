#pragma once

#include "b_local.h"

#define	MIN_MELEE_RANGE		640
#define	MIN_MELEE_RANGE_SQR	( MIN_MELEE_RANGE * MIN_MELEE_RANGE )

#define MIN_DISTANCE		128
#define MIN_DISTANCE_SQR	( MIN_DISTANCE * MIN_DISTANCE )

#define TURN_OFF			0x00000100//G2SURFACEFLAG_NODESCENDANTS

#define LEFT_ARM_HEALTH 40
#define RIGHT_ARM_HEALTH 40

CCALL void NPC_BSATST_Default(void);
CCALL void ATST_Idle(void);
CCALL void ATST_Patrol(void);
CCALL void ATST_Attack(void);
CCALL void ATST_Ranged(qboolean visible,qboolean advance,qboolean altAttack);
CCALL void ATST_Hunt(qboolean visible,qboolean advance);
CCALL void NPC_ATST_Pain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void G_ATSTCheckPain(gentity_t *self,gentity_t *other,int damage);
CCALL void NPC_ATST_Precache(void);
CCALL void G_SoundOnEnt(gentity_t *ent,soundChannel_t channel,const char *soundPath);
