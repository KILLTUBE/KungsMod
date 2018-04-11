#pragma once

#include "g_local.h"
#include "qcommon/q_shared.h"
#include "botlib/botlib.h"
#include "ai_main.h"

EXTERNC wpobject_t *gWPArray[MAX_WPARRAY_SIZE];
EXTERNC char gBotChatBuffer[MAX_CLIENTS][MAX_CHAT_BUFFER_SIZE];
#if defined(BOT_ZMALLOC)
EXTERNC void *BAllocList[MAX_BALLOC];
#endif

CCALL void BotUtilizePersonality(bot_state_t *bs);
CCALL int ReadChatGroups(bot_state_t *bs,char *buf);
CCALL void ParseEmotionalAttachments(bot_state_t *bs,char *buf);
CCALL int BotDoChat(bot_state_t *bs,char *section,int always);
CCALL int GetPairedValue(char *buf,char *key,char *outbuf);
CCALL int GetValueGroup(char *buf,char *group,char *outbuf);
CCALL void B_CleanupAlloc(void);
CCALL void B_InitAlloc(void);
CCALL void B_Free(void *ptr);
CCALL void *B_Alloc(int size);
CCALL void B_TempFree(int size);
CCALL void *B_TempAlloc(int size);
