#pragma once

#include "g_local.h"

CCALL void G_StartObjectMoving(gentity_t *object,vec3_t dir,float speed,trType_t trType);
CCALL void G_RunObject(gentity_t *ent);
CCALL void DoImpact(gentity_t *self,gentity_t *other,qboolean damageSelf);
CCALL void G_BounceObject(gentity_t *ent,trace_t *trace);
CCALL void pitch_roll_for_slope(gentity_t *forwhom,vec3_t pass_slope);
CCALL void pitch_roll_for_slope(gentity_t *forwhom,vec3_t pass_slope);
CCALL void G_StopObjectMoving(gentity_t *object);
CCALL void G_StopObjectMoving(gentity_t *object);
CCALL void G_MoverTouchPushTriggers(gentity_t *ent,vec3_t oldOrg);
