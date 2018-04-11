#pragma once

#include "g_local.h"
#include "w_saber.h"
#include "qcommon/q_shared.h"

#define	MISSILE_PRESTEP_TIME	50

CCALL void G_RunMissile(gentity_t *ent);
CCALL void G_MissileImpact(gentity_t *ent,trace_t *trace);
CCALL void WP_flechette_alt_blow(gentity_t *ent);
CCALL void WP_SaberBlockNonRandom(gentity_t *self,vec3_t hitloc,qboolean missileBlock);
CCALL void G_MissileBounceEffect(gentity_t *ent,vec3_t org,vec3_t dir);
CCALL gentity_t *CreateMissile(vec3_t org,vec3_t dir,float vel,int life,gentity_t *owner,qboolean altFire);
CCALL void G_BounceProjectile(vec3_t start,vec3_t impact,vec3_t dir,vec3_t endout);
CCALL void G_RunStuckMissile(gentity_t *ent);
CCALL void G_ExplodeMissile(gentity_t *ent);
CCALL void G_BounceMissile(gentity_t *ent,trace_t *trace);
CCALL void G_DeflectMissile(gentity_t *ent,gentity_t *missile,vec3_t forward);
CCALL void G_ReflectMissile(gentity_t *ent,gentity_t *missile,vec3_t forward);
CCALL float RandFloat(float min,float max);
CCALL qboolean FighterIsLanded(Vehicle_t *pVeh,playerState_t *parentPS);
CCALL void Jedi_Decloak(gentity_t *self);
CCALL void laserTrapStick(gentity_t *ent,vec3_t endpos,vec3_t normal);
