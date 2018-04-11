#include "g_local.h"
#include "bg_saga.h"

typedef enum tauntTypes_e
{
	TAUNT_TAUNT = 0,
	TAUNT_BOW,
	TAUNT_MEDITATE,
	TAUNT_FLOURISH,
	TAUNT_GLOAT
} tauntTypes_t;

CCALL void ClientEndFrame(gentity_t *ent);
CCALL void SpectatorClientEndFrame(gentity_t *ent);
CCALL void G_RunClient(gentity_t *ent);
CCALL void G_CheckClientTimeouts(gentity_t *ent);
CCALL void ClientThink(int clientNum,usercmd_t *ucmd);
CCALL void ClientThink_real(gentity_t *ent);
CCALL void G_SetTauntAnim(gentity_t *ent,int taunt);
CCALL void G_HeldByMonster(gentity_t *ent,usercmd_t *ucmd);
CCALL void G_CheckMovingLoopingSounds(gentity_t *ent,usercmd_t *ucmd);
CCALL qboolean FlyingCreature(gentity_t *ent);
CCALL void NPC_Accelerate(gentity_t *ent,qboolean fullWalkAcc,qboolean fullRunAcc);
CCALL void G_CheckClientIdle(gentity_t *ent,usercmd_t *ucmd);
CCALL qboolean G_ActionButtonPressed(int buttons);
CCALL qboolean G_StandingAnim(int anim);
CCALL void G_AddPushVecToUcmd(gentity_t *self,usercmd_t *ucmd);
CCALL void G_UpdateClientBroadcasts(gentity_t *self);
CCALL void SendPendingPredictableEvents(playerState_t *ps);
CCALL void ClientEvents(gentity_t *ent,int oldEventSequence);
CCALL qboolean BG_InKnockDownOnly(int anim);
CCALL void G_CheapWeaponFire(int entNum,int ev);
CCALL qboolean BG_SabersOff(playerState_t *ps);
CCALL void G_VehicleAttachDroidUnit(gentity_t *vehEnt);
CCALL void NPC_SetAnim(gentity_t *ent,int setAnimParts,int anim,int setAnimFlags);
CCALL void ClientIntermissionThink(gclient_t *client);
CCALL void ClientTimerActions(gentity_t *ent,int msec);
CCALL qboolean ClientInactivityTimer(gclient_t *client);
CCALL void SpectatorThink(gentity_t *ent,usercmd_t *ucmd);
CCALL void G_MoverTouchPushTriggers(gentity_t *ent,vec3_t oldOrg);
CCALL void G_TouchTriggers(gentity_t *ent);
CCALL void ClientImpacts(gentity_t *ent,pmove_t *pmove);
CCALL void G_SetClientSound(gentity_t *ent);
CCALL void Client_CheckImpactBBrush(gentity_t *self,gentity_t *other);
CCALL void DoImpact(gentity_t *self,gentity_t *other,qboolean damageSelf);
CCALL void G_ApplyKnockback(gentity_t *targ,vec3_t newDir,float knockback);
CCALL void P_WorldEffects(gentity_t *ent);
CCALL void P_DamageFeedback(gentity_t *player);
CCALL void P_SetTwitchInfo(gclient_t *client);
CCALL qboolean saberCheckKnockdown_DuelLoss(gentity_t *saberent,gentity_t *saberOwner,gentity_t *other);
CCALL qboolean WP_SaberStyleValidForSaber(saberInfo_t *saber1,saberInfo_t *saber2,int saberHolstered,int saberAnimLevel);
CCALL qboolean PM_SaberInReturn(int move);
CCALL qboolean PM_SaberInStart(int move);
CCALL qboolean PM_SaberInTransition(int move);
CCALL void Jedi_Decloak(gentity_t *self);
CCALL void Jedi_Cloak(gentity_t *self);
