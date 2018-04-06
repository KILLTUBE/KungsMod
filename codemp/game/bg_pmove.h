#pragma once

#include "../qcommon/q_shared.h"
#include "../game/bg_public.h"
#include "../game/bg_local.h"
#include "../game/g_local.h"

EXTERNC float forceJumpStrength[NUM_FORCE_POWER_LEVELS];
EXTERNC float forceJumpHeight[NUM_FORCE_POWER_LEVELS];
EXTERNC int forcePowerNeeded[NUM_FORCE_POWER_LEVELS][NUM_FORCE_POWERS];
EXTERNC float forceSpeedLevels[4];
EXTERNC int c_pmove;
EXTERNC float pm_spectatorfriction;
EXTERNC float pm_flightfriction;
EXTERNC float pm_waterfriction;
EXTERNC float pm_friction;
EXTERNC float pm_flyaccelerate;
EXTERNC float pm_wateraccelerate;
EXTERNC float pm_airaccelerate;
EXTERNC float pm_accelerate;
EXTERNC float pm_vehicleaccelerate;
EXTERNC float pm_wadeScale;
EXTERNC float pm_swimScale;
EXTERNC float pm_duckScale;
EXTERNC float pm_stopspeed;
EXTERNC qboolean pm_cancelOutZoom;
EXTERNC qboolean gPMDoSlowFall;
EXTERNC bgEntity_t *pm_entVeh;
EXTERNC bgEntity_t *pm_entSelf;
EXTERNC pml_t pml;
EXTERNC pmove_t *pm;
EXTERNC int WeaponReadyLegsAnim[WP_NUM_WEAPONS];
EXTERNC float forceJumpHeightMax[NUM_FORCE_POWER_LEVELS];

CCALL void Pmove(pmove_t *pmove);
CCALL void PmoveSingle(pmove_t *pmove);
CCALL void PM_MoveForKata(usercmd_t *ucmd);
CCALL qboolean BG_FighterUpdate(Vehicle_t *pVeh,const usercmd_t *pUcmd,vec3_t trMins,vec3_t trMaxs,float gravity,void(*traceFunc)(trace_t *results,const vec3_t start,const vec3_t lmins,const vec3_t lmaxs,const vec3_t end,int passEntityNum,int contentMask));
CCALL void BG_VehicleAdjustBBoxForOrientation(Vehicle_t *veh,vec3_t origin,vec3_t mins,vec3_t maxs,int clientNum,int tracemask,void(*localTrace)(trace_t *results,const vec3_t start,const vec3_t mins,const vec3_t maxs,const vec3_t end,int passEntityNum,int contentMask));
CCALL void PM_VehFaceHyperspacePoint(bgEntity_t *veh);
CCALL void PM_VehForcedTurning(bgEntity_t *veh);
CCALL int PM_GetOkWeaponForVehicle(void);
CCALL qboolean PM_WeaponOkOnVehicle(int weapon);
CCALL void PM_VehicleViewAngles(playerState_t *ps,bgEntity_t *veh,usercmd_t *ucmd);
CCALL void BG_G2ATSTAngles(void *ghoul2,int time,vec3_t cent_lerpAngles);
CCALL void BG_G2PlayerAngles(void *ghoul2,int motionBolt,entityState_t *cent,int time,vec3_t cent_lerpOrigin,vec3_t cent_lerpAngles,matrix3_t legs,vec3_t legsAngles,qboolean *tYawing,qboolean *tPitching,qboolean *lYawing,float *tYawAngle,float *tPitchAngle,float *lYawAngle,int frametime,vec3_t turAngles,vec3_t modelScale,int ciLegs,int ciTorso,int *corrTime,vec3_t lookAngles,vec3_t lastHeadAngles,int lookTime,entityState_t *emplaced,int *crazySmoothFactor);
CCALL qboolean BG_SaberLockBreakAnim(int anim);
CCALL qboolean BG_InRoll2(entityState_t *es);
CCALL void BG_UpdateLookAngles(int lookingDebounceTime,vec3_t lastHeadAngles,int time,vec3_t lookAngles,float lookSpeed,float minPitch,float maxPitch,float minYaw,float maxYaw,float minRoll,float maxRoll);
CCALL void BG_IK_MoveArm(void *ghoul2,int lHandBolt,int time,entityState_t *ent,int basePose,vec3_t desiredPos,qboolean *ikInProgress,vec3_t origin,vec3_t angles,vec3_t scale,int blendTime,qboolean forceHalt);
CCALL qboolean BG_InRollES(entityState_t *ps,int anim);
CCALL qboolean BG_InKnockDown(int anim);
CCALL qboolean BG_InRollAnim(entityState_t *cent);
CCALL void BG_AdjustClientSpeed(playerState_t *ps,usercmd_t *cmd,int svTime);
CCALL qboolean PM_SaberInTransition(int move);
CCALL void BG_CmdForRoll(playerState_t *ps,int anim,usercmd_t *pCmd);
CCALL void PM_AdjustAttackStates(pmove_t *pmove);
CCALL void PM_UpdateViewAngles(playerState_t *ps,const usercmd_t *cmd);
CCALL qboolean BG_UnrestrainedPitchRoll(playerState_t *ps,Vehicle_t *pVeh);
CCALL int PM_KickMoveForConditions(void);
CCALL void PM_VehicleWeaponAnimate(void);
CCALL int PM_irand_timesync(int val1,int val2);
CCALL qboolean PM_CanSetWeaponAnims(void);
CCALL int PM_ItemUsable(playerState_t *ps,int forcedUse);
CCALL void PM_RocketLock(float lockDist,qboolean vehicleLock);
CCALL int BG_VehTraceFromCamPos(trace_t *camTrace,bgEntity_t *bgEnt,const vec3_t entOrg,const vec3_t shotStart,const vec3_t end,vec3_t newEnd,vec3_t shotDir,float bestDist);
CCALL void CG_GetVehicleCamPos(vec3_t camPos);
CCALL void WP_GetVehicleCamPos(gentity_t *ent,gentity_t *pilot,vec3_t camPos);
CCALL void PM_FinishWeaponChange(void);
CCALL void PM_BeginWeaponChange(int weapon);
CCALL void BG_ClearRocketLock(playerState_t *ps);
CCALL int PM_LegsSlopeBackTransition(int desiredAnim);
CCALL qboolean PM_AdjustStandAnimForSlope(void);
CCALL qboolean BG_InSlopeAnim(int anim);
CCALL void PM_FootSlopeTrace(float *pDiff,float *pInterval);
CCALL void PM_AnglesForSlope(const float yaw,const vec3_t slope,vec3_t angles);
CCALL qboolean PM_RollingAnim(int anim);
CCALL qboolean PM_SwimmingAnim(int anim);
CCALL qboolean PM_RunningAnim(int anim);
CCALL qboolean PM_WalkingAnim(int anim);
CCALL void PM_Use(void);
CCALL void PM_CheckFixMins(void);
CCALL qboolean PM_CheckDualForwardJumpDuck(void);
CCALL qboolean PM_CanRollFromSoulCal(playerState_t *ps);
CCALL void PM_GrabWallForJump(int anim);
CCALL void PM_SetForceJumpZStart(float value);
CCALL qboolean PM_AdjustAngleForWallJump(playerState_t *ps,usercmd_t *ucmd,qboolean doMove);
CCALL qboolean PM_AdjustAngleForWallRunUp(playerState_t *ps,usercmd_t *ucmd,qboolean doMove);
CCALL qboolean PM_AdjustAnglesForWallRunUpFlipAlt(usercmd_t *ucmd);
CCALL qboolean PM_AdjustAngleForWallRun(playerState_t *ps,usercmd_t *ucmd,qboolean doMove);
CCALL void PM_SetPMViewAngle(playerState_t *ps,vec3_t angle,usercmd_t *ucmd);
CCALL qboolean PM_ForceJumpingUp(void);
CCALL void PM_ClipVelocity(vec3_t in,vec3_t normal,vec3_t out,float overbounce);
CCALL void PM_AddTouchEnt(int entityNum);
CCALL void PM_AddEventWithParm(int newEvent,int parm);
CCALL void PM_AddEvent(int newEvent);
CCALL void PM_HoverTrace(void);
CCALL gentity_t *G_PlayEffectID(const int fxID,vec3_t org,vec3_t ang);
CCALL void BG_VehicleTurnRateForSpeed(Vehicle_t *pVeh,float speed,float *mPitchOverride,float *mYawOverride);
CCALL void PM_SetSpecialMoveValues(void);
CCALL void PM_pitch_roll_for_slope(bgEntity_t *forwhom,vec3_t pass_slope,vec3_t storeAngles);
CCALL qboolean PM_DoSlowFall(void);
CCALL int PM_GetSaberStance(void);
CCALL qboolean BG_KnockDownable(playerState_t *ps);
CCALL qboolean BG_SabersOff(playerState_t *ps);
CCALL bgEntity_t *PM_BGEntForNum(int num);
CCALL saberInfo_t *BG_MySaber(int clientNum,int saberNum);
CCALL qboolean PM_GroundSlideOkay(float zNormal);
CCALL float PM_WalkableGroundDistance(void);
CCALL qboolean BG_FullBodyTauntAnim(int anim);
CCALL qboolean TryGrapple(gentity_t *ent);
CCALL void G_CheapWeaponFire(int entNum,int ev);