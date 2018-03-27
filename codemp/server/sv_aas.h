#ifndef SV_AAS
#define SV_AAS

CCALL int SV_AAS_PointReachabilityAreaIndex(vec3_t point);
CCALL int SV_AAS_PredictRoute(void *route,int areanum,vec3_t origin,int goalareanum,int travelflags,int maxareas,int maxtime,int stopevent,int stopcontents,int stoptfl,int stopareanum);
CCALL int SV_AAS_AlternativeRouteGoals(vec3_t start,int startareanum,vec3_t goal,int goalareanum,int travelflags,void *altroutegoals,int maxaltroutegoals,int type);
CCALL int SV_AAS_PredictClientMovement(void *move,int entnum,vec3_t origin,int presencetype,int onground,vec3_t velocity,vec3_t cmdmove,int cmdframes,int maxframes,float frametime,int stopevent,int stopareanum,int visualize);
CCALL int SV_AAS_Swimming(vec3_t origin);
CCALL int SV_AAS_AreaTravelTimeToGoalArea(int areanum,vec3_t origin,int goalareanum,int travelflags);
CCALL int SV_AAS_AreaReachability(int areanum);
CCALL int SV_AAS_IntForBSPEpairKey(int ent,char *key,int *value);
CCALL int SV_AAS_FloatForBSPEpairKey(int ent,char *key,float *value);
CCALL int SV_AAS_VectorForBSPEpairKey(int ent,char *key,vec3_t v);
CCALL int SV_AAS_ValueForBSPEpairKey(int ent,char *key,char *value,int size);
CCALL int SV_AAS_NextBSPEntity(int ent);
CCALL int SV_AAS_PointContents(vec3_t point);
CCALL int SV_AAS_TraceAreas(vec3_t start,vec3_t end,int *areas,vec3_t *points,int maxareas);
CCALL int SV_AAS_PointAreaNum(vec3_t point);
CCALL float SV_AAS_Time(void);
CCALL void SV_AAS_PresenceTypeBoundingBox(int presencetype,vec3_t mins,vec3_t maxs);
CCALL int SV_AAS_Initialized(void);
CCALL void SV_AAS_EntityInfo(int entnum,void *info);
CCALL int SV_AAS_AreaInfo(int areanum,void *info);
CCALL int SV_AAS_BBoxAreas(vec3_t absmins,vec3_t absmaxs,int *areas,int maxareas);
CCALL int SV_AAS_EnableRoutingArea(int areanum,int enable);


CCALL void SV_RMG_Init(void);
CCALL int SV_CM_RegisterTerrain(const char *config);
CCALL qhandle_t SV_RE_RegisterSkin(const char *name);
CCALL int SV_PC_SourceFileAndLine(int handle,char *filename,int *line);
CCALL int SV_PC_ReadToken(int handle,pc_token_t *pc_token);
CCALL int SV_PC_FreeSource(int handle);
CCALL int SV_PC_LoadSource(const char *filename);
CCALL void SV_EA_ResetInput(int client);
CCALL void SV_EA_GetInput(int client,float thinktime,void *input);
CCALL void SV_EA_EndRegular(int client,float thinktime);
CCALL void SV_EA_View(int client,vec3_t viewangles);
CCALL void SV_EA_Move(int client,vec3_t dir,float speed);
CCALL void SV_EA_DelayedJump(int client);
CCALL void SV_EA_Jump(int client);
CCALL void SV_EA_SelectWeapon(int client,int weapon);
CCALL void SV_EA_MoveRight(int client);
CCALL void SV_EA_MoveLeft(int client);
CCALL void SV_EA_MoveBack(int client);
CCALL void SV_EA_MoveForward(int client);
CCALL void SV_EA_MoveDown(int client);
CCALL void SV_EA_MoveUp(int client);
CCALL void SV_EA_Crouch(int client);
CCALL void SV_EA_Respawn(int client);
CCALL void SV_EA_Use(int client);
CCALL void SV_EA_ForcePower(int client);
CCALL void SV_EA_Alt_Attack(int client);
CCALL void SV_EA_Attack(int client);
CCALL void SV_EA_Talk(int client);
CCALL void SV_EA_Gesture(int client);
CCALL void SV_EA_Action(int client,int action);
CCALL void SV_EA_Command(int client,char *command);
CCALL void SV_EA_SayTeam(int client,char *str);
CCALL void SV_EA_Say(int client,char *str);
CCALL const char *SV_SetActiveSubBSP( int index );

#endif