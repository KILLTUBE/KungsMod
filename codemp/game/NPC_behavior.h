#pragma once

#include "b_local.h"
#include "g_nav.h"
#include "icarus/Q3_Interface.h"
#include "server/sv_nav.h"

#define	APEX_HEIGHT		200.0f
#define	PARA_WIDTH		(sqrt(APEX_HEIGHT)+sqrt(APEX_HEIGHT))
#define	JUMP_SPEED		200.0f

EXTERNC vec3_t NPCDEBUG_BLUE;
EXTERNC qboolean showBBoxes;

CCALL void NPC_BSEmplaced(void);
CCALL void G_StartFlee(gentity_t *self,gentity_t *enemy,vec3_t dangerPoint,int dangerLevel,int fleeTimeMin,int fleeTimeMax);
CCALL void NPC_StartFlee(gentity_t *enemy,vec3_t dangerPoint,int dangerLevel,int fleeTimeMin,int fleeTimeMax);
CCALL void NPC_BSFlee(void);
CCALL qboolean NPC_CheckSurrender(void);
CCALL void NPC_Surrender(void);
CCALL void ChangeWeapon(gentity_t *ent,int newWeapon);
CCALL void WP_DropWeapon(gentity_t *dropper,vec3_t velocity);
CCALL void G_AddVoiceEvent(gentity_t *self,int event,int speakDebounceTime);
CCALL void NPC_BSWander(void);
CCALL void NPC_BSNoClip(void);
CCALL void NPC_BSSearchStart(int homeWp,bState_t bState);
CCALL void NPC_BSSearch(void);
CCALL void NPC_BSRemove(void);
CCALL void NPC_BSJump(void);
CCALL void NPC_BSFollowLeader(void);
CCALL qboolean NPC_MoveDirClear(int forwardmove,int rightmove,qboolean reset);
CCALL void NPC_BSSleep(void);
CCALL qboolean NPC_CheckInvestigate(int alertEventNum);
CCALL void NPC_BSInvestigate(void);
CCALL void NPC_BSWait(void);
CCALL void NPC_BSCinematic(void);
CCALL void BeamOut(gentity_t *self);
CCALL void MakeOwnerInvis(gentity_t *self);
CCALL void Disappear(gentity_t *self);
CCALL void NPC_BSAdvanceFight(void);
CCALL qboolean NPC_SomeoneLookingAtMe(gentity_t *ent);
CCALL void NPC_AimAdjust(int change);
CCALL qboolean PM_InKnockDown(playerState_t *ps);
CCALL void NPC_CheckGetNewWeapon(void);
CCALL void G_Cube(vec3_t mins,vec3_t maxs,vec3_t color,float alpha);
