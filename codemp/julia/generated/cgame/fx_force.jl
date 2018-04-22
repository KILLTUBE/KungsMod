FX_ForceDrained( origin_, dir_ ) = ccall((:FX_ForceDrained, lib), Void, ( vec3_t, vec3_t,  ), origin_, dir_ );
