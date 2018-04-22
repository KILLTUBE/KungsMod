FX_RepeaterProjectileThink( cent_, weapon_ ) = ccall((:FX_RepeaterProjectileThink, lib), Void, ( Ptr{centity_t}, Ptr{weaponInfo_s},  ), cent_, weapon_ );
FX_RepeaterHitWall( origin_, normal_ ) = ccall((:FX_RepeaterHitWall, lib), Void, ( vec3_t, vec3_t,  ), origin_, normal_ );
FX_RepeaterHitPlayer( origin_, normal_, humanoid_ ) = ccall((:FX_RepeaterHitPlayer, lib), Void, ( vec3_t, vec3_t, qboolean,  ), origin_, normal_, humanoid_ );
CG_DistortionOrb( cent_ ) = ccall((:CG_DistortionOrb, lib), Void, ( Ptr{centity_t},  ), cent_ );
FX_RepeaterAltProjectileThink( cent_, weapon_ ) = ccall((:FX_RepeaterAltProjectileThink, lib), Void, ( Ptr{centity_t}, Ptr{weaponInfo_s},  ), cent_, weapon_ );
FX_RepeaterAltHitWall( origin_, normal_ ) = ccall((:FX_RepeaterAltHitWall, lib), Void, ( vec3_t, vec3_t,  ), origin_, normal_ );
FX_RepeaterAltHitPlayer( origin_, normal_, humanoid_ ) = ccall((:FX_RepeaterAltHitPlayer, lib), Void, ( vec3_t, vec3_t, qboolean,  ), origin_, normal_, humanoid_ );
