PM_VehicleImpact( pEnt_, trace_ ) = ccall((:PM_VehicleImpact, lib), Void, ( Ptr{bgEntity_t}, Ptr{trace_t},  ), pEnt_, trace_ );
PM_GroundSlideOkay( zNormal_ ) = ccall((:PM_GroundSlideOkay, lib), qboolean, ( Float32,  ), zNormal_ );
PM_ClientImpact( trace_ ) = ccall((:PM_ClientImpact, lib), qboolean, ( Ptr{trace_t},  ), trace_ );
PM_SlideMove( gravity_ ) = ccall((:PM_SlideMove, lib), qboolean, ( qboolean,  ), gravity_ );
PM_StepSlideMove( gravity_ ) = ccall((:PM_StepSlideMove, lib), Void, ( qboolean,  ), gravity_ );
