CreepToPosition( ideal_, current_ ) = ccall((:CreepToPosition, lib), Void, ( vec3_t, vec3_t,  ), ideal_, current_ );
TurretClientRun( ent_ ) = ccall((:TurretClientRun, lib), Void, ( Ptr{centity_t},  ), ent_ );
