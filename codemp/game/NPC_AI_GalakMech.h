#pragma once

#include "b_local.h"
#include "g_nav.h"
#include "anims.h"
#include "w_saber.h"

#define MELEE_DIST_SQUARED 6400//80*80
#define MIN_LOB_DIST_SQUARED 65536//256*256
#define MAX_LOB_DIST_SQUARED 200704//448*448
#define REPEATER_ALT_SIZE				3	// half of bbox size
#define	GENERATOR_HEALTH	25
#define TURN_ON				0x00000000
#define TURN_OFF			0x00000100
#define GALAK_SHIELD_HEALTH	500

CCALL void NPC_BSGM_Default(void);
CCALL void NPC_BSGM_Attack(void);
CCALL void GM_StartGloat(void);
CCALL void NPC_GM_StartLaser(void);
CCALL void NPC_BSGM_Patrol(void);
CCALL void NPC_GM_Pain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void NPC_SetPainEvent(gentity_t *self);
CCALL void GM_Dying(gentity_t *self);
CCALL void NPC_GalakMech_Init(gentity_t *ent);
CCALL void NPC_GalakMech_Precache(void);
CCALL qboolean NPC_CheckPlayerTeamStealth(void);
CCALL qboolean BG_CrouchAnim(int anim);
CCALL void G_SoundOnEnt(gentity_t *ent,soundChannel_t channel,const char *soundPath);
CCALL qboolean WP_LobFire(gentity_t *self,vec3_t start,vec3_t target,vec3_t mins,vec3_t maxs,int clipmask,vec3_t velocity,qboolean tracePath,int ignoreEntNum,int enemyNum,float minSpeed,float maxSpeed,float idealSpeed,qboolean mustHit);
CCALL void NPC_AimAdjust(int change);
CCALL void G_AddVoiceEvent(gentity_t *self,int event,int speakDebounceTime);
