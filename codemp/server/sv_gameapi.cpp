/*
===========================================================================
Copyright (C) 2013 - 2015, OpenJK contributors

This file is part of the OpenJK source code.

OpenJK is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License version 2 as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, see <http://www.gnu.org/licenses/>.
===========================================================================
*/

// sv_gameapi.cpp  -- interface to the game dll
//Anything above this #include will be ignored by the compiler

#include "server.h"
#include "botlib/botlib.h"
#include "qcommon/stringed_ingame.h"
#include "qcommon/RoffSystem.h"
#include "ghoul2/ghoul2_shared.h"
#include "qcommon/cm_public.h"
#include "icarus/GameInterface.h"
#include "qcommon/timing.h"
#include "NPCNav/navigator.h"
#include "../rd-rend2/G2_API.h"

botlib_export_t	*botlib_export;

//extern "C" {
//	#include "game/g_local.h"
//}

// game interface
static gameExport_t *ge; // game export table
static vm_t *gvm; // game vm, valid for legacy and new api

//
// game vmMain calls
//

CCALL void G_InitGame					( int levelTime, int randomSeed, int restart );
CCALL void G_RunFrame					( int levelTime );
CCALL void G_ShutdownGame				( int restart );
CCALL void CheckExitRules				( void );

CCALL char *ClientConnect( int clientNum, qboolean firstTime, qboolean isBot );
CCALL void ClientBegin( int clientNum, qboolean allowTeamReset );
CCALL qboolean ClientUserinfoChanged( int clientNum );


//CCALL void G_ROFF_NotetrackCallback	( gentity_t *cent, const char *notetrack);

void GVM_InitGame( int levelTime, int randomSeed, int restart ) {
	VMSwap v( gvm );
	G_InitGame( levelTime, randomSeed, restart );
}

void GVM_ShutdownGame( int restart ) {
	VMSwap v( gvm );
	G_ShutdownGame( restart );
}

char *GVM_ClientConnect( int clientNum, qboolean firstTime, qboolean isBot ) {
	VMSwap v( gvm );
	
	return ClientConnect( clientNum, firstTime, isBot );
}

void GVM_ClientBegin( int clientNum ) {
	VMSwap v( gvm );
	ClientBegin( clientNum, qtrue );
}

qboolean GVM_ClientUserinfoChanged( int clientNum ) {
	VMSwap v( gvm );
	return ClientUserinfoChanged( clientNum );
}

CCALL void ClientDisconnect( int clientNum );

void GVM_ClientDisconnect( int clientNum ) {
	VMSwap v( gvm );
	ClientDisconnect( clientNum );
}

CCALL void ClientCommand( int clientNum );
void GVM_ClientCommand( int clientNum ) {
	VMSwap v( gvm );
	ClientCommand( clientNum );
}

CCALL void ClientThink( int clientNum, usercmd_t *ucmd );
void GVM_ClientThink( int clientNum, usercmd_t *ucmd ) {
	VMSwap v( gvm );
	ClientThink( clientNum, ucmd );
}

void GVM_RunFrame( int levelTime ) {
	VMSwap v( gvm );
	G_RunFrame( levelTime );
}

CCALL qboolean	ConsoleCommand( void );
qboolean GVM_ConsoleCommand( void ) {
	VMSwap v( gvm );
	return ConsoleCommand();
}

CCALL int			BotAIStartFrame					( int time );
int GVM_BotAIStartFrame( int time ) {
	VMSwap v( gvm );
	return BotAIStartFrame( time );
}


CCALL void		ROFF_NotetrackCallback			( int entID, const char *notetrack );
void GVM_ROFF_NotetrackCallback( int entID, const char *notetrack ) {
	VMSwap v( gvm );
	ge->ROFF_NotetrackCallback( entID, notetrack );
}

CCALL void		SpawnRMGEntity					( void );
void GVM_SpawnRMGEntity( void ) {
	VMSwap v( gvm );
	ge->SpawnRMGEntity();
}

CCALL int			G_ICARUS_PlaySound					( void );
int GVM_ICARUS_PlaySound( void ) {
	VMSwap v( gvm );
	return G_ICARUS_PlaySound();
}

CCALL qboolean	G_ICARUS_Set						( void );
qboolean GVM_ICARUS_Set( void ) {
	VMSwap v( gvm );
	return G_ICARUS_Set();
}

CCALL void		G_ICARUS_Lerp2Pos					( void );
void GVM_ICARUS_Lerp2Pos( void ) {
	VMSwap v( gvm );
	G_ICARUS_Lerp2Pos();
}

CCALL void		G_ICARUS_Lerp2Origin				( void );
void GVM_ICARUS_Lerp2Origin( void ) {
	VMSwap v( gvm );
	G_ICARUS_Lerp2Origin();
}

CCALL void		G_ICARUS_Lerp2Angles				( void );
void GVM_ICARUS_Lerp2Angles( void ) {
	VMSwap v( gvm );
	G_ICARUS_Lerp2Angles();
}

CCALL int			G_ICARUS_GetTag					( void );
int GVM_ICARUS_GetTag( void ) {
	VMSwap v( gvm );
	return G_ICARUS_GetTag();
}

CCALL void		G_ICARUS_Lerp2Start				( void );
void GVM_ICARUS_Lerp2Start( void ) {
	VMSwap v( gvm );
	G_ICARUS_Lerp2Start();
}

CCALL void		G_ICARUS_Lerp2End					( void );
void GVM_ICARUS_Lerp2End( void ) {
	VMSwap v( gvm );
	G_ICARUS_Lerp2End();
}

CCALL void		G_ICARUS_Use						( void );
void GVM_ICARUS_Use( void ) {
	VMSwap v( gvm );
	G_ICARUS_Use();
}

CCALL void		G_ICARUS_Kill						( void );
void GVM_ICARUS_Kill( void ) {
	VMSwap v( gvm );
	G_ICARUS_Kill();
}

CCALL void		G_ICARUS_Remove					( void );
void GVM_ICARUS_Remove( void ) {
	VMSwap v( gvm );
	G_ICARUS_Remove();
}

CCALL void		G_ICARUS_Play						( void );
void GVM_ICARUS_Play( void ) {
	VMSwap v( gvm );
	G_ICARUS_Play();
}

CCALL int			G_ICARUS_GetFloat					( void );
int GVM_ICARUS_GetFloat( void ) {
	VMSwap v( gvm );
	return G_ICARUS_GetFloat();
}

CCALL int			G_ICARUS_GetVector					( void );
int GVM_ICARUS_GetVector( void ) {
	VMSwap v( gvm );
	return G_ICARUS_GetVector();
}

CCALL int			G_ICARUS_GetString					( void );
int GVM_ICARUS_GetString( void ) {
	VMSwap v( gvm );
	return G_ICARUS_GetString();
}

CCALL void		G_ICARUS_SoundIndex				( void );
void GVM_ICARUS_SoundIndex( void ) {
	VMSwap v( gvm );
	G_ICARUS_SoundIndex();
}

CCALL int			G_ICARUS_GetSetIDForString			( void );
int GVM_ICARUS_GetSetIDForString( void ) {
	VMSwap v( gvm );
	return G_ICARUS_GetSetIDForString();
}

CCALL qboolean	G_NAV_ClearPathToPoint				( int entID, vec3_t pmins, vec3_t pmaxs, vec3_t point, int clipmask, int okToHitEnt );
qboolean GVM_NAV_ClearPathToPoint( int entID, vec3_t pmins, vec3_t pmaxs, vec3_t point, int clipmask, int okToHitEnt ) {
	VMSwap v( gvm );
	return G_NAV_ClearPathToPoint( entID, pmins, pmaxs, point, clipmask, okToHitEnt );
}

CCALL qboolean	G_NPC_ClearLOS2					( int entID, const vec3_t end );
qboolean GVM_NPC_ClearLOS2( int entID, const vec3_t end ) {
	VMSwap v( gvm );
	return G_NPC_ClearLOS2( entID, end );
}

CCALL int			NAVNEW_ClearPathBetweenPoints	( vec3_t start, vec3_t end, vec3_t mins, vec3_t maxs, int ignore, int clipmask );
int GVM_NAVNEW_ClearPathBetweenPoints( vec3_t start, vec3_t end, vec3_t mins, vec3_t maxs, int ignore, int clipmask ) {
	VMSwap v( gvm );
	return NAVNEW_ClearPathBetweenPoints( start, end, mins, maxs, ignore, clipmask );
}

CCALL qboolean	G_NAV_CheckNodeFailedForEnt		( int entID, int nodeNum );
qboolean GVM_NAV_CheckNodeFailedForEnt( int entID, int nodeNum ) {
	VMSwap v( gvm );
	return G_NAV_CheckNodeFailedForEnt( entID, nodeNum );
}

CCALL qboolean	G_EntIsUnlockedDoor			( int entityNum );
qboolean GVM_NAV_EntIsUnlockedDoor( int entityNum ) {
	VMSwap v( gvm );
	return G_EntIsUnlockedDoor( entityNum );
}

CCALL qboolean	G_EntIsDoor					( int entityNum );
qboolean GVM_NAV_EntIsDoor( int entityNum ) {
	VMSwap v( gvm );
	return G_EntIsDoor( entityNum );
}

CCALL qboolean	G_EntIsBreakable				( int entityNum );
qboolean GVM_NAV_EntIsBreakable( int entityNum ) {
	VMSwap v( gvm );
	return G_EntIsBreakable( entityNum );
}

CCALL qboolean	G_EntIsRemovableUsable			( int entNum );
qboolean GVM_NAV_EntIsRemovableUsable( int entNum ) {
	VMSwap v( gvm );
	return G_EntIsRemovableUsable( entNum );
}

CCALL void		CP_FindCombatPointWaypoints		( void );
void GVM_NAV_FindCombatPointWaypoints( void ) {
	VMSwap v( gvm );
	CP_FindCombatPointWaypoints();
}

CCALL int			BG_GetItemIndexByTag				( int tag, int type );
int GVM_BG_GetItemIndexByTag( int tag, int type ) {
	VMSwap v( gvm );
	return BG_GetItemIndexByTag( tag, type );
}

//
// game syscalls
//	only used by legacy mods!
//

// legacy syscall

siegePers_t sv_siegePersData = {qfalse, 0, 0};

extern float g_svCullDist;
int CM_ModelContents( clipHandle_t model, int subBSPIndex );
int CM_LoadSubBSP( const char *name, qboolean clientload );
int CM_FindSubBSP( int modelIndex );
char *CM_SubBSPEntityString( int index );
CCALL qboolean Q3_TaskIDPending( sharedEntity_t *ent, taskID_t taskType );
CCALL void Q3_TaskIDSet( sharedEntity_t *ent, taskID_t taskType, int taskID );
CCALL void Q3_TaskIDComplete( sharedEntity_t *ent, taskID_t taskType );
CCALL void Q3_SetVar( int taskID, int entID, const char *type_name, const char *data );
CCALL int Q3_VariableDeclared( const char *name );
CCALL int Q3_GetFloatVariable( const char *name, float *value );
CCALL int Q3_GetStringVariable( const char *name, const char **value );
CCALL int Q3_GetVectorVariable( const char *name, vec3_t value );
void SV_BotWaypointReception( int wpnum, wpobject_t **wps );
void SV_BotCalculatePaths( int rmg );

CCALL void SV_LocateGameData( sharedEntity_t *gEnts, int numGEntities, int sizeofGEntity_t, playerState_t *clients, int sizeofGameClient ) {
	sv.gentities = gEnts;
	sv.gentitySize = sizeofGEntity_t;
	sv.num_entities = numGEntities;

	sv.gameClients = clients;
	sv.gameClientSize = sizeofGameClient;
}

CCALL void SV_GameDropClient( int clientNum, const char *reason ) {
	if ( clientNum < 0 || clientNum >= sv_maxclients->integer ) {
		return;
	}
	SV_DropClient( svs.clients + clientNum, reason );
}

CCALL void SV_GameSendServerCommand( int clientNum, const char *text ) {
	if ( clientNum == -1 ) {
		SV_SendServerCommand( NULL, "%s", text );
	} else {
		if ( clientNum < 0 || clientNum >= sv_maxclients->integer ) {
			return;
		}
		SV_SendServerCommand( svs.clients + clientNum, "%s", text );
	}
}

CCALL qboolean SV_EntityContact( const vec3_t mins, const vec3_t maxs, const sharedEntity_t *gEnt, int capsule ) {
	const float	*origin, *angles;
	clipHandle_t	ch;
	trace_t			trace;

	// check for exact collision
	origin = gEnt->r.currentOrigin;
	angles = gEnt->r.currentAngles;

	ch = SV_ClipHandleForEntity( gEnt );
	CM_TransformedBoxTrace ( &trace, vec3_origin, vec3_origin, mins, maxs,
		ch, -1, origin, angles, capsule );

	return (qboolean)trace.startsolid;
}

CCALL void SV_SetBrushModel( sharedEntity_t *ent, const char *name ) {
	clipHandle_t	h;
	vec3_t			mins, maxs;

	if (!name)
	{
		Com_Error( ERR_DROP, "SV_SetBrushModel: NULL" );
	}

	if (name[0] == '*')
	{
		ent->s.modelindex = atoi( name + 1 );

		if (sv.mLocalSubBSPIndex != -1)
		{
			ent->s.modelindex += sv.mLocalSubBSPModelOffset;
		}

		h = CM_InlineModel( ent->s.modelindex );

		CM_ModelBounds(h, mins, maxs);

		VectorCopy (mins, ent->r.mins);
		VectorCopy (maxs, ent->r.maxs);
		ent->r.bmodel = qtrue;
		ent->r.contents = CM_ModelContents( h, -1 );
	}
	else if (name[0] == '#')
	{
		ent->s.modelindex = CM_LoadSubBSP(va("maps/%s.bsp", name + 1), qfalse);
		CM_ModelBounds( ent->s.modelindex, mins, maxs );

		VectorCopy (mins, ent->r.mins);
		VectorCopy (maxs, ent->r.maxs);
		ent->r.bmodel = qtrue;

		//rwwNOTE: We don't ever want to set contents -1, it includes CONTENTS_LIGHTSABER.
		//Lots of stuff will explode if there's a brush with CONTENTS_LIGHTSABER that isn't attached to a client owner.
		//ent->contents = -1;		// we don't know exactly what is in the brushes
		h = CM_InlineModel( ent->s.modelindex );
		ent->r.contents = CM_ModelContents( h, CM_FindSubBSP(ent->s.modelindex) );
	}
	else
	{
		Com_Error( ERR_DROP, "SV_SetBrushModel: %s isn't a brush model", name );
	}
}

CCALL qboolean SV_inPVSIgnorePortals( const vec3_t p1, const vec3_t p2 ) {
	int		leafnum, cluster;
//	int		area1, area2;
	byte	*mask;

	leafnum = CM_PointLeafnum( p1 );
	cluster = CM_LeafCluster( leafnum );
//	area1 = CM_LeafArea( leafnum );
	mask = CM_ClusterPVS( cluster );

	leafnum = CM_PointLeafnum( p2 );
	cluster = CM_LeafCluster( leafnum );
//	area2 = CM_LeafArea( leafnum );

	if ( mask && (!(mask[cluster>>3] & (1<<(cluster&7)) ) ) )
		return qfalse;

	return qtrue;
}

CCALL void SV_GetServerinfo( char *buffer, int bufferSize ) {
	if ( bufferSize < 1 ) {
		Com_Error( ERR_DROP, "SV_GetServerinfo: bufferSize == %i", bufferSize );
		return;
	}
	Q_strncpyz( buffer, Cvar_InfoString( CVAR_SERVERINFO ), bufferSize );
}
CCALL void SV_AdjustAreaPortalState( sharedEntity_t *ent, qboolean open ) {
	svEntity_t	*svEnt;

	svEnt = SV_SvEntityForGentity( ent );
	if ( svEnt->areanum2 == -1 )
		return;

	CM_AdjustAreaPortalState( svEnt->areanum, svEnt->areanum2, open );
}

CCALL void SV_GetUsercmd( int clientNum, usercmd_t *cmd ) {
	if ( clientNum < 0 || clientNum >= sv_maxclients->integer ) {
		Com_Error( ERR_DROP, "SV_GetUsercmd: bad clientNum:%i", clientNum );
		return;
	}
	*cmd = svs.clients[clientNum].lastUsercmd;
}

static sharedEntity_t gLocalModifier;
CCALL sharedEntity_t *ConvertedEntity( sharedEntity_t *ent ) { //Return an entity with the memory shifted around to allow reading/modifying VM memory
	int i = 0;

	assert(ent);

	gLocalModifier.s = ent->s;
	gLocalModifier.r = ent->r;
	while (i < NUM_TIDS)
	{
		gLocalModifier.taskID[i] = ent->taskID[i];
		i++;
	}
	i = 0;
	gLocalModifier.parms = (parms_t *)VM_ArgPtr((intptr_t)ent->parms);
	while (i < NUM_BSETS)
	{
		gLocalModifier.behaviorSet[i] = (char *)VM_ArgPtr((intptr_t)ent->behaviorSet[i]);
		i++;
	}
	i = 0;
	gLocalModifier.script_targetname = (char *)VM_ArgPtr((intptr_t)ent->script_targetname);
	gLocalModifier.delayScriptTime = ent->delayScriptTime;
	gLocalModifier.fullName = (char *)VM_ArgPtr((intptr_t)ent->fullName);
	gLocalModifier.targetname = (char *)VM_ArgPtr((intptr_t)ent->targetname);
	gLocalModifier.classname = (char *)VM_ArgPtr((intptr_t)ent->classname);

	gLocalModifier.ghoul2 = ent->ghoul2;

	return &gLocalModifier;
}

CCALL qboolean SV_GetEntityToken( char *buffer, int bufferSize ) {
	char *s;

	if ( sv.mLocalSubBSPIndex == -1 ) {
		s = COM_Parse( (const char **)&sv.entityParsePoint );
		Q_strncpyz( buffer, s, bufferSize );
		if ( !sv.entityParsePoint && !s[0] )
			return qfalse;
		else
			return qtrue;
	}
	else {
		s = COM_Parse( (const char **)&sv.mLocalSubBSPEntityParsePoint);
		Q_strncpyz( buffer, s, bufferSize );
		if ( !sv.mLocalSubBSPEntityParsePoint && !s[0] )
			return qfalse;
		else
			return qtrue;
	}
}

CCALL void SV_PrecisionTimerStart( void **timer ) {
	timing_c *newTimer = new timing_c; //create the new timer
	*timer = newTimer; //assign the pointer within the pointer to point at the mem addr of our new timer
	newTimer->Start(); //start the timer
}

CCALL int SV_PrecisionTimerEnd( void *timer ) {
	int r;
	timing_c *theTimer = (timing_c *)timer; //this is the pointer we assigned in start, so we can directly cast it back
	r = theTimer->End(); //get the result
	delete theTimer; //delete the timer since we're done with it
	return r; //return the result
}

CCALL void SV_RegisterSharedMemory( char *memory ) {
	sv.mSharedMemory = memory;
}

CCALL void SV_SetServerCull( float cullDistance ) {
	g_svCullDist = cullDistance;
}

CCALL void SV_SiegePersSet( siegePers_t *siegePers ) {
	sv_siegePersData = *siegePers;
}

CCALL void SV_SiegePersGet( siegePers_t *siegePers ) {
	*siegePers = sv_siegePersData;
}

CCALL qboolean SV_ROFF_Clean( void ) {
	return theROFFSystem.Clean( qfalse );
}

CCALL void SV_ROFF_UpdateEntities( void ) {
	theROFFSystem.UpdateEntities( qfalse );
}

CCALL int SV_ROFF_Cache( char *file ) {
	return theROFFSystem.Cache( file, qfalse );
}

CCALL qboolean SV_ROFF_Play( int entID, int roffID, qboolean doTranslation ) {
	return theROFFSystem.Play( entID, roffID, doTranslation, qfalse );
}

CCALL qboolean SV_ROFF_Purge_Ent( int entID ) {
	return theROFFSystem.PurgeEnt( entID, qfalse );
}

CCALL qboolean ICARUS_IsInitialized( int entID ) {
	if ( !gSequencers[entID] || !gTaskManagers[entID] )
		return qfalse;

	return qtrue;
}

CCALL qboolean ICARUS_MaintainTaskManager( int entID ) {
	if ( gTaskManagers[entID] ) {
		gTaskManagers[entID]->Update();
		return qtrue;
	}
	return qfalse;
}

CCALL qboolean ICARUS_IsRunning( int entID ) {
	if ( !gTaskManagers[entID] || !gTaskManagers[entID]->IsRunning() )
		return qfalse;
	return qtrue;
}

CCALL qboolean ICARUS_TaskIDPending( sharedEntity_t *ent, int taskID ) {
	return Q3_TaskIDPending( ent, (taskID_t)taskID );
}

CCALL void ICARUS_TaskIDSet( sharedEntity_t *ent, int taskType, int taskID ) {
	Q3_TaskIDSet( ent, (taskID_t)taskType, taskID );
}

CCALL void ICARUS_TaskIDComplete( sharedEntity_t *ent, int taskType ) {
	Q3_TaskIDComplete( ent, (taskID_t)taskType );
}

CCALL int ICARUS_GetStringVariable( const char *name, const char *value ) {
	const char *rec = (const char *)value;
	return Q3_GetStringVariable( name, (const char **)&rec );
}
CCALL int ICARUS_GetVectorVariable( const char *name, const vec3_t value ) {
	return Q3_GetVectorVariable( name, (float *)value );
}

CCALL const char *SV_SetActiveSubBSP( int index ) {
	if ( index >= 0 ) {
		sv.mLocalSubBSPIndex = CM_FindSubBSP( index );
		sv.mLocalSubBSPModelOffset = index;
		sv.mLocalSubBSPEntityParsePoint = CM_SubBSPEntityString( sv.mLocalSubBSPIndex );
		return sv.mLocalSubBSPEntityParsePoint;
	}

	sv.mLocalSubBSPIndex = -1;
	return NULL;
}



CCALL void SV_Nav_Init( void ) {
	navigator.Init();
}

CCALL void SV_Nav_Free( void ) {
	navigator.Free();
}

CCALL qboolean SV_Nav_Load( const char *filename, int checksum ) {
	return (qboolean)navigator.Load( filename, checksum );
}

CCALL qboolean SV_Nav_Save( const char *filename, int checksum ) {
	return (qboolean)navigator.Save( filename, checksum );
}

CCALL int SV_Nav_AddRawPoint( vec3_t point, int flags, int radius ) {
	return navigator.AddRawPoint( point, flags, radius );
}

CCALL void SV_Nav_CalculatePaths( qboolean recalc ) {
	navigator.CalculatePaths( recalc );
}

CCALL void SV_Nav_HardConnect( int first, int second ) {
	navigator.HardConnect( first, second );
}

CCALL void SV_Nav_ShowNodes( void ) {
	navigator.ShowNodes();
}

CCALL void SV_Nav_ShowEdges( void ) {
	navigator.ShowEdges();
}

CCALL void SV_Nav_ShowPath( int start, int end ) {
	navigator.ShowPath( start, end );
}

CCALL int SV_Nav_GetNearestNode( sharedEntity_t *ent, int lastID, int flags, int targetID ) {
	return navigator.GetNearestNode( ent, lastID, flags, targetID );
}

CCALL int SV_Nav_GetBestNode( int startID, int endID, int rejectID ) {
	return navigator.GetBestNode( startID, endID, rejectID );
}

CCALL int SV_Nav_GetNodePosition( int nodeID, vec3_t out ) {
	return navigator.GetNodePosition( nodeID, out );
}

CCALL int SV_Nav_GetNodeNumEdges( int nodeID ) {
	return navigator.GetNodeNumEdges( nodeID );
}

CCALL int SV_Nav_GetNodeEdge( int nodeID, int edge ) {
	return navigator.GetNodeEdge( nodeID, edge );
}

CCALL int SV_Nav_GetNumNodes( void ) {
	return navigator.GetNumNodes();
}

CCALL qboolean SV_Nav_Connected( int startID, int endID ) {
	return (qboolean)navigator.Connected( startID, endID );
}

CCALL int SV_Nav_GetPathCost( int startID, int endID ) {
	return navigator.GetPathCost( startID, endID );
}

CCALL int SV_Nav_GetEdgeCost( int startID, int endID ) {
	return navigator.GetEdgeCost( startID, endID );
}

CCALL int SV_Nav_GetProjectedNode( vec3_t origin, int nodeID ) {
	return navigator.GetProjectedNode( origin, nodeID );
}

CCALL void SV_Nav_CheckFailedNodes( sharedEntity_t *ent ) {
	navigator.CheckFailedNodes( ent );
}

CCALL void SV_Nav_AddFailedNode( sharedEntity_t *ent, int nodeID ) {
	navigator.AddFailedNode( ent, nodeID );
}

CCALL qboolean SV_Nav_NodeFailed( sharedEntity_t *ent, int nodeID ) {
	return navigator.NodeFailed( ent, nodeID );
}

CCALL qboolean SV_Nav_NodesAreNeighbors( int startID, int endID ) {
	return navigator.NodesAreNeighbors( startID, endID );
}

CCALL void SV_Nav_ClearFailedEdge( failedEdge_t *failedEdge ) {
	navigator.ClearFailedEdge( failedEdge );
}

CCALL void SV_Nav_ClearAllFailedEdges( void ) {
	navigator.ClearAllFailedEdges();
}

CCALL int SV_Nav_EdgeFailed( int startID, int endID ) {
	return navigator.EdgeFailed( startID, endID );
}

CCALL void SV_Nav_AddFailedEdge( int entID, int startID, int endID ) {
	navigator.AddFailedEdge( entID, startID, endID );
}

CCALL qboolean SV_Nav_CheckFailedEdge( failedEdge_t *failedEdge ) {
	return navigator.CheckFailedEdge( failedEdge );
}

CCALL void SV_Nav_CheckAllFailedEdges( void ) {
	navigator.CheckAllFailedEdges();
}

CCALL qboolean SV_Nav_RouteBlocked( int startID, int testEdgeID, int endID, int rejectRank ) {
	return navigator.RouteBlocked( startID, testEdgeID, endID, rejectRank );
}

CCALL int SV_Nav_GetBestNodeAltRoute( int startID, int endID, int *pathCost, int rejectID ) {
	return navigator.GetBestNodeAltRoute( startID, endID, pathCost, rejectID );
}

CCALL int SV_Nav_GetBestNodeAltRoute2( int startID, int endID, int rejectID ) {
	return navigator.GetBestNodeAltRoute( startID, endID, rejectID );
}

CCALL int SV_Nav_GetBestPathBetweenEnts( sharedEntity_t *ent, sharedEntity_t *goal, int flags ) {
	return navigator.GetBestPathBetweenEnts( ent, goal, flags );
}

CCALL int SV_Nav_GetNodeRadius( int nodeID ) {
	return navigator.GetNodeRadius( nodeID );
}

CCALL void SV_Nav_CheckBlockedEdges( void ) {
	navigator.CheckBlockedEdges();
}

CCALL void SV_Nav_ClearCheckedNodes( void ) {
	navigator.ClearCheckedNodes();
}

CCALL int SV_Nav_CheckedNode( int wayPoint, int ent ) {
	return navigator.CheckedNode( wayPoint, ent );
}

CCALL void SV_Nav_SetCheckedNode( int wayPoint, int ent, int value ) {
	navigator.SetCheckedNode( wayPoint, ent, value );
}

CCALL void SV_Nav_FlagAllNodes( int newFlag ) {
	navigator.FlagAllNodes( newFlag );
}

CCALL qboolean SV_Nav_GetPathsCalculated( void ) {
	return navigator.pathsCalculated;
}

CCALL void SV_Nav_SetPathsCalculated( qboolean newVal ) {
	navigator.pathsCalculated = newVal;
}

static int SV_BotLoadCharacter( char *charfile, float skill ) {
	return botlib_export->ai.BotLoadCharacter( charfile, skill );
}

static void SV_BotFreeCharacter( int character ) {
	botlib_export->ai.BotFreeCharacter( character );
}

static float SV_Characteristic_Float( int character, int index ) {
	return botlib_export->ai.Characteristic_Float( character, index );
}

static float SV_Characteristic_BFloat( int character, int index, float min, float max ) {
	return botlib_export->ai.Characteristic_BFloat( character, index, min, max );
}

static int SV_Characteristic_Integer( int character, int index ) {
	return botlib_export->ai.Characteristic_Integer( character, index );
}

static int SV_Characteristic_BInteger( int character, int index, int min, int max ) {
	return botlib_export->ai.Characteristic_BInteger( character, index, min, max );
}

static void SV_Characteristic_String( int character, int index, char *buf, int size ) {
	botlib_export->ai.Characteristic_String( character, index, buf, size );
}

static int SV_BotAllocChatState( void ) {
	return botlib_export->ai.BotAllocChatState();
}

static void SV_BotFreeChatState( int handle ) {
	botlib_export->ai.BotFreeChatState( handle );
}

static void SV_BotQueueConsoleMessage( int chatstate, int type, char *message ) {
	botlib_export->ai.BotQueueConsoleMessage( chatstate, type, message );
}

static void SV_BotRemoveConsoleMessage( int chatstate, int handle ) {
	botlib_export->ai.BotRemoveConsoleMessage( chatstate, handle );
}

static int SV_BotNextConsoleMessage( int chatstate, void *cm ) {
	return botlib_export->ai.BotNextConsoleMessage( chatstate, (bot_consolemessage_s *)cm );
}

static int SV_BotNumConsoleMessages( int chatstate ) {
	return botlib_export->ai.BotNumConsoleMessages( chatstate );
}

static void SV_BotInitialChat( int chatstate, char *type, int mcontext, char *var0, char *var1, char *var2, char *var3, char *var4, char *var5, char *var6, char *var7 ) {
	botlib_export->ai.BotInitialChat( chatstate, type, mcontext, var0, var1, var2, var3, var4, var5, var6, var7 );
}

static int SV_BotReplyChat( int chatstate, char *message, int mcontext, int vcontext, char *var0, char *var1, char *var2, char *var3, char *var4, char *var5, char *var6, char *var7 ) {
	return botlib_export->ai.BotReplyChat( chatstate, message, mcontext, vcontext, var0, var1, var2, var3, var4, var5, var6, var7 );
}

static int SV_BotChatLength( int chatstate ) {
	return botlib_export->ai.BotChatLength( chatstate );
}

static void SV_BotEnterChat( int chatstate, int client, int sendto ) {
	botlib_export->ai.BotEnterChat( chatstate, client, sendto );
}

static int SV_StringContains( char *str1, char *str2, int casesensitive ) {
	return botlib_export->ai.StringContains( str1, str2, casesensitive );
}

static int SV_BotFindMatch( char *str, void *match, unsigned long int context ) {
	return botlib_export->ai.BotFindMatch( str, (bot_match_s *)match, context );
}

static void SV_BotMatchVariable( void *match, int variable, char *buf, int size ) {
	botlib_export->ai.BotMatchVariable( (bot_match_s *)match, variable, buf, size );
}

static void SV_UnifyWhiteSpaces( char *string ) {
	botlib_export->ai.UnifyWhiteSpaces( string );
}

CCALL void SV_BotReplaceSynonyms( char *string, unsigned long int context ) {
	botlib_export->ai.BotReplaceSynonyms( string, context );
}

CCALL int SV_BotLoadChatFile( int chatstate, char *chatfile, char *chatname ) {
	return botlib_export->ai.BotLoadChatFile( chatstate, chatfile, chatname );
}

CCALL void SV_BotSetChatGender( int chatstate, int gender ) {
	botlib_export->ai.BotSetChatGender( chatstate, gender );
}

CCALL void SV_BotSetChatName( int chatstate, char *name, int client ) {
	botlib_export->ai.BotSetChatName( chatstate, name, client );
}

CCALL void SV_BotResetGoalState( int goalstate ) {
	botlib_export->ai.BotResetGoalState( goalstate );
}

CCALL void SV_BotResetAvoidGoals( int goalstate ) {
	botlib_export->ai.BotResetAvoidGoals( goalstate );
}

CCALL void SV_BotPushGoal( int goalstate, void *goal ) {
	botlib_export->ai.BotPushGoal( goalstate, (bot_goal_s *)goal );
}

CCALL void SV_BotPopGoal( int goalstate ) {
	botlib_export->ai.BotPopGoal( goalstate );
}

CCALL void SV_BotEmptyGoalStack( int goalstate ) {
	botlib_export->ai.BotEmptyGoalStack( goalstate );
}

CCALL void SV_BotDumpAvoidGoals( int goalstate ) {
	botlib_export->ai.BotDumpAvoidGoals( goalstate );
}

CCALL void SV_BotDumpGoalStack( int goalstate ) {
	botlib_export->ai.BotDumpGoalStack( goalstate );
}

CCALL void SV_BotGoalName( int number, char *name, int size ) {
	botlib_export->ai.BotGoalName( number, name, size );
}

CCALL int SV_BotGetTopGoal( int goalstate, void *goal ) {
	return botlib_export->ai.BotGetTopGoal( goalstate, (bot_goal_s *)goal );
}

CCALL int SV_BotGetSecondGoal( int goalstate, void *goal ) {
	return botlib_export->ai.BotGetSecondGoal( goalstate, (bot_goal_s *)goal );
}

CCALL int SV_BotChooseLTGItem( int goalstate, vec3_t origin, int *inventory, int travelflags ) {
	return botlib_export->ai.BotChooseLTGItem( goalstate, origin, inventory, travelflags );
}

CCALL int SV_BotChooseNBGItem( int goalstate, vec3_t origin, int *inventory, int travelflags, void *ltg, float maxtime ) {
	return botlib_export->ai.BotChooseNBGItem( goalstate, origin, inventory, travelflags, (bot_goal_s *)ltg, maxtime );
}

CCALL int SV_BotTouchingGoal( vec3_t origin, void *goal ) {
	return botlib_export->ai.BotTouchingGoal( origin, (bot_goal_s *)goal );
}

CCALL int SV_BotItemGoalInVisButNotVisible( int viewer, vec3_t eye, vec3_t viewangles, void *goal ) {
	return botlib_export->ai.BotItemGoalInVisButNotVisible( viewer, eye, viewangles, (bot_goal_s *)goal );
}

CCALL int SV_BotGetLevelItemGoal( int index, char *classname, void *goal ) {
	return botlib_export->ai.BotGetLevelItemGoal( index, classname, (bot_goal_s *)goal );
}

CCALL float SV_BotAvoidGoalTime( int goalstate, int number ) {
	return botlib_export->ai.BotAvoidGoalTime( goalstate, number );
}

CCALL void SV_BotInitLevelItems( void ) {
	botlib_export->ai.BotInitLevelItems();
}

CCALL void SV_BotUpdateEntityItems( void ) {
	botlib_export->ai.BotUpdateEntityItems();
}

CCALL int SV_BotLoadItemWeights( int goalstate, char *filename ) {
	return botlib_export->ai.BotLoadItemWeights( goalstate, filename );
}

CCALL void SV_BotFreeItemWeights( int goalstate ) {
	botlib_export->ai.BotFreeItemWeights( goalstate );
}

CCALL void SV_BotSaveGoalFuzzyLogic( int goalstate, char *filename ) {
	botlib_export->ai.BotSaveGoalFuzzyLogic( goalstate, filename );
}

CCALL int SV_BotAllocGoalState( int state ) {
	return botlib_export->ai.BotAllocGoalState( state );
}

CCALL void SV_BotFreeGoalState( int handle ) {
	botlib_export->ai.BotFreeGoalState( handle );
}

CCALL void SV_BotResetMoveState( int movestate ) {
	botlib_export->ai.BotResetMoveState( movestate );
}

CCALL void SV_BotMoveToGoal( void *result, int movestate, void *goal, int travelflags ) {
	botlib_export->ai.BotMoveToGoal( (bot_moveresult_s *)result, movestate, (bot_goal_s *)goal, travelflags );
}

CCALL int SV_BotMoveInDirection( int movestate, vec3_t dir, float speed, int type ) {
	return botlib_export->ai.BotMoveInDirection( movestate, dir, speed, type );
}

CCALL void SV_BotResetAvoidReach( int movestate ) {
	botlib_export->ai.BotResetAvoidReach( movestate );
}

CCALL void SV_BotResetLastAvoidReach( int movestate ) {
	botlib_export->ai.BotResetLastAvoidReach( movestate );
}

CCALL int SV_BotReachabilityArea( vec3_t origin, int testground ) {
	return botlib_export->ai.BotReachabilityArea( origin, testground );
}

CCALL int SV_BotMovementViewTarget( int movestate, void *goal, int travelflags, float lookahead, vec3_t target ) {
	return botlib_export->ai.BotMovementViewTarget( movestate, (bot_goal_s *)goal, travelflags, lookahead, target );
}

CCALL int SV_BotAllocMoveState( void ) {
	return botlib_export->ai.BotAllocMoveState();
}

CCALL void SV_BotFreeMoveState( int handle ) {
	botlib_export->ai.BotFreeMoveState( handle );
}

CCALL void SV_BotInitMoveState( int handle, void *initmove ) {
	botlib_export->ai.BotInitMoveState( handle, (bot_initmove_s *)initmove );
}

CCALL int SV_BotChooseBestFightWeapon( int weaponstate, int *inventory ) {
	return botlib_export->ai.BotChooseBestFightWeapon( weaponstate, inventory );
}

CCALL void SV_BotGetWeaponInfo( int weaponstate, int weapon, void *weaponinfo ) {
	botlib_export->ai.BotGetWeaponInfo( weaponstate, weapon, (weaponinfo_s *)weaponinfo );
}

CCALL int SV_BotLoadWeaponWeights( int weaponstate, char *filename ) {
	return botlib_export->ai.BotLoadWeaponWeights( weaponstate, filename );
}

CCALL int SV_BotAllocWeaponState( void ) {
	return botlib_export->ai.BotAllocWeaponState();
}

CCALL void SV_BotFreeWeaponState( int weaponstate ) {
	botlib_export->ai.BotFreeWeaponState( weaponstate );
}

CCALL void SV_BotResetWeaponState( int weaponstate ) {
	botlib_export->ai.BotResetWeaponState( weaponstate );
}

CCALL int SV_GeneticParentsAndChildSelection( int numranks, float *ranks, int *parent1, int *parent2, int *child ) {
	return botlib_export->ai.GeneticParentsAndChildSelection( numranks, ranks, parent1, parent2, child );
}

CCALL void SV_BotInterbreedGoalFuzzyLogic( int parent1, int parent2, int child ) {
	botlib_export->ai.BotInterbreedGoalFuzzyLogic( parent1, parent2, child );
}

CCALL void SV_BotMutateGoalFuzzyLogic( int goalstate, float range ) {
	botlib_export->ai.BotMutateGoalFuzzyLogic( goalstate, range );
}

CCALL int SV_BotGetNextCampSpotGoal( int num, void *goal ) {
	return botlib_export->ai.BotGetNextCampSpotGoal( num, (bot_goal_s *)goal );
}

CCALL int SV_BotGetMapLocationGoal( char *name, void *goal ) {
	return botlib_export->ai.BotGetMapLocationGoal( name, (bot_goal_s *)goal );
}

CCALL int SV_BotNumInitialChats( int chatstate, char *type ) {
	return botlib_export->ai.BotNumInitialChats( chatstate, type );
}

CCALL void SV_BotGetChatMessage( int chatstate, char *buf, int size ) {
	botlib_export->ai.BotGetChatMessage( chatstate, buf, size );
}

CCALL void SV_BotRemoveFromAvoidGoals( int goalstate, int number ) {
	botlib_export->ai.BotRemoveFromAvoidGoals( goalstate, number );
}

CCALL int SV_BotPredictVisiblePosition( vec3_t origin, int areanum, void *goal, int travelflags, vec3_t target ) {
	return botlib_export->ai.BotPredictVisiblePosition( origin, areanum, (bot_goal_s *)goal, travelflags, target );
}

CCALL void SV_BotSetAvoidGoalTime( int goalstate, int number, float avoidtime ) {
	botlib_export->ai.BotSetAvoidGoalTime( goalstate, number, avoidtime );
}

CCALL void SV_BotAddAvoidSpot( int movestate, vec3_t origin, float radius, int type ) {
	botlib_export->ai.BotAddAvoidSpot( movestate, origin, radius, type );
}

//CCALL int SV_BotLibSetup( void ) {
//	return botlib_export->BotLibSetup();
//}

//CCALL int SV_BotLibShutdown( void ) {
//	return botlib_export->BotLibShutdown();
//}

CCALL int SV_BotLibVarSet( char *var_name, char *value ) {
	return botlib_export->BotLibVarSet( var_name, value );
}

CCALL int SV_BotLibVarGet( char *var_name, char *value, int size ) {
	return botlib_export->BotLibVarGet( var_name, value, size );
}

CCALL int SV_BotLibDefine( char *string ) {
	return botlib_export->PC_AddGlobalDefine( string );
}

CCALL int SV_BotLibStartFrame( float time ) {
	return botlib_export->BotLibStartFrame( time );
}

CCALL int SV_BotLibLoadMap( const char *mapname ) {
	return botlib_export->BotLibLoadMap( mapname );
}

CCALL int SV_BotLibUpdateEntity( int ent, void *bue ) {
	return botlib_export->BotLibUpdateEntity( ent, (bot_entitystate_t *)bue );
}

CCALL int SV_BotLibTest( int parm0, char *parm1, vec3_t parm2, vec3_t parm3 ) {
	return botlib_export->Test( parm0, parm1, parm2, parm3 );
}

CCALL int SV_BotGetServerCommand( int clientNum, char *message, int size ) {
	return SV_BotGetConsoleMessage( clientNum, message, size );
}

CCALL void SV_BotUserCommand( int clientNum, usercmd_t *ucmd ) {
	SV_ClientThink( &svs.clients[clientNum], ucmd );
}

CCALL int SV_AAS_EnableRoutingArea( int areanum, int enable ) {
	return botlib_export->aas.AAS_EnableRoutingArea( areanum, enable );
}

CCALL int SV_AAS_BBoxAreas( vec3_t absmins, vec3_t absmaxs, int *areas, int maxareas ) {
	return botlib_export->aas.AAS_BBoxAreas( absmins, absmaxs, areas, maxareas );
}

CCALL int SV_AAS_AreaInfo( int areanum, void *info ) {
	return botlib_export->aas.AAS_AreaInfo( areanum, (aas_areainfo_s *)info );
}

CCALL void SV_AAS_EntityInfo( int entnum, void *info ) {
	botlib_export->aas.AAS_EntityInfo( entnum, (aas_entityinfo_s *)info );
}

CCALL int SV_AAS_Initialized( void ) {
	return botlib_export->aas.AAS_Initialized();
}

CCALL void SV_AAS_PresenceTypeBoundingBox( int presencetype, vec3_t mins, vec3_t maxs ) {
	botlib_export->aas.AAS_PresenceTypeBoundingBox( presencetype, mins, maxs );
}

CCALL float SV_AAS_Time( void ) {
	return botlib_export->aas.AAS_Time();
}

CCALL int SV_AAS_PointAreaNum( vec3_t point ) {
	return botlib_export->aas.AAS_PointAreaNum( point );
}

CCALL int SV_AAS_TraceAreas( vec3_t start, vec3_t end, int *areas, vec3_t *points, int maxareas ) {
	return botlib_export->aas.AAS_TraceAreas( start, end, areas, points, maxareas );
}

CCALL int SV_AAS_PointContents( vec3_t point ) {
	return botlib_export->aas.AAS_PointContents( point );
}

CCALL int SV_AAS_NextBSPEntity( int ent ) {
	return botlib_export->aas.AAS_NextBSPEntity( ent );
}

CCALL int SV_AAS_ValueForBSPEpairKey( int ent, char *key, char *value, int size ) {
	return botlib_export->aas.AAS_ValueForBSPEpairKey( ent, key, value, size );
}

CCALL int SV_AAS_VectorForBSPEpairKey( int ent, char *key, vec3_t v ) {
	return botlib_export->aas.AAS_VectorForBSPEpairKey( ent, key, v );
}

CCALL int SV_AAS_FloatForBSPEpairKey( int ent, char *key, float *value ) {
	return botlib_export->aas.AAS_FloatForBSPEpairKey( ent, key, value );
}

CCALL int SV_AAS_IntForBSPEpairKey( int ent, char *key, int *value ) {
	return botlib_export->aas.AAS_IntForBSPEpairKey( ent, key, value );
}

CCALL int SV_AAS_AreaReachability( int areanum ) {
	return botlib_export->aas.AAS_AreaReachability( areanum );
}

CCALL int SV_AAS_AreaTravelTimeToGoalArea( int areanum, vec3_t origin, int goalareanum, int travelflags ) {
	return botlib_export->aas.AAS_AreaTravelTimeToGoalArea( areanum, origin, goalareanum, travelflags );
}

CCALL int SV_AAS_Swimming( vec3_t origin ) {
	return botlib_export->aas.AAS_Swimming( origin );
}

CCALL int SV_AAS_PredictClientMovement( void *move, int entnum, vec3_t origin, int presencetype, int onground, vec3_t velocity, vec3_t cmdmove, int cmdframes, int maxframes, float frametime, int stopevent, int stopareanum, int visualize ) {
	return botlib_export->aas.AAS_PredictClientMovement( (aas_clientmove_s *)move, entnum, origin, presencetype, onground, velocity, cmdmove, cmdframes, maxframes, frametime, stopevent, stopareanum, visualize );
}

CCALL int SV_AAS_AlternativeRouteGoals( vec3_t start, int startareanum, vec3_t goal, int goalareanum, int travelflags, void *altroutegoals, int maxaltroutegoals, int type ) {
	return botlib_export->aas.AAS_AlternativeRouteGoals( start, startareanum, goal, goalareanum, travelflags, (aas_altroutegoal_s *)altroutegoals, maxaltroutegoals, type );
}

CCALL int SV_AAS_PredictRoute( void *route, int areanum, vec3_t origin, int goalareanum, int travelflags, int maxareas, int maxtime, int stopevent, int stopcontents, int stoptfl, int stopareanum ) {
	return botlib_export->aas.AAS_PredictRoute( (aas_predictroute_s *)route, areanum, origin, goalareanum, travelflags, maxareas, maxtime, stopevent, stopcontents, stoptfl, stopareanum );
}

CCALL int SV_AAS_PointReachabilityAreaIndex( vec3_t point ) {
	return botlib_export->aas.AAS_PointReachabilityAreaIndex( point );
}

CCALL void SV_EA_Say( int client, char *str ) {
	botlib_export->ea.EA_Say( client, str );
}

CCALL void SV_EA_SayTeam( int client, char *str ) {
	botlib_export->ea.EA_SayTeam( client, str );
}

CCALL void SV_EA_Command( int client, char *command ) {
	botlib_export->ea.EA_Command( client, command );
}

CCALL void SV_EA_Action( int client, int action ) {
	botlib_export->ea.EA_Action( client, action );
}

CCALL void SV_EA_Gesture( int client ) {
	botlib_export->ea.EA_Gesture( client );
}

CCALL void SV_EA_Talk( int client ) {
	botlib_export->ea.EA_Talk( client );
}

CCALL void SV_EA_Attack( int client ) {
	botlib_export->ea.EA_Attack( client );
}

CCALL void SV_EA_Alt_Attack( int client ) {
	botlib_export->ea.EA_Alt_Attack( client );
}

CCALL void SV_EA_ForcePower( int client ) {
	botlib_export->ea.EA_ForcePower( client );
}

CCALL void SV_EA_Use( int client ) {
	botlib_export->ea.EA_Use( client );
}

CCALL void SV_EA_Respawn( int client ) {
	botlib_export->ea.EA_Respawn( client );
}

CCALL void SV_EA_Crouch( int client ) {
	botlib_export->ea.EA_Crouch( client );
}

CCALL void SV_EA_MoveUp( int client ) {
	botlib_export->ea.EA_MoveUp( client );
}

CCALL void SV_EA_MoveDown( int client ) {
	botlib_export->ea.EA_MoveDown( client );
}

CCALL void SV_EA_MoveForward( int client ) {
	botlib_export->ea.EA_MoveForward( client );
}

CCALL void SV_EA_MoveBack( int client ) {
	botlib_export->ea.EA_MoveBack( client );
}

CCALL void SV_EA_MoveLeft( int client ) {
	botlib_export->ea.EA_MoveLeft( client );
}

CCALL void SV_EA_MoveRight( int client ) {
	botlib_export->ea.EA_MoveRight( client );
}

CCALL void SV_EA_SelectWeapon( int client, int weapon ) {
	botlib_export->ea.EA_SelectWeapon( client, weapon );
}

CCALL void SV_EA_Jump( int client ) {
	botlib_export->ea.EA_Jump( client );
}

CCALL void SV_EA_DelayedJump( int client ) {
	botlib_export->ea.EA_DelayedJump( client );
}

CCALL void SV_EA_Move( int client, vec3_t dir, float speed ) {
	botlib_export->ea.EA_Move( client, dir, speed );
}

CCALL void SV_EA_View( int client, vec3_t viewangles ) {
	botlib_export->ea.EA_View( client, viewangles );
}

CCALL void SV_EA_EndRegular( int client, float thinktime ) {
	botlib_export->ea.EA_EndRegular( client, thinktime );
}

CCALL void SV_EA_GetInput( int client, float thinktime, void *input ) {
	botlib_export->ea.EA_GetInput( client, thinktime, (bot_input_t *)input );
}

CCALL void SV_EA_ResetInput( int client ) {
	botlib_export->ea.EA_ResetInput( client );
}

CCALL int SV_PC_LoadSource( const char *filename ) {
	return botlib_export->PC_LoadSourceHandle( filename );
}

CCALL int SV_PC_FreeSource( int handle ) {
	return botlib_export->PC_FreeSourceHandle( handle );
}

CCALL int SV_PC_ReadToken( int handle, pc_token_t *pc_token ) {
	return botlib_export->PC_ReadTokenHandle( handle, pc_token );
}

CCALL int SV_PC_SourceFileAndLine( int handle, char *filename, int *line ) {
	return botlib_export->PC_SourceFileAndLine( handle, filename, line );
}

CCALL qhandle_t SV_R_RegisterSkin( const char *name ) {
	return R_RegisterServerSkin( name );
}

CCALL int SV_CM_RegisterTerrain( const char *config ) {
	return 0;
}

CCALL void SV_RMG_Init( void ) { }

static void SV_G2API_ListModelSurfaces( void *ghlInfo ) {
	G2API_ListSurfaces( (CGhoul2Info *)ghlInfo );
}

CCALL void SV_G2API_ListModelBones( void *ghlInfo, int frame ) {
	G2API_ListBones( (CGhoul2Info *)ghlInfo, frame );
}

CCALL void SV_G2API_SetGhoul2ModelIndexes( void *ghoul2, qhandle_t *modelList, qhandle_t *skinList ) {
	G2API_SetGhoul2ModelIndexes( *((CGhoul2Info_v *)ghoul2), modelList, skinList );
}

CCALL qboolean SV_G2API_HaveWeGhoul2Models( void *ghoul2) {
	return G2API_HaveWeGhoul2Models( *((CGhoul2Info_v *)ghoul2) );
}

CCALL qboolean SV_G2API_GetBoltMatrix( void *ghoul2, const int modelIndex, const int boltIndex, mdxaBone_t *matrix, const vec3_t angles, const vec3_t position, const int frameNum, qhandle_t *modelList, vec3_t scale ) {
	return G2API_GetBoltMatrix( *((CGhoul2Info_v *)ghoul2), modelIndex, boltIndex, matrix, angles, position, frameNum, modelList, scale );
}

CCALL qboolean SV_G2API_GetBoltMatrix_NoReconstruct( void *ghoul2, const int modelIndex, const int boltIndex, mdxaBone_t *matrix, const vec3_t angles, const vec3_t position, const int frameNum, qhandle_t *modelList, vec3_t scale ) {
	G2API_BoltMatrixReconstruction( qfalse );
	return G2API_GetBoltMatrix( *((CGhoul2Info_v *)ghoul2), modelIndex, boltIndex, matrix, angles, position, frameNum, modelList, scale );
}

CCALL qboolean SV_G2API_GetBoltMatrix_NoRecNoRot( void *ghoul2, const int modelIndex, const int boltIndex, mdxaBone_t *matrix, const vec3_t angles, const vec3_t position, const int frameNum, qhandle_t *modelList, vec3_t scale ) {
	G2API_BoltMatrixReconstruction( qfalse );
	G2API_BoltMatrixSPMethod( qtrue );
	return G2API_GetBoltMatrix( *((CGhoul2Info_v *)ghoul2), modelIndex, boltIndex, matrix, angles, position, frameNum, modelList, scale );
}

CCALL int SV_G2API_InitGhoul2Model( void **ghoul2Ptr, const char *fileName, int modelIndex, qhandle_t customSkin, qhandle_t customShader, int modelFlags, int lodBias ) {
#ifdef _FULL_G2_LEAK_CHECKING
		g_G2AllocServer = 1;
#endif
	return G2API_InitGhoul2Model( (CGhoul2Info_v **)ghoul2Ptr, fileName, modelIndex, customSkin, customShader, modelFlags, lodBias );
}

CCALL qboolean SV_G2API_SetSkin( void *ghoul2, int modelIndex, qhandle_t customSkin, qhandle_t renderSkin ) {
	CGhoul2Info_v &g2 = *((CGhoul2Info_v *)ghoul2);
	return G2API_SetSkin( g2, modelIndex, customSkin, renderSkin );
}

CCALL void SV_G2API_CollisionDetect( CollisionRecord_t *collRecMap, void* ghoul2, const vec3_t angles, const vec3_t position, int frameNumber, int entNum, vec3_t rayStart, vec3_t rayEnd, vec3_t scale, int traceFlags, int useLod, float fRadius ) {
	G2API_CollisionDetect( collRecMap, *((CGhoul2Info_v *)ghoul2), angles, position, frameNumber, entNum, rayStart, rayEnd, scale, G2VertSpaceServer, traceFlags, useLod, fRadius );
}

CCALL void SV_G2API_CollisionDetectCache( CollisionRecord_t *collRecMap, void* ghoul2, const vec3_t angles, const vec3_t position, int frameNumber, int entNum, vec3_t rayStart, vec3_t rayEnd, vec3_t scale, int traceFlags, int useLod, float fRadius ) {
	G2API_CollisionDetectCache( collRecMap, *((CGhoul2Info_v *)ghoul2), angles, position, frameNumber, entNum, rayStart, rayEnd, scale, G2VertSpaceServer, traceFlags, useLod, fRadius );
}

CCALL void SV_G2API_CleanGhoul2Models( void **ghoul2Ptr ) {
#ifdef _FULL_G2_LEAK_CHECKING
		g_G2AllocServer = 1;
#endif
	G2API_CleanGhoul2Models( (CGhoul2Info_v **)ghoul2Ptr );
}

CCALL qboolean SV_G2API_SetBoneAngles( void *ghoul2, int modelIndex, const char *boneName, const vec3_t angles, const int flags, const int up, const int right, const int forward, qhandle_t *modelList, int blendTime , int currentTime ) {
	return G2API_SetBoneAngles( *((CGhoul2Info_v *)ghoul2), modelIndex, boneName, angles, flags, (const Eorientations)up, (const Eorientations)right, (const Eorientations)forward, modelList, blendTime , currentTime );
}

CCALL qboolean SV_G2API_SetBoneAnim( void *ghoul2, const int modelIndex, const char *boneName, const int startFrame, const int endFrame, const int flags, const float animSpeed, const int currentTime, const float setFrame, const int blendTime ) {
	return G2API_SetBoneAnim( *((CGhoul2Info_v *)ghoul2), modelIndex, boneName, startFrame, endFrame, flags, animSpeed, currentTime, setFrame, blendTime );
}

CCALL qboolean SV_G2API_GetBoneAnim( void *ghoul2, const char *boneName, const int currentTime, float *currentFrame, int *startFrame, int *endFrame, int *flags, float *animSpeed, int *modelList, const int modelIndex ) {
	CGhoul2Info_v &g2 = *((CGhoul2Info_v *)ghoul2);
	return G2API_GetBoneAnim( g2, modelIndex, boneName, currentTime, currentFrame, startFrame, endFrame, flags, animSpeed, modelList );
}

CCALL void SV_G2API_GetGLAName( void *ghoul2, int modelIndex, char *fillBuf ) {
	assert( ghoul2 && "invalid g2 handle" );

	char *tmp = G2API_GetGLAName( *((CGhoul2Info_v *)ghoul2), modelIndex );
	if ( tmp ) {
		strcpy( fillBuf, tmp );
	}
}

CCALL int SV_G2API_CopyGhoul2Instance( void *g2From, void *g2To, int modelIndex ) {
	return G2API_CopyGhoul2Instance( *((CGhoul2Info_v *)g2From), *((CGhoul2Info_v *)g2To), modelIndex );
}

CCALL void SV_G2API_CopySpecificGhoul2Model( void *g2From, int modelFrom, void *g2To, int modelTo ) {
	G2API_CopySpecificG2Model( *((CGhoul2Info_v *)g2From), modelFrom, *((CGhoul2Info_v *)g2To), modelTo );
}

CCALL void SV_G2API_DuplicateGhoul2Instance( void *g2From, void **g2To ) {
#ifdef _FULL_G2_LEAK_CHECKING
		g_G2AllocServer = 1;
#endif
	G2API_DuplicateGhoul2Instance( *((CGhoul2Info_v *)g2From), (CGhoul2Info_v **)g2To );
}

CCALL qboolean SV_G2API_HasGhoul2ModelOnIndex( void *ghlInfo, int modelIndex ) {
	return G2API_HasGhoul2ModelOnIndex( (CGhoul2Info_v **)ghlInfo, modelIndex );
}

CCALL qboolean SV_G2API_RemoveGhoul2Model( void *ghlInfo, int modelIndex ) {
#ifdef _FULL_G2_LEAK_CHECKING
		g_G2AllocServer = 1;
#endif
	return G2API_RemoveGhoul2Model( (CGhoul2Info_v **)ghlInfo, modelIndex );
}

CCALL qboolean SV_G2API_RemoveGhoul2Models( void *ghlInfo ) {
#ifdef _FULL_G2_LEAK_CHECKING
	g_G2AllocServer = 1;
#endif
	return G2API_RemoveGhoul2Models( (CGhoul2Info_v **)ghlInfo );
}

CCALL int SV_G2API_Ghoul2Size( void *ghlInfo ) {
	return G2API_Ghoul2Size( *((CGhoul2Info_v *)ghlInfo) );
}

CCALL int SV_G2API_AddBolt( void *ghoul2, int modelIndex, const char *boneName ) {
	return G2API_AddBolt( *((CGhoul2Info_v *)ghoul2), modelIndex, boneName );
}

CCALL void SV_G2API_SetBoltInfo( void *ghoul2, int modelIndex, int boltInfo ) {
	G2API_SetBoltInfo( *((CGhoul2Info_v *)ghoul2), modelIndex, boltInfo );
}

CCALL qboolean SV_G2API_SetRootSurface( void *ghoul2, const int modelIndex, const char *surfaceName ) {
	return G2API_SetRootSurface( *((CGhoul2Info_v *)ghoul2), modelIndex, surfaceName );
}

CCALL qboolean SV_G2API_SetSurfaceOnOff( void *ghoul2, const char *surfaceName, const int flags ) {
	return G2API_SetSurfaceOnOff( *((CGhoul2Info_v *)ghoul2), surfaceName, flags );
}

CCALL qboolean SV_G2API_SetNewOrigin( void *ghoul2, const int boltIndex ) {
	return G2API_SetNewOrigin( *((CGhoul2Info_v *)ghoul2), boltIndex );
}

CCALL qboolean SV_G2API_DoesBoneExist( void *ghoul2, int modelIndex, const char *boneName ) {
	CGhoul2Info_v &g2 = *((CGhoul2Info_v *)ghoul2);
	return G2API_DoesBoneExist( g2, modelIndex, boneName );
}

CCALL int SV_G2API_GetSurfaceRenderStatus( void *ghoul2, const int modelIndex, const char *surfaceName ) {
	CGhoul2Info_v &g2 = *((CGhoul2Info_v *)ghoul2);
	return G2API_GetSurfaceRenderStatus( g2, modelIndex, surfaceName );
}

CCALL void SV_G2API_AbsurdSmoothing( void *ghoul2, qboolean status ) {
	CGhoul2Info_v &g2 = *((CGhoul2Info_v *)ghoul2);
	G2API_AbsurdSmoothing( g2, status );
}

CCALL void SV_G2API_SetRagDoll( void *ghoul2, sharedRagDollParams_t *params ) {
	CRagDollParams rdParams;

	if ( !params ) {
		G2API_ResetRagDoll( *((CGhoul2Info_v *)ghoul2) );
		return;
	}

	VectorCopy( params->angles, rdParams.angles );
	VectorCopy( params->position, rdParams.position );
	VectorCopy( params->scale, rdParams.scale );
	VectorCopy( params->pelvisAnglesOffset, rdParams.pelvisAnglesOffset );
	VectorCopy( params->pelvisPositionOffset, rdParams.pelvisPositionOffset );

	rdParams.fImpactStrength = params->fImpactStrength;
	rdParams.fShotStrength = params->fShotStrength;
	rdParams.me = params->me;

	rdParams.startFrame = params->startFrame;
	rdParams.endFrame = params->endFrame;

	rdParams.collisionType = params->collisionType;
	rdParams.CallRagDollBegin = params->CallRagDollBegin;

	rdParams.RagPhase = (CRagDollParams::ERagPhase)params->RagPhase;
	rdParams.effectorsToTurnOff = (CRagDollParams::ERagEffector)params->effectorsToTurnOff;

	G2API_SetRagDoll( *((CGhoul2Info_v *)ghoul2), &rdParams );
}

CCALL void SV_G2API_AnimateG2Models( void *ghoul2, int time, sharedRagDollUpdateParams_t *params ) {
	CRagDollUpdateParams rduParams;

	if ( !params )
		return;

	VectorCopy( params->angles, rduParams.angles );
	VectorCopy( params->position, rduParams.position );
	VectorCopy( params->scale, rduParams.scale );
	VectorCopy( params->velocity, rduParams.velocity );

	rduParams.me = params->me;
	rduParams.settleFrame = params->settleFrame;

	G2API_AnimateG2ModelsRag( *((CGhoul2Info_v *)ghoul2), time, &rduParams );
}

CCALL qboolean SV_G2API_RagPCJConstraint( void *ghoul2, const char *boneName, vec3_t min, vec3_t max ) {
	return G2API_RagPCJConstraint( *((CGhoul2Info_v *)ghoul2), boneName, min, max );
}

CCALL qboolean SV_G2API_RagPCJGradientSpeed( void *ghoul2, const char *boneName, const float speed ) {
	return G2API_RagPCJGradientSpeed( *((CGhoul2Info_v *)ghoul2), boneName, speed );
}

CCALL qboolean SV_G2API_RagEffectorGoal( void *ghoul2, const char *boneName, vec3_t pos ) {
	return G2API_RagEffectorGoal( *((CGhoul2Info_v *)ghoul2), boneName, pos );
}

CCALL qboolean SV_G2API_GetRagBonePos( void *ghoul2, const char *boneName, vec3_t pos, vec3_t entAngles, vec3_t entPos, vec3_t entScale ) {
	return G2API_GetRagBonePos( *((CGhoul2Info_v *)ghoul2), boneName, pos, entAngles, entPos, entScale );
}

CCALL qboolean SV_G2API_RagEffectorKick( void *ghoul2, const char *boneName, vec3_t velocity ) {
	return G2API_RagEffectorKick( *((CGhoul2Info_v *)ghoul2), boneName, velocity );
}

CCALL qboolean SV_G2API_RagForceSolve( void *ghoul2, qboolean force ) {
	return G2API_RagForceSolve( *((CGhoul2Info_v *)ghoul2), force );
}

CCALL qboolean SV_G2API_SetBoneIKState( void *ghoul2, int time, const char *boneName, int ikState, sharedSetBoneIKStateParams_t *params ) {
	return G2API_SetBoneIKState( *((CGhoul2Info_v *)ghoul2), time, boneName, ikState, params );
}

CCALL qboolean SV_G2API_IKMove( void *ghoul2, int time, sharedIKMoveParams_t *params ) {
	return G2API_IKMove( *((CGhoul2Info_v *)ghoul2), time, params );
}

CCALL qboolean SV_G2API_RemoveBone( void *ghoul2, const char *boneName, int modelIndex ) {
	CGhoul2Info_v &g2 = *((CGhoul2Info_v *)ghoul2);
	return G2API_RemoveBone( g2, modelIndex, boneName );
}

CCALL void SV_G2API_AttachInstanceToEntNum( void *ghoul2, int entityNum, qboolean server ) {
	G2API_AttachInstanceToEntNum( *((CGhoul2Info_v *)ghoul2), entityNum, server );
}

CCALL void SV_G2API_ClearAttachedInstance( int entityNum ) {
	G2API_ClearAttachedInstance( entityNum );
}

CCALL void SV_G2API_CleanEntAttachments( void ) {
	G2API_CleanEntAttachments();
}

CCALL qboolean SV_G2API_OverrideServer( void *serverInstance ) {
	CGhoul2Info_v &g2 = *((CGhoul2Info_v *)serverInstance);
	return G2API_OverrideServerWithClientData( g2, 0 );
}

CCALL void SV_G2API_GetSurfaceName( void *ghoul2, int surfNumber, int modelIndex, char *fillBuf ) {
	CGhoul2Info_v &g2 = *((CGhoul2Info_v *)ghoul2);
	char *tmp = G2API_GetSurfaceName( g2, modelIndex, surfNumber );
	strcpy( fillBuf, tmp );
}

static void GVM_Cvar_Set( const char *var_name, const char *value ) {
	Cvar_VM_Set( var_name, value, VM_GAME );
}

void SV_InitGame( qboolean restart ) {
	int i=0;
	client_t *cl = NULL;

	// clear level pointers
	sv.entityParsePoint = CM_EntityString();
	for ( i=0, cl=svs.clients; i<sv_maxclients->integer; i++, cl++ )
		cl->gentity = NULL;

	GVM_InitGame( sv.time, Com_Milliseconds(), restart );
}


void SV_BindGame( void ) {
	gvm = VM_Create( VM_GAME );
}

void SV_UnbindGame( void ) {
	GVM_ShutdownGame( qfalse );
	VM_Free( gvm );
	gvm = NULL;
}

void SV_RestartGame( void ) {
	GVM_ShutdownGame( qtrue );

	gvm = VM_Restart( gvm );
	SV_BindGame();
	if ( !gvm ) {
		svs.gameStarted = qfalse;
		Com_Error( ERR_DROP, "VM_Restart on game failed" );
		return;
	}

	SV_InitGame( qtrue );
}
