#pragma once

#include "b_local.h"
#include "anims.h"
#include "w_saber.h"

#define	MIN_PAIN_TIME	200

EXTERNC int killPlayerTimer;
EXTERNC int teamLastEnemyTime[];

CCALL void NPC_CheckAllClear(void);
CCALL void NPC_CheckPlayerAim(void);
CCALL void NPC_Use(gentity_t *self,gentity_t *other,gentity_t *activator);
CCALL void Add_Batteries(gentity_t *ent,int *count);
CCALL void NPC_UseResponse(gentity_t *self,gentity_t *user,qboolean useWhenDone);
CCALL void NPC_Respond(gentity_t *self,int userNum);
CCALL void NPC_TempLookTarget(gentity_t *self,int lookEntNum,int minLookTime,int maxLookTime);
CCALL void NPC_Touch(gentity_t *self,gentity_t *other,trace_t *trace);
CCALL qboolean INV_SecurityKeyGive(gentity_t *target,const char *keyname);
CCALL void NPC_Pain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void NPC_ChoosePainAnimation(gentity_t *self,gentity_t *other,vec3_t point,int damage,int mod,int hitLoc,int voiceEvent);
CCALL int G_PickPainAnim(gentity_t *self,vec3_t point,int damage,int hitLoc);
CCALL float NPC_GetPainChance(gentity_t *self,int damage);
CCALL void NPC_SetPainEvent(gentity_t *self);
CCALL qboolean BG_CrouchAnim(int anim);
CCALL qboolean PM_InCartwheel(int anim);
CCALL qboolean PM_RollingAnim(int anim);
CCALL qboolean BG_FlippingAnim(int anim);
CCALL qboolean PM_InKnockDown(playerState_t *ps);
CCALL qboolean PM_SpinningAnim(int anim);
CCALL qboolean PM_SpinningSaberAnim(int anim);
CCALL qboolean BG_SaberInSpecialAttack(int anim);
CCALL qboolean NPC_SomeoneLookingAtMe(gentity_t *ent);
CCALL void Jedi_Ambush(gentity_t *self);
CCALL qboolean Jedi_WaitingAmbush(gentity_t *self);
CCALL void NPC_SetLookTarget(gentity_t *self,int entNum,int clearTime);
CCALL qboolean NPC_CheckLookTarget(gentity_t *self);
CCALL qboolean Q3_TaskIDPending(gentity_t *ent,taskID_t taskType);
CCALL void cgi_S_StartSound(vec3_t origin,int entityNum,int entchannel,sfxHandle_t sfx);
CCALL void G_SoundOnEnt(gentity_t *ent,soundChannel_t channel,const char *soundPath);
CCALL void G_AddVoiceEvent(gentity_t *self,int event,int speakDebounceTime);
CCALL qboolean G_CheckForStrongAttackMomentum(gentity_t *self);
