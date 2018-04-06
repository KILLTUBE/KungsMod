#pragma once

#include "../game/g_local.h"
#include "ai_main.h"

#define MAX_SPAWNPOINT_ARRAY 64


EXTERNC float botGlobalNavWeaponWeights[WP_NUM_WEAPONS];
EXTERNC gentity_t *gSpawnPoints[MAX_SPAWNPOINT_ARRAY];
EXTERNC int gSpawnPointNum;
EXTERNC int gLevelFlags;
EXTERNC int nodenum;
EXTERNC nodeobject_t nodetable[MAX_NODETABLE_SIZE];
EXTERNC int gLastPrintedIndex;
EXTERNC int gWPNum;
EXTERNC wpobject_t *gWPArray[MAX_WPARRAY_SIZE];
EXTERNC int gWPRenderedFrame;
EXTERNC float gBotEdit;
EXTERNC float gDeactivated;
EXTERNC float gWPRenderTime;


CCALL int AcceptBotCommand(char *cmd,gentity_t *pl);
CCALL gentity_t *GetNextSpawnInIndex(gentity_t *currentSpawn);
CCALL gentity_t *GetClosestSpawn(gentity_t *ent);
CCALL void LoadPath_ThisLevel(void);
CCALL void BeginAutoPathRoutine(void);
CCALL void G_RMGPathing(void);
CCALL qboolean G_BackwardAttachment(int start,int finalDestination,int insertAfter);
#if defined(ASCII_ART_DEBUG)
CCALL void CreateAsciiNodeTableRepresentation(int start,int end);
CCALL void CreateAsciiTableRepresentation();
#endif
#if defined(DEBUG_NODE_FILE)
CCALL void G_DebugNodeFile();
#endif
CCALL int G_RecursiveConnection(int start,int end,int weight,qboolean traceCheck,float baseHeight);
CCALL int G_NodeMatchingXY_BA(int x,int y,int final);
CCALL int G_NodeMatchingXY(float x,float y);
CCALL void G_NodeClearFlags(void);
CCALL void G_NodeClearForNext(void);
CCALL int G_NearestNodeToPoint(vec3_t point);
CCALL int SavePathData(const char *filename);
CCALL void FlagObjects(void);
CCALL int LoadPathData(const char *filename);
CCALL void CalculateJumpRoutes(void);
CCALL void CalculateWeightGoals(void);
CCALL int GetNearestVisibleWPToItem(vec3_t org,int ignore);
CCALL void CalculateSiegeGoals(void);
CCALL gentity_t *GetObjectThatTargets(gentity_t *ent);
CCALL void CalculatePaths(void);
CCALL int CanForceJumpTo(int baseindex,int testingindex,float distance);
CCALL int OrgVisibleCurve(vec3_t org1,vec3_t mins,vec3_t maxs,vec3_t org2,int ignore);
CCALL int RepairPaths(qboolean behindTheScenes);
CCALL int DoorBlockingSection(int start,int end);
CCALL int OpposingEnds(int start,int end);
CCALL int ConnectTrail(int startindex,int endindex,qboolean behindTheScenes);
CCALL int CanGetToVector(vec3_t org1,vec3_t org2,vec3_t mins,vec3_t maxs);
CCALL int NodeHere(vec3_t spot);
CCALL void WPFlagsModify(int wpnum,int flags);
CCALL void TeleportToWP(gentity_t *pl,int afterindex);
CCALL int CreateNewWP_InsertUnder(vec3_t origin,int flags,int afterindex);
CCALL int CreateNewWP_InTrail(vec3_t origin,int flags,int afterindex);
CCALL void RemoveWP_InTrail(int afterindex);
CCALL void RemoveAllWP(void);
CCALL void RemoveWP(void);
CCALL void CreateNewWP_FromObject(wpobject_t *wp);
CCALL void CreateNewWP(vec3_t origin,int flags);
CCALL void TransferWPData(int from,int to);
CCALL void BotWaypointRender(void);
CCALL void G_TestLine(vec3_t start,vec3_t end,int color,int time);
CCALL char *GetFlagStr(int flags);

