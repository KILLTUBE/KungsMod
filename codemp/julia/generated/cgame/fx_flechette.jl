FX_FlechetteProjectileThink( cent_, weapon_ ) = ccall((:FX_FlechetteProjectileThink, lib), Void, ( Ptr{centity_t}, Ptr{weaponInfo_s},  ), cent_, weapon_ );
FX_FlechetteWeaponHitWall( origin_, normal_ ) = ccall((:FX_FlechetteWeaponHitWall, lib), Void, ( vec3_t, vec3_t,  ), origin_, normal_ );
FX_FlechetteWeaponHitPlayer( origin_, normal_, humanoid_ ) = ccall((:FX_FlechetteWeaponHitPlayer, lib), Void, ( vec3_t, vec3_t, qboolean,  ), origin_, normal_, humanoid_ );
FX_FlechetteAltProjectileThink( cent_, weapon_ ) = ccall((:FX_FlechetteAltProjectileThink, lib), Void, ( Ptr{centity_t}, Ptr{weaponInfo_s},  ), cent_, weapon_ );
