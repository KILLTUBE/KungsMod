void touch_NULL( gentity_t *ent, gentity_t *other, trace_t *trace );
float WP_SpeedOfMissileForWeapon( int wp, qboolean alt_fire );
void W_TraceSetStart( gentity_t *ent, vec3_t start, vec3_t mins, vec3_t maxs );
static void WP_FireBryarPistol( gentity_t *ent, qboolean altFire );
void WP_FireTurretMissile( gentity_t *ent, vec3_t start, vec3_t dir, qboolean altFire, int damage, int velocity, int mod, gentity_t *ignore );
void WP_Explode( gentity_t *self );
void WP_FireGenericBlasterMissile( gentity_t *ent, vec3_t start, vec3_t dir, qboolean altFire, int damage, int velocity, int mod );
void WP_FireBlasterMissile( gentity_t *ent, vec3_t start, vec3_t dir, qboolean altFire );
void WP_FireTurboLaserMissile( gentity_t *ent, vec3_t start, vec3_t dir );
void WP_FireEmplacedMissile( gentity_t *ent, vec3_t start, vec3_t dir, qboolean altFire, gentity_t *ignore );
static void WP_FireBlaster( gentity_t *ent, qboolean altFire );
static void WP_DisruptorMainFire( gentity_t *ent );
qboolean G_CanDisruptify( gentity_t *ent );
void WP_DisruptorAltFire( gentity_t *ent );
static void WP_FireDisruptor( gentity_t *ent, qboolean altFire );
static void WP_BowcasterAltFire( gentity_t *ent );
static void WP_BowcasterMainFire( gentity_t *ent );
static void WP_FireBowcaster( gentity_t *ent, qboolean altFire );
static void WP_RepeaterMainFire( gentity_t *ent, vec3_t dir );
static void WP_RepeaterAltFire( gentity_t *ent );
static void WP_FireRepeater( gentity_t *ent, qboolean altFire );
static void WP_DEMP2_MainFire( gentity_t *ent );
void DEMP2_AltRadiusDamage( gentity_t *ent );
void DEMP2_AltDetonate( gentity_t *ent );
static void WP_DEMP2_AltFire( gentity_t *ent );
static void WP_FireDEMP2( gentity_t *ent, qboolean altFire );
static void WP_FlechetteMainFire( gentity_t *ent );
void prox_mine_think( gentity_t *ent );
static void WP_TraceSetStart( gentity_t *ent, vec3_t start, vec3_t mins, vec3_t maxs );
void WP_ExplosiveDie( gentity_t *self, gentity_t *inflictor, gentity_t *attacker, int damage, int mod );
void WP_flechette_alt_blow( gentity_t *ent );
static void WP_CreateFlechetteBouncyThing( vec3_t start, vec3_t fwd, gentity_t *self );
static void WP_FlechetteAltFire( gentity_t *self );
static void WP_FireFlechette( gentity_t *ent, qboolean altFire );
void rocketThink( gentity_t *ent );
void RocketDie( gentity_t *self, gentity_t *inflictor, gentity_t *attacker, int damage, int mod );
static void WP_FireRocket( gentity_t *ent, qboolean altFire );
void thermalDetonatorExplode( gentity_t *ent );
void thermalThinkStandard( gentity_t *ent );
gentity_t *WP_FireThermalDetonator( gentity_t *ent, qboolean altFire );
gentity_t *WP_DropThermal( gentity_t *ent );
qboolean WP_LobFire( gentity_t *self, vec3_t start, vec3_t target, vec3_t mins, vec3_t maxs, int clipmask, vec3_t velocity, qboolean tracePath, int ignoreEntNum, int enemyNum, float minSpeed, float maxSpeed, float idealSpeed, qboolean mustHit );
void laserTrapExplode( gentity_t *self );
void laserTrapDelayedExplode( gentity_t *self, gentity_t *inflictor, gentity_t *attacker, int damage, int meansOfDeath );
void touchLaserTrap( gentity_t *ent, gentity_t *other, trace_t *trace );
void proxMineThink( gentity_t *ent );
void laserTrapThink( gentity_t *ent );
void laserTrapStick( gentity_t *ent, vec3_t endpos, vec3_t normal );
void TrapThink( gentity_t *ent );
void CreateLaserTrap( gentity_t *laserTrap, vec3_t start, gentity_t *owner );
void WP_PlaceLaserTrap( gentity_t *ent, qboolean alt_fire );
void VectorNPos( vec3_t in, vec3_t out );
void charge_stick( gentity_t *self, gentity_t *other, trace_t *trace );
void DetPackBlow( gentity_t *self );
void DetPackPain( gentity_t *self, gentity_t *attacker, int damage );
void DetPackDie( gentity_t *self, gentity_t *inflictor, gentity_t *attacker, int damage, int mod );
void drop_charge( gentity_t *self, vec3_t start, vec3_t dir );
void BlowDetpacks( gentity_t *ent );
void RemoveDetpacks( gentity_t *ent );
qboolean CheatsOn();
void WP_DropDetPack( gentity_t *ent, qboolean alt_fire );
static void WP_FireConcussionAlt( gentity_t *ent );
static void WP_FireConcussion( gentity_t *ent );
void WP_FireStunBaton( gentity_t *ent, qboolean alt_fire );
void WP_FireMelee( gentity_t *ent, qboolean alt_fire );
void SnapVectorTowards( vec3_t v, vec3_t to );
qboolean LogAccuracyHit( gentity_t *target, gentity_t *attacker );
void CalcMuzzlePoint( gentity_t *ent, const vec3_t inForward, const vec3_t inRight, const vec3_t inUp, vec3_t muzzlePoint );
void WP_TouchVehMissile( gentity_t *ent, gentity_t *other, trace_t *trace );
void WP_CalcVehMuzzle( gentity_t *ent, int muzzleNum );
void WP_VehWeapSetSolidToOwner( gentity_t *self );
gentity_t *WP_FireVehicleWeapon( gentity_t *ent, vec3_t start, vec3_t dir, vehWeaponInfo_t *vehWeapon, qboolean alt_fire, qboolean isTurretWeap );
void G_VehMuzzleFireFX( gentity_t *ent, gentity_t *broadcaster, int muzzlesFired );
void G_EstimateCamPos( vec3_t viewAngles, vec3_t cameraFocusLoc, float viewheight, float thirdPersonRange, float thirdPersonHorzOffset, float vertOffset, float pitchOffset, int ignoreEntNum, vec3_t camPos );
void WP_GetVehicleCamPos( gentity_t *ent, gentity_t *pilot, vec3_t camPos );
void WP_VehLeadCrosshairVeh( gentity_t *camTraceEnt, vec3_t newEnd, const vec3_t dir, const vec3_t shotStart, vec3_t shotDir );
qboolean WP_VehCheckTraceFromCamPos( gentity_t *ent, const vec3_t shotStart, vec3_t shotDir );
void FireVehicleWeapon( gentity_t *ent, qboolean alt_fire );
void FireWeapon( gentity_t *ent, qboolean altFire );
static void WP_FireEmplaced( gentity_t *ent, qboolean altFire );
void emplaced_gun_use( gentity_t *self, gentity_t *other, trace_t *trace );
void emplaced_gun_realuse( gentity_t *self, gentity_t *other, gentity_t *activator );
void emplaced_gun_pain( gentity_t *self, gentity_t *attacker, int damage );
void emplaced_gun_update( gentity_t *self );
void emplaced_gun_die( gentity_t *self, gentity_t *inflictor, gentity_t *attacker, int damage, int mod );
void SP_emplaced_gun( gentity_t *ent );
