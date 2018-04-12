#pragma once

#include "b_local.h"
#include "anims.h"
#include "say.h"
#include "icarus/Q3_Interface.h"

#define REMOVE_DISTANCE		128
#define REMOVE_DISTANCE_SQR (REMOVE_DISTANCE * REMOVE_DISTANCE)

EXTERNC vec3_t NPCDEBUG_LIGHT_BLUE;
EXTERNC vec3_t NPCDEBUG_BLUE;
EXTERNC vec3_t NPCDEBUG_GREEN;
EXTERNC vec3_t NPCDEBUG_RED;
EXTERNC qboolean showBBoxes;
EXTERNC npcStatic_t _saved_NPCS;
EXTERNC int eventClearTime;
EXTERNC npcStatic_t NPCS;
EXTERNC vec3_t playerMaxs;
EXTERNC vec3_t playerMins;
#if AI_TIMERS
EXTERNC int AITime;
#endif

CCALL void NPC_InitGame(void);
CCALL void NPC_InitAI(void);
CCALL void NPC_Think(gentity_t *self);
CCALL void G_DroidSounds(gentity_t *self);
CCALL void NPC_CheckInSolid(void);
CCALL void NPC_ExecuteBState(gentity_t *self);
CCALL void NPC_RunBehavior(int team,int bState);
CCALL qboolean Jedi_CultistDestroyer(gentity_t *self);
CCALL void NPC_BSWampa_Default(void);
CCALL void Boba_FlyStop(gentity_t *self);
CCALL qboolean NPC_CheckSurrender(void);
CCALL void NPC_BSEmplaced(void);
CCALL void NPC_BehaviorSet_Rancor(int bState);
CCALL void NPC_BehaviorSet_Howler(int bState);
CCALL void NPC_BehaviorSet_MineMonster(int bState);
CCALL void NPC_BehaviorSet_ATST(int bState);
CCALL void NPC_BehaviorSet_Mark2(int bState);
CCALL void NPC_BehaviorSet_Mark1(int bState);
CCALL void NPC_BehaviorSet_Droid(int bState);
CCALL void NPC_BehaviorSet_Jedi(int bState);
CCALL void NPC_BehaviorSet_Stormtrooper(int bState);
CCALL void NPC_BehaviorSet_Sniper(int bState);
CCALL void NPC_BehaviorSet_Grenadier(int bState);
CCALL void NPC_BehaviorSet_Sentry(int bState);
CCALL void NPC_BSSentry_Default(void);
CCALL void NPC_BehaviorSet_Remote(int bState);
CCALL void NPC_BSRemote_Default(void);
CCALL void NPC_BehaviorSet_Seeker(int bState);
CCALL void NPC_BSSeeker_Default(void);
CCALL void NPC_BehaviorSet_ImperialProbe(int bState);
CCALL void NPC_BSImperialProbe_Wait(void);
CCALL void NPC_BSImperialProbe_Patrol(void);
CCALL void NPC_BSImperialProbe_Attack(void);
CCALL void NPC_BehaviorSet_Interrogator(int bState);
CCALL void NPC_BehaviorSet_Default(int bState);
CCALL void NPC_BehaviorSet_Charmed(int bState);
CCALL void NPC_KeepCurrentFacing(void);
CCALL void NPC_CheckAttackHold(void);
CCALL float NPC_MaxDistSquaredForWeapon(void);
CCALL void NPC_CheckAttackScript(void);
CCALL void NPC_AvoidWallsAndCliffs(void);
CCALL void NPC_HandleAIFlags(void);
CCALL void Q3_DebugPrint(int level,const char *format,...);
CCALL void NPC_ApplyScriptFlags(void);
CCALL void NPC_ShowDebugInfo(void);
CCALL void G_Cylinder(vec3_t start,vec3_t end,float radius,vec3_t color);
CCALL void G_Line(vec3_t start,vec3_t end,vec3_t color,float alpha);
CCALL void G_Cube(vec3_t mins,vec3_t maxs,vec3_t color,float alpha);
CCALL void ClearNPCGlobals(void);
CCALL void RestoreNPCGlobals(void);
CCALL void SaveNPCGlobals(void);
CCALL void SetNPCGlobals(gentity_t *ent);
CCALL int BodyRemovalPadTime(gentity_t *ent);
CCALL void NPC_RemoveBody(gentity_t *self);
CCALL void CorpsePhysics(gentity_t *self);
CCALL void GM_Dying(gentity_t *self);
CCALL void pitch_roll_for_slope(gentity_t *forwhom,vec3_t pass_slope);
CCALL void pitch_roll_for_slope(gentity_t *forwhom,vec3_t pass_slope);
CCALL void NPC_SetAnim(gentity_t *ent,int type,int anim,int priority);
CCALL void NPC_SetAnim(gentity_t *ent,int setAnimParts,int anim,int setAnimFlags);
CCALL qboolean Boba_Flying(gentity_t *self);
CCALL void NPC_CheckCharmed(void);
CCALL void NPC_BSGM_Default(void);
CCALL int GetTime(int lastTime);
CCALL void NPC_BSCinematic(void);
CCALL void Mark1_dying(gentity_t *self);
CCALL void NPC_SetLookTarget(gentity_t *self,int entNum,int clearTime);
CCALL qboolean NPC_CheckLookTarget(gentity_t *self);
CCALL void NPC_CheckAllClear(void);
CCALL void NPC_CheckPlayerAim(void);
CCALL void NPC_TempLookTarget(gentity_t *self,int lookEntNum,int minLookTime,int maxLookTime);
CCALL void NPC_ApplyRoff(void);
CCALL void G_AddVoiceEvent(gentity_t *self,int event,int speakDebounceTime);
CCALL void G_AddVoiceEvent(gentity_t *self,int event,int speakDebounceTime);
CCALL void NPC_BSNoClip(void);
CCALL void PM_SetLegsAnimTimer(gentity_t *ent,int *legsAnimTimer,int time);
CCALL void PM_SetTorsoAnimTimer(gentity_t *ent,int *torsoAnimTimer,int time);
CCALL void G_SoundOnEnt(gentity_t *ent,soundChannel_t channel,const char *soundPath);
