CG_DrawClientScore( y_, score_, color_, fade_, largeFormat_ ) = ccall((:CG_DrawClientScore, lib), Void, ( Int32, Ptr{score_t}, Ptr{Float32}, Float32, qboolean,  ), y_, score_, color_, fade_, largeFormat_ );
CG_TeamScoreboard( y_, team_, fade_, maxClients_, lineHeight_, countOnly_ ) = ccall((:CG_TeamScoreboard, lib), Int32, ( Int32, team_t, Float32, Int32, Int32, qboolean,  ), y_, team_, fade_, maxClients_, lineHeight_, countOnly_ );
CG_GetClassCount( team_, siegeClass_ ) = ccall((:CG_GetClassCount, lib), Int32, ( team_t, Int32,  ), team_, siegeClass_ );
CG_GetTeamNonScoreCount( team_ ) = ccall((:CG_GetTeamNonScoreCount, lib), Int32, ( team_t,  ), team_ );
CG_GetTeamCount( team_, maxClients_ ) = ccall((:CG_GetTeamCount, lib), Int32, ( team_t, Int32,  ), team_, maxClients_ );
CG_DrawOldScoreboard() = ccall((:CG_DrawOldScoreboard, lib), qboolean, (),  );
