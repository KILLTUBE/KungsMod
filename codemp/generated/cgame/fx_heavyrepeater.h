void FX_RepeaterProjectileThink( centity_t *cent, const struct weaponInfo_s *weapon );
void FX_RepeaterHitWall( vec3_t origin, vec3_t normal );
void FX_RepeaterHitPlayer( vec3_t origin, vec3_t normal, qboolean humanoid );
static void CG_DistortionOrb( centity_t *cent );
void FX_RepeaterAltProjectileThink( centity_t *cent, const struct weaponInfo_s *weapon );
void FX_RepeaterAltHitWall( vec3_t origin, vec3_t normal );
void FX_RepeaterAltHitPlayer( vec3_t origin, vec3_t normal, qboolean humanoid );
