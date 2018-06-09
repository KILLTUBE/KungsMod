ObjectDie( self_, inflictor_, attacker_, damage_, meansOfDeath_ ) = ccall((:ObjectDie, lib), Void, ( Ptr{gentity_t}, Ptr{gentity_t}, Ptr{gentity_t}, Int32, Int32,  ), self_, inflictor_, attacker_, damage_, meansOfDeath_ );
G_HeavyMelee( attacker_ ) = ccall((:G_HeavyMelee, lib), qboolean, ( Ptr{gentity_t},  ), attacker_ );
G_GetHitLocation( target_, ppoint_ ) = ccall((:G_GetHitLocation, lib), Int32, ( Ptr{gentity_t}, vec3_t,  ), target_, ppoint_ );
ExplodeDeath( self_ ) = ccall((:ExplodeDeath, lib), Void, ( Ptr{gentity_t},  ), self_ );
ScorePlum( ent_, origin_, score_ ) = ccall((:ScorePlum, lib), Void, ( Ptr{gentity_t}, vec3_t, Int32,  ), ent_, origin_, score_ );
AddScore( ent_, origin_, score_ ) = ccall((:AddScore, lib), Void, ( Ptr{gentity_t}, vec3_t, Int32,  ), ent_, origin_, score_ );
TossClientWeapon( self_, direction_, speed_ ) = ccall((:TossClientWeapon, lib), Void, ( Ptr{gentity_t}, vec3_t, Float32,  ), self_, direction_, speed_ );
TossClientItems( self_ ) = ccall((:TossClientItems, lib), Void, ( Ptr{gentity_t},  ), self_ );
LookAtKiller( self_, inflictor_, attacker_ ) = ccall((:LookAtKiller, lib), Void, ( Ptr{gentity_t}, Ptr{gentity_t}, Ptr{gentity_t},  ), self_, inflictor_, attacker_ );
GibEntity( self_, killer_ ) = ccall((:GibEntity, lib), Void, ( Ptr{gentity_t}, Int32,  ), self_, killer_ );
BodyRid( ent_ ) = ccall((:BodyRid, lib), Void, ( Ptr{gentity_t},  ), ent_ );
body_die( self_, inflictor_, attacker_, damage_, meansOfDeath_ ) = ccall((:body_die, lib), Void, ( Ptr{gentity_t}, Ptr{gentity_t}, Ptr{gentity_t}, Int32, Int32,  ), self_, inflictor_, attacker_, damage_, meansOfDeath_ );
CheckAlmostCapture( self_, attacker_ ) = ccall((:CheckAlmostCapture, lib), Void, ( Ptr{gentity_t}, Ptr{gentity_t},  ), self_, attacker_ );
G_InKnockDown( ps_ ) = ccall((:G_InKnockDown, lib), qboolean, ( Ptr{playerState_t},  ), ps_ );
G_CheckSpecialDeathAnim( self_, point_, damage_, mod_, hitLoc_ ) = ccall((:G_CheckSpecialDeathAnim, lib), Int32, ( Ptr{gentity_t}, vec3_t, Int32, Int32, Int32,  ), self_, point_, damage_, mod_, hitLoc_ );
G_PickDeathAnim( self_, point_, damage_, mod_, hitLoc_ ) = ccall((:G_PickDeathAnim, lib), Int32, ( Ptr{gentity_t}, vec3_t, Int32, Int32, Int32,  ), self_, point_, damage_, mod_, hitLoc_ );
G_GetJediMaster() = ccall((:G_GetJediMaster, lib), Ptr{gentity_t}, (),  );
G_AlertTeam( victim_, attacker_, radius_, soundDist_ ) = ccall((:G_AlertTeam, lib), Void, ( Ptr{gentity_t}, Ptr{gentity_t}, Float32, Float32,  ), victim_, attacker_, radius_, soundDist_ );
G_DeathAlert( victim_, attacker_ ) = ccall((:G_DeathAlert, lib), Void, ( Ptr{gentity_t}, Ptr{gentity_t},  ), victim_, attacker_ );
DeathFX( ent_ ) = ccall((:DeathFX, lib), Void, ( Ptr{gentity_t},  ), ent_ );
G_CheckVictoryScript( self_ ) = ccall((:G_CheckVictoryScript, lib), Void, ( Ptr{gentity_t},  ), self_ );
G_AddPowerDuelScore( team_, score_ ) = ccall((:G_AddPowerDuelScore, lib), Void, ( Int32, Int32,  ), team_, score_ );
G_AddPowerDuelLoserScore( team_, score_ ) = ccall((:G_AddPowerDuelLoserScore, lib), Void, ( Int32, Int32,  ), team_, score_ );
player_die( self_, inflictor_, attacker_, damage_, meansOfDeath_ ) = ccall((:player_die, lib), Void, ( Ptr{gentity_t}, Ptr{gentity_t}, Ptr{gentity_t}, Int32, Int32,  ), self_, inflictor_, attacker_, damage_, meansOfDeath_ );
CheckArmor( ent_, damage_, dflags_ ) = ccall((:CheckArmor, lib), Int32, ( Ptr{gentity_t}, Int32, Int32,  ), ent_, damage_, dflags_ );
G_ApplyKnockback( targ_, newDir_, knockback_ ) = ccall((:G_ApplyKnockback, lib), Void, ( Ptr{gentity_t}, vec3_t, Float32,  ), targ_, newDir_, knockback_ );
RaySphereIntersections( origin_, radius_, point_, dir_, intersections_ ) = ccall((:RaySphereIntersections, lib), Int32, ( vec3_t, Float32, vec3_t, vec3_t, vec3_t,  ), origin_, radius_, point_, dir_, intersections_ );
G_GetDismemberLoc( self_, boltPoint_, limbType_ ) = ccall((:G_GetDismemberLoc, lib), Void, ( Ptr{gentity_t}, vec3_t, Int32,  ), self_, boltPoint_, limbType_ );
G_GetDismemberBolt( self_, boltPoint_, limbType_ ) = ccall((:G_GetDismemberBolt, lib), Void, ( Ptr{gentity_t}, vec3_t, Int32,  ), self_, boltPoint_, limbType_ );
LimbTouch( self_, other_, trace_ ) = ccall((:LimbTouch, lib), Void, ( Ptr{gentity_t}, Ptr{gentity_t}, Ptr{trace_t},  ), self_, other_, trace_ );
LimbThink( ent_ ) = ccall((:LimbThink, lib), Void, ( Ptr{gentity_t},  ), ent_ );
G_Dismember( ent_, enemy_, point_, limbType_, limbRollBase_, limbPitchBase_, deathAnim_, postDeath_ ) = ccall((:G_Dismember, lib), Void, ( Ptr{gentity_t}, Ptr{gentity_t}, vec3_t, Int32, Float32, Float32, Int32, qboolean,  ), ent_, enemy_, point_, limbType_, limbRollBase_, limbPitchBase_, deathAnim_, postDeath_ );
DismembermentTest( self_ ) = ccall((:DismembermentTest, lib), Void, ( Ptr{gentity_t},  ), self_ );
DismembermentByNum( self_, num_ ) = ccall((:DismembermentByNum, lib), Void, ( Ptr{gentity_t}, Int32,  ), self_, num_ );
G_GetHitQuad( self_, hitloc_ ) = ccall((:G_GetHitQuad, lib), Int32, ( Ptr{gentity_t}, vec3_t,  ), self_, hitloc_ );
G_GetHitLocFromSurfName( ent_, surfName_, hitLoc_, point_, dir_, bladeDir_, mod_ ) = ccall((:G_GetHitLocFromSurfName, lib), qboolean, ( Ptr{gentity_t}, Ptr{Char}, Ptr{Int32}, vec3_t, vec3_t, vec3_t, Int32,  ), ent_, surfName_, hitLoc_, point_, dir_, bladeDir_, mod_ );
G_CheckForDismemberment( ent_, enemy_, point_, damage_, deathAnim_, postDeath_ ) = ccall((:G_CheckForDismemberment, lib), Void, ( Ptr{gentity_t}, Ptr{gentity_t}, vec3_t, Int32, Int32, qboolean,  ), ent_, enemy_, point_, damage_, deathAnim_, postDeath_ );
G_LocationBasedDamageModifier( ent_, point_, mod_, dflags_, damage_ ) = ccall((:G_LocationBasedDamageModifier, lib), Void, ( Ptr{gentity_t}, vec3_t, Int32, Int32, Ptr{Int32},  ), ent_, point_, mod_, dflags_, damage_ );
G_ThereIsAMaster() = ccall((:G_ThereIsAMaster, lib), qboolean, (),  );
G_Knockdown( victim_ ) = ccall((:G_Knockdown, lib), Void, ( Ptr{gentity_t},  ), victim_ );
G_Damage( targ_, inflictor_, attacker_, dir_, point_, damage_, dflags_, mod_ ) = ccall((:G_Damage, lib), Void, ( Ptr{gentity_t}, Ptr{gentity_t}, Ptr{gentity_t}, vec3_t, vec3_t, Int32, Int32, Int32,  ), targ_, inflictor_, attacker_, dir_, point_, damage_, dflags_, mod_ );
CanDamage( targ_, origin_ ) = ccall((:CanDamage, lib), qboolean, ( Ptr{gentity_t}, vec3_t,  ), targ_, origin_ );
G_RadiusDamage( origin_, attacker_, damage_, radius_, ignore_, missile_, mod_ ) = ccall((:G_RadiusDamage, lib), qboolean, ( vec3_t, Ptr{gentity_t}, Float32, Float32, Ptr{gentity_t}, Ptr{gentity_t}, Int32,  ), origin_, attacker_, damage_, radius_, ignore_, missile_, mod_ );