#ifndef SV_NAV
#define SV_NAV

CCALL void SV_Nav_SetPathsCalculated(qboolean newVal);
CCALL qboolean SV_Nav_GetPathsCalculated(void);
CCALL void SV_Nav_FlagAllNodes(int newFlag);
CCALL void SV_Nav_SetCheckedNode(int wayPoint,int ent,int value);
CCALL int SV_Nav_CheckedNode(int wayPoint,int ent);
CCALL void SV_Nav_ClearCheckedNodes(void);
CCALL void SV_Nav_CheckBlockedEdges(void);
CCALL int SV_Nav_GetNodeRadius(int nodeID);
CCALL int SV_Nav_GetBestPathBetweenEnts(sharedEntity_t *ent,sharedEntity_t *goal,int flags);
CCALL int SV_Nav_GetBestNodeAltRoute2(int startID,int endID,int rejectID);
CCALL int SV_Nav_GetBestNodeAltRoute(int startID,int endID,int *pathCost,int rejectID);
CCALL qboolean SV_Nav_RouteBlocked(int startID,int testEdgeID,int endID,int rejectRank);
CCALL void SV_Nav_CheckAllFailedEdges(void);
CCALL qboolean SV_Nav_CheckFailedEdge(failedEdge_t *failedEdge);
CCALL void SV_Nav_AddFailedEdge(int entID,int startID,int endID);
CCALL int SV_Nav_EdgeFailed(int startID,int endID);
CCALL void SV_Nav_ClearAllFailedEdges(void);
CCALL void SV_Nav_ClearFailedEdge(failedEdge_t *failedEdge);
CCALL qboolean SV_Nav_NodesAreNeighbors(int startID,int endID);
CCALL qboolean SV_Nav_NodeFailed(sharedEntity_t *ent,int nodeID);
CCALL void SV_Nav_AddFailedNode(sharedEntity_t *ent,int nodeID);
CCALL void SV_Nav_CheckFailedNodes(sharedEntity_t *ent);
CCALL int SV_Nav_GetProjectedNode(vec3_t origin,int nodeID);
CCALL int SV_Nav_GetEdgeCost(int startID,int endID);
CCALL int SV_Nav_GetPathCost(int startID,int endID);
CCALL qboolean SV_Nav_Connected(int startID,int endID);
CCALL int SV_Nav_GetNumNodes(void);
CCALL int SV_Nav_GetNodeEdge(int nodeID,int edge);
CCALL int SV_Nav_GetNodeNumEdges(int nodeID);
CCALL int SV_Nav_GetNodePosition(int nodeID,vec3_t out);
CCALL int SV_Nav_GetBestNode(int startID,int endID,int rejectID);
CCALL int SV_Nav_GetNearestNode(sharedEntity_t *ent,int lastID,int flags,int targetID);
CCALL void SV_Nav_ShowPath(int start,int end);
CCALL void SV_Nav_ShowEdges(void);
CCALL void SV_Nav_ShowNodes(void);
CCALL void SV_Nav_HardConnect(int first,int second);
CCALL void SV_Nav_CalculatePaths(qboolean recalc);
CCALL int SV_Nav_AddRawPoint(vec3_t point,int flags,int radius);
CCALL qboolean SV_Nav_Save(const char *filename,int checksum);
CCALL qboolean SV_Nav_Load(const char *filename,int checksum);
CCALL void SV_Nav_Free(void);
CCALL void SV_Nav_Init(void);

#endif