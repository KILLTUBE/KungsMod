void CorpsePhysics( gentity_t *self );
void NPC_RemoveBody( gentity_t *self );
int BodyRemovalPadTime( gentity_t *ent );
static void NPC_RemoveBodyEffect();
void pitch_roll_for_slope( gentity_t *forwhom, vec3_t pass_slope );
static void DeadThink();
void SetNPCGlobals( gentity_t *ent );
void SaveNPCGlobals();
void RestoreNPCGlobals();
void ClearNPCGlobals();
void NPC_ShowDebugInfo();
void NPC_ApplyScriptFlags();
void NPC_HandleAIFlags();
void NPC_AvoidWallsAndCliffs();
void NPC_CheckAttackScript();
void NPC_CheckAttackHold();
void NPC_KeepCurrentFacing();
void NPC_BehaviorSet_Charmed( int bState );
void NPC_BehaviorSet_Default( int bState );
void NPC_BehaviorSet_Interrogator( int bState );
void NPC_BehaviorSet_ImperialProbe( int bState );
void NPC_BehaviorSet_Seeker( int bState );
void NPC_BehaviorSet_Remote( int bState );
void NPC_BehaviorSet_Sentry( int bState );
void NPC_BehaviorSet_Grenadier( int bState );
void NPC_BehaviorSet_Sniper( int bState );
void NPC_BehaviorSet_Stormtrooper( int bState );
void NPC_BehaviorSet_Jedi( int bState );
void NPC_BehaviorSet_Droid( int bState );
void NPC_BehaviorSet_Mark1( int bState );
void NPC_BehaviorSet_Mark2( int bState );
void NPC_BehaviorSet_ATST( int bState );
void NPC_BehaviorSet_MineMonster( int bState );
void NPC_BehaviorSet_Howler( int bState );
void NPC_BehaviorSet_Rancor( int bState );
void NPC_RunBehavior( int team, int bState );
void NPC_ExecuteBState( gentity_t *self );
void NPC_CheckInSolid();
void G_DroidSounds( gentity_t *self );
void NPC_Think( gentity_t *self );
void NPC_InitAI();
void NPC_InitGame();
void NPC_SetAnim( gentity_t *ent, int setAnimParts, int anim, int setAnimFlags );
