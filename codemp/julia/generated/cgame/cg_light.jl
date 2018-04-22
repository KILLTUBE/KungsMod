CG_ClearLightStyles() = ccall((:CG_ClearLightStyles, lib), Void, (),  );
CG_RunLightStyles() = ccall((:CG_RunLightStyles, lib), Void, (),  );
CG_SetLightstyle( i_ ) = ccall((:CG_SetLightstyle, lib), Void, ( Int32,  ), i_ );
