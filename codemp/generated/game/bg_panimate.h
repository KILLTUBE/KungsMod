qboolean BG_SaberStanceAnim( int anim );
qboolean BG_CrouchAnim( int anim );
qboolean BG_InSpecialJump( int anim );
qboolean BG_InSaberStandAnim( int anim );
qboolean BG_InReboundJump( int anim );
qboolean BG_InReboundHold( int anim );
qboolean BG_InReboundRelease( int anim );
qboolean BG_InBackFlip( int anim );
qboolean BG_DirectFlippingAnim( int anim );
qboolean BG_SaberInAttackPure( int move );
qboolean BG_SaberInAttack( int move );
qboolean BG_SaberInKata( int saberMove );
qboolean BG_InKataAnim( int anim );
qboolean BG_SaberInSpecial( int move );
qboolean BG_KickMove( int move );
qboolean BG_SaberInIdle( int move );
qboolean BG_InExtraDefenseSaberMove( int move );
qboolean BG_FlippingAnim( int anim );
qboolean BG_SpinningSaberAnim( int anim );
qboolean BG_SaberInSpecialAttack( int anim );
qboolean BG_KickingAnim( int anim );
int BG_InGrappleMove( int anim );
int BG_BrokenParryForAttack( int move );
int BG_BrokenParryForParry( int move );
int BG_KnockawayForParry( int move );
qboolean BG_InRoll( playerState_t *ps, int anim );
qboolean BG_InSpecialDeathAnim( int anim );
qboolean BG_InDeathAnim( int anim );
qboolean BG_InKnockDownOnly( int anim );
qboolean BG_InSaberLockOld( int anim );
qboolean BG_InSaberLock( int anim );
qboolean PM_InCartwheel( int anim );
qboolean BG_InKnockDownOnGround( playerState_t *ps );
qboolean BG_StabDownAnim( int anim );
int PM_SaberBounceForAttack( int move );
int PM_SaberDeflectionForQuad( int quad );
qboolean PM_SaberInDeflect( int move );
qboolean PM_SaberInParry( int move );
qboolean PM_SaberInKnockaway( int move );
qboolean PM_SaberInReflect( int move );
qboolean PM_SaberInStart( int move );
qboolean PM_SaberInReturn( int move );
qboolean BG_SaberInReturn( int move );
qboolean PM_InSaberAnim( int anim );
qboolean PM_InKnockDown( playerState_t *ps );
qboolean PM_PainAnim( int anim );
qboolean PM_JumpingAnim( int anim );
qboolean PM_LandingAnim( int anim );
qboolean PM_SpinningAnim( int anim );
qboolean PM_InOnGroundAnim( int anim );
qboolean PM_InRollComplete( playerState_t *ps, int anim );
qboolean PM_CanRollFromSoulCal( playerState_t *ps );
qboolean BG_SuperBreakLoseAnim( int anim );
qboolean BG_SuperBreakWinAnim( int anim );
qboolean BG_SaberLockBreakAnim( int anim );
qboolean BG_FullBodyTauntAnim( int anim );
int BG_AnimLength( int index, animNumber_t anim );
int PM_AnimLength( int index, animNumber_t anim );
void PM_DebugLegsAnim( int anim );
qboolean PM_SaberInTransition( int move );
qboolean BG_SaberInTransitionAny( int move );
void BG_FlipPart( playerState_t *ps, int part );
void BG_InitAnimsets();
void BG_ClearAnimsets();
animation_t *BG_AnimsetAlloc();
void BG_AnimsetFree( animation_t *animset );
int CheckAnimFrameForEventType( animevent_t *animEvents, int keyFrame, animEventType_t eventType );
void ParseAnimationEvtBlock( const char *aeb_filename, animevent_t *animEvents, animation_t *animations, int *i, const char **text_p );
int BG_ParseAnimationEvtFile( const char *as_filename, int animFileIndex, int eventFileIndex );
int BG_ParseAnimationFile( const char *filename, animation_t *animset, qboolean isHumanoid );
static void BG_StartLegsAnim( playerState_t *ps, int anim );
void PM_ContinueLegsAnim( int anim );
void PM_ForceLegsAnim( int anim );
void BG_StartTorsoAnim( playerState_t *ps, int anim );
void PM_StartTorsoAnim( int anim );
void BG_SetLegsAnimTimer( playerState_t *ps, int time );
void PM_SetLegsAnimTimer( int time );
void BG_SetTorsoAnimTimer( playerState_t *ps, int time );
void PM_SetTorsoAnimTimer( int time );
void BG_SaberStartTransAnim( int clientNum, int saberAnimLevel, int weapon, int anim, float *animSpeed, int broken );
void BG_SetAnimFinal( playerState_t *ps, animation_t *animations, int setAnimParts, int anim, int setAnimFlags );
void PM_SetAnimFinal( int setAnimParts, int anim, int setAnimFlags );
qboolean BG_HasAnimation( int animIndex, int animation );
int BG_PickAnim( int animIndex, int minAnim, int maxAnim );
void BG_SetAnim( playerState_t *ps, animation_t *animations, int setAnimParts, int anim, int setAnimFlags );
void PM_SetAnim( int setAnimParts, int anim, int setAnimFlags );
