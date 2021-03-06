#pragma once

#include "qcommon/q_shared.h"

EXTERNC int transitionMove[Q_NUM_QUADS][Q_NUM_QUADS];
EXTERNC saberMoveData_t saberMoveData[LS_MOVE_MAX];
EXTERNC int bg_parryDebounce[NUM_FORCE_POWER_LEVELS];
EXTERNC int saberMoveTransitionAngle[Q_NUM_QUADS][Q_NUM_QUADS];

CCALL void PM_SetSaberMove(short newMove);
CCALL void PM_WeaponLightsaber(void);
CCALL qboolean BG_SuperBreakWinAnim(int anim);
CCALL qboolean BG_SuperBreakLoseAnim(int anim);
CCALL int PM_SaberBounceForAttack(int move);
CCALL qboolean PM_SwimmingAnim(int anim);
CCALL qboolean PM_WalkingAnim(int anim);
CCALL qboolean PM_CanDoRollStab(void);
CCALL qboolean PM_SaberPowerCheck(void);
CCALL qboolean PM_CheckAltKickAttack(void);
CCALL qboolean PM_CanDoKata(void);
CCALL qboolean PM_SaberMoveOkayForKata(void);
CCALL qboolean PM_RunningAnim(int anim);
CCALL qboolean BG_InSlopeAnim(int anim);
CCALL int PM_KickMoveForConditions(void);
CCALL saberMoveName_t PM_SaberAttackForMovement(saberMoveName_t curmove);
CCALL qboolean PM_InSecondaryStyle(void);
CCALL saberMoveName_t PM_CheckPullAttack(void);
CCALL qboolean PM_SaberInReturn(int move);
CCALL qboolean BG_SaberInTransitionAny(int move);
CCALL float PM_WalkableGroundDistance(void);
CCALL float PM_GroundDistance(void);
CCALL saberMoveName_t PM_SaberJumpAttackMove(void);
CCALL saberMoveName_t PM_SaberJumpAttackMove2(void);
CCALL saberMoveName_t PM_SaberLungeAttackMove(qboolean noSpecials);
CCALL qboolean PM_SomeoneInFront(trace_t *tr);
CCALL saberMoveName_t PM_SaberDualJumpAttackMove(void);
CCALL saberMoveName_t PM_SaberBackflipAttackMove(void);
CCALL saberMoveName_t PM_SaberFlipOverAttackMove(void);
CCALL qboolean PM_CanBackstab(void);
CCALL int PM_BrokenParryForParry(int move);
CCALL qboolean PM_SaberInBrokenParry(int move);
CCALL void PM_SaberLocked(void);
CCALL qboolean ValidAnimFileIndex(int index);
CCALL qboolean BG_CheckIncrementLockAnim(int anim,int winOrLose);
CCALL void PM_SaberLockBreak(playerState_t *genemy,qboolean victory,int strength);
CCALL int PM_SaberLockResultAnim(playerState_t *duelist,qboolean superBreak,qboolean won);
CCALL int PM_SaberLockLoseAnim(playerState_t *genemy,qboolean victory,qboolean superBreak);
CCALL int PM_SaberLockWinAnim(qboolean victory,qboolean superBreak);
CCALL void PM_SetAnimFrame(playerState_t *gent,int frame,qboolean torso,qboolean legs);
CCALL int PM_SaberAttackChainAngle(int move1,int move2);
CCALL qboolean PM_SaberInTransition(int move);
CCALL qboolean PM_SaberInBounce(int move);
CCALL int PM_SaberMoveQuadrantForMovement(usercmd_t *ucmd);
CCALL saberMoveName_t PM_CheckStabDown(void);
CCALL qboolean BG_InKnockDown(int anim);
CCALL int PM_SaberAnimTransitionAnim(int curmove,int newmove);
CCALL qboolean PM_SaberKataDone(int curmove,int newmove);
CCALL qboolean PM_SaberKataDone(int curmove,int newmove);
CCALL saberMoveName_t PM_AttackMoveForQuad(int quad);
CCALL qboolean BG_EnoughForcePowerForMove(int cost);
CCALL void BG_ForcePowerDrain(playerState_t *ps,forcePowers_t forcePower,int overrideAmt);
CCALL int PM_irand_timesync(int val1,int val2);
CCALL saberInfo_t *BG_MySaber(int clientNum,int saberNum);
CCALL saberInfo_t *BG_MySaber(int clientNum,int saberNum);
CCALL qboolean BG_SabersOff(playerState_t *ps);