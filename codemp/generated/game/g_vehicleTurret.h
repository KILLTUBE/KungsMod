void VEH_TurretCheckFire( Vehicle_t *pVeh, gentity_t *parent, turretStats_t *turretStats, vehWeaponInfo_t *vehWeapon, int turretNum, int curMuzzle );
void VEH_TurretAnglesToEnemy( Vehicle_t *pVeh, int curMuzzle, float fSpeed, gentity_t *turretEnemy, qboolean bAILead, vec3_t desiredAngles );
qboolean VEH_TurretAim( Vehicle_t *pVeh, gentity_t *parent, gentity_t *turretEnemy, turretStats_t *turretStats, vehWeaponInfo_t *vehWeapon, int turretNum, int curMuzzle, vec3_t desiredAngles );
static qboolean VEH_TurretFindEnemies( Vehicle_t *pVeh, gentity_t *parent, turretStats_t *turretStats, int turretNum, int curMuzzle );
void VEH_TurretObeyPassengerControl( Vehicle_t *pVeh, gentity_t *parent, int turretNum );
void VEH_TurretThink( Vehicle_t *pVeh, gentity_t *parent, int turretNum );
