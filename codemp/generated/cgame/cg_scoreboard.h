static void CG_DrawClientScore( int y, score_t *score, float *color, float fade, qboolean largeFormat );
static int CG_TeamScoreboard( int y, team_t team, float fade, int maxClients, int lineHeight, qboolean countOnly );
int CG_GetClassCount( team_t team, int siegeClass );
int CG_GetTeamNonScoreCount( team_t team );
int CG_GetTeamCount( team_t team, int maxClients );
qboolean CG_DrawOldScoreboard();
