#pragma once

#include "b_local.h"
#include "icarus/Q3_Interface.h"

CCALL gentity_t *UpdateGoal(void);
CCALL qboolean ReachedGoal(gentity_t *goal);
CCALL void NPC_ReachedGoal(void);
CCALL qboolean G_BoundsOverlap(const vec3_t mins1,const vec3_t maxs1,const vec3_t mins2,const vec3_t maxs2);
CCALL void NPC_ClearGoal(void);
CCALL void NPC_SetGoal(gentity_t *goal,float rating);
CCALL void SetGoal(gentity_t *goal,float rating);
CCALL qboolean FlyingCreature(gentity_t *ent);
