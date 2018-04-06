#pragma once

#include "qcommon/q_shared.h"

EXTERNC const char *gametypeStringShort[GT_MAX_GAME_TYPE];
EXTERNC cvar_t *bg_showevents;
EXTERNC const char *eventnames[];
EXTERNC int bg_numItems;
EXTERNC gitem_t bg_itemlist[];
EXTERNC int WeaponAttackAnim[WP_NUM_WEAPONS];
EXTERNC int WeaponReadyLegsAnim[WP_NUM_WEAPONS];
EXTERNC int WeaponReadyAnim[WP_NUM_WEAPONS];
EXTERNC int forcePowerDarkLight[NUM_FORCE_POWERS];
EXTERNC int forcePowerSorted[NUM_FORCE_POWERS];
EXTERNC int bgForcePowerCost[NUM_FORCE_POWERS][NUM_FORCE_POWER_LEVELS];
EXTERNC int forceMasteryPoints[NUM_FORCE_MASTERY_LEVELS];
EXTERNC char *forceMasteryLevels[NUM_FORCE_MASTERY_LEVELS];
EXTERNC const char *bg_customSiegeSoundNames[MAX_CUSTOM_SIEGE_SOUNDS];
EXTERNC const int bgToggleableSurfaceDebris[BG_NUM_TOGGLEABLE_SURFACES];
EXTERNC const char *bgToggleableSurfaces[BG_NUM_TOGGLEABLE_SURFACES];

CCALL int BG_GetGametypeForString(const char *gametype);
CCALL const char *BG_GetGametypeString(int gametype);
CCALL qboolean BG_OutOfMemory(void);
CCALL char *BG_StringAlloc(const char *source);
CCALL void BG_TempFree(int size);
CCALL void *BG_TempAlloc(int size);
CCALL void *BG_AllocUnaligned(int size);
CCALL void *BG_Alloc(int size);
CCALL int BG_ModelCache(const char *modelName,const char *skinName);
CCALL void BG_PlayerStateToEntityStateExtraPolate(playerState_t *ps,entityState_t *s,int time,qboolean snap);
CCALL void BG_PlayerStateToEntityState(playerState_t *ps,entityState_t *s,qboolean snap);
CCALL qboolean BG_ValidateSkinForTeam(const char *modelName,char *skinName,int team,float *colors);
CCALL qboolean BG_IsValidCharacterModel(const char *modelName,const char *skinName);
CCALL int BG_EmplacedView(vec3_t baseAngles,vec3_t angles,float *newYaw,float constraint);
CCALL void BG_TouchJumpPad(playerState_t *ps,entityState_t *jumppad);
CCALL void BG_AddPredictableEventToPlayerstate(int newEvent,int eventParm,playerState_t *ps);
CCALL void BG_EvaluateTrajectoryDelta(const trajectory_t *tr,int atTime,vec3_t result);
CCALL qboolean BG_CanItemBeGrabbed(int gametype,const entityState_t *ent,const playerState_t *ps);
CCALL void BG_CycleInven(playerState_t *ps,int direction);
CCALL qboolean BG_IsItemSelectable(playerState_t *ps,int item);
CCALL int BG_GetItemIndexByTag(int tag,int type);
CCALL void BG_CycleForce(playerState_t *ps,int direction);
CCALL int BG_ProperForceIndex(int power);
CCALL void BG_EvaluateTrajectory(const trajectory_t *tr,int atTime,vec3_t result);
CCALL qboolean BG_PlayerTouchesItem(playerState_t *ps,entityState_t *item,int atTime);
CCALL gitem_t *BG_FindItem(const char *classname);
CCALL gitem_t *BG_FindItemForAmmo(ammo_t ammo);
CCALL gitem_t *BG_FindItemForWeapon(weapon_t weapon);
CCALL gitem_t *BG_FindItemForHoldable(holdable_t pw);
CCALL gitem_t *BG_FindItemForPowerup(powerup_t pw);
CCALL qboolean BG_CanUseFPNow(int gametype,playerState_t *ps,int time,forcePowers_t power);
CCALL qboolean BG_HasYsalamiri(int gametype,playerState_t *ps);
CCALL float vectoyaw(const vec3_t vec);
CCALL qboolean BG_LegalizedForcePowers(char *powerOut,size_t powerOutSize,int maxRank,qboolean freeSaber,int teamForce,int gametype,int fpDisabled);
CCALL void BG_GiveMeVectorFromMatrix(mdxaBone_t *boltMatrix,int flags,vec3_t vec);
CCALL qboolean BG_FileExists(const char *fileName);
