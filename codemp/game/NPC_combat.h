
#pragma once

#include "b_local.h"
#include "g_nav.h"


#define	ANGER_ALERT_RADIUS			512
#define	ANGER_ALERT_SOUND_RADIUS	256

#define	MIN_AVOID_DOT				0.75f
#define MIN_AVOID_DISTANCE			128
#define MIN_AVOID_DISTANCE_SQUARED	( MIN_AVOID_DISTANCE * MIN_AVOID_DISTANCE )
#define	CP_COLLECT_RADIUS			512.0f

typedef struct combatPt_s {
	float dist;
	int index;
} combatPt_t;

CCALL void NPC_AimAdjust(int change);
CCALL void NPC_CheckGetNewWeapon(void);
CCALL void NPC_SetPickUpGoal(gentity_t *foundWeap);
CCALL gentity_t *NPC_SearchForWeapons(void);
CCALL qboolean CheckItemCanBePickedUpByNPC(gentity_t *item,gentity_t *pickerupper);
CCALL qboolean NPC_SetCombatPoint(int combatPointID);
CCALL qboolean NPC_FreeCombatPoint(int combatPointID,qboolean failed);
CCALL qboolean NPC_ReserveCombatPoint(int combatPointID);
CCALL int NPC_FindSquadPoint(vec3_t position);
CCALL int NPC_FindCombatPoint(const vec3_t position,const vec3_t avoidPosition,vec3_t enemyPosition,const int flags,const float avoidDist,const int ignorePoint);
CCALL void CP_FindCombatPointWaypoints(void);
CCALL void SP_point_combat(gentity_t *self);
CCALL float IdealDistance(gentity_t *self);
CCALL qboolean NPC_CheckCanAttack(float attack_scale,qboolean stationary);
CCALL qboolean NPC_CheckDefend(float scale);
CCALL qboolean NPC_CheckAttack(float scale);
CCALL qboolean NPC_EvaluateShot(int hit,qboolean glassOK);
CCALL int NPC_ShotEntity(gentity_t *ent,vec3_t impactPos);
CCALL qboolean NPC_ClearShot(gentity_t *ent);
CCALL gentity_t *NPC_CheckEnemy(qboolean findNew,qboolean tooFarOk,qboolean setEnemy);
CCALL gentity_t *NPC_PickAlly(qboolean facingEachOther,float range,qboolean ignoreGroup,qboolean movingOnly);
CCALL gentity_t *NPC_PickEnemy(gentity_t *closestTo,int enemyTeam,qboolean checkVis,qboolean findPlayersFirst,qboolean findClosest);
CCALL qboolean NPC_EnemyTooFar(gentity_t *enemy,float dist,qboolean toShoot);
CCALL qboolean ValidEnemy(gentity_t *ent);
CCALL float NPC_MaxDistSquaredForWeapon(void);
CCALL void NPC_CheckPossibleEnemy(gentity_t *other,visibility_t vis);
CCALL qboolean CanShoot(gentity_t *ent,gentity_t *shooter);
CCALL qboolean ShotThroughGlass(trace_t *tr,gentity_t *target,vec3_t spot,int mask);
CCALL qboolean EntIsGlass(gentity_t *check);
CCALL qboolean HaveWeapon(int weapon);
CCALL void WeaponThink(qboolean inCombat);
CCALL int NPC_AttackDebounceForWeapon(void);
CCALL void ShootThink(void);
CCALL void NPC_ApplyWeaponFireDelay(void);
CCALL void NPC_ChangeWeapon(int newWeapon);
CCALL void G_AimSet(gentity_t *self,int aim);
CCALL void G_AimSet(gentity_t *self,int aim);
CCALL void G_ForceSaberOn(gentity_t *ent);
CCALL void G_AttackDelay(gentity_t *self,gentity_t *enemy);
CCALL qboolean G_TeamEnemy(gentity_t *self);
CCALL void G_AngerAlert(gentity_t *self);
CCALL void G_ClearEnemy(gentity_t *self);
CCALL void ChangeWeapon(gentity_t *ent,int newWeapon);
CCALL void ChangeWeapon(gentity_t *ent,int newWeapon);
CCALL qboolean PM_DroidMelee(int npc_class);
CCALL void G_CreateG2AttachedWeaponModel(gentity_t *ent,const char *weaponModel,int boltNum,int weaponNum);
CCALL int NAV_GetNearestNode(gentity_t *self,int lastNode);
CCALL int NAV_FindClosestWaypointForPoint2(vec3_t point);
CCALL void NPC_Jedi_RateNewEnemy(gentity_t *self,gentity_t *enemy);
CCALL void NPC_ClearLookTarget(gentity_t *self);
CCALL qboolean NPC_CheckLookTarget(gentity_t *self);
CCALL void G_SetEnemy(gentity_t *self,gentity_t *enemy);
CCALL void G_SetEnemy(gentity_t *self,gentity_t *enemy);
CCALL void G_AddVoiceEvent(gentity_t *self,int event,int speakDebounceTime);
