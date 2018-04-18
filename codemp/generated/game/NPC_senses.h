qboolean G_ClearLineOfSight( const vec3_t point1, const vec3_t point2, int ignore, int clipmask );
qboolean CanSee( gentity_t *ent );
qboolean InFront( vec3_t spot, vec3_t from, vec3_t fromAngles, float threshHold );
qboolean InFOV3( vec3_t spot, vec3_t from, vec3_t fromAngles, int hFOV, int vFOV );
qboolean InFOV2( vec3_t origin, gentity_t *from, int hFOV, int vFOV );
qboolean InFOV( gentity_t *ent, gentity_t *from, int hFOV, int vFOV );
qboolean InVisrange( gentity_t *ent );
visibility_t NPC_CheckVisibility( gentity_t *ent, int flags );
static int G_CheckSoundEvents( gentity_t *self, float maxHearDist, int ignoreAlert, qboolean mustHaveOwner, int minAlertLevel );
float G_GetLightLevel( vec3_t pos, vec3_t fromDir );
static int G_CheckSightEvents( gentity_t *self, int hFOV, int vFOV, float maxSeeDist, int ignoreAlert, qboolean mustHaveOwner, int minAlertLevel );
int G_CheckAlertEvents( gentity_t *self, qboolean checkSight, qboolean checkSound, float maxSeeDist, float maxHearDist, int ignoreAlert, qboolean mustHaveOwner, int minAlertLevel );
int NPC_CheckAlertEvents( qboolean checkSight, qboolean checkSound, int ignoreAlert, qboolean mustHaveOwner, int minAlertLevel );
qboolean G_CheckForDanger( gentity_t *self, int alertEvent );
qboolean NPC_CheckForDanger( int alertEvent );
void AddSoundEvent( gentity_t *owner, vec3_t position, float radius, alertEventLevel_e alertLevel, qboolean needLOS );
void AddSightEvent( gentity_t *owner, vec3_t position, float radius, alertEventLevel_e alertLevel, float addLight );
void ClearPlayerAlertEvents();
qboolean RemoveOldestAlert();
qboolean G_ClearLOS( gentity_t *self, const vec3_t start, const vec3_t end );
qboolean G_ClearLOS2( gentity_t *self, gentity_t *ent, const vec3_t end );
qboolean G_ClearLOS3( gentity_t *self, const vec3_t start, gentity_t *ent );
qboolean G_ClearLOS4( gentity_t *self, gentity_t *ent );
qboolean G_ClearLOS5( gentity_t *self, const vec3_t end );
float NPC_GetHFOVPercentage( vec3_t spot, vec3_t from, vec3_t facing, float hFOV );
float NPC_GetVFOVPercentage( vec3_t spot, vec3_t from, vec3_t facing, float vFOV );
int G_FindLocalInterestPoint( gentity_t *self );
void SP_target_interest( gentity_t *self );
