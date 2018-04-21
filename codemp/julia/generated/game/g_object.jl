G_BounceObject( ent_, trace_ ) = ccall((:G_BounceObject, lib), Void, ( Ptr{gentity_t}, Ptr{trace_t},  ), ent_, trace_ );
G_RunObject( ent_ ) = ccall((:G_RunObject, lib), Void, ( Ptr{gentity_t},  ), ent_ );
G_StopObjectMoving( object_ ) = ccall((:G_StopObjectMoving, lib), Void, ( Ptr{gentity_t},  ), object_ );
G_StartObjectMoving( object_, dir_, speed_, trType_ ) = ccall((:G_StartObjectMoving, lib), Void, ( Ptr{gentity_t}, vec3_t, Float32, trType_t,  ), object_, dir_, speed_, trType_ );
