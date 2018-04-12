#pragma once

#include "b_local.h"
#include "g_nav.h"
#include "anims.h"
#include "w_saber.h"

#define	MAX_VIEW_DIST		2048
#define MAX_VIEW_SPEED		100
#define	JEDI_MAX_LIGHT_INTENSITY 64
#define	JEDI_MIN_LIGHT_THRESHOLD 10
#define	JEDI_MAX_LIGHT_THRESHOLD 50

#define	DISTANCE_SCALE		0.25f
#define	SPEED_SCALE			0.25f
#define	FOV_SCALE			0.5f
#define	LIGHT_SCALE			0.25f

#define	REALIZE_THRESHOLD	0.6f
#define CAUTIOUS_THRESHOLD	( REALIZE_THRESHOLD * 0.3 )

#define	MAX_CHECK_THRESHOLD	1

#define	APEX_HEIGHT		200.0f
#define	PARA_WIDTH		(sqrt(APEX_HEIGHT)+sqrt(APEX_HEIGHT))
#define	JUMP_SPEED		200.0f

typedef enum
{
	LSTATE_NONE = 0,
	LSTATE_UNDERFIRE,
	LSTATE_INVESTIGATE,
} JediLState;

EXTERNC int bg_parryDebounce[];

CCALL void NPC_BSJedi_Default(void);
CCALL void NPC_BSSniper_Default(void);
CCALL void NPC_BSST_Patrol(void);
CCALL qboolean Jedi_InSpecialMove(void);
CCALL void WP_Explode(gentity_t *self);
CCALL void NPC_BSJedi_FollowLeader(void);
CCALL qboolean Jedi_CanPullBackSaber(gentity_t *self);
CCALL void Jedi_Ambush(gentity_t *self);
CCALL qboolean Jedi_CheckAmbushPlayer(void);
CCALL qboolean Jedi_CheckDanger(void);
CCALL void NPC_Jedi_Pain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void G_UcmdMoveForDir(gentity_t *self,usercmd_t *cmd,vec3_t dir);
CCALL float WP_SpeedOfMissileForWeapon(int wp,qboolean alt_fire);
CCALL gentity_t *Jedi_FindEnemyInCone(gentity_t *self,gentity_t *fallback,float minDot);
CCALL int WPDEBUG_SaberColor(saber_colors_t saberColor);
CCALL float ShortestLineSegBewteen2LineSegs(vec3_t start1,vec3_t end1,vec3_t start2,vec3_t end2,vec3_t close_pnt1,vec3_t close_pnt2);
CCALL evasionType_t Jedi_SaberBlockGo(gentity_t *self,usercmd_t *cmd,vec3_t pHitloc,vec3_t phitDir,gentity_t *incoming,float dist);
CCALL qboolean G_FindClosestPointOnLineSegment(const vec3_t start,const vec3_t end,const vec3_t from,vec3_t result);
CCALL qboolean Jedi_SaberBusy(gentity_t *self);
CCALL qboolean Jedi_QuickReactions(gentity_t *self);
CCALL int Jedi_ReCalcParryTime(gentity_t *self,evasionType_t evasionType);
CCALL evasionType_t Jedi_CheckFlipEvasions(gentity_t *self,float rightdot,float zdiff);
CCALL void ForceDrain(gentity_t *self);
CCALL qboolean NPC_MoveDirClear(int forwardmove,int rightmove,qboolean reset);
CCALL void Jedi_RageStop(gentity_t *self);
CCALL void NPC_Jedi_RateNewEnemy(gentity_t *self,gentity_t *enemy);
CCALL void Jedi_CheckCloak(void);
CCALL void Jedi_Decloak(gentity_t *self);
CCALL void Jedi_Cloak(gentity_t *self);
CCALL void Boba_FireDecide(void);
CCALL void Boba_DoFlameThrower(gentity_t *self);
CCALL void Boba_StartFlameThrower(gentity_t *self);
CCALL void Boba_FireFlameThrower(gentity_t *self);
CCALL qboolean Boba_Flying(gentity_t *self);
CCALL void Boba_FlyStop(gentity_t *self);
CCALL void Boba_FlyStart(gentity_t *self);
CCALL qboolean Boba_StopKnockdown(gentity_t *self,gentity_t *pusher,vec3_t pushDir,qboolean forceKnockdown);
CCALL void WP_ResistForcePush(gentity_t *self,gentity_t *pusher,qboolean noPenalty);
CCALL void Boba_ChangeWeapon(int wp);
CCALL void ChangeWeapon(gentity_t *ent,int newWeapon);
CCALL void G_CreateG2AttachedWeaponModel(gentity_t *ent,const char *weaponModel,int boltNum,int weaponNum);
CCALL void Boba_Precache(void);
CCALL qboolean Jedi_CultistDestroyer(gentity_t *self);
CCALL void NPC_Jedi_PlayConfusionSound(gentity_t *self);
CCALL void Jedi_PlayDeflectSound(gentity_t *self);
CCALL void Jedi_PlayBlockedPushSound(gentity_t *self);
CCALL void Jedi_ClearTimers(gentity_t *ent);
CCALL void NPC_ShadowTrooper_Precache(void);
CCALL qboolean Jedi_WaitingAmbush(gentity_t *self);
CCALL void G_TestLine(vec3_t start,vec3_t end,int color,int time);
CCALL int WP_GetVelocityForForceJump(gentity_t *self,vec3_t jumpVel,usercmd_t *ucmd);
CCALL qboolean NPC_SomeoneLookingAtMe(gentity_t *ent);
CCALL qboolean BG_CrouchAnim(int anim);
CCALL qboolean BG_InRoll(playerState_t *ps,int anim);
CCALL qboolean PM_InKnockDown(playerState_t *ps);
CCALL qboolean PM_RollingAnim(int anim);
CCALL qboolean BG_FlippingAnim(int anim);
CCALL qboolean BG_SpinningSaberAnim(int anim);
CCALL qboolean PM_SaberInDeflect(int move);
CCALL qboolean PM_SaberInBrokenParry(int move);
CCALL qboolean PM_SaberInKnockaway(int move);
CCALL qboolean PM_SaberInParry(int move);
CCALL qboolean PM_SaberInBounce(int move);
CCALL qboolean BG_SaberInAttack(int move);
CCALL qboolean BG_SaberInSpecialAttack(int anim);
CCALL qboolean PM_SaberInStart(int move);
CCALL void WP_ActivateSaber(gentity_t *self);
CCALL void WP_DeactivateSaber(gentity_t *self,qboolean clearLength);
CCALL void WP_ForcePowerStop(gentity_t *self,forcePowers_t forcePower);
CCALL qboolean WP_ForcePowerAvailable(gentity_t *self,forcePowers_t forcePower,int overrideAmt);
CCALL qboolean WP_ForcePowerUsable(gentity_t *self,forcePowers_t forcePower);
CCALL qboolean G_GetHitLocFromSurfName(gentity_t *ent,const char *surfName,int *hitLoc,vec3_t point,vec3_t dir,vec3_t bladeDir,int mod);
CCALL int WP_MissileBlockForBlock(int saberBlock);
CCALL void ForceAbsorb(gentity_t *self);
CCALL void ForceProtect(gentity_t *self);
CCALL void ForceRage(gentity_t *self);
CCALL void ForceHeal(gentity_t *self);
CCALL void ForceLightning(gentity_t *self);
CCALL void ForceThrow(gentity_t *self,qboolean pull);
CCALL gitem_t *BG_FindItemForAmmo(ammo_t ammo);
CCALL void G_SoundOnEnt(gentity_t *ent,soundChannel_t channel,const char *soundPath);
CCALL qboolean NPC_CheckEnemyStealth(void);
CCALL qboolean G_ExpandPointToBBox(vec3_t point,const vec3_t mins,const vec3_t maxs,int ignore,int clipmask);
CCALL void NPC_TempLookTarget(gentity_t *self,int lookEntNum,int minLookTime,int maxLookTime);
CCALL void NPC_SetLookTarget(gentity_t *self,int entNum,int clearTime);
CCALL void NPC_ClearLookTarget(gentity_t *self);
CCALL void ForceJump(gentity_t *self,usercmd_t *ucmd);
CCALL void G_AddVoiceEvent(gentity_t *self,int event,int speakDebounceTime);
CCALL void CG_DrawAlert(vec3_t origin,float rating);
CCALL qboolean BG_SabersOff(playerState_t *ps);
