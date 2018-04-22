FX_DisruptorMainShot( start_, end_ ) = ccall((:FX_DisruptorMainShot, lib), Void, ( vec3_t, vec3_t,  ), start_, end_ );
FX_DisruptorAltShot( start_, end_, fullCharge_ ) = ccall((:FX_DisruptorAltShot, lib), Void, ( vec3_t, vec3_t, qboolean,  ), start_, end_, fullCharge_ );
FX_DisruptorAltMiss( origin_, normal_ ) = ccall((:FX_DisruptorAltMiss, lib), Void, ( vec3_t, vec3_t,  ), origin_, normal_ );
FX_DisruptorAltHit( origin_, normal_ ) = ccall((:FX_DisruptorAltHit, lib), Void, ( vec3_t, vec3_t,  ), origin_, normal_ );
FX_DisruptorHitWall( origin_, normal_ ) = ccall((:FX_DisruptorHitWall, lib), Void, ( vec3_t, vec3_t,  ), origin_, normal_ );
FX_DisruptorHitPlayer( origin_, normal_, humanoid_ ) = ccall((:FX_DisruptorHitPlayer, lib), Void, ( vec3_t, vec3_t, qboolean,  ), origin_, normal_, humanoid_ );
