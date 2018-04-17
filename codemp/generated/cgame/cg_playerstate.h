void CG_CheckAmmo();
void CG_DamageFeedback( int yawByte, int pitchByte, int damage );
void CG_Respawn();
void CG_CheckPlayerstateEvents( playerState_t *ps, playerState_t *ops );
void CG_CheckChangedPredictableEvents( playerState_t *ps );
static void pushReward( sfxHandle_t sfx, qhandle_t shader, int rewardCount );
void CG_CheckLocalSounds( playerState_t *ps, playerState_t *ops );
void CG_TransitionPlayerState( playerState_t *ps, playerState_t *ops );
