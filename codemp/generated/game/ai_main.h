void BotStraightTPOrderCheck( gentity_t *ent, int ordernum, bot_state_t *bs );
void BotSelectWeapon( int client, int weapon );
void BotReportStatus( bot_state_t *bs );
void BotOrder( gentity_t *ent, int clientnum, int ordernum );
int BotMindTricked( int botClient, int enemyClient );
QDECL void BotAI_Print( int type, char *fmt, ... );
int IsTeamplay();
int BotAI_GetClientState( int clientNum, playerState_t *state );
int BotAI_GetEntityState( int entityNum, entityState_t *state );
int BotAI_GetSnapshotEntity( int clientNum, int sequence, entityState_t *state );
void BotEntityInfo( int entnum, aas_entityinfo_t *info );
int NumBots();
float AngleDifference( float ang1, float ang2 );
float BotChangeViewAngle( float angle, float ideal_angle, float speed );
void BotChangeViewAngles( bot_state_t *bs, float thinktime );
void BotInputToUserCommand( bot_input_t *bi, usercmd_t *ucmd, int delta_angles[3], int time, int useTime );
void BotUpdateInput( bot_state_t *bs, int time, int elapsed_time );
void BotAIRegularUpdate();
void RemoveColorEscapeSequences( char *text );
int BotAI( int client, float thinktime );
void BotScheduleBotThink();
int PlayersInGame();
int BotAISetupClient( int client, struct bot_settings_s *settings, qboolean restart );
int BotAIShutdownClient( int client, qboolean restart );
void BotResetState( bot_state_t *bs );
int BotAILoadMap( int restart );
int OrgVisible( vec3_t org1, vec3_t org2, int ignore );
int WPOrgVisible( gentity_t *bot, vec3_t org1, vec3_t org2, int ignore );
int OrgVisibleBox( vec3_t org1, vec3_t mins, vec3_t maxs, vec3_t org2, int ignore );
int CheckForFunc( vec3_t org, int ignore );
qboolean BotPVSCheck( const vec3_t p1, const vec3_t p2 );
int GetNearestVisibleWP( vec3_t org, int ignore );
int PassWayCheck( bot_state_t *bs, int windex );
float TotalTrailDistance( int start, int end, bot_state_t *bs );
void CheckForShorterRoutes( bot_state_t *bs, int newwpindex );
void WPConstantRoutine( bot_state_t *bs );
qboolean BotCTFGuardDuty( bot_state_t *bs );
void WPTouchRoutine( bot_state_t *bs );
void MoveTowardIdealAngles( bot_state_t *bs );
int BotTrace_Strafe( bot_state_t *bs, vec3_t traceto );
int BotTrace_Jump( bot_state_t *bs, vec3_t traceto );
int BotTrace_Duck( bot_state_t *bs, vec3_t traceto );
int PassStandardEnemyChecks( bot_state_t *bs, gentity_t *en );
void BotDamageNotification( gclient_t *bot, gentity_t *attacker );
int BotCanHear( bot_state_t *bs, gentity_t *en, float endist );
void UpdateEventTracker();
int InFieldOfVision( vec3_t viewangles, float fov, vec3_t angles );
int PassLovedOneCheck( bot_state_t *bs, gentity_t *ent );
int ScanForEnemies( bot_state_t *bs );
int WaitingForNow( bot_state_t *bs, vec3_t goalpos );
int BotGetWeaponRange( bot_state_t *bs );
int BotIsAChickenWuss( bot_state_t *bs );
gentity_t *GetNearestBadThing( bot_state_t *bs );
int BotDefendFlag( bot_state_t *bs );
int BotGetEnemyFlag( bot_state_t *bs );
int BotGetFlagBack( bot_state_t *bs );
int BotGuardFlagCarrier( bot_state_t *bs );
int BotGetFlagHome( bot_state_t *bs );
void GetNewFlagPoint( wpobject_t *wp, gentity_t *flagEnt, int team );
int CTFTakesPriority( bot_state_t *bs );
int EntityVisibleBox( vec3_t org1, vec3_t mins, vec3_t maxs, vec3_t org2, int ignore, int ignore2 );
int Siege_TargetClosestObjective( bot_state_t *bs, int flag );
void Siege_DefendFromAttackers( bot_state_t *bs );
int Siege_CountDefenders( bot_state_t *bs );
int Siege_CountTeammates( bot_state_t *bs );
int SiegeTakesPriority( bot_state_t *bs );
int JMTakesPriority( bot_state_t *bs );
int BotHasAssociated( bot_state_t *bs, wpobject_t *wp );
int GetBestIdleGoal( bot_state_t *bs );
void GetIdealDestination( bot_state_t *bs );
void CommanderBotCTFAI( bot_state_t *bs );
void CommanderBotSiegeAI( bot_state_t *bs );
void BotDoTeamplayAI( bot_state_t *bs );
void CommanderBotTeamplayAI( bot_state_t *bs );
void CommanderBotAI( bot_state_t *bs );
void MeleeCombatHandling( bot_state_t *bs );
void SaberCombatHandling( bot_state_t *bs );
float BotWeaponCanLead( bot_state_t *bs );
void BotAimLeading( bot_state_t *bs, vec3_t headlevel, float leadAmount );
void BotAimOffsetGoalAngles( bot_state_t *bs );
int ShouldSecondaryFire( bot_state_t *bs );
int CombatBotAI( bot_state_t *bs, float thinktime );
int BotFallbackNavigation( bot_state_t *bs );
int BotTryAnotherWeapon( bot_state_t *bs );
qboolean BotWeaponSelectable( bot_state_t *bs, int weapon );
int BotSelectIdealWeapon( bot_state_t *bs );
int BotSelectChoiceWeapon( bot_state_t *bs, int weapon, int doselection );
int BotSelectMelee( bot_state_t *bs );
int GetLoveLevel( bot_state_t *bs, bot_state_t *love );
void BotLovedOneDied( bot_state_t *bs, bot_state_t *loved, int lovelevel );
void BotDeathNotify( bot_state_t *bs );
void StrafeTracing( bot_state_t *bs );
int PrimFiring( bot_state_t *bs );
int KeepPrimFromFiring( bot_state_t *bs );
int AltFiring( bot_state_t *bs );
int KeepAltFromFiring( bot_state_t *bs );
gentity_t *CheckForFriendInLOF( bot_state_t *bs );
void BotScanForLeader( bot_state_t *bs );
void BotReplyGreetings( bot_state_t *bs );
void CTFFlagMovement( bot_state_t *bs );
void BotCheckDetPacks( bot_state_t *bs );
int BotUseInventoryItem( bot_state_t *bs );
int BotSurfaceNear( bot_state_t *bs );
int BotWeaponBlockable( int weapon );
void Bot_SetForcedMovement( int bot, int forward, int right, int up );
void StandardBotAI( bot_state_t *bs, float thinktime );
int BotAIStartFrame( int time );
int BotAISetup( int restart );
int BotAIShutdown( int restart );