#pragma once

#include "g_local.h"
#include "ghoul2/G2.h"
#include "qcommon/q_shared.h"

/*

  Items are any object that a player can touch to gain some effect.

  Pickup will return the number of seconds until they should respawn.

  all items should pop when dropped in lava or slime

  Respawnable items don't actually go away when picked up, they are
  just made invisible and untouchable.  This allows them to ride
  movers and respawn appropriately.
*/


#define	RESPAWN_ARMOR		20
#define	RESPAWN_TEAM_WEAPON	30
#define	RESPAWN_HEALTH		30
#define	RESPAWN_AMMO		40
#define	RESPAWN_HOLDABLE	60
#define	RESPAWN_MEGAHEALTH	120
#define	RESPAWN_POWERUP		120

// Item Spawn flags
#define ITMSF_SUSPEND		1
#define ITMSF_NOPLAYER		2
#define ITMSF_ALLOWNPC		4
#define ITMSF_NOTSOLID		8
#define ITMSF_VERTICAL		16
#define ITMSF_INVISIBLE		32

//======================================================================
#define MAX_MEDPACK_HEAL_AMOUNT		25
#define MAX_MEDPACK_BIG_HEAL_AMOUNT	50
#define MAX_SENTRY_DISTANCE			256

#define SHIELD_HEALTH				250
#define SHIELD_HEALTH_DEC			10		// 25 seconds
#define MAX_SHIELD_HEIGHT			254
#define MAX_SHIELD_HALFWIDTH		255
#define SHIELD_HALFTHICKNESS		4
#define SHIELD_PLACEDIST			64

#define SHIELD_SIEGE_HEALTH			2000
#define SHIELD_SIEGE_HEALTH_DEC		(SHIELD_SIEGE_HEALTH/25)	// still 25 seconds.

#define TURRET_DEATH_DELAY 2000
#define TURRET_LIFETIME 60000

#define CLOAK_TOGGLE_TIME			1000

#define TOSSED_ITEM_STAY_PERIOD			20000
#define TOSSED_ITEM_OWNER_NOTOUCH_DUR	1000

#define DISP_HEALTH_ITEM		"item_medpak_instant"
#define DISP_AMMO_ITEM			"ammo_all"

//e-web death
#define EWEB_DEATH_RADIUS		128
#define EWEB_DEATH_DMG			90

//fire a shot off
#define EWEB_MISSILE_DAMAGE			20

#define EWEB_HEALTH			200

EXTERNC qboolean itemRegistered[MAX_ITEMS];
EXTERNC gentity_t *droppedBlueFlag;
EXTERNC gentity_t *droppedRedFlag;

CCALL void G_RunItem(gentity_t *ent);
CCALL void G_BounceItem(gentity_t *ent,trace_t *trace);
CCALL void G_SpawnItem(gentity_t *ent,gitem_t *item);
CCALL int G_ItemDisabled(gitem_t *item);
CCALL void SaveRegisteredItems(void);
CCALL void ClearRegisteredItems(void);
CCALL void G_CheckTeamItems(void);
CCALL void FinishSpawningItem(gentity_t *ent);
CCALL void Use_Item(gentity_t *ent,gentity_t *other,gentity_t *activator);
CCALL gentity_t *Drop_Item(gentity_t *ent,gitem_t *item,float angle);
CCALL gentity_t *LaunchItem(gitem_t *item,vec3_t origin,vec3_t velocity);
CCALL qboolean CheckItemCanBePickedUpByNPC(gentity_t *item,gentity_t *pickerupper);
CCALL void RespawnItem(gentity_t *ent);
CCALL int Pickup_Armor(gentity_t *ent,gentity_t *other);
CCALL int Pickup_Health(gentity_t *ent,gentity_t *other);
CCALL int Pickup_Weapon(gentity_t *ent,gentity_t *other);
CCALL int Pickup_Ammo(gentity_t *ent,gentity_t *other);
CCALL void Add_Ammo(gentity_t *ent,int weapon,int count);
CCALL int Pickup_Holdable(gentity_t *ent,gentity_t *other);
CCALL int Pickup_Powerup(gentity_t *ent,gentity_t *other);
CCALL void ItemUse_UseEWeb(gentity_t *ent);
CCALL gentity_t *EWeb_Create(gentity_t *spawner);
CCALL void EWebThink(gentity_t *self);
CCALL int BG_EmplacedView(vec3_t baseAngles,vec3_t angles,float *newYaw,float constraint);
CCALL void EWebUpdateBoneAngles(gentity_t *owner,gentity_t *eweb);
CCALL void EWebPositionUser(gentity_t *owner,gentity_t *eweb);
CCALL void EWebFire(gentity_t *owner,gentity_t *eweb);
CCALL void EWeb_SetBoneAnim(gentity_t *eweb,int startFrame,int endFrame);
CCALL void EWeb_SetBoneAngles(gentity_t *ent,char *bone,vec3_t angles);
CCALL void EWebPain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void EWebDie(gentity_t *self,gentity_t *inflictor,gentity_t *attacker,int damage,int mod);
CCALL void BG_CycleInven(playerState_t *ps,int direction);
CCALL void EWebPrecache(void);
CCALL void EWebDisattach(gentity_t *owner,gentity_t *eweb);
CCALL void ItemUse_UseDisp(gentity_t *ent,int type);
CCALL void G_PrecacheDispensers(void);
CCALL void Touch_Item(gentity_t *ent,gentity_t *other,trace_t *trace);
CCALL void RegisterItem(gitem_t *item);
CCALL void G_SpecialSpawnItem(gentity_t *ent,gitem_t *item);
CCALL void SpecialItemThink(gentity_t *ent);
CCALL void ItemUse_UseCloak(gentity_t *ent);
CCALL void Jedi_Decloak(gentity_t *self);
CCALL void Jedi_Cloak(gentity_t *self);
CCALL void ItemUse_Jetpack(gentity_t *ent);
CCALL void Jetpack_On(gentity_t *ent);
CCALL void Jetpack_Off(gentity_t *ent);
CCALL void ItemUse_MedPack(gentity_t *ent);
CCALL void ItemUse_MedPack_Big(gentity_t *ent);
CCALL void ItemUse_Seeker(gentity_t *ent);
CCALL gentity_t *NPC_SpawnType(gentity_t *ent,char *npc_type,char *targetname,qboolean isVehicle);
CCALL void ItemUse_Sentry(gentity_t *ent);
CCALL void SP_PAS(gentity_t *base);
CCALL void turret_free(gentity_t *self);
CCALL void pas_think(gentity_t *ent);
CCALL void sentryExpire(gentity_t *self);
CCALL void turret_die(gentity_t *self,gentity_t *inflictor,gentity_t *attacker,int damage,int mod);
CCALL void turret_die(gentity_t *self,gentity_t *inflictor,gentity_t *attacker,int damage,int mod);
CCALL void pas_adjust_enemy(gentity_t *ent);
CCALL void pas_fire(gentity_t *ent);
CCALL void SentryTouch(gentity_t *ent,gentity_t *other,trace_t *trace);
CCALL void ItemUse_Shield(gentity_t *ent);
CCALL void ItemUse_Binoculars(gentity_t *ent);
CCALL qboolean PlaceShield(gentity_t *playerent);
CCALL void CreateShield(gentity_t *ent);
CCALL void ShieldTouch(gentity_t *self,gentity_t *other,trace_t *trace);
CCALL void ShieldGoNotSolid(gentity_t *self);
CCALL void ShieldGoSolid(gentity_t *self);
CCALL void ShieldPain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void ShieldDie(gentity_t *self,gentity_t *inflictor,gentity_t *attacker,int damage,int mod);
CCALL void ShieldThink(gentity_t *self);
CCALL void ShieldRemove(gentity_t *self);
CCALL int adjustRespawnTime(float preRespawnTime,int itemType,int itemTag);

