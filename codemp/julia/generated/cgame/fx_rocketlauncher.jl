FX_RocketProjectileThink( cent_, weapon_ ) = ccall((:FX_RocketProjectileThink, lib), Void, ( Ptr{centity_t}, Ptr{weaponInfo_s},  ), cent_, weapon_ );
FX_RocketHitWall( origin_, normal_ ) = ccall((:FX_RocketHitWall, lib), Void, ( vec3_t, vec3_t,  ), origin_, normal_ );
FX_RocketHitPlayer( origin_, normal_, humanoid_ ) = ccall((:FX_RocketHitPlayer, lib), Void, ( vec3_t, vec3_t, qboolean,  ), origin_, normal_, humanoid_ );
FX_RocketAltProjectileThink( cent_, weapon_ ) = ccall((:FX_RocketAltProjectileThink, lib), Void, ( Ptr{centity_t}, Ptr{weaponInfo_s},  ), cent_, weapon_ );
