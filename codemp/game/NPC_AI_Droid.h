#pragma once

#include "b_local.h"

#define TURN_OFF   0x00000100

//Local state enums
typedef enum
{
	LSTATE_NONE = 0,
	LSTATE_BACKINGUP,
	LSTATE_SPINNING,
	LSTATE_PAIN,
	LSTATE_DROP
} LSTATE;

CCALL void NPC_BSDroid_Default(void);
CCALL void NPC_Protocol_Precache(void);
CCALL void NPC_Gonk_Precache(void);
CCALL void NPC_R2D2_Precache(void);
CCALL void NPC_R5D2_Precache(void);
CCALL void NPC_Mouse_Precache(void);
CCALL void Droid_Pain(void);
CCALL void NPC_Droid_Pain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void Droid_Spin(void);
CCALL void Droid_Run(void);
CCALL void Droid_Patrol(void);
CCALL void R2D2_TurnAnims(void);
CCALL void Droid_Idle(void);
CCALL void R2D2_PartsMove(void);
CCALL void G_SoundOnEnt(gentity_t *ent,soundChannel_t channel,const char *soundPath);
CCALL float NPC_GetPainChance(gentity_t *self,int damage);
