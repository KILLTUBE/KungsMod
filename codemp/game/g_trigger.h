#pragma once

#include "g_local.h"
#include "bg_saga.h"

EXTERNC int gTrigFallSound;
EXTERNC qboolean gSiegeRoundBegun;

CCALL void SP_trigger_asteroid_field(gentity_t *self);
CCALL void asteroid_field_think(gentity_t *self);
CCALL void Q3_Lerp2Origin(int taskID,int entID,vec3_t origin,float duration);
CCALL void SP_func_rotating(gentity_t *ent);
CCALL int asteroid_count_num_asteroids(gentity_t *self);
CCALL gentity_t *asteroid_pick_random_asteroid(gentity_t *self);
CCALL void SP_func_timer(gentity_t *self);
CCALL void func_timer_use(gentity_t *self,gentity_t *other,gentity_t *activator);
CCALL void func_timer_think(gentity_t *self);
CCALL void SP_trigger_hyperspace(gentity_t *self);
CCALL void hyperspace_touch(gentity_t *self,gentity_t *other,trace_t *trace);
CCALL void SP_trigger_shipboundary(gentity_t *self);
CCALL void shipboundary_think(gentity_t *ent);
CCALL void shipboundary_touch(gentity_t *self,gentity_t *other,trace_t *trace);
CCALL void SP_trigger_space(gentity_t *self);
CCALL void space_touch(gentity_t *self,gentity_t *other,trace_t *trace);
CCALL void SP_trigger_hurt(gentity_t *self);
CCALL void hurt_touch(gentity_t *self,gentity_t *other,trace_t *trace);
CCALL void hurt_use(gentity_t *self,gentity_t *other,gentity_t *activator);
CCALL void SP_trigger_teleport(gentity_t *self);
CCALL void trigger_teleporter_touch(gentity_t *self,gentity_t *other,trace_t *trace);
CCALL void SP_target_push(gentity_t *self);
CCALL void Use_target_push(gentity_t *self,gentity_t *other,gentity_t *activator);
CCALL void SP_trigger_push(gentity_t *self);
CCALL void AimAtTarget(gentity_t *self);
CCALL void trigger_push_touch(gentity_t *self,gentity_t *other,trace_t *trace);
CCALL void SP_trigger_always(gentity_t *ent);
CCALL void trigger_always_think(gentity_t *ent);
CCALL void SP_trigger_lightningstrike(gentity_t *ent);
CCALL void Use_Strike(gentity_t *ent,gentity_t *other,gentity_t *activator);
CCALL void Think_Strike(gentity_t *ent);
CCALL void Do_Strike(gentity_t *ent);
CCALL void SP_trigger_once(gentity_t *ent);
CCALL void SP_trigger_multiple(gentity_t *ent);
CCALL void Touch_Multi(gentity_t *self,gentity_t *other,trace_t *trace);
CCALL qboolean G_PointInBounds(vec3_t point,vec3_t mins,vec3_t maxs);
CCALL void Use_Multi(gentity_t *ent,gentity_t *other,gentity_t *activator);
CCALL void multi_trigger(gentity_t *ent,gentity_t *activator);
CCALL void SiegeItemRemoveOwner(gentity_t *ent,gentity_t *carrier);
CCALL qboolean G_NameInTriggerClassList(char *list,char *str);
CCALL void multi_trigger_run(gentity_t *ent);
CCALL void trigger_cleared_fire(gentity_t *self);
CCALL void trigger_cleared_fire(gentity_t *self);
CCALL void multi_wait(gentity_t *ent);
CCALL void InitTrigger(gentity_t *self);
