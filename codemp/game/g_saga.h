#pragma once

#include "g_local.h"
#include "bg_saga.h"

EXTERNC int g_preroundState;
EXTERNC int gSiegeBeginTime;
EXTERNC int gSiegeRoundWinningTeam;
EXTERNC qboolean gSiegeRoundEnded;
EXTERNC qboolean gSiegeRoundBegun;
EXTERNC int imperial_attackers;
EXTERNC int rebel_attackers;
EXTERNC int gRebelCountdown;
EXTERNC int gImperialCountdown;
EXTERNC int rebel_time_limit;
EXTERNC int imperial_time_limit;
EXTERNC int rebel_goals_completed;
EXTERNC int rebel_goals_required;
EXTERNC int imperial_goals_completed;
EXTERNC int imperial_goals_required;
EXTERNC siegePers_t g_siegePersistant;

CCALL void G_SiegeClientExData(gentity_t *msgTarg);
CCALL void SP_misc_siege_item(gentity_t *ent);
CCALL void SiegeItemUse(gentity_t *ent,gentity_t *other,gentity_t *activator);
CCALL void SiegeItemDie(gentity_t *self,gentity_t *inflictor,gentity_t *attacker,int damage,int meansOfDeath);
CCALL void SiegeItemPain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void SiegeItemTouch(gentity_t *self,gentity_t *other,trace_t *trace);
CCALL void SiegeItemThink(gentity_t *ent);
CCALL void SiegeItemRemoveOwner(gentity_t *ent,gentity_t *carrier);
CCALL void SP_target_siege_end(gentity_t *ent);
CCALL void siegeEndUse(gentity_t *ent,gentity_t *other,gentity_t *activator);
CCALL void SP_info_siege_decomplete(gentity_t *ent);
CCALL void decompTriggerUse(gentity_t *ent,gentity_t *other,gentity_t *activator);
CCALL void SP_info_siege_radaricon(gentity_t *ent);
CCALL void SiegeIconUse(gentity_t *ent,gentity_t *other,gentity_t *activator);
CCALL void SP_info_siege_objective(gentity_t *ent);
CCALL void siegeTriggerUse(gentity_t *ent,gentity_t *other,gentity_t *activator);
CCALL void SiegeObjectiveCompleted(int team,int objective,int final,int client);
CCALL void SiegeCheckTimers(void);
CCALL void SiegeBeginRound(int entNum);
CCALL void SiegeRespawn(gentity_t *ent);
CCALL void G_ValidateSiegeClassForTeam(gentity_t *ent,int team);
CCALL void SiegeRoundComplete(int winningteam,int winningclient);
CCALL void SiegeTeamSwitch(int winTeam,int winTime);
CCALL void SiegeDoTeamAssign(void);
CCALL void SiegeClearSwitchData(void);
CCALL void AddSiegeWinningTeamPoints(int team,int winner);
CCALL void BroadcastObjectiveCompletion(int team,int objective,int final,int client);
CCALL void SiegeBroadcast_ROUNDOVER(int winningteam,int winningclient);
CCALL void SiegeBroadcast_OBJECTIVECOMPLETE(int team,int client,int objective);
CCALL void UseSiegeTarget(gentity_t *other,gentity_t *en,char *target);
CCALL qboolean G_SiegeGetCompletionStatus(int team,int objective);
CCALL void G_SiegeSetObjectiveComplete(int team,int objective,qboolean failIt);
CCALL void InitSiegeMode(void);
CCALL void SiegeSetCompleteData(int team);
CCALL void G_SiegeRegisterWeaponsAndHoldables(int team);
CCALL void SetTeamQuick(gentity_t *ent,int team,qboolean doBegin);
CCALL void SetTeamQuick(gentity_t *ent,int team,qboolean doBegin);
CCALL void LogExit(const char *string);

