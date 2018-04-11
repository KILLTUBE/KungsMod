#pragma once

#include "g_local.h"

#define ACT_ACTIVE		qtrue
#define ACT_INACTIVE	qfalse

EXTERNC int numNewICARUSEnts;

CCALL void SP_target_play_music(gentity_t *self);
CCALL void target_play_music_use(gentity_t *self,gentity_t *other,gentity_t *activator);
CCALL void SP_target_level_change(gentity_t *self);
CCALL void target_level_change_use(gentity_t *self,gentity_t *other,gentity_t *activator);
CCALL void SP_target_deactivate(gentity_t *self);
CCALL void SP_target_activate(gentity_t *self);
CCALL void target_deactivate_use(gentity_t *self,gentity_t *other,gentity_t *activator);
CCALL void target_activate_use(gentity_t *self,gentity_t *other,gentity_t *activator);
CCALL void G_SetActiveState(char *targetstring,qboolean actState);
CCALL void SP_target_scriptrunner(gentity_t *self);
CCALL void target_scriptrunner_use(gentity_t *self,gentity_t *other,gentity_t *activator);
CCALL void scriptrunner_run(gentity_t *self);
CCALL void SP_target_random(gentity_t *self);
CCALL void target_random_use(gentity_t *self,gentity_t *other,gentity_t *activator);
CCALL void SP_target_counter(gentity_t *self);
CCALL void target_counter_use(gentity_t *self,gentity_t *other,gentity_t *activator);
CCALL void G_DebugPrint(int level,const char *format,...);
CCALL void SP_target_location(gentity_t *self);
CCALL void SP_target_position(gentity_t *self);
CCALL void SP_target_kill(gentity_t *self);
CCALL void target_kill_use(gentity_t *self,gentity_t *other,gentity_t *activator);
CCALL void SP_target_relay(gentity_t *self);
CCALL void target_relay_use(gentity_t *self,gentity_t *other,gentity_t *activator);
CCALL void SP_target_teleporter(gentity_t *self);
CCALL void target_teleporter_use(gentity_t *self,gentity_t *other,gentity_t *activator);
CCALL void SP_target_laser(gentity_t *self);
CCALL void target_laser_start(gentity_t *self);
CCALL void target_laser_use(gentity_t *self,gentity_t *other,gentity_t *activator);
CCALL void target_laser_off(gentity_t *self);
CCALL void target_laser_on(gentity_t *self);
CCALL void target_laser_think(gentity_t *self);
CCALL void SP_target_speaker(gentity_t *ent);
CCALL void Use_Target_Speaker(gentity_t *ent,gentity_t *other,gentity_t *activator);
CCALL void SP_target_print(gentity_t *ent);
CCALL void Use_Target_Print(gentity_t *ent,gentity_t *other,gentity_t *activator);
CCALL void SP_target_score(gentity_t *ent);
CCALL void Use_Target_Score(gentity_t *ent,gentity_t *other,gentity_t *activator);
CCALL void SP_target_delay(gentity_t *ent);
CCALL void Use_Target_Delay(gentity_t *ent,gentity_t *other,gentity_t *activator);
CCALL void Think_Target_Delay(gentity_t *ent);
CCALL void SP_target_remove_powerups(gentity_t *ent);
CCALL void Use_target_remove_powerups(gentity_t *ent,gentity_t *other,gentity_t *activator);
CCALL void SP_target_give(gentity_t *ent);
CCALL void Use_Target_Give(gentity_t *ent,gentity_t *other,gentity_t *activator);
