#pragma once

#include "cg_local.h"
#include "fx_local.h"
#include "ui/ui_shared.h"
#include "ui/ui_public.h"

// for the voice chats
#include "ui/menudef.h"

#include "ghoul2/G2.h"
#include "../game/bg_g2_utils.h"

EXTERNC const char *cg_stringEdVoiceChatTable[MAX_CUSTOM_SIEGE_SOUNDS];
EXTERNC int cg_vehicleAmmoWarningTime;
EXTERNC int cg_vehicleAmmoWarning;
EXTERNC int cg_siegeDeathDelay;
EXTERNC int cg_siegeDeathTime;
EXTERNC char *showPowersName[];
EXTERNC vec3_t cg_saberFlashPos;
EXTERNC int cg_saberFlashTime;
EXTERNC vec4_t cg_genericTimerColor;
EXTERNC int cg_genericTimerDur;
EXTERNC int cg_genericTimerBar;

CCALL void CG_CheckEvents(centity_t *cent);
CCALL void CG_EntityEvent(centity_t *cent,vec3_t position);
CCALL void CG_ChatBox_AddString(char *chatStr);
CCALL const char *CG_GetStringForVoiceSound(const char *s);
CCALL void CG_VehMuzzleFireFX(centity_t *veh,entityState_t *broadcaster);
CCALL void CG_CalcVehMuzzle(Vehicle_t *pVeh,centity_t *ent,int muzzleNum);
CCALL void CG_G2MarkEvent(entityState_t *es);
CCALL void CG_TryPlayCustomSound(vec3_t origin,int entityNum,int channel,const char *soundName);
CCALL void CG_PlayDoorSound(centity_t *cent,int type);
CCALL void CG_PlayDoorLoopSound(centity_t *cent);
CCALL int CG_InClientBitflags(entityState_t *ent,int client);
CCALL void DoFall(centity_t *cent,entityState_t *es,int clientNum);
CCALL qboolean BG_InKnockDownOnly(int anim);
CCALL void CG_GetCTFMessageEvent(entityState_t *es);
CCALL void CG_PrintCTFMessage(clientInfo_t *ci,const char *teamName,int ctfMessage);
CCALL const char *CG_TeamName(int team);
CCALL void CG_ReattachLimb(centity_t *source);
CCALL void CG_PainEvent(centity_t *cent,int health);
CCALL void CG_LocalTimingBar(int startTime,int duration);
CCALL void CG_ToggleBinoculars(centity_t *cent,int forceZoom);
CCALL qboolean CG_ThereIsAMaster(void);
CCALL const char *CG_PlaceString(int rank);
CCALL qboolean CG_InATST(void);
CCALL qboolean CG_InFighter(void);
CCALL qboolean CG_VehicleWeaponImpact(centity_t *cent);
CCALL qboolean WP_SaberBladeUseSecondBladeStyle(saberInfo_t *saber,int bladeNum);
