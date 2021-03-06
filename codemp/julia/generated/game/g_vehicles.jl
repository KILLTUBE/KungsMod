Vehicle_SetAnim( ent_, setAnimParts_, anim_, setAnimFlags_, iBlend_ ) = ccall((:Vehicle_SetAnim, lib), Void, ( Ptr{gentity_t}, Int32, Int32, Int32, Int32,  ), ent_, setAnimParts_, anim_, setAnimFlags_, iBlend_ );
G_VehicleTrace( results_, start_, tMins_, tMaxs_, end_, passEntityNum_, contentmask_ ) = ccall((:G_VehicleTrace, lib), Void, ( Ptr{trace_t}, vec3_t, vec3_t, vec3_t, vec3_t, Int32, Int32,  ), results_, start_, tMins_, tMaxs_, end_, passEntityNum_, contentmask_ );
G_IsRidingVehicle( pEnt_ ) = ccall((:G_IsRidingVehicle, lib), Ptr{Vehicle_t}, ( Ptr{gentity_t},  ), pEnt_ );
G_CanJumpToEnemyVeh( pVeh_, pUcmd_ ) = ccall((:G_CanJumpToEnemyVeh, lib), Float32, ( Ptr{Vehicle_t}, Ptr{usercmd_t},  ), pVeh_, pUcmd_ );
G_VehicleSpawn( self_ ) = ccall((:G_VehicleSpawn, lib), Void, ( Ptr{gentity_t},  ), self_ );
G_AttachToVehicle( pEnt_, ucmd_ ) = ccall((:G_AttachToVehicle, lib), Void, ( Ptr{gentity_t}, Ptr{Ptr{usercmd_t}},  ), pEnt_, ucmd_ );
Animate( pVeh_ ) = ccall((:Animate, lib), Void, ( Ptr{Vehicle_t},  ), pVeh_ );
ValidateBoard( pVeh_, pEnt_ ) = ccall((:ValidateBoard, lib), qboolean, ( Ptr{Vehicle_t}, Ptr{bgEntity_t},  ), pVeh_, pEnt_ );
FighterStorePilotViewAngles( pVeh_, parent_ ) = ccall((:FighterStorePilotViewAngles, lib), Void, ( Ptr{Vehicle_t}, Ptr{bgEntity_t},  ), pVeh_, parent_ );
Board( pVeh_, pEnt_ ) = ccall((:Board, lib), qboolean, ( Ptr{Vehicle_t}, Ptr{bgEntity_t},  ), pVeh_, pEnt_ );
VEH_TryEject( pVeh_, parent_, ent_, ejectDir_, vExitPos_ ) = ccall((:VEH_TryEject, lib), qboolean, ( Ptr{Vehicle_t}, Ptr{gentity_t}, Ptr{gentity_t}, Int32, vec3_t,  ), pVeh_, parent_, ent_, ejectDir_, vExitPos_ );
G_EjectDroidUnit( pVeh_, kill_ ) = ccall((:G_EjectDroidUnit, lib), Void, ( Ptr{Vehicle_t}, qboolean,  ), pVeh_, kill_ );
Eject( pVeh_, pEnt_, forceEject_ ) = ccall((:Eject, lib), qboolean, ( Ptr{Vehicle_t}, Ptr{bgEntity_t}, qboolean,  ), pVeh_, pEnt_, forceEject_ );
EjectAll( pVeh_ ) = ccall((:EjectAll, lib), qboolean, ( Ptr{Vehicle_t},  ), pVeh_ );
StartDeathDelay( pVeh_, iDelayTimeOverride_ ) = ccall((:StartDeathDelay, lib), Void, ( Ptr{Vehicle_t}, Int32,  ), pVeh_, iDelayTimeOverride_ );
DeathUpdate( pVeh_ ) = ccall((:DeathUpdate, lib), Void, ( Ptr{Vehicle_t},  ), pVeh_ );
RegisterAssets( pVeh_ ) = ccall((:RegisterAssets, lib), Void, ( Ptr{Vehicle_t},  ), pVeh_ );
Initialize( pVeh_ ) = ccall((:Initialize, lib), qboolean, ( Ptr{Vehicle_t},  ), pVeh_ );
Update( pVeh_, pUmcd_ ) = ccall((:Update, lib), qboolean, ( Ptr{Vehicle_t}, Ptr{usercmd_t},  ), pVeh_, pUmcd_ );
UpdateRider( pVeh_, pRider_, pUmcd_ ) = ccall((:UpdateRider, lib), qboolean, ( Ptr{Vehicle_t}, Ptr{bgEntity_t}, Ptr{usercmd_t},  ), pVeh_, pRider_, pUmcd_ );
AttachRiders( pVeh_ ) = ccall((:AttachRiders, lib), Void, ( Ptr{Vehicle_t},  ), pVeh_ );
Ghost( pVeh_, pEnt_ ) = ccall((:Ghost, lib), Void, ( Ptr{Vehicle_t}, Ptr{bgEntity_t},  ), pVeh_, pEnt_ );
UnGhost( pVeh_, pEnt_ ) = ccall((:UnGhost, lib), Void, ( Ptr{Vehicle_t}, Ptr{bgEntity_t},  ), pVeh_, pEnt_ );
G_VehicleDamageBoxSizing( pVeh_ ) = ccall((:G_VehicleDamageBoxSizing, lib), Void, ( Ptr{Vehicle_t},  ), pVeh_ );
G_FlyVehicleImpactDir( veh_, trace_ ) = ccall((:G_FlyVehicleImpactDir, lib), Int32, ( Ptr{gentity_t}, Ptr{trace_t},  ), veh_, trace_ );
G_ShipSurfaceForSurfName( surfaceName_ ) = ccall((:G_ShipSurfaceForSurfName, lib), Int32, ( Ptr{Char},  ), surfaceName_ );
G_SetVehDamageFlags( veh_, shipSurf_, damageLevel_ ) = ccall((:G_SetVehDamageFlags, lib), Void, ( Ptr{gentity_t}, Int32, Int32,  ), veh_, shipSurf_, damageLevel_ );
G_VehicleSetDamageLocFlags( veh_, impactDir_, deathPoint_ ) = ccall((:G_VehicleSetDamageLocFlags, lib), Void, ( Ptr{gentity_t}, Int32, Int32,  ), veh_, impactDir_, deathPoint_ );
G_FlyVehicleDestroySurface( veh_, surface_ ) = ccall((:G_FlyVehicleDestroySurface, lib), qboolean, ( Ptr{gentity_t}, Int32,  ), veh_, surface_ );
G_FlyVehicleSurfaceDestruction( veh_, trace_, magnitude_, force_ ) = ccall((:G_FlyVehicleSurfaceDestruction, lib), Void, ( Ptr{gentity_t}, Ptr{trace_t}, Int32, qboolean,  ), veh_, trace_, magnitude_, force_ );
G_VehUpdateShields( targ_ ) = ccall((:G_VehUpdateShields, lib), Void, ( Ptr{gentity_t},  ), targ_ );
_SetParent( pVeh_, pParentEntity_ ) = ccall((:_SetParent, lib), Void, ( Ptr{Vehicle_t}, Ptr{bgEntity_t},  ), pVeh_, pParentEntity_ );
SetPilot( pVeh_, pPilot_ ) = ccall((:SetPilot, lib), Void, ( Ptr{Vehicle_t}, Ptr{bgEntity_t},  ), pVeh_, pPilot_ );
AddPassenger( pVeh_ ) = ccall((:AddPassenger, lib), qboolean, ( Ptr{Vehicle_t},  ), pVeh_ );
Inhabited( pVeh_ ) = ccall((:Inhabited, lib), qboolean, ( Ptr{Vehicle_t},  ), pVeh_ );
G_SetSharedVehicleFunctions( pVehInfo_ ) = ccall((:G_SetSharedVehicleFunctions, lib), Void, ( Ptr{vehicleInfo_t},  ), pVehInfo_ );
