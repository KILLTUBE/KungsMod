#pragma once

#include "cg_local.h"
#include "game/bg_saga.h"

#define MASK_CAMERACLIP (MASK_SOLID|CONTENTS_PLAYERCLIP)
#define CAMERA_SIZE	4
#define CAMERA_DAMP_INTERVAL	50

EXTERNC qboolean cgQueueLoad;
EXTERNC int cg_autoMapInputTime;
EXTERNC autoMapInput_t cg_autoMapInput;
EXTERNC vec3_t cg_autoMapAngle;
EXTERNC float cg_autoMapZoomMainOffset;
EXTERNC float cg_autoMapZoom;
EXTERNC float cg_linearFogOverride;
EXTERNC cgscreffects_t cgScreenEffects;
EXTERNC vec3_t cg_lastTurretViewAngles;
EXTERNC vec3_t cg_actionCamLastPos;
EXTERNC int cg_actionCamLastTime;
EXTERNC float zoomFov;
EXTERNC qboolean cg_noFogOutsidePortal;
EXTERNC float cg_skyOriScale;
EXTERNC vec3_t cg_skyOriPos;
EXTERNC qboolean cg_skyOri;
EXTERNC vec3_t gCGFallVector;
EXTERNC qboolean gCGHasFallVector;
EXTERNC float cameraStiffFactor;
EXTERNC float cameraLastYaw;
EXTERNC int cameraLastFrame;
EXTERNC vec3_t cameraOldLoc;
EXTERNC vec3_t cameraCurTarget;
EXTERNC vec3_t cameraCurLoc;
EXTERNC vec3_t cameraIdealTarget;
EXTERNC vec3_t cameraIdealLoc;
EXTERNC vec3_t cameraFocusAngles;
EXTERNC vec3_t cameraFocusLoc;
EXTERNC vec3_t camerafwd;
EXTERNC vec3_t cameraup;

CCALL void CG_DrawActiveFrame(int serverTime,stereoFrame_t stereoView,qboolean demoPlayback);
CCALL void CG_ActualLoadDeferredPlayers(void);
CCALL qboolean PM_InKnockDown(playerState_t *ps);
CCALL void BG_VehicleTurnRateForSpeed(Vehicle_t *pVeh,float speed,float *mPitchOverride,float *mYawOverride);
CCALL qboolean CG_CullPointAndRadius(const vec3_t pt,float radius);
CCALL qboolean CG_CullPoint(vec3_t pt);
CCALL void CG_SetupFrustum(void);
CCALL void CG_DrawAutoMap(void);
CCALL void CG_AddRadarAutomapEnts(void);
CCALL int BG_EmplacedView(vec3_t baseAngles,vec3_t angles,float *newYaw,float constraint);
CCALL void CGCam_SetMusicMult(float multiplier,int duration);
CCALL void CG_DoCameraShake(vec3_t origin,float intensity,int radius,int time);
CCALL void CGCam_Shake(float intensity,int duration);
CCALL void CG_CalcScreenEffects(void);
CCALL void CG_SE_UpdateMusic(void);
CCALL void CG_SE_UpdateShake(vec3_t origin,vec3_t angles);
CCALL void CG_UpdateSoundTrackers();
CCALL void CG_AddBufferedSound(sfxHandle_t sfx);
CCALL void CG_DrawSkyBoxPortal(const char *cstr);
CCALL void CG_EmplacedView(vec3_t angles);
CCALL void CG_EmplacedView(vec3_t angles);
CCALL qboolean CG_CheckPassengerTurretView(void);
CCALL void CG_GetVehicleCamPos(vec3_t camPos);
CCALL qboolean BG_UnrestrainedPitchRoll(playerState_t *ps,Vehicle_t *pVeh);
CCALL void CG_CalcEntityLerpPositions(centity_t *cent);
CCALL void CG_TestModelPrevSkin_f(void);
CCALL void CG_TestModelNextSkin_f(void);
CCALL void CG_TestModelPrevFrame_f(void);
CCALL void CG_TestModelNextFrame_f(void);
CCALL void CG_TestGun_f(void);
CCALL void CG_TestModel_f(void);
