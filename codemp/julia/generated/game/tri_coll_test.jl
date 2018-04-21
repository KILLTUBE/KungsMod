coplanar_tri_tri( N_, V0_, V1_, V2_, U0_, U1_, U2_ ) = ccall((:coplanar_tri_tri, lib), qboolean, ( vec3_t, vec3_t, vec3_t, vec3_t, vec3_t, vec3_t, vec3_t,  ), N_, V0_, V1_, V2_, U0_, U1_, U2_ );
tri_tri_intersect( V0_, V1_, V2_, U0_, U1_, U2_ ) = ccall((:tri_tri_intersect, lib), qboolean, ( vec3_t, vec3_t, vec3_t, vec3_t, vec3_t, vec3_t,  ), V0_, V1_, V2_, U0_, U1_, U2_ );
