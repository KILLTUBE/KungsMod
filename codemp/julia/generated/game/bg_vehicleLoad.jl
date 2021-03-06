BG_ClearVehicleParseParms() = ccall((:BG_ClearVehicleParseParms, lib), Void, (),  );
vfieldcmp( a_, b_ ) = ccall((:vfieldcmp, lib), Int32, ( Ptr{Void}, Ptr{Void},  ), a_, b_ );
BG_ParseVehWeaponParm( vehWeapon_, parmName_, pValue_ ) = ccall((:BG_ParseVehWeaponParm, lib), qboolean, ( Ptr{vehWeaponInfo_t}, Ptr{Char}, Ptr{Char},  ), vehWeapon_, parmName_, pValue_ );
VEH_LoadVehWeapon( vehWeaponName_ ) = ccall((:VEH_LoadVehWeapon, lib), Int32, ( Ptr{Char},  ), vehWeaponName_ );
VEH_VehWeaponIndexForName( vehWeaponName_ ) = ccall((:VEH_VehWeaponIndexForName, lib), Int32, ( Ptr{Char},  ), vehWeaponName_ );
BG_SetSharedVehicleFunctions( pVehInfo_ ) = ccall((:BG_SetSharedVehicleFunctions, lib), Void, ( Ptr{vehicleInfo_t},  ), pVehInfo_ );
BG_VehicleSetDefaults( vehicle_ ) = ccall((:BG_VehicleSetDefaults, lib), Void, ( Ptr{vehicleInfo_t},  ), vehicle_ );
BG_VehicleClampData( vehicle_ ) = ccall((:BG_VehicleClampData, lib), Void, ( Ptr{vehicleInfo_t},  ), vehicle_ );
BG_ParseVehicleParm( vehicle_, parmName_, pValue_ ) = ccall((:BG_ParseVehicleParm, lib), qboolean, ( Ptr{vehicleInfo_t}, Ptr{Char}, Ptr{Char},  ), vehicle_, parmName_, pValue_ );
VEH_LoadVehicle( vehicleName_ ) = ccall((:VEH_LoadVehicle, lib), Int32, ( Ptr{Char},  ), vehicleName_ );
VEH_VehicleIndexForName( vehicleName_ ) = ccall((:VEH_VehicleIndexForName, lib), Int32, ( Ptr{Char},  ), vehicleName_ );
BG_VehWeaponLoadParms() = ccall((:BG_VehWeaponLoadParms, lib), Void, (),  );
BG_VehicleLoadParms() = ccall((:BG_VehicleLoadParms, lib), Void, (),  );
BG_VehicleGetIndex( vehicleName_ ) = ccall((:BG_VehicleGetIndex, lib), Int32, ( Ptr{Char},  ), vehicleName_ );
BG_GetVehicleModelName( modelName_, vehicleName_, len_ ) = ccall((:BG_GetVehicleModelName, lib), Void, ( Ptr{Char}, Ptr{Char}, size_t,  ), modelName_, vehicleName_, len_ );
BG_GetVehicleSkinName( skinname_, len_ ) = ccall((:BG_GetVehicleSkinName, lib), Void, ( Ptr{Char}, Int32,  ), skinname_, len_ );
BG_GetTime() = ccall((:BG_GetTime, lib), Int32, (),  );
AttachRidersGeneric( pVeh_ ) = ccall((:AttachRidersGeneric, lib), Void, ( Ptr{Vehicle_t},  ), pVeh_ );
