CG_InitMarkPolys() = ccall((:CG_InitMarkPolys, lib), Void, (),  );
CG_FreeMarkPoly( le_ ) = ccall((:CG_FreeMarkPoly, lib), Void, ( Ptr{markPoly_t},  ), le_ );
CG_AllocMark() = ccall((:CG_AllocMark, lib), markPoly_t, (),  );
CG_ImpactMark( markShader_, origin_, dir_, orientation_, red_, green_, blue_, alpha_, alphaFade_, radius_, temporary_ ) = ccall((:CG_ImpactMark, lib), Void, ( qhandle_t, vec3_t, vec3_t, Float32, Float32, Float32, Float32, Float32, qboolean, Float32, qboolean,  ), markShader_, origin_, dir_, orientation_, red_, green_, blue_, alpha_, alphaFade_, radius_, temporary_ );
CG_AddMarks() = ccall((:CG_AddMarks, lib), Void, (),  );
