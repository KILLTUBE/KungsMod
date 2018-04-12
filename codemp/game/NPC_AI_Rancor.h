#pragma once

#include "b_local.h"

#define MIN_DISTANCE		128
#define MIN_DISTANCE_SQR	( MIN_DISTANCE * MIN_DISTANCE )

#define MAX_DISTANCE		1024
#define MAX_DISTANCE_SQR	( MAX_DISTANCE * MAX_DISTANCE )

#define LSTATE_CLEAR		0
#define LSTATE_WAITING		1

CCALL void NPC_BSRancor_Default(void);
CCALL void Rancor_Crush(void);
CCALL void Rancor_CheckDropVictim(void);
CCALL void NPC_Rancor_Pain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void Rancor_Combat(void);
CCALL void Rancor_Attack(float distance,qboolean doCharge);
CCALL void TossClientItems(gentity_t *self);
CCALL void Rancor_Bite(void);
CCALL void Rancor_Smash(void);
CCALL void Rancor_Swing(qboolean tryGrab);
CCALL void Rancor_DropVictim(gentity_t *self);
CCALL int NPC_GetEntsNearBolt(int *radiusEnts,float radius,int boltIndex,vec3_t boltOrg);
CCALL float NPC_EntRangeFromBolt(gentity_t *targEnt,int boltIndex);
CCALL void G_Dismember(gentity_t *ent,gentity_t *enemy,vec3_t point,int limbType,float limbRollBase,float limbPitchBase,int deathAnim,qboolean postDeath);
CCALL void G_Knockdown(gentity_t *victim);
CCALL void Rancor_Move(qboolean visible);
CCALL void Rancor_Patrol(void);
CCALL qboolean Rancor_CheckRoar(gentity_t *self);
CCALL void Rancor_Idle(void);
CCALL void NPC_Rancor_Precache(void);
CCALL void Rancor_SetBolts(gentity_t *self);
CCALL void G_GetBoltPosition(gentity_t *self,int boltIndex,vec3_t pos,int modelIndex);
