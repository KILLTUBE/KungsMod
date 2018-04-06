#pragma once

#include "g_local.h"
#include "../qcommon/qcommon.h"

EXTERNC qboolean g_dontPenalizeTeam;
EXTERNC qboolean gSiegeRoundEnded;
EXTERNC qboolean gSiegeRoundBegun;
EXTERNC int g_siegeRespawnCheck;
EXTERNC forcedata_t Client_Force[MAX_CLIENTS];
EXTERNC gentity_t *gJMSaberEnt;
EXTERNC void *g2SaberInstance;

CCALL void G_ClearTeamVote(gentity_t *ent,int team);
CCALL void G_ClearVote(gentity_t *ent);
CCALL void G_LeaveVehicle(gentity_t *ent,qboolean ConCheck);
CCALL qboolean WP_HasForcePowers(const playerState_t *ps);
CCALL void G_UpdateClientAnims(gentity_t *self,float animSpeedScale);
CCALL qboolean PM_RunningAnim(int anim);
CCALL qboolean BG_SaberStanceAnim(int anim);
CCALL void G_BreakArm(gentity_t *ent,int arm);
CCALL void ClientBegin(int clientNum,qboolean allowTeamReset);
CCALL void SetTeamQuick(gentity_t *ent,int team,qboolean doBegin);
CCALL void WP_SetSaber(int entNum,saberInfo_t *sabers,int saberNum,const char *saberName);
CCALL void G_WriteClientSessionData(gclient_t *client);
CCALL void ClientDisconnect(int clientNum);
CCALL char *ClientConnect(int clientNum,qboolean firstTime,qboolean isBot);
CCALL qboolean ClientUserinfoChanged(int clientNum);
CCALL char *G_ValidateUserinfo(const char *userinfo);
CCALL void Svcmd_ToggleUserinfoValidation_f(void);
CCALL void G_ValidateSiegeClassForTeam(gentity_t *ent,int team);
CCALL qboolean G_SetSaber(gentity_t *ent,int saberNum,char *saberName,qboolean siegeOverride);
CCALL void SetupGameGhoul2Model(gentity_t *ent,char *modelname,char *skinName);
CCALL void BG_GetVehicleModelName(char *modelName,const char *vehicleName,size_t len);
CCALL qboolean BG_ValidateSkinForTeam(const char *modelName,char *skinName,int team,float *colors);
CCALL qboolean BG_IsValidCharacterModel(const char *modelName,const char *skinName);
CCALL qboolean G_SaberModelSetup(gentity_t *ent);
#if defined(_DEBUG)
CCALL void G_DebugWrite(const char *path,const char *text);
#endif
CCALL team_t PickTeam(int ignoreClientNum);
CCALL int TeamLeader(int team);
CCALL int TeamCount(int ignoreClientNum,team_t team);
CCALL void ClientSpawn(gentity_t *ent);
CCALL void ClientRespawn(gentity_t *ent);
CCALL void SiegeRespawn(gentity_t *ent);
CCALL void MaintainBodyQueue(gentity_t *ent);
CCALL void SetClientViewAngle(gentity_t *ent,vec3_t angle);
CCALL void BodySink(gentity_t *ent);
CCALL void InitBodyQue(void);
CCALL gentity_t *SelectSpectatorSpawnPoint(vec3_t origin,vec3_t angles);
CCALL gentity_t *SelectInitialSpawnPoint(vec3_t origin,vec3_t angles,team_t team,qboolean isbot);
CCALL gentity_t *SelectSpawnPoint(vec3_t avoidPoint,vec3_t origin,vec3_t angles,team_t team,qboolean isbot);
CCALL gentity_t *SelectDuelSpawnPoint(int team,vec3_t avoidPoint,vec3_t origin,vec3_t angles,qboolean isbot);
CCALL gentity_t *SelectRandomFurthestSpawnPoint(vec3_t avoidPoint,vec3_t origin,vec3_t angles,team_t team,qboolean isbot);
CCALL gentity_t *SelectRandomDeathmatchSpawnPoint(qboolean isbot);
CCALL gentity_t *SelectNearestDeathmatchSpawnPoint(vec3_t from);
CCALL qboolean SpotWouldTelefrag2(gentity_t *mover,vec3_t dest);
CCALL qboolean SpotWouldTelefrag(gentity_t *spot);
CCALL void SP_info_jedimaster_start(gentity_t *ent);
CCALL void JMSaberTouch(gentity_t *self,gentity_t *other,trace_t *trace);
CCALL void JMSaberThink(gentity_t *ent);
CCALL void ThrowSaberToAttacker(gentity_t *self,gentity_t *attacker);
CCALL void SP_info_player_intermission_blue(gentity_t *ent);
CCALL void SP_info_player_intermission_red(gentity_t *ent);
CCALL void SP_info_player_intermission(gentity_t *ent);
CCALL void SP_info_player_siegeteam2(gentity_t *ent);
CCALL void SP_info_player_siegeteam1(gentity_t *ent);
CCALL void SiegePointUse(gentity_t *self,gentity_t *other,gentity_t *activator);
CCALL void SP_info_player_start_blue(gentity_t *ent);
CCALL void SP_info_player_start_red(gentity_t *ent);
CCALL void SP_info_player_start(gentity_t *ent);
CCALL void SP_info_player_deathmatch(gentity_t *ent);
CCALL void SP_info_player_duel2(gentity_t *ent);
CCALL void SP_info_player_duel1(gentity_t *ent);
CCALL void SP_info_player_duel(gentity_t *ent);
CCALL qboolean WP_UseFirstValidSaberStyle(saberInfo_t *saber1,saberInfo_t *saber2,int saberHolstered,int *saberAnimLevel);
CCALL qboolean WP_SaberStyleValidForSaber(saberInfo_t *saber1,saberInfo_t *saber2,int saberHolstered,int saberAnimLevel);
CCALL void WP_SaberRemoveG2Model(gentity_t *saberent);
CCALL void WP_SaberAddG2Model(gentity_t *saberent,const char *saberModel,qhandle_t saberSkin);
CCALL qboolean isUI();
CCALL qboolean isCGame();
CCALL qboolean isGame();
