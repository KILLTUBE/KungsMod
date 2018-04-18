void trap_SendServerCommand( int clientNum, const char *text );
qboolean SVSyscall_EntityContact( const vec3_t mins, const vec3_t maxs, const sharedEntity_t *ent, int capsule );
void SVSyscall_Trace( trace_t *results, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end, int passEntityNum, int contentmask, int capsule, int traceFlags, int useLod );
void G_Error( int errorLevel, const char *error, ... );
void G_Printf( const char *msg, ... );
