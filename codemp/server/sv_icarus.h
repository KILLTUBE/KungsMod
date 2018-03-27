#ifndef ICARUS
#define ICARUS


CCALL int ICARUS_GetVectorVariable(const char *name,const vec3_t value);
CCALL int ICARUS_GetStringVariable(const char *name,const char *value);
CCALL void ICARUS_TaskIDComplete(sharedEntity_t *ent,int taskType);
CCALL void ICARUS_TaskIDSet(sharedEntity_t *ent,int taskType,int taskID);
CCALL qboolean ICARUS_TaskIDPending(sharedEntity_t *ent,int taskID);
CCALL qboolean ICARUS_IsRunning(int entID);
CCALL qboolean ICARUS_MaintainTaskManager(int entID);
CCALL qboolean ICARUS_IsInitialized(int entID);
CCALL qboolean ICARUS_ValidEnt(sharedEntity_t *ent);


CCALL void ICARUS_AssociateEnt( sharedEntity_t *ent );
CCALL void SV_SiegePersGet(siegePers_t *siegePers);
CCALL void SV_SiegePersSet(siegePers_t *siegePers);
CCALL void SV_SetServerCull(float cullDistance);
CCALL void SV_RegisterSharedMemory(char *memory);
CCALL int SV_PrecisionTimerEnd(void *timer);
CCALL void SV_PrecisionTimerStart(void **timer);
CCALL qboolean SV_GetEntityToken(char *buffer,int bufferSize);
CCALL sharedEntity_t *ConvertedEntity(sharedEntity_t *ent);
CCALL void SV_GetUsercmd(int clientNum,usercmd_t *cmd);
CCALL void SV_AdjustAreaPortalState(sharedEntity_t *ent,qboolean open);
CCALL int ICARUS_RunScript( sharedEntity_t *ent, const char *name );
CCALL int ICARUS_GetScript( const char *name, char **buf );
CCALL void ICARUS_Init( void );
CCALL void ICARUS_Shutdown( void );
CCALL qboolean ICARUS_RegisterScript( const char *name, qboolean bCalledDuringInterrogate /* = false */ );


#endif