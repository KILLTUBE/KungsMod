#pragma once

#include "g_local.h"

typedef enum {
	AWARD_EFFICIENCY,		// Accuracy
	AWARD_SHARPSHOOTER,		// Most compression rifle frags
	AWARD_UNTOUCHABLE,		// Perfect (no deaths)
	AWARD_LOGISTICS,		// Most pickups
	AWARD_TACTICIAN,		// Kills with all weapons
	AWARD_DEMOLITIONIST,	// Most explosive damage kills
	AWARD_STREAK,			// Ace/Expert/Master/Champion
	AWARD_TEAM,				// MVP/Defender/Warrior/Carrier/Interceptor/Bravery
	AWARD_SECTION31,		// All-around god
	AWARD_MAX
} awardType_t;

typedef enum
{
	TEAM_NONE = 0,			// ha ha! you suck!
	TEAM_MVP,				// most overall points
	TEAM_DEFENDER,			// killed the most baddies near your flag
	TEAM_WARRIOR,			// most frags
	TEAM_CARRIER,			// infected the most people with plague
	TEAM_INTERCEPTOR,		// returned your own flag the most
	TEAM_BRAVERY,			// Red Shirt Award (tm). you died more than anybody.
	TEAM_MAX
} teamAward_e;

CCALL void QDECL G_ClearClientLog(int client);
CCALL qboolean CalculateSection31Award(gentity_t *ent);
CCALL int CalculateTeamAward(gentity_t *ent);
CCALL qboolean CalculateTeamRedShirt(gentity_t *ent);
CCALL qboolean CalculateTeamInterceptor(gentity_t *ent);
CCALL qboolean CalculateTeamCarrier(gentity_t *ent);
CCALL qboolean CalculateTeamWarrior(gentity_t *ent);
CCALL qboolean CalculateTeamDefender(gentity_t *ent);
CCALL qboolean CalculateTeamMVP(gentity_t *ent);
CCALL int CalculateStreak(gentity_t *ent);
CCALL qboolean CalculateDemolitionist(gentity_t *ent,int *kills);
CCALL qboolean CalculateTactician(gentity_t *ent,int *kills);
CCALL qboolean CalculateLogistics(gentity_t *ent,int *stuffUsed);
CCALL qboolean CalculateUntouchable(gentity_t *ent);
CCALL qboolean CalculateSharpshooter(gentity_t *ent,int *frags);
CCALL qboolean CalculateEfficiency(gentity_t *ent,int *efficiency);
CCALL void G_LogWeaponOutput(void);
CCALL void G_LogWeaponItem(int client,int itemid);
CCALL void G_LogWeaponPowerup(int client,int powerupid);
CCALL void G_LogWeaponDeath(int client,int weaponid);
CCALL void G_LogWeaponFrag(int attacker,int deadguy);
CCALL void G_LogWeaponKill(int client,int mod);
CCALL void G_LogWeaponDamage(int client,int mod,int amount);
CCALL void G_LogWeaponFire(int client,int weaponid);
CCALL void G_LogWeaponPickup(int client,int weaponid);
CCALL void G_LogWeaponInit(void);
#if defined(LOGGING_WEAPONS)
EXTERNC char *modNames[];
EXTERNC char *weaponNameFromIndex[WP_NUM_WEAPONS];
EXTERNC int weaponFromMOD[MOD_MAX];
EXTERNC int G_WeaponLogItems[MAX_CLIENTS][PW_NUM_POWERUPS];
EXTERNC int G_WeaponLogPowerups[MAX_CLIENTS][HI_NUM_HOLDABLE];
EXTERNC qboolean G_WeaponLogClientTouch[MAX_CLIENTS];
EXTERNC int G_WeaponLogLastTime[MAX_CLIENTS];
EXTERNC int G_WeaponLogTime[MAX_CLIENTS][WP_NUM_WEAPONS];
EXTERNC int G_WeaponLogFrags[MAX_CLIENTS][MAX_CLIENTS];
EXTERNC int G_WeaponLogDeaths[MAX_CLIENTS][WP_NUM_WEAPONS];
EXTERNC int G_WeaponLogKills[MAX_CLIENTS][MOD_MAX];
EXTERNC int G_WeaponLogDamage[MAX_CLIENTS][MOD_MAX];
EXTERNC int G_WeaponLogFired[MAX_CLIENTS][WP_NUM_WEAPONS];
EXTERNC int G_WeaponLogPickups[MAX_CLIENTS][WP_NUM_WEAPONS];
#endif
