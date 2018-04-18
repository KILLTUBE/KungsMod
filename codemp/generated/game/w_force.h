gentity_t *G_PreDefSound( vec3_t org, int pdSound );
void WP_InitForcePowers( gentity_t *ent );
void WP_SpawnInitForcePowers( gentity_t *ent );
int ForcePowerUsableOn( gentity_t *attacker, gentity_t *other, forcePowers_t forcePower );
qboolean WP_ForcePowerAvailable( gentity_t *self, forcePowers_t forcePower, int overrideAmt );
qboolean WP_ForcePowerInUse( gentity_t *self, forcePowers_t forcePower );
qboolean WP_ForcePowerUsable( gentity_t *self, forcePowers_t forcePower );
int WP_AbsorbConversion( gentity_t *attacked, int atdAbsLevel, gentity_t *attacker, int atPower, int atPowerLevel, int atForceSpent );
void WP_ForcePowerRegenerate( gentity_t *self, int overrideAmt );
void WP_ForcePowerStart( gentity_t *self, forcePowers_t forcePower, int overrideAmt );
void ForceHeal( gentity_t *self );
void WP_AddToClientBitflags( gentity_t *ent, int entNum );
void ForceTeamHeal( gentity_t *self );
void ForceTeamForceReplenish( gentity_t *self );
void ForceGrip( gentity_t *self );
void ForceSpeed( gentity_t *self, int forceDuration );
void ForceSeeing( gentity_t *self );
void ForceProtect( gentity_t *self );
void ForceAbsorb( gentity_t *self );
void ForceRage( gentity_t *self );
void ForceLightning( gentity_t *self );
void ForceLightningDamage( gentity_t *self, gentity_t *traceEnt, vec3_t dir, vec3_t impactPoint );
void ForceShootLightning( gentity_t *self );
void ForceDrain( gentity_t *self );
void ForceDrainDamage( gentity_t *self, gentity_t *traceEnt, vec3_t dir, vec3_t impactPoint );
int ForceShootDrain( gentity_t *self );
void ForceJumpCharge( gentity_t *self, usercmd_t *ucmd );
int WP_GetVelocityForForceJump( gentity_t *self, vec3_t jumpVel, usercmd_t *ucmd );
void ForceJump( gentity_t *self, usercmd_t *ucmd );
void WP_AddAsMindtricked( forcedata_t *fd, int entNum );
qboolean ForceTelepathyCheckDirectNPCTarget( gentity_t *self, trace_t *tr, qboolean *tookPower );
void ForceTelepathy( gentity_t *self );
void GEntity_UseFunc( gentity_t *self, gentity_t *other, gentity_t *activator );
qboolean CanCounterThrow( gentity_t *self, gentity_t *thrower, qboolean pull );
qboolean G_InGetUpAnim( playerState_t *ps );
void G_LetGoOfWall( gentity_t *ent );
void ForceThrow( gentity_t *self, qboolean pull );
void WP_ForcePowerStop( gentity_t *self, forcePowers_t forcePower );
void DoGripAction( gentity_t *self, forcePowers_t forcePower );
qboolean G_IsMindTricked( forcedata_t *fd, int client );
static void RemoveTrickedEnt( forcedata_t *fd, int client );
void WP_UpdateMindtrickEnts( gentity_t *self );
void WP_ForcePowerRun( gentity_t *self, forcePowers_t forcePower, usercmd_t *cmd );
int WP_DoSpecificPower( gentity_t *self, usercmd_t *ucmd, forcePowers_t forcepower );
void FindGenericEnemyIndex( gentity_t *self );
void SeekerDroneUpdate( gentity_t *self );
void HolocronUpdate( gentity_t *self );
void JediMasterUpdate( gentity_t *self );
qboolean WP_HasForcePowers( const playerState_t *ps );
qboolean G_SpecialRollGetup( gentity_t *self );
void WP_ForcePowersUpdate( gentity_t *self, usercmd_t *ucmd );
qboolean Jedi_DodgeEvasion( gentity_t *self, gentity_t *shooter, trace_t *tr, int hitLoc );
