#pragma once

#include "b_local.h"
#include "w_saber.h"
#include "ai_main.h"
#include "ghoul2/G2.h"

#define METROID_JUMP 1

EXTERNC int g_TimeSinceLastFrame;
EXTERNC int g_LastFrameTime;
EXTERNC float forcePushPullRadius[NUM_FORCE_POWER_LEVELS];
EXTERNC const int mindTrickTime[NUM_FORCE_POWER_LEVELS];
EXTERNC const int forcePowerMinRank[NUM_FORCE_POWER_LEVELS][NUM_FORCE_POWERS];
EXTERNC int ysalamiriLoopSound;
EXTERNC int seeLoopSound;
EXTERNC int absorbLoopSound;
EXTERNC int protectLoopSound;
EXTERNC int rageLoopSound;
EXTERNC int speedLoopSound;
EXTERNC bot_state_t *botstates[MAX_CLIENTS];

CCALL qboolean Jedi_DodgeEvasion(gentity_t *self,gentity_t *shooter,trace_t *tr,int hitLoc);
CCALL void WP_ForcePowersUpdate(gentity_t *self,usercmd_t *ucmd);
CCALL qboolean G_SpecialRollGetup(gentity_t *self);
CCALL qboolean WP_HasForcePowers(const playerState_t *ps);
CCALL void JediMasterUpdate(gentity_t *self);
CCALL void HolocronUpdate(gentity_t *self);
CCALL void SeekerDroneUpdate(gentity_t *self);
CCALL void FindGenericEnemyIndex(gentity_t *self);
CCALL int WP_DoSpecificPower(gentity_t *self,usercmd_t *ucmd,forcePowers_t forcepower);
CCALL qboolean G_IsMindTricked(forcedata_t *fd,int client);
CCALL void DoGripAction(gentity_t *self,forcePowers_t forcePower);
CCALL void ForceThrow(gentity_t *self,qboolean pull);
CCALL void Touch_Button(gentity_t *ent,gentity_t *other,trace_t *trace);
CCALL void G_LetGoOfWall(gentity_t *ent);
CCALL qboolean G_InGetUpAnim(playerState_t *ps);
CCALL qboolean CanCounterThrow(gentity_t *self,gentity_t *thrower,qboolean pull);
CCALL void GEntity_UseFunc(gentity_t *self,gentity_t *other,gentity_t *activator);
CCALL void ForceTelepathy(gentity_t *self);
CCALL qboolean ForceTelepathyCheckDirectNPCTarget(gentity_t *self,trace_t *tr,qboolean *tookPower);
CCALL void WP_AddAsMindtricked(forcedata_t *fd,int entNum);
CCALL void ForceJump(gentity_t *self,usercmd_t *ucmd);
CCALL int WP_GetVelocityForForceJump(gentity_t *self,vec3_t jumpVel,usercmd_t *ucmd);
CCALL void ForceJumpCharge(gentity_t *self,usercmd_t *ucmd);
CCALL void ForceDrainDamage(gentity_t *self,gentity_t *traceEnt,vec3_t dir,vec3_t impactPoint);
CCALL void ForceDrain(gentity_t *self);
CCALL void ForceShootLightning(gentity_t *self);
CCALL void ForceLightningDamage(gentity_t *self,gentity_t *traceEnt,vec3_t dir,vec3_t impactPoint);
CCALL void ForceLightning(gentity_t *self);
CCALL void ForceRage(gentity_t *self);
CCALL void ForceAbsorb(gentity_t *self);
CCALL void ForceProtect(gentity_t *self);
CCALL void ForceSeeing(gentity_t *self);
CCALL void ForceSpeed(gentity_t *self,int forceDuration);
CCALL void ForceGrip(gentity_t *self);
CCALL void ForceTeamForceReplenish(gentity_t *self);
CCALL void ForceTeamHeal(gentity_t *self);
CCALL void WP_AddToClientBitflags(gentity_t *ent,int entNum);
CCALL void ForceHeal(gentity_t *self);
CCALL void WP_ForcePowerStart(gentity_t *self,forcePowers_t forcePower,int overrideAmt);
CCALL void WP_ForcePowerRegenerate(gentity_t *self,int overrideAmt);
CCALL int WP_AbsorbConversion(gentity_t *attacked,int atdAbsLevel,gentity_t *attacker,int atPower,int atPowerLevel,int atForceSpent);
CCALL qboolean WP_ForcePowerUsable(gentity_t *self,forcePowers_t forcePower);
CCALL qboolean WP_ForcePowerInUse(gentity_t *self,forcePowers_t forcePower);
CCALL qboolean WP_ForcePowerAvailable(gentity_t *self,forcePowers_t forcePower,int overrideAmt);
CCALL int ForcePowerUsableOn(gentity_t *attacker,gentity_t *other,forcePowers_t forcePower);
CCALL qboolean BG_InKnockDown(int anim);
CCALL void WP_ForcePowerStop(gentity_t *self,forcePowers_t forcePower);
CCALL void WP_SpawnInitForcePowers(gentity_t *ent);
CCALL void WP_InitForcePowers(gentity_t *ent);
CCALL gentity_t *G_PreDefSound(vec3_t org,int pdSound);
CCALL int ForceShootDrain(gentity_t *self);
CCALL int ForceShootDrain(gentity_t *self);
CCALL qboolean BG_FullBodyTauntAnim(int anim);
CCALL void Jedi_Decloak(gentity_t *self);
CCALL void NPC_UseResponse(gentity_t *self,gentity_t *user,qboolean useWhenDone);
CCALL void NPC_Jedi_PlayConfusionSound(gentity_t *self);
CCALL void NPC_PlayConfusionSound(gentity_t *self);
