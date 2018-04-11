#pragma once

#include "g_local.h"
#include "botlib/be_aas.h"
#include "bg_saga.h"
#include "ghoul2/G2.h"
#include "qcommon/q_shared.h"


// Bryar Pistol
//--------
#define BRYAR_PISTOL_VEL			1600
#define BRYAR_PISTOL_DAMAGE			10
#define BRYAR_CHARGE_UNIT			200.0f	// bryar charging gives us one more unit every 200ms--if you change this, you'll have to do the same in bg_pmove
#define BRYAR_ALT_SIZE				1.0f

// E11 Blaster
//---------
#define BLASTER_SPREAD				1.6f//1.2f
#define BLASTER_VELOCITY			2300
#define BLASTER_DAMAGE				20

// Tenloss Disruptor
//----------
#define DISRUPTOR_MAIN_DAMAGE			30 //40
#define DISRUPTOR_MAIN_DAMAGE_SIEGE		50
#define DISRUPTOR_NPC_MAIN_DAMAGE_CUT	0.25f

#define DISRUPTOR_ALT_DAMAGE			100 //125
#define DISRUPTOR_NPC_ALT_DAMAGE_CUT	0.2f
#define DISRUPTOR_ALT_TRACES			3		// can go through a max of 3 damageable(sp?) entities
#define DISRUPTOR_CHARGE_UNIT			50.0f	// distruptor charging gives us one more unit every 50ms--if you change this, you'll have to do the same in bg_pmove

// Wookiee Bowcaster
//----------
#define	BOWCASTER_DAMAGE			50
#define	BOWCASTER_VELOCITY			1300
#define BOWCASTER_SPLASH_DAMAGE		0
#define BOWCASTER_SPLASH_RADIUS		0
#define BOWCASTER_SIZE				2

#define BOWCASTER_ALT_SPREAD		5.0f
#define BOWCASTER_VEL_RANGE			0.3f
#define BOWCASTER_CHARGE_UNIT		200.0f	// bowcaster charging gives us one more unit every 200ms--if you change this, you'll have to do the same in bg_pmove

// Heavy Repeater
//----------
#define REPEATER_SPREAD				1.4f
#define	REPEATER_DAMAGE				14
#define	REPEATER_VELOCITY			1600

#define REPEATER_ALT_SIZE				3	// half of bbox size
#define	REPEATER_ALT_DAMAGE				60
#define REPEATER_ALT_SPLASH_DAMAGE		60
#define REPEATER_ALT_SPLASH_RADIUS		128
#define REPEATER_ALT_SPLASH_RAD_SIEGE	80
#define	REPEATER_ALT_VELOCITY			1100

// DEMP2
//----------
#define	DEMP2_DAMAGE				35
#define	DEMP2_VELOCITY				1800
#define	DEMP2_SIZE					2		// half of bbox size

#define DEMP2_ALT_DAMAGE			8 //12		// does 12, 36, 84 at each of the 3 charge levels.
#define DEMP2_CHARGE_UNIT			700.0f	// demp2 charging gives us one more unit every 700ms--if you change this, you'll have to do the same in bg_weapons
#define DEMP2_ALT_RANGE				4096
#define DEMP2_ALT_SPLASHRADIUS		256

// Golan Arms Flechette
//---------
#define FLECHETTE_SHOTS				5
#define FLECHETTE_SPREAD			4.0f
#define FLECHETTE_DAMAGE			12//15
#define FLECHETTE_VEL				3500
#define FLECHETTE_SIZE				1
#define FLECHETTE_MINE_RADIUS_CHECK	256
#define FLECHETTE_ALT_DAMAGE		60
#define FLECHETTE_ALT_SPLASH_DAM	60
#define FLECHETTE_ALT_SPLASH_RAD	128

// Personal Rocket Launcher
//---------
#define	ROCKET_VELOCITY				900
#define	ROCKET_DAMAGE				100
#define	ROCKET_SPLASH_DAMAGE		100
#define	ROCKET_SPLASH_RADIUS		160
#define ROCKET_SIZE					3
#define ROCKET_ALT_THINK_TIME		100

// Concussion Rifle
//---------
//primary
//man, this thing is too absurdly powerful. having to
//slash the values way down from sp.
#define	CONC_VELOCITY				3000
#define	CONC_DAMAGE					75 //150
#define	CONC_NPC_DAMAGE_EASY		40
#define	CONC_NPC_DAMAGE_NORMAL		80
#define	CONC_NPC_DAMAGE_HARD		100
#define	CONC_SPLASH_DAMAGE			40 //50
#define	CONC_SPLASH_RADIUS			200 //300
//alt
#define CONC_ALT_DAMAGE				25 //100
#define CONC_ALT_NPC_DAMAGE_EASY	20
#define CONC_ALT_NPC_DAMAGE_MEDIUM	35
#define CONC_ALT_NPC_DAMAGE_HARD	50

// Stun Baton
//--------------
#define STUN_BATON_DAMAGE			20
#define STUN_BATON_ALT_DAMAGE		20
#define STUN_BATON_RANGE			8

// Melee
//--------------
#define MELEE_SWING1_DAMAGE			10
#define MELEE_SWING2_DAMAGE			12
#define MELEE_RANGE					8

// ATST Main Gun
//--------------
#define ATST_MAIN_VEL				4000	//
#define ATST_MAIN_DAMAGE			25		//
#define ATST_MAIN_SIZE				3		// make it easier to hit things

// ATST Side Gun
//---------------
#define ATST_SIDE_MAIN_DAMAGE				75
#define ATST_SIDE_MAIN_VELOCITY				1300
#define ATST_SIDE_MAIN_NPC_DAMAGE_EASY		30
#define ATST_SIDE_MAIN_NPC_DAMAGE_NORMAL	40
#define ATST_SIDE_MAIN_NPC_DAMAGE_HARD		50
#define ATST_SIDE_MAIN_SIZE					4
#define ATST_SIDE_MAIN_SPLASH_DAMAGE		10	// yeah, pretty small, either zero out or make it worth having?
#define ATST_SIDE_MAIN_SPLASH_RADIUS		16	// yeah, pretty small, either zero out or make it worth having?

#define ATST_SIDE_ALT_VELOCITY				1100
#define ATST_SIDE_ALT_NPC_VELOCITY			600
#define ATST_SIDE_ALT_DAMAGE				130

#define ATST_SIDE_ROCKET_NPC_DAMAGE_EASY	30
#define ATST_SIDE_ROCKET_NPC_DAMAGE_NORMAL	50
#define ATST_SIDE_ROCKET_NPC_DAMAGE_HARD	90

#define	ATST_SIDE_ALT_SPLASH_DAMAGE			130
#define	ATST_SIDE_ALT_SPLASH_RADIUS			200
#define ATST_SIDE_ALT_ROCKET_SIZE			5
#define ATST_SIDE_ALT_ROCKET_SPLASH_SCALE	0.5f	// scales splash for NPC's

/*
======================================================================

LASER TRAP / TRIP MINE

======================================================================
*/
#define LT_DAMAGE			100
#define LT_SPLASH_RAD		256.0f
#define LT_SPLASH_DAM		105
#define LT_VELOCITY			900.0f
#define LT_SIZE				1.5f
#define LT_ALT_TIME			2000
#define	LT_ACTIVATION_DELAY	1000
#define	LT_DELAY_TIME		50


/*
======================================================================

THERMAL DETONATOR

======================================================================
*/

#define TD_DAMAGE			70 //only do 70 on a direct impact
#define TD_SPLASH_RAD		128
#define TD_SPLASH_DAM		90
#define TD_VELOCITY			900
#define TD_MIN_CHARGE		0.15f
#define TD_TIME				3000//6000
#define TD_ALT_TIME			3000

#define TD_ALT_DAMAGE		60//100
#define TD_ALT_SPLASH_RAD	128
#define TD_ALT_SPLASH_DAM	50//90
#define TD_ALT_VELOCITY		600
#define TD_ALT_MIN_CHARGE	0.15f
#define TD_ALT_TIME			3000

EXTERNC float g_cullDistance;

CCALL void SP_emplaced_gun(gentity_t *ent);
CCALL void emplaced_gun_die(gentity_t *self,gentity_t *inflictor,gentity_t *attacker,int damage,int mod);
CCALL void emplaced_gun_update(gentity_t *self);
CCALL void emplaced_gun_pain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void emplaced_gun_realuse(gentity_t *self,gentity_t *other,gentity_t *activator);
CCALL void emplaced_gun_use(gentity_t *self,gentity_t *other,trace_t *trace);
CCALL qboolean TryHeal(gentity_t *ent,gentity_t *target);
CCALL void FireWeapon(gentity_t *ent,qboolean altFire);
CCALL int BG_EmplacedView(vec3_t baseAngles,vec3_t angles,float *newYaw,float constraint);
CCALL void FireVehicleWeapon(gentity_t *ent,qboolean alt_fire);
CCALL qboolean WP_VehCheckTraceFromCamPos(gentity_t *ent,const vec3_t shotStart,vec3_t shotDir);
CCALL int BG_VehTraceFromCamPos(trace_t *camTrace,bgEntity_t *bgEnt,const vec3_t entOrg,const vec3_t shotStart,const vec3_t end,vec3_t newEnd,vec3_t shotDir,float bestDist);
CCALL void WP_VehLeadCrosshairVeh(gentity_t *camTraceEnt,vec3_t newEnd,const vec3_t dir,const vec3_t shotStart,vec3_t shotDir);
CCALL void WP_GetVehicleCamPos(gentity_t *ent,gentity_t *pilot,vec3_t camPos);
CCALL void G_EstimateCamPos(vec3_t viewAngles,vec3_t cameraFocusLoc,float viewheight,float thirdPersonRange,float thirdPersonHorzOffset,float vertOffset,float pitchOffset,int ignoreEntNum,vec3_t camPos);
CCALL void G_VehMuzzleFireFX(gentity_t *ent,gentity_t *broadcaster,int muzzlesFired);
CCALL gentity_t *WP_FireVehicleWeapon(gentity_t *ent,vec3_t start,vec3_t dir,vehWeaponInfo_t *vehWeapon,qboolean alt_fire,qboolean isTurretWeap);
CCALL void WP_VehWeapSetSolidToOwner(gentity_t *self);
CCALL void WP_CalcVehMuzzle(gentity_t *ent,int muzzleNum);
CCALL void WP_TouchVehMissile(gentity_t *ent,gentity_t *other,trace_t *trace);
CCALL void G_MissileImpact(gentity_t *ent,trace_t *trace);
CCALL void SnapVectorTowards(vec3_t v,vec3_t to);
CCALL void WP_FireMelee(gentity_t *ent,qboolean alt_fire);
CCALL void WP_FireStunBaton(gentity_t *ent,qboolean alt_fire);
CCALL void CalcMuzzlePoint(gentity_t *ent,const vec3_t inForward,const vec3_t inRight,const vec3_t inUp,vec3_t muzzlePoint);
CCALL void WP_DropDetPack(gentity_t *ent,qboolean alt_fire);
CCALL qboolean CheatsOn(void);
CCALL void RemoveDetpacks(gentity_t *ent);
CCALL void BlowDetpacks(gentity_t *ent);
CCALL void drop_charge(gentity_t *self,vec3_t start,vec3_t dir);
CCALL void DetPackDie(gentity_t *self,gentity_t *inflictor,gentity_t *attacker,int damage,int mod);
CCALL void DetPackPain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void charge_stick(gentity_t *self,gentity_t *other,trace_t *trace);
CCALL void DetPackBlow(gentity_t *self);
CCALL void DetPackBlow(gentity_t *self);
CCALL void VectorNPos(vec3_t in,vec3_t out);
CCALL void WP_PlaceLaserTrap(gentity_t *ent,qboolean alt_fire);
CCALL void CreateLaserTrap(gentity_t *laserTrap,vec3_t start,gentity_t *owner);
CCALL void TrapThink(gentity_t *ent);
CCALL void laserTrapThink(gentity_t *ent);
CCALL void proxMineThink(gentity_t *ent);
CCALL void touchLaserTrap(gentity_t *ent,gentity_t *other,trace_t *trace);
CCALL void laserTrapDelayedExplode(gentity_t *self,gentity_t *inflictor,gentity_t *attacker,int damage,int meansOfDeath);
CCALL qboolean WP_LobFire(gentity_t *self,vec3_t start,vec3_t target,vec3_t mins,vec3_t maxs,int clipmask,vec3_t velocity,qboolean tracePath,int ignoreEntNum,int enemyNum,float minSpeed,float maxSpeed,float idealSpeed,qboolean mustHit);
CCALL gentity_t *WP_DropThermal(gentity_t *ent);
CCALL gentity_t *WP_FireThermalDetonator(gentity_t *ent,qboolean altFire);
CCALL void thermalDetonatorExplode(gentity_t *ent);
CCALL void thermalThinkStandard(gentity_t *ent);
CCALL void thermalThinkStandard(gentity_t *ent);
CCALL void G_ExplodeMissile(gentity_t *ent);
CCALL void rocketThink(gentity_t *ent);
CCALL void WP_flechette_alt_blow(gentity_t *ent);
CCALL void WP_ExplosiveDie(gentity_t *self,gentity_t *inflictor,gentity_t *attacker,int damage,int mod);
CCALL void prox_mine_think(gentity_t *ent);
CCALL void DEMP2_AltDetonate(gentity_t *ent);
CCALL void DEMP2_AltRadiusDamage(gentity_t *ent);
CCALL void WP_DisruptorAltFire(gentity_t *ent);
CCALL qboolean G_CanDisruptify(gentity_t *ent);
CCALL qboolean LogAccuracyHit(gentity_t *target,gentity_t *attacker);
CCALL int G_GetHitLocation(gentity_t *target,vec3_t ppoint);
CCALL void WP_FireEmplacedMissile(gentity_t *ent,vec3_t start,vec3_t dir,qboolean altFire,gentity_t *ignore);
CCALL void WP_FireTurboLaserMissile(gentity_t *ent,vec3_t start,vec3_t dir);
CCALL void WP_FireBlasterMissile(gentity_t *ent,vec3_t start,vec3_t dir,qboolean altFire);
CCALL void WP_FireGenericBlasterMissile(gentity_t *ent,vec3_t start,vec3_t dir,qboolean altFire,int damage,int velocity,int mod);
CCALL void WP_Explode(gentity_t *self);
CCALL void WP_FireTurretMissile(gentity_t *ent,vec3_t start,vec3_t dir,qboolean altFire,int damage,int velocity,int mod,gentity_t *ignore);
CCALL void W_TraceSetStart(gentity_t *ent,vec3_t start,vec3_t mins,vec3_t maxs);
CCALL float WP_SpeedOfMissileForWeapon(int wp,qboolean alt_fire);
CCALL void RocketDie(gentity_t *self,gentity_t *inflictor,gentity_t *attacker,int damage,int mod);
CCALL void RocketDie(gentity_t *self,gentity_t *inflictor,gentity_t *attacker,int damage,int mod);
CCALL void laserTrapExplode(gentity_t *self);
CCALL void laserTrapExplode(gentity_t *self);
CCALL void touch_NULL(gentity_t *ent,gentity_t *other,trace_t *trace);
CCALL void laserTrapStick(gentity_t *ent,vec3_t endpos,vec3_t normal);
CCALL void laserTrapStick(gentity_t *ent,vec3_t endpos,vec3_t normal);
CCALL void Jedi_Decloak(gentity_t *self);
CCALL qboolean G_HeavyMelee(gentity_t *attacker);
CCALL qboolean G_BoxInBounds(vec3_t point,vec3_t mins,vec3_t maxs,vec3_t boundsMins,vec3_t boundsMaxs);
