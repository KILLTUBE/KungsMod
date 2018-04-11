#pragma once

#include "b_local.h"
#include "bg_saga.h"
#include "../game/bg_g2_utils.h"

EXTERNC vec3_t gPainPoint;
EXTERNC int gPainMOD;
EXTERNC qboolean gSiegeRoundBegun;
EXTERNC int gPainHitLoc;
EXTERNC char *hitLocName[HL_MAX];
EXTERNC qboolean g_noPDuelCheck;
EXTERNC qboolean g_endPDuel;
EXTERNC qboolean g_dontFrickinCheck;
EXTERNC qboolean g_dontPenalizeTeam;
EXTERNC char *modNames[MOD_MAX];
EXTERNC int gGAvoidDismember;

CCALL qboolean CanDamage(gentity_t *targ,vec3_t origin);
CCALL void G_Knockdown(gentity_t *victim);
CCALL qboolean G_ThereIsAMaster(void);
CCALL void G_LocationBasedDamageModifier(gentity_t *ent,vec3_t point,int mod,int dflags,int *damage);
CCALL qboolean G_GetHitLocFromSurfName(gentity_t *ent,const char *surfName,int *hitLoc,vec3_t point,vec3_t dir,vec3_t bladeDir,int mod);
CCALL void UpdateClientRenderBolts(gentity_t *self,vec3_t renderOrigin,vec3_t renderAngles);
CCALL int G_GetHitQuad(gentity_t *self,vec3_t hitloc);
CCALL void DismembermentByNum(gentity_t *self,int num);
CCALL void DismembermentTest(gentity_t *self);
CCALL void G_Dismember(gentity_t *ent,gentity_t *enemy,vec3_t point,int limbType,float limbRollBase,float limbPitchBase,int deathAnim,qboolean postDeath);
CCALL void LimbThink(gentity_t *ent);
CCALL void LimbTouch(gentity_t *self,gentity_t *other,trace_t *trace);
CCALL void G_GetDismemberBolt(gentity_t *self,vec3_t boltPoint,int limbType);
CCALL void G_GetDismemberLoc(gentity_t *self,vec3_t boltPoint,int limbType);
CCALL int RaySphereIntersections(vec3_t origin,float radius,vec3_t point,vec3_t dir,vec3_t intersections[2]);
CCALL void G_ApplyKnockback(gentity_t *targ,vec3_t newDir,float knockback);
CCALL int CheckArmor(gentity_t *ent,int damage,int dflags);
CCALL void G_CheckForDismemberment(gentity_t *ent,gentity_t *enemy,vec3_t point,int damage,int deathAnim,qboolean postDeath);
CCALL void G_Damage(gentity_t *targ,gentity_t *inflictor,gentity_t *attacker,vec3_t dir,vec3_t point,int damage,int dflags,int mod);
CCALL void player_die(gentity_t *self,gentity_t *inflictor,gentity_t *attacker,int damage,int meansOfDeath);
CCALL void saberBackToOwner(gentity_t *saberent);
CCALL void saberReactivate(gentity_t *saberent,gentity_t *saberOwner);
CCALL void Rancor_DropVictim(gentity_t *self);
CCALL void CheckExitRules(void);
CCALL qboolean Jedi_WaitingAmbush(gentity_t *self);
CCALL void Boba_FlyStop(gentity_t *self);
CCALL void AI_GroupMemberKilled(gentity_t *self);
CCALL void AI_DeleteSelfFromGroup(gentity_t *self);
CCALL extern stringID_table_t animTable[MAX_ANIMATIONS+1];
CCALL void G_AddPowerDuelLoserScore(int team,int score);
CCALL void G_AddPowerDuelScore(int team,int score);
CCALL void G_CheckVictoryScript(gentity_t *self);
CCALL void DeathFX(gentity_t *ent);
CCALL void G_DeathAlert(gentity_t *victim,gentity_t *attacker);
CCALL void G_AlertTeam(gentity_t *victim,gentity_t *attacker,float radius,float soundDist);
CCALL gentity_t *G_GetJediMaster(void);
CCALL int G_PickDeathAnim(gentity_t *self,vec3_t point,int damage,int mod,int hitLoc);
CCALL qboolean G_InKnockDown(playerState_t *ps);
CCALL void CheckAlmostCapture(gentity_t *self,gentity_t *attacker);
CCALL void body_die(gentity_t *self,gentity_t *inflictor,gentity_t *attacker,int damage,int meansOfDeath);
CCALL void BodyRid(gentity_t *ent);
CCALL void GibEntity(gentity_t *self,int killer);
CCALL void LookAtKiller(gentity_t *self,gentity_t *inflictor,gentity_t *attacker);
CCALL void TossClientItems(gentity_t *self);
CCALL void TossClientWeapon(gentity_t *self,vec3_t direction,float speed);
CCALL void AddScore(gentity_t *ent,vec3_t origin,int score);
CCALL void ScorePlum(gentity_t *ent,vec3_t origin,int score);
CCALL qboolean G_RadiusDamage(vec3_t origin,gentity_t *attacker,float damage,float radius,gentity_t *ignore,gentity_t *missile,int mod);
CCALL void ExplodeDeath(gentity_t *self);
CCALL int G_GetHitLocation(gentity_t *target,vec3_t ppoint);
CCALL qboolean G_HeavyMelee(gentity_t *attacker);
CCALL void ObjectDie(gentity_t *self,gentity_t *inflictor,gentity_t *attacker,int damage,int meansOfDeath);
CCALL void ThrowSaberToAttacker(gentity_t *self,gentity_t *attacker);
CCALL void BotDamageNotification(gclient_t *bot,gentity_t *attacker);
CCALL void BG_ClearRocketLock(playerState_t *ps);
CCALL void G_LetGoOfWall(gentity_t *ent);
CCALL void G_VehUpdateShields(gentity_t *targ);
CCALL void G_VehicleSetDamageLocFlags(gentity_t *veh,int impactDir,int deathPoint);
CCALL qboolean G_FlyVehicleDestroySurface(gentity_t *veh,int surface);
CCALL int G_ShipSurfaceForSurfName(const char *surfaceName);
