static void RegisterAssets( Vehicle_t *pVeh );
static qboolean Board( Vehicle_t *pVeh, bgEntity_t *pEnt );
static void ProcessMoveCommands( Vehicle_t *pVeh );
void WalkerYawAdjust( Vehicle_t *pVeh, playerState_t *riderPS, playerState_t *parentPS );
static void ProcessOrientCommands( Vehicle_t *pVeh );
static void AnimateVehicle( Vehicle_t *pVeh );
void G_SetWalkerVehicleFunctions( vehicleInfo_t *pVehInfo );
void G_CreateWalkerNPC( Vehicle_t **pVeh, const char *strAnimalType );
