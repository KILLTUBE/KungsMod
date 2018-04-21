VEH_StartStrafeRam( pVeh_, Right_, Duration_ ) = ccall((:VEH_StartStrafeRam, lib), qboolean, ( Ptr{Vehicle_t}, qboolean, Int32,  ), pVeh_, Right_, Duration_ );
Update( pVeh_, pUcmd_ ) = ccall((:Update, lib), qboolean, ( Ptr{Vehicle_t}, Ptr{usercmd_t},  ), pVeh_, pUcmd_ );
ProcessMoveCommands( pVeh_ ) = ccall((:ProcessMoveCommands, lib), Void, ( Ptr{Vehicle_t},  ), pVeh_ );
ProcessOrientCommands( pVeh_ ) = ccall((:ProcessOrientCommands, lib), Void, ( Ptr{Vehicle_t},  ), pVeh_ );
AnimateVehicle( pVeh_ ) = ccall((:AnimateVehicle, lib), Void, ( Ptr{Vehicle_t},  ), pVeh_ );
AnimateRiders( pVeh_ ) = ccall((:AnimateRiders, lib), Void, ( Ptr{Vehicle_t},  ), pVeh_ );
G_SetSpeederVehicleFunctions( pVehInfo_ ) = ccall((:G_SetSpeederVehicleFunctions, lib), Void, ( Ptr{vehicleInfo_t},  ), pVehInfo_ );
G_CreateSpeederNPC( pVeh_, strType_ ) = ccall((:G_CreateSpeederNPC, lib), Void, ( Ptr{Ptr{Vehicle_t}}, Ptr{Char},  ), pVeh_, strType_ );
