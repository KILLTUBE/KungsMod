#include "fx_rocketlauncher.h"

void FX_RocketProjectileThink( centity_t *cent, const struct weaponInfo_s *weapon ) {
	vec3_t forward;
	if ( VectorNormalize2( cent->currentState.pos.trDelta, forward ) == 0.0f ) {
		forward[2] = 1.0f;
	}
	FX_PlayEffectID( cgs.effects.rocketShotEffect, cent->lerpOrigin, forward, -1, -1, qfalse );
}

void FX_RocketHitWall( vec3_t origin, vec3_t normal ) {
	FX_PlayEffectID( cgs.effects.rocketExplosionEffect, origin, normal, -1, -1, qfalse );
}

void FX_RocketHitPlayer( vec3_t origin, vec3_t normal, qboolean humanoid ) {
	FX_PlayEffectID( cgs.effects.rocketExplosionEffect, origin, normal, -1, -1, qfalse );
}

void FX_RocketAltProjectileThink( centity_t *cent, const struct weaponInfo_s *weapon ) {
	vec3_t forward;
	if ( VectorNormalize2( cent->currentState.pos.trDelta, forward ) == 0.0f ) {
		forward[2] = 1.0f;
	}
	FX_PlayEffectID( cgs.effects.rocketShotEffect, cent->lerpOrigin, forward, -1, -1, qfalse );
}
