
#pragma once

#include "g_local.h"
#include "ghoul2/G2.h"
#include "ai_main.h" //for the g2animents

#define HOLOCRON_RESPAWN_TIME 30000
#define MAX_AMMO_GIVE 2
#define STATION_RECHARGE_TIME 100
#define FX_RUNNER_RESERVED 0x800000
#define FX_ENT_RADIUS 32

//rww - ref tag stuff ported from SP (and C-ified)
#define	TAG_GENERIC_NAME	"__WORLD__"	//If a designer chooses this name, cut a finger off as an example to the others

//MAX_TAG_OWNERS is 16 for now in order to not use too much VM memory.
//Each tag owner has preallocated space for tags up to MAX_TAGS.
//As is this means 16*256 sizeof(reference_tag_t)'s in addition to name+inuse*16.
#define MAX_TAGS 256
#define MAX_TAG_OWNERS 16

//Maybe I should use my SV_TrueMalloc/SV_TrueFree stuff with this.
//But I am not yet confident that it can be used without exploding at some point.

typedef struct tagOwner_s
{
	char			name[MAX_REFNAME];
	reference_tag_t	tags[MAX_TAGS];
	qboolean		inuse;
} tagOwner_t;


/*QUAKED misc_weapon_shooter (1 0 0) (-8 -8 -8) (8 8 8) ALTFIRE TOGGLE
ALTFIRE - fire the alt-fire of the chosen weapon
TOGGLE - keep firing until used again (fires at intervals of "wait")

"wait" - debounce time between refires (defaults to 500)

"target" - what to aim at (will update aim every frame if it's a moving target)

"weapon" - specify the weapon to use (default is WP_BLASTER)
	WP_BRYAR_PISTOL
	WP_BLASTER
	WP_DISRUPTOR
	WP_BOWCASTER
	WP_REPEATER
	WP_DEMP2
	WP_FLECHETTE
	WP_ROCKET_LAUNCHER
	WP_THERMAL
	WP_TRIP_MINE
	WP_DET_PACK
	WP_STUN_BATON
	WP_EMPLACED_GUN
	WP_BOT_LASER
	WP_TURRET
	WP_ATST_MAIN
	WP_ATST_SIDE
	WP_TIE_FIGHTER
	WP_RAPID_FIRE_CONC
	WP_BLASTER_PISTOL
*/
//kind of hacky, but we have to do this with no dynamic allocation
#define MAX_SHOOTERS		16
typedef struct shooterClient_s
{
	gclient_t		cl;
	qboolean		inuse;
} shooterClient_t;

EXTERNC stringID_table_t WPTable[];
EXTERNC tagOwner_t refTagOwnerMap[MAX_TAG_OWNERS];
EXTERNC int gEscapeTime;
EXTERNC qboolean gEscaping;
EXTERNC int BMS_END;
EXTERNC int BMS_MID;
EXTERNC int BMS_START;


CCALL void SP_misc_cubemap(gentity_t *ent);
CCALL void SP_misc_weather_zone(gentity_t *ent);
CCALL void SP_misc_weapon_shooter(gentity_t *self);
CCALL void misc_weapon_shooter_aim(gentity_t *self);
CCALL void misc_weapon_shooter_use(gentity_t *self,gentity_t *other,gentity_t *activator);
CCALL void misc_weapon_shooter_fire(gentity_t *self);
CCALL void G_FreeClientForShooter(gclient_t *cl);
CCALL gclient_t *G_ClientForShooter(void);
CCALL void SP_reference_tag(gentity_t *ent);
CCALL void ref_link(gentity_t *ent);
CCALL int TAG_GetFlags(const char *owner,const char *name);
CCALL int TAG_GetRadius(const char *owner,const char *name);
CCALL int TAG_GetAngles(const char *owner,const char *name,vec3_t angles);
CCALL int TAG_GetOrigin2(const char *owner,const char *name,vec3_t origin);
CCALL int TAG_GetOrigin(const char *owner,const char *name,vec3_t origin);
CCALL reference_tag_t *TAG_Add(const char *name,const char *owner,vec3_t origin,vec3_t angles,int radius,int flags);
CCALL reference_tag_t *TAG_Find(const char *owner,const char *name);
CCALL tagOwner_t *TAG_FindOwner(const char *owner);
CCALL void TAG_Init(void);
CCALL reference_tag_t *FirstFreeRefTag(tagOwner_t *tagOwner);
CCALL tagOwner_t *FirstFreeTagOwner(void);
CCALL void SP_misc_faller(gentity_t *ent);
CCALL void misc_faller_think(gentity_t *ent);
CCALL void misc_faller_create(gentity_t *ent,gentity_t *other,gentity_t *activator);
CCALL void faller_think(gentity_t *ent);
CCALL void faller_touch(gentity_t *self,gentity_t *other,trace_t *trace);
CCALL void SP_misc_maglock(gentity_t *self);
CCALL gentity_t *G_FindDoorTrigger(gentity_t *ent);
CCALL void maglock_link(gentity_t *self);
CCALL void maglock_link(gentity_t *self);
CCALL void maglock_die(gentity_t *self,gentity_t *inflictor,gentity_t *attacker,int damage,int mod);
CCALL void SP_target_escapetrig(gentity_t *ent);
CCALL void Use_Target_Escapetrig(gentity_t *ent,gentity_t *other,gentity_t *activator);
CCALL void LogExit(const char *string);
CCALL void SP_target_screenshake(gentity_t *ent);
CCALL void Use_Target_Screenshake(gentity_t *ent,gentity_t *other,gentity_t *activator);
CCALL void SP_CreateRain(gentity_t *ent);
CCALL void SP_CreateSnow(gentity_t *ent);
CCALL void SP_CreateSpaceDust(gentity_t *ent);
CCALL void SP_CreateWind(gentity_t *ent);
CCALL void SP_fx_runner(gentity_t *ent);
CCALL void fx_runner_link(gentity_t *ent);
CCALL void fx_runner_use(gentity_t *self,gentity_t *other,gentity_t *activator);
CCALL void fx_runner_think(gentity_t *ent);
CCALL void SP_misc_model_health_power_converter(gentity_t *ent);
CCALL void health_power_converter_use(gentity_t *self,gentity_t *other,gentity_t *activator);
CCALL void EnergyHealthStationSettings(gentity_t *ent);
CCALL void SP_misc_model_ammo_power_converter(gentity_t *ent);
CCALL void ammo_power_converter_use(gentity_t *self,gentity_t *other,gentity_t *activator);
CCALL void EnergyAmmoStationSettings(gentity_t *ent);
CCALL void SP_misc_model_shield_power_converter(gentity_t *ent);
CCALL void SP_misc_shield_floor_unit(gentity_t *ent);
CCALL void SP_misc_ammo_floor_unit(gentity_t *ent);
CCALL void ammo_generic_power_converter_use(gentity_t *self,gentity_t *other,gentity_t *activator);
CCALL void shield_power_converter_use(gentity_t *self,gentity_t *other,gentity_t *activator);
CCALL void EnergyShieldStationSettings(gentity_t *ent);
CCALL void check_recharge(gentity_t *ent);
CCALL void SP_shooter_blaster(gentity_t *ent);
CCALL void InitShooter(gentity_t *ent,int weapon);
CCALL void Use_Shooter(gentity_t *ent,gentity_t *other,gentity_t *activator);
CCALL void SP_misc_holocron(gentity_t *ent);
CCALL void HolocronTouch(gentity_t *self,gentity_t *other,trace_t *trace);
CCALL void HolocronPopOut(gentity_t *self);
CCALL void HolocronRespawn(gentity_t *self);
CCALL void SP_misc_skyportal(gentity_t *ent);
CCALL void SP_misc_skyportal_orient(gentity_t *ent);
CCALL void G_PortalifyEntities(gentity_t *ent);
CCALL void SP_terrain(gentity_t *ent);
CCALL void AddSpawnField(char *field,char *value);
CCALL void SP_misc_bsp(gentity_t *ent);
CCALL void SP_misc_portal_camera(gentity_t *ent);
CCALL void SP_misc_portal_surface(gentity_t *ent);
CCALL void locateCamera(gentity_t *ent);
CCALL void SP_misc_G2model(gentity_t *ent);
CCALL void SP_misc_model_breakable(gentity_t *ent);
CCALL void misc_model_breakable_init(gentity_t *ent);
CCALL void misc_model_breakable_init(gentity_t *ent);
CCALL void misc_model_breakable_gravity_init(gentity_t *ent,qboolean dropToFloor);
CCALL void misc_model_breakable_gravity_init(gentity_t *ent,qboolean dropToFloor);
CCALL void SP_misc_model_static(gentity_t *ent);
CCALL void SP_misc_model(gentity_t *ent);
CCALL void SP_misc_teleporter_dest(gentity_t *ent);
CCALL void TeleportPlayer(gentity_t *player,vec3_t origin,vec3_t angles);
CCALL void SP_light(gentity_t *self);
CCALL void misc_dlight_use(gentity_t *ent,gentity_t *other,gentity_t *activator);
CCALL void SP_info_notnull(gentity_t *self);
CCALL void SP_info_null(gentity_t *self);
CCALL void SP_info_camp(gentity_t *self);
CCALL void HolocronThink(gentity_t *ent);
CCALL void HolocronThink(gentity_t *ent);
