#pragma once

#include "b_local.h"
#include "qcommon/q_shared.h"

CCALL void Debug_NPCPrintf(gentity_t *printNPC,cvar_t *cv,int debugLevel,char *fmt,...);
CCALL void Debug_Printf(cvar_t *cv,int debugLevel,char *fmt,...);
