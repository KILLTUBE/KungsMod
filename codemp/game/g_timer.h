#pragma once

#include "g_local.h"


#define MAX_GTIMERS	16384

typedef struct gtimer_s
{
	const char *name;
	int time;
	struct gtimer_s *next;	// In either free list or current list
} gtimer_t;

EXTERNC gtimer_t *g_timerFreeList;
EXTERNC gtimer_t *g_timers[MAX_GENTITIES];
EXTERNC gtimer_t g_timerPool[MAX_GTIMERS];

CCALL qboolean TIMER_Start(gentity_t *self,const char *identifier,int duration);
CCALL void TIMER_Remove(gentity_t *ent,const char *identifier);
CCALL qboolean TIMER_Exists(gentity_t *ent,const char *identifier);
CCALL qboolean TIMER_Done2(gentity_t *ent,const char *identifier,qboolean remove);
CCALL void TIMER_RemoveHelper(int num,gtimer_t *timer);
CCALL qboolean TIMER_Done(gentity_t *ent,const char *identifier);
CCALL int TIMER_Get(gentity_t *ent,const char *identifier);
CCALL void TIMER_Set(gentity_t *ent,const char *identifier,int duration);
CCALL gtimer_t *TIMER_GetExisting(int num,const char *identifier);
CCALL gtimer_t *TIMER_GetNew(int num,const char *identifier);
CCALL void TIMER_Clear2(gentity_t *ent);
CCALL void TIMER_Clear(void);
