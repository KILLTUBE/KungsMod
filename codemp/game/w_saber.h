/*
===========================================================================
Copyright (C) 2000 - 2013, Raven Software, Inc.
Copyright (C) 2001 - 2013, Activision, Inc.
Copyright (C) 2013 - 2015, OpenJK contributors

This file is part of the OpenJK source code.

OpenJK is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License version 2 as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, see <http://www.gnu.org/licenses/>.
===========================================================================
*/

#pragma once

#include "../game/g_local.h"

#define ARMOR_EFFECT_TIME	500

//saberEventFlags
#define	SEF_HITENEMY	0x1		//Hit the enemy
#define	SEF_HITOBJECT	0x2		//Hit some other object
#define	SEF_HITWALL		0x4		//Hit a wall
#define	SEF_PARRIED		0x8		//Parried a saber swipe
#define	SEF_DEFLECTED	0x10	//Deflected a missile or saberInFlight
#define	SEF_BLOCKED		0x20	//Was blocked by a parry
#define	SEF_EVENTS		(SEF_HITENEMY|SEF_HITOBJECT|SEF_HITWALL|SEF_PARRIED|SEF_DEFLECTED|SEF_BLOCKED)
#define	SEF_LOCKED		0x40	//Sabers locked with someone else
#define	SEF_INWATER		0x80	//Saber is in water
#define	SEF_LOCK_WON	0x100	//Won a saberLock
//saberEntityState
#define SES_LEAVING		1
#define SES_HOVERING	1//2
#define SES_RETURNING	1//3
//This is a hack because ATM the saberEntityState is only non-0 if out or 0 if in, and we
//at least want NPCs knowing when their saber is out regardless.


#define JSF_AMBUSH		16	//ambusher Jedi

#define SABER_RADIUS_STANDARD	3.0f
#define	SABER_REFLECT_MISSILE_CONE	0.2f

#define	FORCE_POWER_MAX	100
#define MAX_GRIP_DISTANCE 256
#define MAX_TRICK_DISTANCE 512
#define FORCE_JUMP_CHARGE_TIME 6400//3000.0f
#define GRIP_DRAIN_AMOUNT 30
#define FORCE_LIGHTNING_RADIUS 300
#define MAX_DRAIN_DISTANCE 512
#define SABER_BOX_SIZE 16.0f

typedef enum forceJump_e
{
	FJ_FORWARD,
	FJ_BACKWARD,
	FJ_RIGHT,
	FJ_LEFT,
	FJ_UP
} forceJump_t;

typedef enum
{
	EVASION_NONE = 0,
	EVASION_PARRY,
	EVASION_DUCK_PARRY,
	EVASION_JUMP_PARRY,
	EVASION_DODGE,
	EVASION_JUMP,
	EVASION_DUCK,
	EVASION_FJUMP,
	EVASION_CARTWHEEL,
	EVASION_OTHER,
	NUM_EVASION_TYPES
} evasionType_t;

#define SABERMINS_X -3.0f//-24.0f
#define SABERMINS_Y -3.0f//-24.0f
#define SABERMINS_Z -3.0f//-8.0f
#define SABERMAXS_X 3.0f//24.0f
#define SABERMAXS_Y 3.0f//24.0f
#define SABERMAXS_Z 3.0f//8.0f
#define	SABER_MIN_THROW_DIST	80.0f

EXTERNC int forcePowerNeeded[NUM_FORCE_POWER_LEVELS][NUM_FORCE_POWERS];
EXTERNC float forceJumpHeight[NUM_FORCE_POWER_LEVELS];
EXTERNC float forceJumpStrength[NUM_FORCE_POWER_LEVELS];
EXTERNC float forcePushPullRadius[NUM_FORCE_POWER_LEVELS];
//EXTERNC bot_state_t *botstates[MAX_CLIENTS];
EXTERNC int saberSpinSound;
EXTERNC stringID_table_t animTable[MAX_ANIMATIONS+1];


CCALL qboolean HasSetSaberOnly(void);
CCALL void WP_SaberBlock(gentity_t *playerent,vec3_t hitloc,qboolean missileBlock);
CCALL int WP_MissileBlockForBlock(int saberBlock);
CCALL void WP_SaberPositionUpdate(gentity_t *self,usercmd_t *ucmd);
CCALL qboolean BG_InKnockDown(int anim);
CCALL void G_GetBoltPosition(gentity_t *self,int boltIndex,vec3_t pos,int modelIndex);
CCALL void UpdateClientRenderinfo(gentity_t *self,vec3_t renderOrigin,vec3_t renderAngles);
CCALL void UpdateClientRenderBolts(gentity_t *self,vec3_t renderOrigin,vec3_t renderAngles);
CCALL void saberFirstThrown(gentity_t *saberent);
CCALL void saberFirstThrown(gentity_t *saberent);
CCALL qboolean BG_InExtraDefenseSaberMove(int move);
CCALL qboolean saberCheckKnockdown_DuelLoss(gentity_t *saberent,gentity_t *saberOwner,gentity_t *other);
CCALL qboolean saberKnockOutOfHand(gentity_t *saberent,gentity_t *saberOwner,vec3_t velocity);
CCALL void saberKnockDown(gentity_t *saberent,gentity_t *saberOwner,gentity_t *other);
CCALL void DownedSaberThink(gentity_t *saberent);
CCALL void saberBackToOwner(gentity_t *saberent);
CCALL void saberBackToOwner(gentity_t *saberent);
CCALL void saberReactivate(gentity_t *saberent,gentity_t *saberOwner);
CCALL void saberReactivate(gentity_t *saberent,gentity_t *saberOwner);
CCALL void MakeDeadSaber(gentity_t *ent);
CCALL void DeadSaberThink(gentity_t *saberent);
CCALL void SaberBounceSound(gentity_t *self,gentity_t *other,trace_t *trace);
CCALL void thrownSaberTouch(gentity_t *saberent,gentity_t *other,trace_t *trace);
CCALL void thrownSaberTouch(gentity_t *saberent,gentity_t *other,trace_t *trace);
CCALL void WP_SaberStartMissileBlockCheck(gentity_t *self,usercmd_t *ucmd);
CCALL void NPC_SetLookTarget(gentity_t *self,int entNum,int clearTime);
CCALL evasionType_t Jedi_SaberBlockGo(gentity_t *self,usercmd_t *cmd,vec3_t pHitloc,vec3_t phitDir,gentity_t *incoming,float dist);
CCALL void Jedi_Ambush(gentity_t *self);
CCALL qboolean Jedi_WaitingAmbush(gentity_t *self);
CCALL qboolean InFOV3(vec3_t spot,vec3_t from,vec3_t fromAngles,int hFOV,int vFOV);
CCALL qboolean WP_ForcePowerUsable(gentity_t *self,forcePowers_t forcePower);
CCALL void G_SPSaberDamageTraceLerped(gentity_t *self,int saberNum,int bladeNum,vec3_t baseNew,vec3_t endNew,int clipmask);
CCALL int WP_SaberCanBlock(gentity_t *self,vec3_t point,int dflags,int mod,qboolean projectile,int attackStr);
CCALL qboolean BG_SuperBreakWinAnim(int anim);
CCALL void WP_SaberBounceSound(gentity_t *ent,int saberNum,int bladeNum);
CCALL void WP_SaberDoClash(gentity_t *self,int saberNum,int bladeNum);
CCALL void WP_SaberRadiusDamage(gentity_t *ent,vec3_t point,float radius,int damage,float knockBack);
CCALL void G_Knockdown(gentity_t *victim);
CCALL qboolean G_EntIsBreakable(int entityNum);
CCALL void WP_SaberDoHit(gentity_t *self,int saberNum,int bladeNum);
CCALL void WP_SaberApplyDamage(gentity_t *self);
CCALL void WP_SaberDamageAdd(int trVictimEntityNum,vec3_t trDmgDir,vec3_t trDmgSpot,int trDmg,qboolean doDismemberment,int knockBackFlags);
CCALL void WP_SaberClearDamage(void);
CCALL qboolean WP_SabersIntersect(gentity_t *ent1,int ent1SaberNum,int ent1BladeNum,gentity_t *ent2,qboolean checkDir);
CCALL qboolean tri_tri_intersect(vec3_t V0,vec3_t V1,vec3_t V2,vec3_t U0,vec3_t U1,vec3_t U2);
CCALL int WPDEBUG_SaberColor(saber_colors_t saberColor);
CCALL float WP_SaberLength(gentity_t *ent);
CCALL float WP_SaberBladeLength(saberInfo_t *saber);
CCALL qboolean saberCheckKnockdown_BrokenParry(gentity_t *saberent,gentity_t *saberOwner,gentity_t *other);
CCALL qboolean saberCheckKnockdown_BrokenParry(gentity_t *saberent,gentity_t *saberOwner,gentity_t *other);
CCALL qboolean saberCheckKnockdown_Smashed(gentity_t *saberent,gentity_t *saberOwner,gentity_t *other,int damage);
CCALL qboolean saberCheckKnockdown_Smashed(gentity_t *saberent,gentity_t *saberOwner,gentity_t *other,int damage);
CCALL qboolean saberCheckKnockdown_Thrown(gentity_t *saberent,gentity_t *saberOwner,gentity_t *other);
CCALL qboolean saberCheckKnockdown_Thrown(gentity_t *saberent,gentity_t *saberOwner,gentity_t *other);
CCALL int G_KnockawayForParry(int move);
CCALL int PM_SaberDeflectionForQuad(int quad);
CCALL int PM_SaberBounceForAttack(int move);
CCALL qboolean WP_SabersCheckLock(gentity_t *ent1,gentity_t *ent2);
CCALL qboolean BG_CheckIncrementLockAnim(int anim,int winOrLose);
CCALL int G_SaberLockAnim(int attackerSaberStyle,int defenderSaberStyle,int topOrSide,int lockOrBreakOrSuperBreak,int winOrLose);
CCALL void WP_SaberBlockNonRandom(gentity_t *self,vec3_t hitloc,qboolean missileBlock);
CCALL void WP_SaberBlockNonRandom(gentity_t *self,vec3_t hitloc,qboolean missileBlock);
CCALL void NPC_SetBoneAngles(gentity_t *ent,char *bone,vec3_t angles);
CCALL void WP_SaberInitBladeData(gentity_t *ent);
CCALL qboolean BG_SuperBreakLoseAnim(int anim);
CCALL void SaberGotHit(gentity_t *self,gentity_t *other,trace_t *trace);
CCALL void SaberUpdateSelf(gentity_t *ent);
CCALL void WP_ActivateSaber(gentity_t *self);
CCALL void WP_DeactivateSaber(gentity_t *self,qboolean clearLength);
CCALL qboolean G_CanBeEnemy(gentity_t *self,gentity_t *enemy);
#if defined(DEBUG_SABER_BOX)
CCALL void G_DebugBoxLines(vec3_t mins,vec3_t maxs,int duration);
#endif
CCALL float RandFloat(float min,float max);
CCALL void WP_SaberRemoveG2Model(gentity_t *saberent);
CCALL void WP_SaberRemoveG2Model(gentity_t *saberent);
CCALL void WP_SaberAddG2Model(gentity_t *saberent,const char *saberModel,qhandle_t saberSkin);
CCALL void WP_SaberAddG2Model(gentity_t *saberent,const char *saberModel,qhandle_t saberSkin);
CCALL qboolean WP_SaberBladeDoTransitionDamage(saberInfo_t *saber,int bladeNum);
CCALL qboolean WP_SaberBladeUseSecondBladeStyle(saberInfo_t *saber,int bladeNum);
CCALL qboolean BG_SaberInAttackPure(int move);
CCALL qboolean BG_SaberInTransitionAny(int move);
CCALL qboolean BG_SaberInTransitionAny(int move);
CCALL qboolean BG_SabersOff(playerState_t *ps);
CCALL qboolean BG_StabDownAnim(int anim);
CCALL qboolean BG_InKnockDownOnGround(playerState_t *ps);
CCALL qboolean BG_SaberInReturn(int move);
CCALL qboolean PM_SaberInBounce(int move);
CCALL qboolean PM_SaberInBrokenParry(int move);
CCALL qboolean PM_SaberInDeflect(int move);
CCALL qboolean PM_SaberInTransition(int move);
CCALL void G_TestLine(vec3_t start,vec3_t end,int color,int time);
CCALL qboolean InFront(vec3_t spot,vec3_t from,vec3_t fromAngles,float threshHold);
