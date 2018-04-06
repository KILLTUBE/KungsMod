#pragma once

#include "../qcommon/q_shared.h"
#include "../game/g_local.h"

#define MOVER_START_ON		1
#define MOVER_FORCE_ACTIVATE	2
#define MOVER_CRUSHER		4
#define MOVER_TOGGLE		8
#define MOVER_LOCKED		16
#define MOVER_GOODIE		32
#define MOVER_PLAYER_USE	64
#define MOVER_INACTIVE		128

EXTERNC int BMS_END;
EXTERNC int BMS_MID;
EXTERNC int BMS_START;

typedef struct pushed_s {
	gentity_t	*ent;
	vec3_t	origin;
	vec3_t	angles;
	float	deltayaw;
} pushed_t;

EXTERNC pushed_t pushed[MAX_GENTITIES], *pushed_p;

CCALL void SP_func_wall(gentity_t *ent);
CCALL void use_wall(gentity_t *ent,gentity_t *other,gentity_t *activator);
CCALL void SP_func_usable(gentity_t *self);
CCALL void func_usable_die(gentity_t *self,gentity_t *inflictor,gentity_t *attacker,int damage,int mod);
CCALL void func_usable_pain(gentity_t *self,gentity_t *attacker,int damage);
CCALL qboolean G_EntIsRemovableUsable(int entNum);
CCALL void func_usable_think(gentity_t *self);
CCALL void func_wait_return_solid(gentity_t *self);
CCALL void func_usable_use(gentity_t *self,gentity_t *other,gentity_t *activator);
CCALL void func_usable_use(gentity_t *self,gentity_t *other,gentity_t *activator);
CCALL void SP_func_glass(gentity_t *ent);
CCALL void GlassUse(gentity_t *self,gentity_t *other,gentity_t *activator);
CCALL void GlassPain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void GlassDie_Old(gentity_t *self,gentity_t *inflictor,gentity_t *attacker,int damage,int mod);
CCALL void GlassDie(gentity_t *self,gentity_t *inflictor,gentity_t *attacker,int damage,int mod);
CCALL qboolean G_EntIsBreakable(int entityNum);
CCALL void funcBBrushTouch(gentity_t *ent,gentity_t *other,trace_t *trace);
CCALL void funcBBrushPain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void funcBBrushUse(gentity_t *self,gentity_t *other,gentity_t *activator);
CCALL void funcBBrushDie(gentity_t *self,gentity_t *inflictor,gentity_t *attacker,int damage,int mod);
CCALL void funcBBrushDieGo(gentity_t *self);
CCALL void G_Chunks(int owner,vec3_t origin,const vec3_t normal,const vec3_t mins,const vec3_t maxs,float speed,int numChunks,material_t chunkType,int customChunk,float baseScale);
CCALL void G_MiscModelExplosion(vec3_t mins,vec3_t maxs,int size,material_t chunkType);
CCALL void SP_func_pendulum(gentity_t *ent);
CCALL void SP_func_bobbing(gentity_t *ent);
CCALL void SP_func_rotating(gentity_t *ent);
CCALL void SP_func_breakable(gentity_t *self);
CCALL void SP_func_breakable(gentity_t *self);
CCALL void func_rotating_use(gentity_t *self,gentity_t *other,gentity_t *activator);
CCALL void SP_func_static(gentity_t *ent);
CCALL void func_static_use(gentity_t *self,gentity_t *other,gentity_t *activator);
CCALL void func_static_use(gentity_t *self,gentity_t *other,gentity_t *activator);
CCALL void SP_func_train(gentity_t *self);
CCALL void SP_path_corner(gentity_t *self);
CCALL void Think_SetupTrainTargets(gentity_t *ent);
CCALL void Reached_Train(gentity_t *ent);
CCALL void Think_BeginMoving(gentity_t *ent);
CCALL void SP_func_button(gentity_t *ent);
CCALL void Touch_Button(gentity_t *ent,gentity_t *other,trace_t *trace);
CCALL void SP_func_plat(gentity_t *ent);
CCALL void SpawnPlatTrigger(gentity_t *ent);
CCALL void Touch_PlatCenterTrigger(gentity_t *ent,gentity_t *other,trace_t *trace);
CCALL void Touch_Plat(gentity_t *ent,gentity_t *other,trace_t *trace);
CCALL void SP_func_door(gentity_t *ent);
CCALL qboolean G_EntIsUnlockedDoor(int entityNum);
CCALL gentity_t *G_FindDoorTrigger(gentity_t *ent);
CCALL qboolean G_EntIsDoor(int entityNum);
CCALL void Think_MatchTeam(gentity_t *ent);
CCALL void Think_SpawnNewDoorTrigger(gentity_t *ent);
CCALL void Touch_DoorTrigger(gentity_t *ent,gentity_t *other,trace_t *trace);
CCALL void Blocked_Door(gentity_t *ent,gentity_t *other);
CCALL void InitMover(gentity_t *ent);
CCALL void InitMoverTrData(gentity_t *ent);
CCALL void Use_BinaryMover(gentity_t *ent,gentity_t *other,gentity_t *activator);
CCALL void LockDoors(gentity_t *const ent);
CCALL void UnLockDoors(gentity_t *const ent);
CCALL void Use_BinaryMover_Go(gentity_t *ent);
CCALL void Reached_BinaryMover(gentity_t *ent);
CCALL void ReturnToPos1(gentity_t *ent);
CCALL void SetMoverState(gentity_t *ent,moverState_t moverState,int time);
CCALL void CalcTeamDoorCenter(gentity_t *ent,vec3_t center);
CCALL void G_RunMover(gentity_t *ent);
CCALL void G_MoverTeam(gentity_t *ent);
CCALL qboolean G_MoverPush(gentity_t *pusher,vec3_t move,vec3_t amove,gentity_t **obstacle);
CCALL void NPC_RemoveBody(gentity_t *self);
CCALL void G_ExplodeMissile(gentity_t *ent);
CCALL qboolean G_TryPushingEntity(gentity_t *check,gentity_t *pusher,vec3_t move,vec3_t amove);
CCALL void G_RotatePoint(vec3_t point,matrix3_t matrix);
CCALL void G_TransposeMatrix(matrix3_t matrix,matrix3_t transpose);
CCALL void G_CreateRotationMatrix(vec3_t angles,matrix3_t matrix);
CCALL gentity_t *G_TestEntityPosition(gentity_t *ent);
CCALL gentity_t *G_TestEntityPosition(gentity_t *ent);
CCALL void G_PlayDoorSound(gentity_t *ent,int type);
CCALL void G_PlayDoorLoopSound(gentity_t *ent);
CCALL void MatchTeam(gentity_t *teamLeader,int moverState,int time);
CCALL void MatchTeam(gentity_t *teamLeader,int moverState,int time);
