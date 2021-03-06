void G_FindTeams();
void G_CacheGametype();
void G_CacheMapname( const cvar_t *mapname );
void G_InitGame( int levelTime, int randomSeed, int restart );
void G_ShutdownGame( int restart );
void AddTournamentPlayer();
void AddTournamentQueue( gclient_t *client );
void RemoveTournamentLoser();
void G_PowerDuelCount( int *loners, int *doubles, qboolean countSpec );
void AddPowerDuelPlayers();
void RemovePowerDuelLosers();
void RemoveDuelDrawLoser();
void RemoveTournamentWinner();
void AdjustTournamentScores();
QDECL int SortRanks( const void *a, const void *b );
qboolean G_CanResetDuelists();
void G_ResetDuelists();
void CalculateRanks();
void SendScoreboardMessageToAllClients();
void MoveClientToIntermission( gentity_t *ent );
void FindIntermissionPoint();
void BeginIntermission();
qboolean DuelLimitHit();
void DuelResetWinsLosses();
void ExitLevel();
QDECL void G_LogPrintf( const char *fmt, ... );
QDECL void G_SecurityLogPrintf( const char *fmt, ... );
void LogExit( const char *string );
void CheckIntermissionExit();
qboolean ScoreIsTied();
void CheckExitRules();
void G_RemoveDuelist( int team );
void CheckTournament();
void G_KickAllBots();
void CheckVote();
void PrintTeam( int team, char *message );
void SetLeader( int team, int client );
void CheckTeamLeader( int team );
void CheckTeamVote( int team );
void CheckCvars();
void G_RunThink( gentity_t *ent );
void NAV_CheckCalcPaths();
void G_RunFrame( int levelTime );
CCALL const char *G_GetStringEdString( char *refSection, char *refName );
CCALL void G_SpawnRMGEntity();
CCALL void _G_ROFF_NotetrackCallback( int entID, const char *notetrack );
CCALL int G_ICARUS_PlaySound();
CCALL qboolean G_ICARUS_Set();
CCALL void G_ICARUS_Lerp2Pos();
CCALL void G_ICARUS_Lerp2Origin();
CCALL void G_ICARUS_Lerp2Angles();
CCALL int G_ICARUS_GetTag();
CCALL void G_ICARUS_Lerp2Start();
CCALL void G_ICARUS_Lerp2End();
CCALL void G_ICARUS_Use();
CCALL void G_ICARUS_Kill();
CCALL void G_ICARUS_Remove();
CCALL void G_ICARUS_Play();
CCALL int G_ICARUS_GetFloat();
CCALL int G_ICARUS_GetVector();
CCALL int G_ICARUS_GetString();
CCALL void G_ICARUS_SoundIndex();
CCALL int G_ICARUS_GetSetIDForString();
CCALL qboolean G_NAV_ClearPathToPoint( int entID, vec3_t pmins, vec3_t pmaxs, vec3_t point, int clipmask, int okToHitEnt );
CCALL qboolean G_NPC_ClearLOS2( int entID, const vec3_t end );
CCALL qboolean G_NAV_CheckNodeFailedForEnt( int entID, int nodeNum );
