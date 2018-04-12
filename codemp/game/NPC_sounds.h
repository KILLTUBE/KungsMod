#pragma once

#include "b_local.h"
#include "icarus/Q3_Interface.h"

CCALL void NPC_PlayConfusionSound(gentity_t *self);
CCALL void G_AddVoiceEvent(gentity_t *self,int event,int speakDebounceTime);
CCALL void G_SpeechEvent(gentity_t *self,int event);
