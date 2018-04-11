#pragma once

#include "g_local.h"

CCALL void G_WriteSessionData(void);
CCALL void G_InitWorldSession(void);
CCALL void G_InitSessionData(gclient_t *client,char *userinfo,qboolean isBot);
CCALL void G_ReadSessionData(gclient_t *client);
CCALL void G_WriteClientSessionData(gclient_t *client);
