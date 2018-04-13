#include "fx_flechette.h"

// Golan Arms Flechette Weapon

void FX_FlechetteProjectileThink( centity_t *cent, const struct weaponInfo_s *weapon ) {
	vec3_t forward;
	if ( VectorNormalize2( cent->currentState.pos.trDelta, forward ) == 0.0f ) {
		forward[2] = 1.0f;
	}
	FX_PlayEffectID( cgs.effects.flechetteShotEffect, cent->lerpOrigin, forward, -1, -1, qfalse );
}

void FX_FlechetteWeaponHitWall( vec3_t origin, vec3_t normal ) {
	FX_PlayEffectID( cgs.effects.flechetteWallImpactEffect, origin, normal, -1, -1, qfalse );
}


void FX_FlechetteWeaponHitPlayer( vec3_t origin, vec3_t normal, qboolean humanoid ) {
//	if ( humanoid )
//	{
		FX_PlayEffectID( cgs.effects.flechetteFleshImpactEffect, origin, normal, -1, -1, qfalse );
//	}
//	else
//	{
//		FX_PlayEffect( "blaster/droid_impact", origin, normal );
//	}
}

void FX_FlechetteAltProjectileThink( centity_t *cent, const struct weaponInfo_s *weapon ) {
	vec3_t forward;
	if ( VectorNormalize2( cent->currentState.pos.trDelta, forward ) == 0.0f ) {
		forward[2] = 1.0f;
	}
	FX_PlayEffectID( cgs.effects.flechetteAltShotEffect, cent->lerpOrigin, forward, -1, -1, qfalse );
}
