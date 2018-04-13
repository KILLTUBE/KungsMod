#pragma once

#include "g_local.h"

#define	MAX_IPFILTERS (1024)

typedef struct svcmd_s {
	const char	*name;
	void		(*func)(void);
	qboolean	dedicated;
} svcmd_t;

typedef struct ipFilter_s {
	uint32_t mask;
	uint32_t compare;
} ipFilter_t;

EXTERNC svcmd_t svcmds[];

CCALL qboolean ConsoleCommand(void);
CCALL int svcmdcmp(const void *a,const void *b);
CCALL void Svcmd_Say_f(void);
CCALL char *ConcatArgs(int start);
CCALL void Svcmd_ForceTeam_f(void);
CCALL gclient_t *ClientForString(const char *s);
CCALL qboolean StringIsInteger(const char *s);
CCALL void Svcmd_EntityList_f(void);
CCALL void Svcmd_ListIP_f(void);
CCALL void Svcmd_RemoveIP_f(void);
CCALL void Svcmd_AddIP_f(void);
CCALL void G_ProcessIPBans(void);
CCALL qboolean G_FilterPacket(char *from);
