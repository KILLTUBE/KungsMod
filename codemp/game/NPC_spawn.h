#pragma once

#include "b_local.h"
#include "anims.h"
#include "w_saber.h"
#include "bg_saga.h"
#include "bg_vehicles.h"
#include "g_nav.h"

#define SHY_THINK_TIME			1000
#define SHY_SPAWN_DISTANCE		128
#define SHY_SPAWN_DISTANCE_SQR	( SHY_SPAWN_DISTANCE * SHY_SPAWN_DISTANCE )


#define	NSF_DROP_TO_FLOOR	16

typedef void (PAIN_FUNC) (gentity_t *self, gentity_t *attacker, int damage);
typedef void (TOUCH_FUNC) (gentity_t *self, gentity_t *other, trace_t *trace);

EXTERNC stringID_table_t TeamTable[];
EXTERNC qboolean showBBoxes;
EXTERNC gNPC_t *gNPCPtrs[MAX_GENTITIES];
EXTERNC char *TeamNames[TEAM_NUM_TEAMS];

CCALL void Cmd_NPC_f(gentity_t *ent);
CCALL void NPC_PrintScore(gentity_t *ent);
CCALL void NPC_Kill_f(void);
CCALL void NPC_Spawn_f(gentity_t *ent);
CCALL void SP_NPC_Droid_Protocol(gentity_t *self);
CCALL void SP_NPC_Droid_R5D2(gentity_t *self);
CCALL void SP_NPC_Droid_R2D2(gentity_t *self);
CCALL void SP_NPC_Droid_Mouse(gentity_t *self);
CCALL void SP_NPC_Droid_Gonk(gentity_t *self);
CCALL void SP_NPC_Droid_Sentry(gentity_t *self);
CCALL void SP_NPC_Droid_Seeker(gentity_t *self);
CCALL void SP_NPC_Droid_Remote(gentity_t *self);
CCALL void SP_NPC_Droid_ATST(gentity_t *self);
CCALL void SP_NPC_Droid_Mark2(gentity_t *self);
CCALL void SP_NPC_Droid_Mark1(gentity_t *self);
CCALL void SP_NPC_Droid_Probe(gentity_t *self);
CCALL void SP_NPC_Droid_Interrogator(gentity_t *self);
CCALL void SP_NPC_Monster_Rancor(gentity_t *self);
CCALL void SP_NPC_Monster_Wampa(gentity_t *self);
CCALL void SP_NPC_Monster_Fish(gentity_t *self);
CCALL void SP_NPC_Monster_Lizard(gentity_t *self);
CCALL void SP_NPC_Monster_Flier2(gentity_t *self);
CCALL void SP_NPC_Monster_Glider(gentity_t *self);
CCALL void SP_NPC_Monster_Claw(gentity_t *self);
CCALL void SP_NPC_MineMonster(gentity_t *self);
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
CCALL void SP_NPC_Cultist_Destroyer(gentity_t *self);
CCALL void SP_NPC_Cultist_Commando(gentity_t *self);
CCALL void SP_NPC_Cultist(gentity_t *self);
CCALL void SP_NPC_Cultist_Saber_Powers(gentity_t *self);
CCALL void SP_NPC_Cultist_Saber(gentity_t *self);
CCALL void SP_NPC_Reborn_New(gentity_t *self);
CCALL void SP_NPC_Alora(gentity_t *self);
CCALL void SP_NPC_Tavion_New(gentity_t *self);
CCALL void SP_NPC_Tavion(gentity_t *self);
CCALL void SP_NPC_MonMothma(gentity_t *self);
CCALL void SP_NPC_Luke(gentity_t *self);
CCALL void SP_NPC_Jan(gentity_t *self);
CCALL void SP_NPC_Lando(gentity_t *self);
CCALL void SP_NPC_Kyle(gentity_t *self);
CCALL void SP_NPC_Vehicle(gentity_t *self);
CCALL void NPC_VehicleSpawnUse(gentity_t *self,gentity_t *other,gentity_t *activator);
CCALL qboolean NPC_VehiclePrecache(gentity_t *spawner);
CCALL void G_VehicleSpawn(gentity_t *self);
CCALL void SP_NPC_spawner(gentity_t *self);
CCALL void NPC_PrecacheType(char *NPC_type);
CCALL void NPC_Precache(gentity_t *spawner);
CCALL void NPC_PrecacheAnimationCFG(const char *NPC_type);
CCALL void NPC_Spawn(gentity_t *ent,gentity_t *other,gentity_t *activator);
CCALL void NPC_ShySpawn(gentity_t *ent);
CCALL void NPC_Spawn_Go(gentity_t *ent);
CCALL gentity_t *NPC_Spawn_Do(gentity_t *ent);
CCALL void G_CreateFighterNPC(Vehicle_t **pVeh,const char *strType);
CCALL void G_CreateWalkerNPC(Vehicle_t **pVeh,const char *strAnimalType);
CCALL void G_CreateSpeederNPC(Vehicle_t **pVeh,const char *strType);
CCALL void G_CreateAnimalNPC(Vehicle_t **pVeh,const char *strAnimalType);
CCALL void NPC_DefaultScriptFlags(gentity_t *ent);
CCALL gNPC_t *New_NPC_t(int entNum);
CCALL void NPC_Begin(gentity_t *ent);
CCALL qboolean NPC_SpotWouldTelefrag(gentity_t *npc);
CCALL void NPC_SetFX_SpawnStates(gentity_t *ent);
CCALL void NPC_SpawnEffect(gentity_t *ent);
CCALL void NPC_SetWeapons(gentity_t *ent);
CCALL void ChangeWeapon(gentity_t *ent,int newWeapon);
CCALL int NPC_WeaponsForTeam(team_t team,int spawnflags,const char *NPC_type);
CCALL void NPC_SetMiscDefaultData(gentity_t *ent);
CCALL void G_CreateG2AttachedWeaponModel(gentity_t *ent,const char *weaponModel,int boltNum,int weaponNum);
CCALL TOUCH_FUNC *NPC_TouchFunc(gentity_t *ent);
CCALL PAIN_FUNC *NPC_PainFunc(gentity_t *ent);
CCALL int WP_SetSaberModel(gclient_t *client,class_t npcClass);
CCALL void NPC_Rancor_Pain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void NPC_Wampa_Pain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void TurretPain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void CrystalCratePain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void GasBurst(gentity_t *self,gentity_t *attacker,int damage);
CCALL void PlayerPain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void NPC_Mark2_Pain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void NPC_Sentry_Pain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void NPC_GM_Pain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void NPC_Mark1_Pain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void emplaced_gun_pain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void NPC_Remote_Pain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void NPC_Seeker_Pain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void NPC_Howler_Pain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void NPC_MineMonster_Pain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void NPC_Probe_Pain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void NPC_Droid_Pain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void NPC_Jedi_Pain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void NPC_ST_Pain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void NPC_ATST_Pain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void func_usable_pain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void station_pain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void NPC_Pain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void misc_model_breakable_pain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void funcBBrushPain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void Wampa_SetBolts(gentity_t *self);
CCALL void Rancor_SetBolts(gentity_t *self);
CCALL gentity_t *NPC_SpawnType(gentity_t *ent,char *npc_type,char *targetname,qboolean isVehicle);
CCALL gentity_t *NPC_SpawnType(gentity_t *ent,char *npc_type,char *targetname,qboolean isVehicle);
CCALL void NPC_Wampa_Precache(void);
CCALL void Boba_Precache(void);
CCALL void NPC_Protocol_Precache(void);
CCALL void NPC_GalakMech_Init(gentity_t *ent);
CCALL void NPC_GalakMech_Precache(void);
CCALL void NPC_Mark2_Precache(void);
CCALL void NPC_Mark1_Precache(void);
CCALL void NPC_Sentry_Precache(void);
CCALL void NPC_ATST_Precache(void);
CCALL void NPC_Howler_Precache(void);
CCALL void NPC_MineMonster_Precache(void);
CCALL void NPC_Interrogator_Precache(gentity_t *self);
CCALL void NPC_Probe_Precache(void);
CCALL void NPC_R5D2_Precache(void);
CCALL void NPC_R2D2_Precache(void);
CCALL void NPC_Remote_Precache(void);
CCALL void NPC_Seeker_Precache(void);
CCALL void NPC_Mouse_Precache(void);
CCALL void NPC_Gonk_Precache(void);
CCALL void NPC_ShadowTrooper_Precache(void);
CCALL void Jedi_ClearTimers(gentity_t *ent);
CCALL void ST_ClearTimers(gentity_t *ent);
CCALL void PM_SetLegsAnimTimer(gentity_t *ent,int *legsAnimTimer,int time);
CCALL void PM_SetTorsoAnimTimer(gentity_t *ent,int *torsoAnimTimer,int time);
CCALL team_t TranslateTeamName(const char *name);
CCALL void Q3_SetParm(int entID,int parmNum,const char *parmValue);
CCALL void Jedi_Cloak(gentity_t *self);
CCALL qboolean SpotWouldTelefrag2(gentity_t *mover,vec3_t dest);
CCALL qboolean ClientUserinfoChanged(int clientNum);
CCALL qboolean G_CheckInSolid(gentity_t *self,qboolean fix);
CCALL void G_DebugPrint(int level,const char *format,...);
