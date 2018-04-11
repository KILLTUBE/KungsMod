#pragma once

#include "cg_local.h"
#include "game/bg_saga.h"
#include "ui/ui_shared.h"

typedef struct consoleCommand_s {
	const char	*cmd;
	void		(*func)(void);
} consoleCommand_t;

CCALL void CG_InitConsoleCommands(void);
CCALL qboolean CG_ConsoleCommand(void);
CCALL int cmdcmp_cg(const void *a,const void *b);
CCALL void CG_SiegeBriefingDisplay(int team,int dontshow);
CCALL void CG_ClientList_f(void);
CCALL void CG_TargetCommand_f(void);
