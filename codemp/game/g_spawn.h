#pragma once

#include "g_local.h"

#define NOVALUE "novalue"

typedef struct spawn_s {
	const char	*name;
	void		(*spawn)(gentity_t *ent);
} spawn_t;

//
// fields are needed for spawning from the entity string
//
typedef enum {
	F_INT,
	F_FLOAT,
	F_STRING,			// string on disk, pointer in memory
	F_VECTOR,
	F_ANGLEHACK,
	F_PARM1,			// Special case for parms
	F_PARM2,			// Special case for parms
	F_PARM3,			// Special case for parms
	F_PARM4,			// Special case for parms
	F_PARM5,			// Special case for parms
	F_PARM6,			// Special case for parms
	F_PARM7,			// Special case for parms
	F_PARM8,			// Special case for parms
	F_PARM9,			// Special case for parms
	F_PARM10,			// Special case for parms
	F_PARM11,			// Special case for parms
	F_PARM12,			// Special case for parms
	F_PARM13,			// Special case for parms
	F_PARM14,			// Special case for parms
	F_PARM15,			// Special case for parms
	F_PARM16			// Special case for parms
} fieldtype_t;

typedef struct spawnfield_s {
	const char	*name;
	size_t		ofs;
	fieldtype_t	type;
} spawnfield_t;

EXTERNC void *precachedKyle;
EXTERNC spawn_t spawns[];
EXTERNC spawnfield_t fields[];
EXTERNC float g_cullDistance;

CCALL void G_SpawnEntitiesFromString(qboolean inSubBSP);
CCALL void G_LinkLocations(void);
CCALL void G_PrecacheSoundsets(void);
CCALL qboolean SP_bsp_worldspawn(void);
CCALL void SP_worldspawn(void);
CCALL void EWebPrecache(void);
CCALL void scriptrunner_run(gentity_t *self);
CCALL qboolean G_ParseSpawnVars(qboolean inSubBSP);
CCALL void AddSpawnField(char *field,char *value);
CCALL char *G_AddSpawnVarToken(const char *string);
CCALL void G_SpawnGEntityFromSpawnVars(qboolean inSubBSP);
CCALL void G_ParseField(const char *key,const char *value,gentity_t *ent);
CCALL void Q3_SetParm(int entID,int parmNum,const char *parmValue);
CCALL char *G_NewString_Safe(const char *string);
CCALL char *G_NewString(const char *string);
CCALL qboolean G_CallSpawn(gentity_t *ent);
CCALL void SP_emplaced_gun(gentity_t *ent);
CCALL void SP_gametype_item(gentity_t *ent);
CCALL void SP_item_botroam(gentity_t *ent);
CCALL void SP_misc_turretG2(gentity_t *base);
CCALL void SP_misc_turret(gentity_t *ent);
CCALL void SP_team_CTF_bluespawn(gentity_t *ent);
CCALL void SP_team_CTF_redspawn(gentity_t *ent);
CCALL void SP_team_CTF_blueplayer(gentity_t *ent);
CCALL void SP_team_CTF_redplayer(gentity_t *ent);
CCALL void SP_shooter_blaster(gentity_t *ent);
CCALL void SP_point_combat(gentity_t *self);
CCALL void SP_CreateRain(gentity_t *ent);
CCALL void SP_CreateSnow(gentity_t *ent);
CCALL void SP_CreateSpaceDust(gentity_t *ent);
CCALL void SP_CreateWind(gentity_t *ent);
CCALL void SP_waypoint_navgoal_1(gentity_t *ent);
CCALL void SP_waypoint_navgoal_2(gentity_t *ent);
CCALL void SP_waypoint_navgoal_4(gentity_t *ent);
CCALL void SP_waypoint_navgoal_8(gentity_t *ent);
CCALL void SP_waypoint_navgoal(gentity_t *ent);
CCALL void SP_waypoint_small(gentity_t *ent);
CCALL void SP_waypoint(gentity_t *ent);
CCALL void SP_NPC_Cultist_Commando(gentity_t *self);
CCALL void SP_NPC_Cultist_Destroyer(gentity_t *self);
CCALL void SP_NPC_Cultist_Saber_Powers(gentity_t *self);
CCALL void SP_NPC_Cultist_Saber(gentity_t *self);
CCALL void SP_NPC_Cultist(gentity_t *self);
CCALL void SP_NPC_Reborn_New(gentity_t *self);
CCALL void SP_NPC_Droid_Protocol(gentity_t *self);
CCALL void SP_NPC_Droid_R5D2(gentity_t *self);
CCALL void SP_NPC_Droid_R2D2(gentity_t *self);
CCALL void SP_NPC_Droid_Mouse(gentity_t *self);
CCALL void SP_NPC_Droid_Gonk(gentity_t *self);
CCALL void SP_NPC_Droid_Sentry(gentity_t *self);
CCALL void SP_NPC_Droid_Remote(gentity_t *self);
CCALL void SP_NPC_Droid_Seeker(gentity_t *self);
CCALL void SP_NPC_Droid_ATST(gentity_t *self);
CCALL void SP_NPC_Droid_Mark2(gentity_t *self);
CCALL void SP_NPC_Droid_Mark1(gentity_t *self);
CCALL void SP_NPC_Droid_Probe(gentity_t *self);
CCALL void SP_NPC_Droid_Interrogator(gentity_t *self);
CCALL void SP_NPC_MineMonster(gentity_t *self);
CCALL void SP_NPC_Monster_Rancor(gentity_t *self);
CCALL void SP_NPC_Monster_Wampa(gentity_t *self);
CCALL void SP_NPC_Monster_Fish(gentity_t *self);
CCALL void SP_NPC_Monster_Lizard(gentity_t *self);
CCALL void SP_NPC_Monster_Flier2(gentity_t *self);
CCALL void SP_NPC_Monster_Glider(gentity_t *self);
CCALL void SP_NPC_Monster_Claw(gentity_t *self);
CCALL void SP_NPC_Monster_Howler(gentity_t *self);
CCALL void SP_NPC_Monster_Swamp(gentity_t *self);
CCALL void SP_NPC_Monster_Murjj(gentity_t *self);
CCALL void SP_NPC_ShadowTrooper(gentity_t *self);
CCALL void SP_NPC_Reborn(gentity_t *self);
CCALL void SP_NPC_BespinCop(gentity_t *self);
CCALL void SP_NPC_ImpWorker(gentity_t *self);
CCALL void SP_NPC_Imperial(gentity_t *self);
CCALL void SP_NPC_SwampTrooper(gentity_t *self);
CCALL void SP_NPC_Noghri(gentity_t *self);
CCALL void SP_NPC_Tusken(gentity_t *self);
CCALL void SP_NPC_Trandoshan(gentity_t *self);
CCALL void SP_NPC_Weequay(gentity_t *self);
CCALL void SP_NPC_Rodian(gentity_t *self);
CCALL void SP_NPC_Gran(gentity_t *self);
CCALL void SP_NPC_Jawa(gentity_t *self);
CCALL void SP_NPC_Ugnaught(gentity_t *self);
CCALL void SP_NPC_Tie_Pilot(gentity_t *self);
CCALL void SP_NPC_Snowtrooper(gentity_t *self);
CCALL void SP_NPC_StormtrooperOfficer(gentity_t *self);
CCALL void SP_NPC_Stormtrooper(gentity_t *self);
CCALL void SP_NPC_Human_Merc(gentity_t *self);
CCALL void SP_NPC_Rebel(gentity_t *self);
CCALL void SP_NPC_Prisoner(gentity_t *self);
CCALL void SP_NPC_Jedi(gentity_t *self);
CCALL void SP_NPC_MorganKatarn(gentity_t *self);
CCALL void SP_NPC_Bartender(gentity_t *self);
CCALL void SP_NPC_Desann(gentity_t *self);
CCALL void SP_NPC_Galak(gentity_t *self);
CCALL void SP_NPC_Reelo(gentity_t *self);
CCALL void SP_NPC_Alora(gentity_t *self);
CCALL void SP_NPC_Tavion_New(gentity_t *self);
CCALL void SP_NPC_Tavion(gentity_t *self);
CCALL void SP_NPC_MonMothma(gentity_t *self);
CCALL void SP_NPC_Luke(gentity_t *self);
CCALL void SP_NPC_Jan(gentity_t *self);
CCALL void SP_NPC_Lando(gentity_t *self);
CCALL void SP_NPC_Kyle(gentity_t *self);
CCALL void SP_NPC_Vehicle(gentity_t *self);
CCALL void SP_NPC_spawner(gentity_t *self);
CCALL void SP_misc_cubemap(gentity_t *ent);
CCALL void SP_misc_weapon_shooter(gentity_t *self);
CCALL void SP_reference_tag(gentity_t *ent);
CCALL void SP_misc_holocron(gentity_t *ent);
CCALL void SP_misc_faller(gentity_t *ent);
CCALL void SP_misc_maglock(gentity_t *self);
CCALL void SP_target_escapetrig(gentity_t *ent);
CCALL void SP_target_screenshake(gentity_t *ent);
CCALL void SP_fx_runner(gentity_t *ent);
CCALL void SP_misc_model_health_power_converter(gentity_t *ent);
CCALL void SP_misc_model_ammo_power_converter(gentity_t *ent);
CCALL void SP_misc_model_shield_power_converter(gentity_t *ent);
CCALL void SP_misc_shield_floor_unit(gentity_t *ent);
CCALL void SP_misc_ammo_floor_unit(gentity_t *ent);
CCALL void SP_misc_skyportal(gentity_t *ent);
CCALL void SP_misc_skyportal_orient(gentity_t *ent);
CCALL void SP_terrain(gentity_t *ent);
CCALL void SP_misc_bsp(gentity_t *ent);
CCALL void SP_misc_weather_zone(gentity_t *ent);
CCALL void SP_misc_portal_surface(gentity_t *ent);
CCALL void SP_misc_portal_camera(gentity_t *ent);
CCALL void SP_misc_G2model(gentity_t *ent);
CCALL void SP_misc_model_breakable(gentity_t *ent);
CCALL void SP_misc_model_static(gentity_t *ent);
CCALL void SP_misc_model(gentity_t *ent);
CCALL void SP_misc_teleporter_dest(gentity_t *self);
CCALL void SP_path_corner(gentity_t *self);
CCALL void SP_info_camp(gentity_t *self);
CCALL void SP_info_notnull(gentity_t *self);
CCALL void SP_info_null(gentity_t *self);
CCALL void SP_light(gentity_t *self);
CCALL void SP_target_push(gentity_t *ent);
CCALL void SP_target_play_music(gentity_t *self);
CCALL void SP_target_level_change(gentity_t *self);
CCALL void SP_target_deactivate(gentity_t *self);
CCALL void SP_target_activate(gentity_t *self);
CCALL void SP_target_interest(gentity_t *self);
CCALL void SP_target_scriptrunner(gentity_t *self);
CCALL void SP_target_random(gentity_t *self);
CCALL void SP_target_counter(gentity_t *self);
CCALL void SP_target_location(gentity_t *ent);
CCALL void SP_target_position(gentity_t *ent);
CCALL void SP_target_kill(gentity_t *ent);
CCALL void SP_target_relay(gentity_t *ent);
CCALL void SP_target_teleporter(gentity_t *ent);
CCALL void SP_target_score(gentity_t *ent);
CCALL void SP_target_character(gentity_t *ent);
CCALL void SP_target_laser(gentity_t *self);
CCALL void SP_target_print(gentity_t *ent);
CCALL void SP_target_speaker(gentity_t *ent);
CCALL void SP_target_delay(gentity_t *ent);
CCALL void SP_target_give(gentity_t *ent);
CCALL void SP_target_remove_powerups(gentity_t *ent);
CCALL void SP_trigger_asteroid_field(gentity_t *self);
CCALL void SP_trigger_hyperspace(gentity_t *self);
CCALL void SP_trigger_shipboundary(gentity_t *self);
CCALL void SP_trigger_space(gentity_t *self);
CCALL void SP_trigger_hurt(gentity_t *ent);
CCALL void SP_trigger_teleport(gentity_t *ent);
CCALL void SP_trigger_push(gentity_t *ent);
CCALL void SP_trigger_once(gentity_t *ent);
CCALL void SP_trigger_multiple(gentity_t *ent);
CCALL void SP_trigger_always(gentity_t *ent);
CCALL void SP_trigger_lightningstrike(gentity_t *ent);
CCALL void SP_func_wall(gentity_t *ent);
CCALL void SP_func_usable(gentity_t *ent);
CCALL void SP_func_glass(gentity_t *ent);
CCALL void SP_func_breakable(gentity_t *ent);
CCALL void SP_func_timer(gentity_t *self);
CCALL void SP_func_train(gentity_t *ent);
CCALL void SP_func_door(gentity_t *ent);
CCALL void SP_func_button(gentity_t *ent);
CCALL void SP_func_pendulum(gentity_t *ent);
CCALL void SP_func_bobbing(gentity_t *ent);
CCALL void SP_func_rotating(gentity_t *ent);
CCALL void SP_func_static(gentity_t *ent);
CCALL void SP_func_plat(gentity_t *ent);
CCALL void SP_misc_siege_item(gentity_t *ent);
CCALL void SP_target_siege_end(gentity_t *ent);
CCALL void SP_info_siege_decomplete(gentity_t *ent);
CCALL void SP_info_siege_radaricon(gentity_t *ent);
CCALL void SP_info_siege_objective(gentity_t *ent);
CCALL void SP_info_podium(gentity_t *ent);
CCALL void SP_info_thirdplace(gentity_t *ent);
CCALL void SP_info_secondplace(gentity_t *ent);
CCALL void SP_info_firstplace(gentity_t *ent);
CCALL void SP_info_player_start_blue(gentity_t *ent);
CCALL void SP_info_player_start_red(gentity_t *ent);
CCALL void SP_info_jedimaster_start(gentity_t *ent);
CCALL void SP_info_player_intermission_blue(gentity_t *ent);
CCALL void SP_info_player_intermission_red(gentity_t *ent);
CCALL void SP_info_player_intermission(gentity_t *ent);
CCALL void SP_info_player_siegeteam2(gentity_t *ent);
CCALL void SP_info_player_siegeteam1(gentity_t *ent);
CCALL void SP_info_player_deathmatch(gentity_t *ent);
CCALL void SP_info_player_duel2(gentity_t *ent);
CCALL void SP_info_player_duel1(gentity_t *ent);
CCALL void SP_info_player_duel(gentity_t *ent);
CCALL void SP_info_player_start(gentity_t *ent);
CCALL qboolean G_SpawnBoolean(const char *key,const char *defaultString,qboolean *out);
CCALL qboolean G_SpawnVector(const char *key,const char *defaultString,float *out);
CCALL qboolean G_SpawnInt(const char *key,const char *defaultString,int *out);
CCALL qboolean G_SpawnFloat(const char *key,const char *defaultString,float *out);
CCALL qboolean G_SpawnString(const char *key,const char *defaultString,char **out);
