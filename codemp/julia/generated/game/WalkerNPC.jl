RegisterAssets( pVeh_ ) = ccall((:RegisterAssets, lib), Void, ( Ptr{Vehicle_t},  ), pVeh_ );
Board( pVeh_, pEnt_ ) = ccall((:Board, lib), qboolean, ( Ptr{Vehicle_t}, Ptr{bgEntity_t},  ), pVeh_, pEnt_ );
ProcessMoveCommands( pVeh_ ) = ccall((:ProcessMoveCommands, lib), Void, ( Ptr{Vehicle_t},  ), pVeh_ );
WalkerYawAdjust( pVeh_, riderPS_, parentPS_ ) = ccall((:WalkerYawAdjust, lib), Void, ( Ptr{Vehicle_t}, Ptr{playerState_t}, Ptr{playerState_t},  ), pVeh_, riderPS_, parentPS_ );
ProcessOrientCommands( pVeh_ ) = ccall((:ProcessOrientCommands, lib), Void, ( Ptr{Vehicle_t},  ), pVeh_ );
AnimateVehicle( pVeh_ ) = ccall((:AnimateVehicle, lib), Void, ( Ptr{Vehicle_t},  ), pVeh_ );
G_SetWalkerVehicleFunctions( pVehInfo_ ) = ccall((:G_SetWalkerVehicleFunctions, lib), Void, ( Ptr{vehicleInfo_t},  ), pVehInfo_ );
G_CreateWalkerNPC( pVeh_, strAnimalType_ ) = ccall((:G_CreateWalkerNPC, lib), Void, ( Ptr{Ptr{Vehicle_t}}, Ptr{Char},  ), pVeh_, strAnimalType_ );
