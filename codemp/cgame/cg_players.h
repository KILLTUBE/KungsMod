#pragma once

#include "game/g_local.h"
#include "cg_local.h"
#include "ghoul2/G2.h"
#include "game/bg_saga.h"

EXTERNC vec3_t cameraCurLoc;
EXTERNC vec3_t cg_crosshairPos;
EXTERNC void *cg_g2JetpackInstance;
EXTERNC int cg_lastHyperSpaceEffectTime;
EXTERNC char *forceHolocronModels[];
EXTERNC playerState_t *cgSendPS[MAX_GENTITIES];
EXTERNC int cgSiegeTeam2PlShader;
EXTERNC int cgSiegeTeam1PlShader;
EXTERNC const char *cg_customDuelSoundNames[MAX_CUSTOM_DUEL_SOUNDS];
EXTERNC const char *cg_customJediSoundNames[MAX_CUSTOM_JEDI_SOUNDS];
EXTERNC const char *cg_customExtraSoundNames[MAX_CUSTOM_EXTRA_SOUNDS];
EXTERNC const char *cg_customCombatSoundNames[MAX_CUSTOM_COMBAT_SOUNDS];
EXTERNC char *cg_customSoundNames[MAX_CUSTOM_SOUNDS];
EXTERNC stringID_table_t animTable[MAX_ANIMATIONS+1];
EXTERNC qboolean cgQueueLoad;

CCALL void CG_CheckThirdPersonAlpha(centity_t *cent,refEntity_t *legs);
CCALL float CG_RadiusForCent(centity_t *cent);
CCALL int BG_EmplacedView(vec3_t baseAngles,vec3_t angles,float *newYaw,float constraint);
CCALL void CG_CleanJetpackGhoul2(void);
CCALL void CG_InitJetpackGhoul2(void);
CCALL void CG_DestroyNPCClient(clientInfo_t **ci);
CCALL void CG_CreateNPCClient(clientInfo_t **ci);
CCALL void CG_Player(centity_t *cent);
CCALL void CG_G2Animated(centity_t *cent);
CCALL qboolean CG_VehicleAttachDroidUnit(centity_t *droidCent,refEntity_t *legs);
CCALL qboolean CG_VehicleShouldDrawShields(centity_t *vehCent);
CCALL void CG_G2AnimEntModelLoad(centity_t *cent);
CCALL void G_CreateFighterNPC(Vehicle_t **pVeh,const char *strType);
CCALL void G_CreateWalkerNPC(Vehicle_t **pVeh,const char *strAnimalType);
CCALL void G_CreateSpeederNPC(Vehicle_t **pVeh,const char *strType);
CCALL void G_CreateAnimalNPC(Vehicle_t **pVeh,const char *strAnimalType);
CCALL void CG_HandleNPCSounds(centity_t *cent);
CCALL void CG_CacheG2AnimInfo(char *modelName);
CCALL void BG_GetVehicleSkinName(char *skinname,int len);
CCALL void BG_GetVehicleModelName(char *modelName,const char *vehicleName,size_t len);
CCALL int CG_HandleAppendedSkin(char *modelName);
CCALL qboolean CG_ThereIsAMaster(void);
CCALL void CG_AddRandomLightning(vec3_t start,vec3_t end);
CCALL void CG_AddLightningBeam(vec3_t start,vec3_t end);
CCALL void CG_DrawPlayerSphere(centity_t *cent,vec3_t origin,float scale,int shader);
CCALL void CG_AddSaberBlade(centity_t *cent,centity_t *scent,refEntity_t *saber,int renderfx,int modelIndex,int saberNum,int bladeNum,vec3_t origin,vec3_t angles,qboolean fromSaber,qboolean dontDraw);
CCALL qboolean BG_SuperBreakWinAnim(int anim);
CCALL void CG_SaberCompWork(vec3_t start,vec3_t end,centity_t *owner,int saberNum,int bladeNum);
CCALL void CG_AddGhoul2Mark(int shader,float size,vec3_t start,vec3_t end,int entnum,vec3_t entposition,float entangle,void *ghoul2,vec3_t scale,int lifeTime);
CCALL void CG_G2SaberEffects(vec3_t start,vec3_t end,centity_t *owner);
CCALL qboolean CG_G2TraceCollide(trace_t *tr,vec3_t const mins,vec3_t const maxs,const vec3_t lastValidStart,const vec3_t lastValidEnd);
CCALL void CG_CreateSaberMarks(vec3_t start,vec3_t end,vec3_t normal);
CCALL markPoly_t *CG_AllocMark();
CCALL void CG_GetTagWorldPosition(refEntity_t *model,char *tag,vec3_t pos,matrix3_t axis);
CCALL void CG_DoSaber(vec3_t origin,vec3_t dir,float length,float lengthMax,float radius,saber_colors_t color,int rfx,qboolean doLight);
CCALL int CG_LightVerts(vec3_t normal,int numVerts,polyVert_t *verts);
CCALL void CG_PlayerHitFX(centity_t *cent);
CCALL void CG_DrawPlayerShield(centity_t *cent,vec3_t origin);
CCALL void CG_PlayerShieldHit(int entitynum,vec3_t dir,int amount);
CCALL void CG_AddRefEntityWithPowerups(refEntity_t *ent,entityState_t *state,int team);
CCALL int CG_IsMindTricked(int trickIndex1,int trickIndex2,int trickIndex3,int trickIndex4,int client);
CCALL qboolean CG_G2PlayerHeadAnims(centity_t *cent);
CCALL void CG_G2ServerBoneAngles(centity_t *cent);
CCALL qboolean CG_RagDoll(centity_t *cent,vec3_t forcedAngles);
#if defined(_RAG_BOLT_TESTING)
CCALL void CG_TempTestFunction(centity_t *cent,vec3_t forcedAngles);
#endif
CCALL void CG_Rag_Trace(trace_t *result,const vec3_t start,const vec3_t mins,const vec3_t maxs,const vec3_t end,int skipNumber,int mask);
CCALL void CG_G2SetBoneAngles(void *ghoul2,int modelIndex,const char *boneName,const vec3_t angles,const int flags,const int up,const int right,const int forward,qhandle_t *modelList,int blendTime,int currentTime);
CCALL qboolean PM_WalkingAnim(int anim);
CCALL qboolean PM_RunningAnim(int anim);
CCALL qboolean BG_SaberStanceAnim(int anim);
CCALL qboolean CG_InRollAnim(centity_t *cent);
CCALL qboolean CG_InRoll(centity_t *cent);
CCALL void CG_TriggerAnimSounds(centity_t *cent);
CCALL void CG_PlayerAnimEvents(int animFileIndex,int eventFileIndex,qboolean torso,int oldFrame,int frame,int entNum);
CCALL void CG_PlayerAnimEventDo(centity_t *cent,animevent_t *animEvent);
CCALL void CG_LoadDeferredPlayers(void);
CCALL void CG_ActualLoadDeferredPlayers(void);
CCALL void CG_NewClientInfo(int clientNum,qboolean entitiesInitialized);
CCALL void WP_SetSaber(int entNum,saberInfo_t *sabers,int saberNum,const char *saberName);
CCALL void CG_ResetPlayerEntity(centity_t *cent);
CCALL void CG_LoadClientInfo(clientInfo_t *ci);
CCALL void CG_LoadCISounds(clientInfo_t *ci,qboolean modelloaded);
CCALL int CG_G2EvIndexForModel(void *g2,int animIndex);
CCALL int CG_G2SkelForModel(void *g2);
CCALL qboolean BG_ValidateSkinForTeam(const char *modelName,char *skinName,int team,float *colors);
CCALL qboolean BG_IsValidCharacterModel(const char *modelName,const char *skinName);
CCALL qboolean CG_ParseSurfsFile(const char *modelName,const char *skinName,char *surfOff,char *surfOn);
CCALL sfxHandle_t CG_CustomSound(int clientNum,const char *soundName);
CCALL void CG_Disintegration(centity_t *cent,refEntity_t *ent);
CCALL qboolean WP_SaberBladeUseSecondBladeStyle(saberInfo_t *saber,int bladeNum);
CCALL qboolean CG_InFighter(void);
CCALL void CG_AddBracketedEnt(centity_t *cent);
CCALL void CG_AddRadarEnt(centity_t *cent);
