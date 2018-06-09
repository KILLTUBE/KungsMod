static qboolean StringToFilter( char *s, ipFilter_t *f );
static void UpdateIPBans();
qboolean G_FilterPacket( char *from );
static void AddIP( char *str );
void G_ProcessIPBans();
void Svcmd_AddIP_f();
void Svcmd_RemoveIP_f();
void Svcmd_ListIP_f();
void Svcmd_EntityList_f();
gclient_t *ClientForString( const char *s );
void Svcmd_ForceTeam_f();
void Svcmd_Say_f();
int svcmdcmp( const void *a, const void *b );
qboolean ConsoleCommand();