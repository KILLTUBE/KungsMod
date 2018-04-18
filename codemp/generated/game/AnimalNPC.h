static void DeathUpdate( Vehicle_t *pVeh );
static qboolean Update( Vehicle_t *pVeh, const usercmd_t *pUcmd );
static void ProcessMoveCommands( Vehicle_t *pVeh );
static void ProcessOrientCommands( Vehicle_t *pVeh );
void AnimalProcessOri( Vehicle_t *pVeh );
static void AnimateVehicle( Vehicle_t *pVeh );
static void AnimateRiders( Vehicle_t *pVeh );
void G_SetAnimalVehicleFunctions( vehicleInfo_t *pVehInfo );
void G_CreateAnimalNPC( Vehicle_t **pVeh, const char *strAnimalType );
