#pragma once

#include "b_local.h"
#include "g_nav.h"

#define MIN_DISTANCE		48
#define MIN_DISTANCE_SQR	( MIN_DISTANCE * MIN_DISTANCE )

#define MAX_DISTANCE		1024
#define MAX_DISTANCE_SQR	( MAX_DISTANCE * MAX_DISTANCE )

#define LSTATE_CLEAR		0
#define LSTATE_WAITING		1

EXTERNC float enemyDist;

CCALL void NPC_BSWampa_Default(void);
CCALL void NPC_Wampa_Pain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void Wampa_Combat(void);
CCALL void Wampa_Attack(float distance,qboolean doCharge);
CCALL void Wampa_Slash(int boltIndex,qboolean backhand);
CCALL int NPC_GetEntsNearBolt(int *radiusEnts,float radius,int boltIndex,vec3_t boltOrg);
CCALL void G_Dismember(gentity_t *ent,gentity_t *enemy,vec3_t point,int limbType,float limbRollBase,float limbPitchBase,int deathAnim,qboolean postDeath);
CCALL void G_Knockdown(gentity_t *victim);
CCALL void Wampa_Move(qboolean visible);
CCALL void Wampa_Patrol(void);
CCALL qboolean Wampa_CheckRoar(gentity_t *self);
CCALL void Wampa_Idle(void);
CCALL void NPC_Wampa_Precache(void);
CCALL void Wampa_SetBolts(gentity_t *self);
