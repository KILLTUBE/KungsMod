#pragma once

#include "../qcommon/q_shared.h"
#include "cg_local.h"
#include "../ui/ui_shared.h"

#define MAX_HUD_TICS 4

typedef enum
{
	VEH_DAMAGE_FRONT=0,
	VEH_DAMAGE_BACK,
	VEH_DAMAGE_LEFT,
	VEH_DAMAGE_RIGHT,
} veh_damage_e;

typedef struct
{
	const char	*itemName;
	short	heavyDamage;
	short	lightDamage;
} veh_damage_t;

EXTERNC char *showPowersName[];
EXTERNC const char *ammoTicName[MAX_HUD_TICS];
EXTERNC const char *forceTicName[MAX_HUD_TICS];
EXTERNC const char *healthTicName[MAX_HUD_TICS];
EXTERNC const char *armorTicName[MAX_HUD_TICS];
EXTERNC int cg_siegeDeathTime;
EXTERNC char teamChat2[256];
EXTERNC char teamChat1[256];
EXTERNC char systemChat[256];
EXTERNC float zoomFov;
EXTERNC int lastvalidlockdif;
EXTERNC int numSortedTeamPlayers;
EXTERNC int sortedTeamPlayers[TEAM_MAXOVERLAY];
EXTERNC displayContextDef_t cgDC;
EXTERNC int cg_targVehLastTime;
EXTERNC int cg_targVeh;
EXTERNC int cg_vehicleAmmoWarningTime;
EXTERNC int cg_vehicleAmmoWarning;
EXTERNC qboolean cg_drawLink;
EXTERNC veh_damage_t vehDamageData[4];
EXTERNC int cgSiegeEntityRender;
EXTERNC int cgSiegeRoundCountTime;
EXTERNC int cgSiegeRoundBeganTime;
EXTERNC int cg_beatingSiegeTime;
EXTERNC int team2Timed;
EXTERNC int team1Timed;
EXTERNC int cgSiegeRoundTime;
EXTERNC int cgSiegeRoundState;
EXTERNC vec3_t gCGFallVector;
EXTERNC qboolean gCGHasFallVector;
EXTERNC float cgYsalFadeVal;
EXTERNC int cgYsalFadeTime;
EXTERNC int cgYsalTime;
EXTERNC float cgProtectFadeVal;
EXTERNC int cgProtectFadeTime;
EXTERNC int cgProtectTime;
EXTERNC float cgAbsorbFadeVal;
EXTERNC int cgAbsorbFadeTime;
EXTERNC int cgAbsorbTime;
EXTERNC float cgRageRecFadeVal;
EXTERNC int cgRageRecFadeTime;
EXTERNC int cgRageRecTime;
EXTERNC float cgRageFadeVal;
EXTERNC int cgRageFadeTime;
EXTERNC int cgRageTime;
EXTERNC vec3_t cg_saberFlashPos;
EXTERNC int cg_saberFlashTime;
EXTERNC vec3_t cg_crosshairPos;
EXTERNC float cg_crosshairPrevPosY;
EXTERNC float cg_crosshairPrevPosX;
EXTERNC vec4_t cg_genericTimerColor;
EXTERNC int cg_genericTimerDur;
EXTERNC int cg_genericTimerBar;
EXTERNC float cg_radarRange;


CCALL void CG_DrawActive(stereoFrame_t stereoView);
CCALL void CG_DrawMiscStaticModels(void);
CCALL qboolean CG_CullPointAndRadius(const vec3_t pt,float radius);
CCALL void CG_ChatBox_ArrayInsert(chatBoxItem_t **array_,int insPoint,int maxNum,chatBoxItem_t *item);
CCALL void CG_ChatBox_AddString(char *chatStr);
CCALL void CG_ChatBox_StrInsert(char *buffer,int place,char *str);
CCALL void CG_DrawCloakFuel(void);
CCALL void CG_DrawEWebHealth(void);
CCALL void CG_DrawJetpackFuel(void);
CCALL void CG_DrawFlagStatus();
CCALL void CG_DrawTimedMenus();
CCALL void CG_CalcEWebMuzzlePoint(centity_t *cent,vec3_t start,vec3_t d_f,vec3_t d_rt,vec3_t d_up);
CCALL qboolean CG_CalcVehicleMuzzlePoint(int entityNum,vec3_t start,vec3_t d_f,vec3_t d_rt,vec3_t d_up);
CCALL void CG_CalcVehMuzzle(Vehicle_t *pVeh,centity_t *ent,int muzzleNum);
CCALL void CG_DrawBracketedEntities(void);
CCALL qboolean CG_InATST(void);
CCALL qboolean CG_InFighter(void);
CCALL void CG_BracketEntity(centity_t *cent,float radius);
CCALL void CG_DottedLine(float x1,float y1,float x2,float y2,float dotSize,int numDots,vec4_t color,float alpha);
CCALL void CG_SaberClashFlare(void);
CCALL qboolean CG_WorldCoordToScreenCoord(vec3_t worldCoord,int *x,int *y);
CCALL void CG_LerpCrosshairPos(float *x,float *y);
CCALL void CG_DrawGenericTimerBar(void);
CCALL void CG_DrawHaqrBar(float chX,float chY,float chW,float chH);
CCALL void CG_DrawHealthBar(centity_t *cent,float chX,float chY,float chW,float chH);
CCALL void CG_DrawSiegeInfo(centity_t *cent,float chX,float chY,float chW,float chH);
CCALL qboolean BG_IsWhiteSpace(char c);
CCALL void CG_CenterPrint(const char *str,int y,int charWidth);
CCALL void CG_DrawSiegeMessageNonMenu(const char *str);
CCALL void CG_DrawSiegeMessage(const char *str,int objectiveScreen);
CCALL void CG_AddLagometerSnapshotInfo(snapshot_t *snap);
CCALL void CG_AddLagometerFrameInfo(void);
CCALL const char *CG_GetLocationString(const char *loc);
CCALL float CG_DrawRadar(float y);
CCALL void CG_DrawHealthBarRough(float x,float y,int width,int height,float ratio,const float *color1,const float *color2);
CCALL void CG_DrawTeamBackground(int x,int y,int w,int h,float alpha,int team);
CCALL qboolean CG_DrawVehicleHud(const centity_t *cent);
CCALL void CG_DrawVehicleDamageHUD(const centity_t *veh,int brokenLimbs,float percShields,char *menuName,float alpha);
CCALL void CG_DrawVehicleDamage(const centity_t *veh,int brokenLimbs,const menuDef_t *menuHUD,float alpha,int index);
CCALL void CG_DrawVehicleArmor(const menuDef_t *menuHUD,const centity_t *veh);
CCALL void CG_DrawVehicleSpeed(const menuDef_t *menuHUD,const centity_t *veh);
CCALL void CG_DrawVehicleWeaponsLinked(const menuDef_t *menuHUD,const centity_t *veh);
CCALL void CG_DrawVehicleTurboRecharge(const menuDef_t *menuHUD,const centity_t *veh);
CCALL void CG_DrawVehicleAmmoLower(const menuDef_t *menuHUD,const centity_t *veh);
CCALL void CG_DrawVehicleAmmoUpper(const menuDef_t *menuHUD,const centity_t *veh);
CCALL void CG_DrawVehicleAmmo(const menuDef_t *menuHUD,const centity_t *veh);
CCALL float CG_DrawVehicleShields(const menuDef_t *menuHUD,const centity_t *veh);
CCALL qboolean CG_CheckTargetVehicle(centity_t **pTargetVeh,float *alpha);
CCALL void CG_DrawInvenSelect(void);
CCALL void CG_DrawForceSelect(void);
CCALL qboolean ForcePower_Valid(int i);
CCALL void CG_DrawHUD(centity_t *cent);
CCALL void CG_DrawForcePower(menuDef_t *menuHUD);
CCALL void CG_DrawArmor(menuDef_t *menuHUD);
CCALL void CG_DrawHealth(menuDef_t *menuHUD);
CCALL void CG_DrawFlagModel(float x,float y,float w,float h,int team,qboolean force2D);
CCALL void CG_DrawHead(float x,float y,float w,float h,int clientNum,vec3_t headAngles);
CCALL void CG_Draw3DModel(float x,float y,float w,float h,qhandle_t model,void *ghoul2,int g2radius,qhandle_t skin,vec3_t origin,vec3_t angles);
CCALL void CG_Text_Paint(float x,float y,float scale,vec4_t color,const char *text,float adjust,int limit,int style,int iMenuFont);
CCALL int CG_Text_Height(const char *text,float scale,int iMenuFont);
CCALL int CG_Text_Width(const char *text,float scale,int iMenuFont);
CCALL int MenuFontToHandle_CG(int iMenuFont);
CCALL void CG_DrawDuelistHealth(float x,float y,float w,float h,int duelist);
CCALL void CG_DrawDuelistHealth(float x,float y,float w,float h,int duelist);
CCALL qboolean CG_CalcMuzzlePoint(int entityNum,vec3_t muzzle);
CCALL qboolean CG_WorldCoordToScreenCoordFloat(vec3_t worldCoord,float *x,float *y);
CCALL qboolean CG_WorldCoordToScreenCoordFloat(vec3_t worldCoord,float *x,float *y);
CCALL float CG_RadiusForCent(centity_t *cent);
