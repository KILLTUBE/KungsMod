qboolean VEH_StartStrafeRam( Vehicle_t *pVeh, qboolean Right, int Duration );
qboolean Update( Vehicle_t *pVeh, const usercmd_t *pUcmd );
static void ProcessMoveCommands( Vehicle_t *pVeh );
void ProcessOrientCommands( Vehicle_t *pVeh );
void AnimateVehicle( Vehicle_t *pVeh );
void AnimateRiders( Vehicle_t *pVeh );
void G_SetSpeederVehicleFunctions( vehicleInfo_t *pVehInfo );
void G_CreateSpeederNPC( Vehicle_t **pVeh, const char *strType );
