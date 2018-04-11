#pragma once

#include "g_local.h"
#include "bg_saga.h"
#include "ui/menudef.h"			// for the voice chats

#define CMD_NOINTERMISSION		(1<<0)
#define CMD_CHEAT				(1<<1)
#define CMD_ALIVE				(1<<2)

typedef struct command_s {
	const char	*name;
	void		(*func)(gentity_t *ent);
	int			flags;
} command_t;

EXTERNC command_t commands[];
EXTERNC qboolean g_preventTeamBegin;
EXTERNC qboolean g_dontPenalizeTeam;

CCALL void ClientCommand(int clientNum);
CCALL int cmdcmp(const void *a,const void *b);
CCALL void Cmd_AddBot_f(gentity_t *ent);
CCALL void Cmd_BotMoveUp_f(gentity_t *ent);
CCALL void Cmd_BotMoveLeft_f(gentity_t *ent);
CCALL void Cmd_BotMoveRight_f(gentity_t *ent);
CCALL void Cmd_BotMoveBack_f(gentity_t *ent);
CCALL void Cmd_BotMoveForward_f(gentity_t *ent);
CCALL void Cmd_TheDestroyer_f(gentity_t *ent);
CCALL void Cmd_TargetUse_f(gentity_t *ent);
CCALL qboolean TryGrapple(gentity_t *ent);
#if !defined(FINAL_BUILD)
CCALL void G_SetVehDamageFlags(gentity_t *veh,int shipSurf,int damageLevel);
CCALL void DismembermentByNum(gentity_t *self,int num);
#endif
CCALL void Bot_SetForcedMovement(int bot,int forward,int right,int up);
CCALL void DismembermentTest(gentity_t *self);
CCALL void StandardSetBodyAnim(gentity_t *self,int anim,int flags);
#if !defined(FINAL_BUILD)
CCALL void Cmd_DebugSetBodyAnim_f(gentity_t *self);
CCALL void Cmd_DebugSetSaberMove_f(gentity_t *self);
EXTERNC stringID_table_t animTable[MAX_ANIMATIONS+1];
#endif
CCALL void Cmd_EngageDuel_f(gentity_t *ent);
CCALL qboolean G_OtherPlayersDueling(void);
CCALL void Cmd_SaberAttackCycle_f(gentity_t *ent);
CCALL qboolean WP_SaberCanTurnOffSomeBlades(saberInfo_t *saber);
CCALL void Cmd_ToggleSaber_f(gentity_t *ent);
CCALL void saberKnockDown(gentity_t *saberent,gentity_t *saberOwner,gentity_t *other);
CCALL int G_ItemUsable(playerState_t *ps,int forcedUse);
CCALL void Cmd_SetViewpos_f(gentity_t *ent);
CCALL void Cmd_TeamVote_f(gentity_t *ent);
CCALL void Cmd_CallTeamVote_f(gentity_t *ent);
CCALL qboolean G_TeamVoteLeader(gentity_t *ent,int cs_offset,team_t team,int numArgs,const char *arg1,const char *arg2);
CCALL void Cmd_Vote_f(gentity_t *ent);
CCALL void Cmd_CallVote_f(gentity_t *ent);
CCALL void Svcmd_ToggleAllowVote_f(void);
CCALL qboolean G_VoteWarmup(gentity_t *ent,int numArgs,const char *arg1,const char *arg2);
CCALL qboolean G_VoteTimelimit(gentity_t *ent,int numArgs,const char *arg1,const char *arg2);
CCALL qboolean G_VoteNextmap(gentity_t *ent,int numArgs,const char *arg1,const char *arg2);
CCALL qboolean G_VoteMapRestart(gentity_t *ent,int numArgs,const char *arg1,const char *arg2);
CCALL qboolean G_VoteMap(gentity_t *ent,int numArgs,const char *arg1,const char *arg2);
CCALL void Cmd_MapList_f(gentity_t *ent);
CCALL const char *G_GetArenaInfoByMap(const char *map);
CCALL qboolean G_VoteKick(gentity_t *ent,int numArgs,const char *arg1,const char *arg2);
CCALL qboolean G_VoteGametype(gentity_t *ent,int numArgs,const char *arg1,const char *arg2);
CCALL qboolean G_VoteFraglimit(gentity_t *ent,int numArgs,const char *arg1,const char *arg2);
CCALL qboolean G_VoteClientkick(gentity_t *ent,int numArgs,const char *arg1,const char *arg2);
CCALL qboolean G_VoteCapturelimit(gentity_t *ent,int numArgs,const char *arg1,const char *arg2);
CCALL void SiegeClearSwitchData(void);
CCALL void Cmd_Where_f(gentity_t *ent);
CCALL void Cmd_GameCommand_f(gentity_t *ent);
CCALL void G_Say(gentity_t *ent,gentity_t *target,int mode,const char *chatText);
CCALL void Cmd_FollowPrev_f(gentity_t *ent);
CCALL void Cmd_FollowNext_f(gentity_t *ent);
CCALL void Cmd_FollowCycle_f(gentity_t *ent,int dir);
CCALL void Cmd_Follow_f(gentity_t *ent);
CCALL qboolean G_SetSaber(gentity_t *ent,int saberNum,char *saberName,qboolean siegeOverride);
CCALL qboolean WP_UseFirstValidSaberStyle(saberInfo_t *saber1,saberInfo_t *saber2,int saberHolstered,int *saberAnimLevel);
CCALL qboolean WP_SaberStyleValidForSaber(saberInfo_t *saber1,saberInfo_t *saber2,int saberHolstered,int saberAnimLevel);
CCALL void Cmd_ForceChanged_f(gentity_t *ent);
CCALL void Cmd_SiegeClass_f(gentity_t *ent);
CCALL int G_TeamForSiegeClass(const char *clName);
CCALL void Cmd_DuelTeam_f(gentity_t *ent);
CCALL void Cmd_Team_f(gentity_t *ent);
CCALL void StopFollowing(gentity_t *ent);
CCALL void G_LeaveVehicle(gentity_t *ent,qboolean ConCheck);
CCALL void G_LeaveVehicle(gentity_t *ent,qboolean ConCheck);
CCALL void SetTeam(gentity_t *ent,char *s);
CCALL qboolean G_PowerDuelCheckFail(gentity_t *ent);
CCALL void BroadcastTeamChange(gclient_t *client,int oldTeam);
CCALL void Cmd_KillOther_f(gentity_t *ent);
CCALL void Cmd_Kill_f(gentity_t *ent);
CCALL void G_Kill(gentity_t *ent);
CCALL void Cmd_LevelShot_f(gentity_t *ent);
CCALL void Cmd_Noclip_f(gentity_t *ent);
CCALL void Cmd_Notarget_f(gentity_t *ent);
CCALL void Cmd_God_f(gentity_t *ent);
CCALL void Cmd_GiveOther_f(gentity_t *ent);
CCALL void Cmd_Give_f(gentity_t *ent);
CCALL void G_Give(gentity_t *ent,const char *name,const char *args,int argc);
CCALL int ClientNumberFromString(gentity_t *to,const char *s,qboolean allowconnecting);
CCALL qboolean StringIsInteger(const char *s);
CCALL char *ConcatArgs(int start);
CCALL void Cmd_Score_f(gentity_t *ent);
CCALL void DeathmatchScoreboardMessage(gentity_t *ent);
CCALL void SetTeamQuick(gentity_t *ent,int team,qboolean doBegin);
CCALL void Cmd_NPC_f(gentity_t *ent);
CCALL void WP_SetSaber(int entNum,saberInfo_t *sabers,int saberNum,const char *saberName);
CCALL int AcceptBotCommand(char *cmd,gentity_t *pl);
