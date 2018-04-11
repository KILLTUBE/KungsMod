#pragma once

#include "g_local.h"
#include "qcommon/q_shared.h"
#include "botlib/botlib.h"		//bot lib interface
#include "botlib/be_aas.h"
#include "botlib/be_ea.h"
#include "botlib/be_ai_char.h"
#include "botlib/be_ai_chat.h"
#include "botlib/be_ai_gen.h"
#include "botlib/be_ai_goal.h"
#include "botlib/be_ai_move.h"
#include "botlib/be_ai_weap.h"
#include "ai_main_2.h"
#include "w_saber.h"
#include "chars.h"
#include "inv.h"

/*
#define BOT_CTF_DEBUG	1
*/

#define BOT_THINK_TIME	0

EXTERNC char *teamplayStateDescriptions[];
EXTERNC char *siegeStateDescriptions[];
EXTERNC char *ctfStateDescriptions[];
EXTERNC char *ctfStateNames[];
EXTERNC gentity_t *droppedBlueFlag;
EXTERNC gentity_t *eFlagBlue;
EXTERNC gentity_t *droppedRedFlag;
EXTERNC gentity_t *eFlagRed;
EXTERNC wpobject_t *oFlagBlue;
EXTERNC wpobject_t *flagBlue;
EXTERNC wpobject_t *oFlagRed;
EXTERNC wpobject_t *flagRed;
EXTERNC boteventtracker_t gBotEventTracker[MAX_CLIENTS];
EXTERNC int imperial_attackers;
EXTERNC int rebel_attackers;
EXTERNC float regularupdate_time;
EXTERNC float floattime;
EXTERNC int numbots;
EXTERNC bot_state_t *botstates[MAX_CLIENTS];
EXTERNC int gUpdateVars;


CCALL int BotAIShutdown(int restart);
CCALL int BotAISetup(int restart);
CCALL int BotAIStartFrame(int time);
CCALL void Bot_SetForcedMovement(int bot,int forward,int right,int up);
CCALL void Cmd_ToggleSaber_f(gentity_t *ent);
CCALL void Cmd_EngageDuel_f(gentity_t *ent);
CCALL int BotWeaponBlockable(int weapon);
CCALL int BotSurfaceNear(bot_state_t *bs);
CCALL int BotUseInventoryItem(bot_state_t *bs);
CCALL void BotCheckDetPacks(bot_state_t *bs);
CCALL void CTFFlagMovement(bot_state_t *bs);
CCALL void BotReplyGreetings(bot_state_t *bs);
CCALL void BotScanForLeader(bot_state_t *bs);
CCALL gentity_t *CheckForFriendInLOF(bot_state_t *bs);
CCALL int KeepAltFromFiring(bot_state_t *bs);
CCALL int AltFiring(bot_state_t *bs);
CCALL int KeepPrimFromFiring(bot_state_t *bs);
CCALL int PrimFiring(bot_state_t *bs);
CCALL void StrafeTracing(bot_state_t *bs);
CCALL void BotDeathNotify(bot_state_t *bs);
CCALL void BotLovedOneDied(bot_state_t *bs,bot_state_t *loved,int lovelevel);
CCALL int GetLoveLevel(bot_state_t *bs,bot_state_t *love);
CCALL int BotSelectMelee(bot_state_t *bs);
CCALL int BotSelectChoiceWeapon(bot_state_t *bs,int weapon,int doselection);
CCALL int BotSelectIdealWeapon(bot_state_t *bs);
CCALL qboolean BotWeaponSelectable(bot_state_t *bs,int weapon);
CCALL int BotTryAnotherWeapon(bot_state_t *bs);
CCALL int BotFallbackNavigation(bot_state_t *bs);
CCALL int CombatBotAI(bot_state_t *bs,float thinktime);
CCALL int ShouldSecondaryFire(bot_state_t *bs);
CCALL void BotAimOffsetGoalAngles(bot_state_t *bs);
CCALL void BotAimLeading(bot_state_t *bs,vec3_t headlevel,float leadAmount);
CCALL float BotWeaponCanLead(bot_state_t *bs);
CCALL void SaberCombatHandling(bot_state_t *bs);
CCALL void MeleeCombatHandling(bot_state_t *bs);
CCALL void CommanderBotAI(bot_state_t *bs);
CCALL void CommanderBotTeamplayAI(bot_state_t *bs);
CCALL void BotDoTeamplayAI(bot_state_t *bs);
CCALL void CommanderBotSiegeAI(bot_state_t *bs);
CCALL void CommanderBotCTFAI(bot_state_t *bs);
CCALL void GetIdealDestination(bot_state_t *bs);
CCALL int BotHasAssociated(bot_state_t *bs,wpobject_t *wp);
CCALL int JMTakesPriority(bot_state_t *bs);
CCALL int SiegeTakesPriority(bot_state_t *bs);
CCALL int Siege_CountTeammates(bot_state_t *bs);
CCALL int Siege_CountDefenders(bot_state_t *bs);
CCALL void Siege_DefendFromAttackers(bot_state_t *bs);
CCALL int Siege_TargetClosestObjective(bot_state_t *bs,int flag);
CCALL int EntityVisibleBox(vec3_t org1,vec3_t mins,vec3_t maxs,vec3_t org2,int ignore,int ignore2);
CCALL int GetBestIdleGoal(bot_state_t *bs);
CCALL int CTFTakesPriority(bot_state_t *bs);
CCALL void GetNewFlagPoint(wpobject_t *wp,gentity_t *flagEnt,int team);
CCALL int BotGetFlagHome(bot_state_t *bs);
CCALL int BotGuardFlagCarrier(bot_state_t *bs);
CCALL int BotGetFlagBack(bot_state_t *bs);
CCALL int BotGetEnemyFlag(bot_state_t *bs);
CCALL int BotDefendFlag(bot_state_t *bs);
CCALL gentity_t *GetNearestBadThing(bot_state_t *bs);
CCALL int WaitingForNow(bot_state_t *bs,vec3_t goalpos);
CCALL int ScanForEnemies(bot_state_t *bs);
CCALL qboolean G_ThereIsAMaster(void);
CCALL int InFieldOfVision(vec3_t viewangles,float fov,vec3_t angles);
CCALL void UpdateEventTracker(void);
CCALL int BotCanHear(bot_state_t *bs,gentity_t *en,float endist);
CCALL void BotDamageNotification(gclient_t *bot,gentity_t *attacker);
CCALL int PassStandardEnemyChecks(bot_state_t *bs,gentity_t *en);
CCALL int BotTrace_Duck(bot_state_t *bs,vec3_t traceto);
CCALL int BotTrace_Jump(bot_state_t *bs,vec3_t traceto);
#if defined(BOT_STRAFE_AVOIDANCE)
CCALL int BotTrace_Strafe(bot_state_t *bs,vec3_t traceto);
#endif
CCALL void MoveTowardIdealAngles(bot_state_t *bs);
CCALL int BotIsAChickenWuss(bot_state_t *bs);
CCALL void WPTouchRoutine(bot_state_t *bs);
CCALL qboolean BotCTFGuardDuty(bot_state_t *bs);
CCALL void WPConstantRoutine(bot_state_t *bs);
CCALL void CheckForShorterRoutes(bot_state_t *bs,int newwpindex);
CCALL float TotalTrailDistance(int start,int end,bot_state_t *bs);
CCALL int PassWayCheck(bot_state_t *bs,int windex);
CCALL int GetNearestVisibleWP(vec3_t org,int ignore);
CCALL qboolean BotPVSCheck(const vec3_t p1,const vec3_t p2);
CCALL int CheckForFunc(vec3_t org,int ignore);
CCALL int OrgVisibleBox(vec3_t org1,vec3_t mins,vec3_t maxs,vec3_t org2,int ignore);
CCALL int WPOrgVisible(gentity_t *bot,vec3_t org1,vec3_t org2,int ignore);
CCALL int OrgVisible(vec3_t org1,vec3_t org2,int ignore);
CCALL int BotAILoadMap(int restart);
CCALL void BotResetState(bot_state_t *bs);
CCALL int BotAIShutdownClient(int client,qboolean restart);
CCALL int BotAISetupClient(int client,struct bot_settings_s *settings,qboolean restart);
CCALL int PlayersInGame(void);
CCALL void BotScheduleBotThink(void);
CCALL void StandardBotAI(bot_state_t *bs,float thinktime);
CCALL int BotAI(int client,float thinktime);
CCALL void RemoveColorEscapeSequences(char *text);
CCALL void BotAIRegularUpdate(void);
CCALL void BotUpdateInput(bot_state_t *bs,int time,int elapsed_time);
CCALL void BotInputToUserCommand(bot_input_t *bi,usercmd_t *ucmd,int delta_angles[3],int time,int useTime);
CCALL void BotChangeViewAngles(bot_state_t *bs,float thinktime);
CCALL float BotChangeViewAngle(float angle,float ideal_angle,float speed);
CCALL float AngleDifference(float ang1,float ang2);
CCALL int NumBots(void);
CCALL void BotEntityInfo(int entnum,aas_entityinfo_t *info);
CCALL int BotAI_GetSnapshotEntity(int clientNum,int sequence,entityState_t *state);
CCALL int BotAI_GetEntityState(int entityNum,entityState_t *state);
CCALL int BotAI_GetClientState(int clientNum,playerState_t *state);
CCALL int IsTeamplay(void);
CCALL qboolean WP_ForcePowerUsable(gentity_t *self,forcePowers_t forcePower);
CCALL void QDECL BotAI_Print(int type,char *fmt,...);
CCALL void ExitLevel(void);
CCALL int PassLovedOneCheck(bot_state_t *bs,gentity_t *ent);
CCALL int PassLovedOneCheck(bot_state_t *bs,gentity_t *ent);
CCALL int BotGetWeaponRange(bot_state_t *bs);
CCALL int BotGetWeaponRange(bot_state_t *bs);
CCALL int BotMindTricked(int botClient,int enemyClient);
CCALL void BotOrder(gentity_t *ent,int clientnum,int ordernum);
CCALL void BotReportStatus(bot_state_t *bs);
CCALL void BotSelectWeapon(int client,int weapon);
CCALL void BotStraightTPOrderCheck(gentity_t *ent,int ordernum,bot_state_t *bs);
