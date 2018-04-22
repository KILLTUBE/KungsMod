FX_BlasterProjectileThink( cent_, weapon_ ) = ccall((:FX_BlasterProjectileThink, lib), Void, ( Ptr{centity_t}, Ptr{weaponInfo_s},  ), cent_, weapon_ );
FX_BlasterAltFireThink( cent_, weapon_ ) = ccall((:FX_BlasterAltFireThink, lib), Void, ( Ptr{centity_t}, Ptr{weaponInfo_s},  ), cent_, weapon_ );
FX_BlasterWeaponHitWall( origin_, normal_ ) = ccall((:FX_BlasterWeaponHitWall, lib), Void, ( vec3_t, vec3_t,  ), origin_, normal_ );
FX_BlasterWeaponHitPlayer( origin_, normal_, humanoid_ ) = ccall((:FX_BlasterWeaponHitPlayer, lib), Void, ( vec3_t, vec3_t, qboolean,  ), origin_, normal_, humanoid_ );
