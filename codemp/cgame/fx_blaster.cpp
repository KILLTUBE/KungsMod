#include  "fx_blaster.h"

void FX_BlasterProjectileThink( centity_t *cent, const struct weaponInfo_s *weapon ) {
	vec3_t forward;
	if ( VectorNormalize2( cent->currentState.pos.trDelta, forward ) == 0.0f ) {
		forward[2] = 1.0f;
	}
	FX_PlayEffectID( cgs.effects.blasterShotEffect, cent->lerpOrigin, forward, -1, -1, qfalse );
}

void FX_BlasterAltFireThink( centity_t *cent, const struct weaponInfo_s *weapon ) {
	vec3_t forward;
	if ( VectorNormalize2( cent->currentState.pos.trDelta, forward ) == 0.0f ) {
		forward[2] = 1.0f;
	}
	FX_PlayEffectID( cgs.effects.blasterShotEffect, cent->lerpOrigin, forward, -1, -1, qfalse );
}

void FX_BlasterWeaponHitWall( vec3_t origin, vec3_t normal ) {
	FX_PlayEffectID( cgs.effects.blasterWallImpactEffect, origin, normal, -1, -1, qfalse );
}

void FX_BlasterWeaponHitPlayer( vec3_t origin, vec3_t normal, qboolean humanoid ) {
	if ( humanoid ) {
		FX_PlayEffectID( cgs.effects.blasterFleshImpactEffect, origin, normal, -1, -1, qfalse );
	} else {
		FX_PlayEffectID( cgs.effects.blasterDroidImpactEffect, origin, normal, -1, -1, qfalse );
	}
}
