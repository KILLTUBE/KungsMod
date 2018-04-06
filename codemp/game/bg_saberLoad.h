#pragma once

#include "../qcommon/q_shared.h"
#include "../game/bg_public.h"
#include "ui/ui_local.h"

EXTERNC stringID_table_t animTable[MAX_ANIMATIONS+1];
EXTERNC stringID_table_t saberMoveTable[];
EXTERNC stringID_table_t saberTable[];
EXTERNC stringID_table_t FPTable[];

CCALL void BG_SI_DeactivateTrail(saberInfo_t *saber,float duration);
CCALL void BG_SI_ActivateTrail(saberInfo_t *saber,float duration);
CCALL float BG_SI_LengthMax(saberInfo_t *saber);
CCALL float BG_SI_Length(saberInfo_t *saber);
CCALL void BG_SI_SetLengthGradual(saberInfo_t *saber,int time);
CCALL void BG_SI_SetDesiredLength(saberInfo_t *saber,float len,int bladeNum);
CCALL qboolean BG_SI_Active(saberInfo_t *saber);
CCALL void BG_SI_BladeActivate(saberInfo_t *saber,int iBlade,qboolean bActive);
CCALL void BG_SI_Activate(saberInfo_t *saber);
CCALL void BG_BLADE_DeactivateTrail(bladeInfo_t *blade,float duration);
CCALL void BG_BLADE_ActivateTrail(bladeInfo_t *blade,float duration);
CCALL void WP_SaberGetHiltInfo(const char *singleHilts[MAX_SABER_HILTS],const char *staffHilts[MAX_SABER_HILTS]);
CCALL qboolean WP_IsSaberTwoHanded(const char *saberName);
CCALL void WP_SaberLoadParms(void);
CCALL void WP_SaberSetColor(saberInfo_t *sabers,int saberNum,int bladeNum,char *colorName);
CCALL void WP_SetSaber(int entNum,saberInfo_t *sabers,int saberNum,const char *saberName);
CCALL void BG_SI_SetLength(saberInfo_t *saber,float length);
CCALL void BG_SI_Deactivate(saberInfo_t *saber);
CCALL void WP_RemoveSaber(saberInfo_t *sabers,int saberNum);
CCALL qboolean WP_SaberValidForPlayerInMP(const char *saberName);
CCALL qboolean WP_SaberParseParm(const char *saberName,const char *parmname,char *saberData);
CCALL qboolean WP_SaberParseParms(const char *saberName,saberInfo_t *saber);
CCALL void WP_SaberSetDefaults(saberInfo_t *saber);
CCALL qboolean WP_SaberCanTurnOffSomeBlades(saberInfo_t *saber);
CCALL qboolean WP_SaberStyleValidForSaber(saberInfo_t *saber1,saberInfo_t *saber2,int saberHolstered,int saberAnimLevel);
CCALL qboolean WP_UseFirstValidSaberStyle(saberInfo_t *saber1,saberInfo_t *saber2,int saberHolstered,int *saberAnimLevel);
CCALL qboolean WP_SaberBladeDoTransitionDamage(saberInfo_t *saber,int bladeNum);
CCALL qboolean WP_SaberBladeUseSecondBladeStyle(saberInfo_t *saber,int bladeNum);
CCALL saberType_t TranslateSaberType(const char *name);
CCALL saber_styles_t TranslateSaberStyle(const char *name);
CCALL const char *SaberColorToString(saber_colors_t color);
CCALL saber_colors_t TranslateSaberColor(const char *name);
CCALL qboolean BG_ParseLiteralSilent(const char **data,const char *string);
CCALL qboolean BG_ParseLiteral(const char **data,const char *string);
CCALL int BG_SoundIndex(const char *sound);