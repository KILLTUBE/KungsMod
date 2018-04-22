FX_DEMP2_ProjectileThink( cent_, weapon_ ) = ccall((:FX_DEMP2_ProjectileThink, lib), Void, ( Ptr{centity_t}, Ptr{weaponInfo_s},  ), cent_, weapon_ );
FX_DEMP2_HitWall( origin_, normal_ ) = ccall((:FX_DEMP2_HitWall, lib), Void, ( vec3_t, vec3_t,  ), origin_, normal_ );
FX_DEMP2_HitPlayer( origin_, normal_, humanoid_ ) = ccall((:FX_DEMP2_HitPlayer, lib), Void, ( vec3_t, vec3_t, qboolean,  ), origin_, normal_, humanoid_ );
FX_DEMP2_AltBeam( start_, end_, normal_, targ1_, targ2_ ) = ccall((:FX_DEMP2_AltBeam, lib), Void, ( vec3_t, vec3_t, vec3_t, vec3_t, vec3_t,  ), start_, end_, normal_, targ1_, targ2_ );
FX_DEMP2_AltDetonate( org_, size_ ) = ccall((:FX_DEMP2_AltDetonate, lib), Void, ( vec3_t, Float32,  ), org_, size_ );
