#include "fx_bryarpistol.h"

//
//	MAIN FIRE
//

void FX_BryarProjectileThink(  centity_t *cent, const struct weaponInfo_s *weapon ) {
	vec3_t forward;
	if ( VectorNormalize2( cent->currentState.pos.trDelta, forward ) == 0.0f ) {
		forward[2] = 1.0f;
	}
	FX_PlayEffectID( cgs.effects.bryarShotEffect, cent->lerpOrigin, forward, -1, -1, qfalse );
}

void FX_BryarHitWall( vec3_t origin, vec3_t normal ) {
	FX_PlayEffectID( cgs.effects.bryarWallImpactEffect, origin, normal, -1, -1, qfalse );
}

void FX_BryarHitPlayer( vec3_t origin, vec3_t normal, qboolean humanoid ) {
	if ( humanoid ) {
		FX_PlayEffectID( cgs.effects.bryarFleshImpactEffect, origin, normal, -1, -1, qfalse );
	} else {
		FX_PlayEffectID( cgs.effects.bryarDroidImpactEffect, origin, normal, -1, -1, qfalse );
	}
}

//
//	ALT FIRE
//

void FX_BryarAltProjectileThink(  centity_t *cent, const struct weaponInfo_s *weapon ) {
	vec3_t forward;
	int t;
	if ( VectorNormalize2( cent->currentState.pos.trDelta, forward ) == 0.0f ) {
		forward[2] = 1.0f;
	}
	// see if we have some sort of extra charge going on
	for (t = 1; t < cent->currentState.generic1; t++ ) {
		// just add ourselves over, and over, and over when we are charged
		FX_PlayEffectID( cgs.effects.bryarPowerupShotEffect, cent->lerpOrigin, forward, -1, -1, qfalse );
	}
	//	for ( int t = 1; t < cent->gent->count; t++ )	// The single player stores the charge in count, which isn't accessible on the client
	FX_PlayEffectID( cgs.effects.bryarShotEffect, cent->lerpOrigin, forward, -1, -1, qfalse );
}

void FX_BryarAltHitWall( vec3_t origin, vec3_t normal, int power ) {
	switch( power ) {
	case 4:
	case 5:
		FX_PlayEffectID( cgs.effects.bryarWallImpactEffect3, origin, normal, -1, -1, qfalse );
		break;
	case 2:
	case 3:
		FX_PlayEffectID( cgs.effects.bryarWallImpactEffect2, origin, normal, -1, -1, qfalse );
		break;
	default:
		FX_PlayEffectID( cgs.effects.bryarWallImpactEffect, origin, normal, -1, -1, qfalse );
		break;
	}
}

void FX_BryarAltHitPlayer( vec3_t origin, vec3_t normal, qboolean humanoid ) {
	if ( humanoid ) {
		FX_PlayEffectID( cgs.effects.bryarFleshImpactEffect, origin, normal, -1, -1, qfalse );
	} else {
		FX_PlayEffectID( cgs.effects.bryarDroidImpactEffect, origin, normal, -1, -1, qfalse );
	}
}

//
//	TURRET
//

void FX_TurretProjectileThink(  centity_t *cent, const struct weaponInfo_s *weapon ) {
	vec3_t forward;

	if ( VectorNormalize2( cent->currentState.pos.trDelta, forward ) == 0.0f )
	{
		forward[2] = 1.0f;
	}

	FX_PlayEffectID( cgs.effects.turretShotEffect, cent->lerpOrigin, forward, -1, -1, qfalse );
}

void FX_TurretHitWall( vec3_t origin, vec3_t normal ) {
	FX_PlayEffectID( cgs.effects.bryarWallImpactEffect, origin, normal, -1, -1, qfalse );
}

void FX_TurretHitPlayer( vec3_t origin, vec3_t normal, qboolean humanoid ) {
	if ( humanoid ) {
		FX_PlayEffectID( cgs.effects.bryarFleshImpactEffect, origin, normal, -1, -1, qfalse );
	} else {
		FX_PlayEffectID( cgs.effects.bryarDroidImpactEffect, origin, normal, -1, -1, qfalse );
	}
}

//CONCUSSION (yeah, should probably make a new file for this.. or maybe just move all these stupid semi-redundant fx_ functions into one file)

void FX_ConcussionHitWall( vec3_t origin, vec3_t normal ) {
	FX_PlayEffectID( cgs.effects.concussionImpactEffect, origin, normal, -1, -1, qfalse );
}

void FX_ConcussionHitPlayer( vec3_t origin, vec3_t normal, qboolean humanoid ) {
	FX_PlayEffectID( cgs.effects.concussionImpactEffect, origin, normal, -1, -1, qfalse );
}

void FX_ConcussionProjectileThink(  centity_t *cent, const struct weaponInfo_s *weapon ) {
	vec3_t forward;
	if ( VectorNormalize2( cent->currentState.pos.trDelta, forward ) == 0.0f ) {
		forward[2] = 1.0f;
	}
	FX_PlayEffectID( cgs.effects.concussionShotEffect, cent->lerpOrigin, forward, -1, -1, qfalse );
}

static vec3_t WHITE	={1.0f,1.0f,1.0f};
static vec3_t BRIGHT={0.75f,0.5f,1.0f};

void FX_ConcAltShot( vec3_t start, vec3_t end ) {
	//"concussion/beam"
	CGFX_AddLine(
		start, end, 0.1f, 10.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		WHITE, WHITE, 0.0f,
		175, R_RegisterShader( "gfx/effects/blueLine" ),
		FX_SIZE_LINEAR | FX_ALPHA_LINEAR
	);

	// add some beef
	CGFX_AddLine(
		start, end, 0.1f, 7.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		BRIGHT, BRIGHT, 0.0f,
		150, R_RegisterShader( "gfx/misc/whiteline2" ),
		FX_SIZE_LINEAR | FX_ALPHA_LINEAR
	);
}
