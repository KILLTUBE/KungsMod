#pragma once

#include "qcommon/q_shared.h"
#include "bg_public.h"
#include "b_local.h"
#include "icarus/Q3_Interface.h"
#include "icarus/Q3_Registers.h"
#include "g_nav.h"

//This is a hack I guess. It's because we can't include the file this enum is in
//unless we're using cpp. But we need it for the interpreter stuff.
//In any case, DO NOT modify this enum.

// Hack++
// This code is compiled as C++ on Xbox. We could try and rig something above
// so that we only get the C version of the includes (no full Icarus) in that
// scenario, but I think we'll just try to leave this out instead.
//#if defined(__linux__) && defined(__GCC__) || !defined(__linux__)

// seems to be not even used anymore, it will just redefine old values, had to rename all
// from TK_EOF to TK_ICARUS_EOF
// type redefinition seems to work in C, but C++ wont play along with that...
typedef enum
{
	TK_ICARUS_EOF = -1,
	TK_ICARUS_UNDEFINED,
	TK_ICARUS_COMMENT,
	TK_ICARUS_EOL,
	TK_ICARUS_CHAR,
	TK_ICARUS_STRING,
	TK_ICARUS_INT,
	TK_ICARUS_INTEGER = TK_INT,
	TK_ICARUS_FLOAT,
	TK_ICARUS_IDENTIFIER,
	TK_ICARUS_USERDEF,
} icarustoken_t;
//#endif

EXTERNC vec4_t textcolor_scroll;
EXTERNC vec4_t textcolor_center;
EXTERNC vec4_t textcolor_caption;
EXTERNC qboolean player_locked;
EXTERNC char cinematicSkipScript[1024];
EXTERNC cvar_t *g_gravity;
EXTERNC stringID_table_t setTable[];
EXTERNC stringID_table_t animTable[MAX_ANIMATIONS+1];
EXTERNC stringID_table_t BSTable[];
EXTERNC stringID_table_t WPTable[];

CCALL qboolean Q3_Set(int taskID,int entID,const char *type_name,const char *data);
CCALL void LockDoors(gentity_t *const ent);
CCALL void UnLockDoors(gentity_t *const ent);
CCALL void SolidifyOwner(gentity_t *self);
CCALL void Q3_SetParm(int entID,int parmNum,const char *parmValue);
CCALL void ChangeWeapon(gentity_t *ent,int newWeapon);
CCALL void Q3_SetViewEntity(int entID,const char *name);
CCALL void Q3_SetICARUSFreeze(int entID,const char *name,qboolean freeze);
CCALL void Q3_SetLoopSound(int entID,const char *name);
CCALL void Q3_Lerp2Origin(int taskID,int entID,vec3_t origin,float duration);
CCALL void MoveOwner(gentity_t *self);
CCALL qboolean SpotWouldTelefrag2(gentity_t *mover,vec3_t dest);
CCALL int Q3_GetString(int entID,int type,const char *name,char **value);
CCALL int Q3_GetVector(int entID,int type,const char *name,vec3_t value);
CCALL int Q3_GetFloat(int entID,int type,const char *name,float *value);
CCALL void Q3_Remove(int entID,const char *name);
CCALL void Q3_RemoveEnt(gentity_t *victim);
CCALL void Q3_Kill(int entID,const char *name);
CCALL void Q3_Use(int entID,const char *target);
CCALL int Q3_GetTag(int entID,const char *name,int lookup,vec3_t info);
CCALL void Q3_Lerp2Angles(int taskID,int entID,vec3_t angles,float duration);
CCALL void Q3_Lerp2Pos(int taskID,int entID,vec3_t origin,vec3_t angles,float duration);
CCALL void InitMoverTrData(gentity_t *ent);
CCALL void Q3_Lerp2End(int entID,int taskID,float duration);
CCALL void Q3_Lerp2Start(int entID,int taskID,float duration);
CCALL void moveAndRotateCallback(gentity_t *ent);
CCALL void moverCallback(gentity_t *ent);
CCALL void Blocked_Mover(gentity_t *ent,gentity_t *other);
CCALL void Blocked_Mover(gentity_t *ent,gentity_t *other);
CCALL void MatchTeam(gentity_t *teamLeader,int moverState,int time);
CCALL void anglerCallback(gentity_t *ent);
CCALL void Q3_Play(int taskID,int entID,const char *type,const char *name);
CCALL int Q3_PlaySound(int taskID,int entID,const char *name,const char *channel);
CCALL void G_DebugPrint(int printLevel,const char *format,...);
CCALL qboolean BG_SabersOff(playerState_t *ps);
CCALL void ICARUS_SetVar(int taskID,int entID,const char *type_name,const char *data);
CCALL int ICARUS_GetFloatVariable(const char *name,float *value);
CCALL int ICARUS_VariableDeclared(const char *name);
