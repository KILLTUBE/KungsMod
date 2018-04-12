#pragma once

#include "ui_local.h"
#include "ui_shared.h"
#include "ui_only_c_defines.h"

EXTERNC qboolean ui_saber_parms_parsed;

CCALL void UI_SaberAttachToChar(itemDef_t *item);
CCALL void UI_SaberDrawBlades(itemDef_t *item,vec3_t origin,vec3_t angles);
CCALL void UI_GetSaberForMenu(char *saber,int saberNum);
CCALL void UI_SaberDrawBlade(itemDef_t *item,char *saberName,int saberModel,saberType_t saberType,vec3_t origin,vec3_t angles,int bladeNum);
CCALL void UI_DoSaber(vec3_t origin,vec3_t dir,float length,float lengthMax,float radius,saber_colors_t color);
CCALL void UI_SaberLoadParms(void);
CCALL qboolean UI_SaberValidForPlayerInMP(const char *saberName);
CCALL qboolean UI_SaberProperNameForSaber(const char *saberName,char *saberProperName);
CCALL float UI_SaberBladeRadiusForSaber(const char *saberName,int bladeNum);
CCALL float UI_SaberBladeLengthForSaber(const char *saberName,int bladeNum);
CCALL qboolean UI_IsSaberTwoHanded(const char *saberName);
CCALL qboolean UI_SaberShouldDrawBlade(const char *saberName,int bladeNum);
CCALL int UI_SaberNumBladesForSaber(const char *saberName);
CCALL qboolean UI_SaberTypeForSaber(const char *saberName,char *saberType);
CCALL qboolean UI_SaberSkinForSaber(const char *saberName,char *saberSkin);
CCALL qboolean UI_SaberModelForSaber(const char *saberName,char *saberModel);
CCALL void UI_CacheSaberGlowGraphics(void);
CCALL saberType_t TranslateSaberType(const char *name);
CCALL saber_styles_t TranslateSaberStyle(const char *name);
CCALL const char *SaberColorToString(saber_colors_t color);
CCALL saber_colors_t TranslateSaberColor(const char *name);
CCALL qboolean WP_SaberParseParm(const char *saberName,const char *parmname,char *saberData);
CCALL void WP_SaberLoadParms(void);
