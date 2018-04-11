#pragma once

#include "cg_local.h"

EXTERNC int cgAnnouncerTime;

CCALL void CG_TransitionPlayerState(playerState_t *ps,playerState_t *ops);
CCALL void CG_CheckLocalSounds(playerState_t *ps,playerState_t *ops);
CCALL void CG_CheckChangedPredictableEvents(playerState_t *ps);
CCALL void CG_CheckPlayerstateEvents(playerState_t *ps,playerState_t *ops);
CCALL void CG_Respawn(void);
CCALL void CG_DamageFeedback(int yawByte,int pitchByte,int damage);
CCALL void CG_CheckAmmo(void);
