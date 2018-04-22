CG_CheckAmmo() = ccall((:CG_CheckAmmo, lib), Void, (),  );
CG_DamageFeedback( yawByte_, pitchByte_, damage_ ) = ccall((:CG_DamageFeedback, lib), Void, ( Int32, Int32, Int32,  ), yawByte_, pitchByte_, damage_ );
CG_Respawn() = ccall((:CG_Respawn, lib), Void, (),  );
CG_CheckPlayerstateEvents( ps_, ops_ ) = ccall((:CG_CheckPlayerstateEvents, lib), Void, ( Ptr{playerState_t}, Ptr{playerState_t},  ), ps_, ops_ );
CG_CheckChangedPredictableEvents( ps_ ) = ccall((:CG_CheckChangedPredictableEvents, lib), Void, ( Ptr{playerState_t},  ), ps_ );
pushReward( sfx_, shader_, rewardCount_ ) = ccall((:pushReward, lib), Void, ( sfxHandle_t, qhandle_t, Int32,  ), sfx_, shader_, rewardCount_ );
CG_CheckLocalSounds( ps_, ops_ ) = ccall((:CG_CheckLocalSounds, lib), Void, ( Ptr{playerState_t}, Ptr{playerState_t},  ), ps_, ops_ );
CG_TransitionPlayerState( ps_, ops_ ) = ccall((:CG_TransitionPlayerState, lib), Void, ( Ptr{playerState_t}, Ptr{playerState_t},  ), ps_, ops_ );
