#pragma once

#include "b_local.h"
#include "g_nav.h"
#include "icarus/Q3_Interface.h"

CCALL void NPC_BSDefault(void);
CCALL void NPC_BSST_Attack(void);
CCALL void NPC_CheckGetNewWeapon(void);
CCALL void NPC_BSPatrol(void);
CCALL void NPC_BSShoot(void);
CCALL void NPC_BSMove(void);
CCALL void NPC_BSPointShoot(qboolean shoot);
CCALL void NPC_BSFace(void);
CCALL void NPC_BSRunAndShoot(void);
CCALL void NPC_BSStandAndShoot(void);
CCALL void NPC_BSHuntAndKill(void);
CCALL void NPC_BSStandGuard(void);
CCALL void NPC_BSRun(void);
CCALL void NPC_BSIdle(void);
CCALL qboolean NPC_StandTrackAndShoot(gentity_t *NPC,qboolean canDuck);
CCALL void NPC_StandIdle(void);
CCALL void NPC_LostEnemyDecideChase(void);
CCALL qboolean NPC_SomeoneLookingAtMe(gentity_t *ent);
