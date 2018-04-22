SetGoal( goal_, rating_ ) = ccall((:SetGoal, lib), Void, ( Ptr{gentity_t}, Float32,  ), goal_, rating_ );
NPC_SetGoal( goal_, rating_ ) = ccall((:NPC_SetGoal, lib), Void, ( Ptr{gentity_t}, Float32,  ), goal_, rating_ );
NPC_ClearGoal() = ccall((:NPC_ClearGoal, lib), Void, (),  );
G_BoundsOverlap( mins1_, maxs1_, mins2_, maxs2_ ) = ccall((:G_BoundsOverlap, lib), qboolean, ( vec3_t, vec3_t, vec3_t, vec3_t,  ), mins1_, maxs1_, mins2_, maxs2_ );
NPC_ReachedGoal() = ccall((:NPC_ReachedGoal, lib), Void, (),  );
ReachedGoal( goal_ ) = ccall((:ReachedGoal, lib), qboolean, ( Ptr{gentity_t},  ), goal_ );
UpdateGoal() = ccall((:UpdateGoal, lib), Ptr{gentity_t}, (),  );
