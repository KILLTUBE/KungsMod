#pragma once

#include "qcommon/q_shared.h"
#include "bg_public.h"
#include "bg_local.h"
#include "g_local.h"
#include "cgame/cg_local.h"
#include "ui/ui_local.h"

#define	MAX_CLIP_PLANES	5

EXTERNC bgEntity_t *pm_entVeh;
EXTERNC bgEntity_t *pm_entSelf;

CCALL void PM_StepSlideMove(qboolean gravity);
CCALL qboolean PM_SlideMove(qboolean gravity);
CCALL qboolean PM_ClientImpact(trace_t *trace);
CCALL void Client_CheckImpactBBrush(gentity_t *self,gentity_t *other);
CCALL qboolean PM_GroundSlideOkay(float zNormal);
CCALL void PM_VehicleImpact(bgEntity_t *pEnt,trace_t *trace);
CCALL void PM_SetPMViewAngle(playerState_t *ps,vec3_t angle,usercmd_t *ucmd);
CCALL qboolean FighterIsLanded(Vehicle_t *pVeh,playerState_t *parentPS);
CCALL qboolean BG_UnrestrainedPitchRoll(playerState_t *ps,Vehicle_t *pVeh);
CCALL qboolean G_CanBeEnemy(gentity_t *self,gentity_t *enemy);
CCALL void G_FlyVehicleSurfaceDestruction(gentity_t *veh,trace_t *trace,int magnitude,qboolean force);
