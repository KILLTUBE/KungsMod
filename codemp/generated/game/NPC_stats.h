int NPC_ReactionTime();
static rank_t TranslateRankName( const char *name );
void SpewDebugStuffToFile( animation_t *anims );
qboolean G_ParseAnimFileSet( const char *filename, const char *animCFG, int *animFileIndex );
void NPC_PrecacheAnimationCFG( const char *NPC_type );
void NPC_PrecacheWeapons( team_t playerTeam, int spawnflags, char *NPCtype );
void NPC_Precache( gentity_t *spawner );
void NPC_BuildRandom( gentity_t *NPC );
qboolean NPC_ParseParms( const char *NPCName, gentity_t *NPC );
void NPC_LoadParms();
