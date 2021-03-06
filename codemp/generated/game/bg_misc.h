qboolean BG_FileExists( const char *fileName );
void BG_GiveMeVectorFromMatrix( mdxaBone_t *boltMatrix, int flags, vec3_t vec );
qboolean BG_LegalizedForcePowers( char *powerOut, size_t powerOutSize, int maxRank, qboolean freeSaber, int teamForce, int gametype, int fpDisabled );
float vectoyaw( const vec3_t vec );
qboolean BG_HasYsalamiri( int gametype, playerState_t *ps );
qboolean BG_CanUseFPNow( int gametype, playerState_t *ps, int time, forcePowers_t power );
gitem_t *BG_FindItemForPowerup( powerup_t pw );
gitem_t *BG_FindItemForHoldable( holdable_t pw );
gitem_t *BG_FindItemForWeapon( weapon_t weapon );
gitem_t *BG_FindItemForAmmo( ammo_t ammo );
gitem_t *BG_FindItem( const char *classname );
qboolean BG_PlayerTouchesItem( playerState_t *ps, entityState_t *item, int atTime );
int BG_ProperForceIndex( int power );
void BG_CycleForce( playerState_t *ps, int direction );
int BG_GetItemIndexByTag( int tag, int type );
qboolean BG_IsItemSelectable( playerState_t *ps, int item );
void BG_CycleInven( playerState_t *ps, int direction );
qboolean BG_CanItemBeGrabbed( int gametype, const entityState_t *ent, const playerState_t *ps );
void BG_EvaluateTrajectory( const trajectory_t *tr, int atTime, vec3_t result );
void BG_EvaluateTrajectoryDelta( const trajectory_t *tr, int atTime, vec3_t result );
void BG_AddPredictableEventToPlayerstate( int newEvent, int eventParm, playerState_t *ps );
void BG_TouchJumpPad( playerState_t *ps, entityState_t *jumppad );
int BG_EmplacedView( vec3_t baseAngles, vec3_t angles, float *newYaw, float constraint );
qboolean BG_IsValidCharacterModel( const char *modelName, const char *skinName );
qboolean BG_ValidateSkinForTeam( const char *modelName, char *skinName, int team, float *colors );
void BG_PlayerStateToEntityState( playerState_t *ps, entityState_t *s, qboolean snap );
void BG_PlayerStateToEntityStateExtraPolate( playerState_t *ps, entityState_t *s, int time, qboolean snap );
int BG_ModelCache( const char *modelName, const char *skinName );
void *BG_Alloc( int size );
void *BG_AllocUnaligned( int size );
void *BG_TempAlloc( int size );
void BG_TempFree( int size );
char *BG_StringAlloc( const char *source );
qboolean BG_OutOfMemory();
const char *BG_GetGametypeString( int gametype );
int BG_GetGametypeForString( const char *gametype );
