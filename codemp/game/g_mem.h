#pragma once

#include "g_local.h"

#define POOLSIZE	(4 * 1024 * 1024) // (256*1024)

CCALL void Svcmd_GameMem_f(void);
CCALL void G_InitMemory(void);
CCALL void *G_Alloc(int size);
