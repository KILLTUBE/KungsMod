/* This file was automatically generated.  Do not edit! */
void CG_PredictPlayerState(void);
extern qboolean cg_vehPmoveSet;
extern pmove_t cg_vehPmove;
void CG_Cube(vec3_t mins,vec3_t maxs,vec3_t color,float alpha);
qboolean CG_UsingEWeb(void);
void CG_PmoveClientPointerUpdate();
#if defined(_PROFILE_ES_TO_PS)
extern int g_cgEStoPSTime;
#endif
extern playerState_t *cgSendPS[MAX_GENTITIES];
extern playerState_t cgSendPSPool[MAX_GENTITIES];
int CG_PointContents(const vec3_t point,int passEntityNum);
void CG_G2Trace(trace_t *result,const vec3_t start,const vec3_t mins,const vec3_t maxs,const vec3_t end,int skipNumber,int mask);
void CG_Trace(trace_t *result,const vec3_t start,const vec3_t mins,const vec3_t maxs,const vec3_t end,int skipNumber,int mask);
void BG_VehicleAdjustBBoxForOrientation(Vehicle_t *veh,vec3_t origin,vec3_t mins,vec3_t maxs,int clientNum,int tracemask,void(*localTrace)(trace_t *results,const vec3_t start,const vec3_t mins,const vec3_t maxs,const vec3_t end,int passEntityNum,int contentMask));
void CG_BuildSolidList(void);
