FX_BowcasterProjectileThink( cent_, weapon_ ) = ccall((:FX_BowcasterProjectileThink, lib), Void, ( Ptr{centity_t}, Ptr{weaponInfo_s},  ), cent_, weapon_ );
FX_BowcasterHitWall( origin_, normal_ ) = ccall((:FX_BowcasterHitWall, lib), Void, ( vec3_t, vec3_t,  ), origin_, normal_ );
FX_BowcasterHitPlayer( origin_, normal_, humanoid_ ) = ccall((:FX_BowcasterHitPlayer, lib), Void, ( vec3_t, vec3_t, qboolean,  ), origin_, normal_, humanoid_ );
FX_BowcasterAltProjectileThink( cent_, weapon_ ) = ccall((:FX_BowcasterAltProjectileThink, lib), Void, ( Ptr{centity_t}, Ptr{weaponInfo_s},  ), cent_, weapon_ );
