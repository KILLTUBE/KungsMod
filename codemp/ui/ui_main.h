#pragma once

#include "../ui/ui_local.h"
#include "../qcommon/q_shared.h"
#include "game/bg_saga.h"

typedef struct serverStatusCvar_s {
	char *name, *altName;
} serverStatusCvar_t;

enum MoveData {
	MD_ACROBATICS = 0,
	MD_SINGLE_FAST,
	MD_SINGLE_MEDIUM,
	MD_SINGLE_STRONG,
	MD_DUAL_SABERS,
	MD_SABER_STAFF,
	MD_MOVE_TITLE_MAX
};

enum MoveDataSound {
	MDS_NONE = 0,
	MDS_FORCE_JUMP,
	MDS_ROLL,
	MDS_SABER,
	MDS_MOVE_SOUNDS_MAX
};

typedef struct datpadmovedata_s
{
	const char	*title;
	const char	*desc;
	const char	*anim;
	short	sound;
} datpadmovedata_t;

EXTERNC int uiNumAllAnims;
EXTERNC bgLoadedAnim_t bgAllAnims[MAX_ANIM_FILES];
EXTERNC animation_t uiHumanoidAnimations[MAX_TOTALANIMATIONS];
EXTERNC qboolean UIPAFtextLoaded;
EXTERNC const char *datapadMoveTitleBaseAnims[MD_MOVE_TITLE_MAX];
EXTERNC const char *datapadMoveTitleData[MD_MOVE_TITLE_MAX];
EXTERNC const char *forcepowerDesc[NUM_FORCE_POWERS];
EXTERNC stringID_table_t animTable[MAX_ANIMATIONS+1];
EXTERNC serverStatusCvar_t serverStatusCvars[];
EXTERNC const char *saberStaffHiltInfo[MAX_SABER_HILTS];
EXTERNC const char *saberSingleHiltInfo[MAX_SABER_HILTS];
EXTERNC int gUISelectedMap;
EXTERNC int FPMessageTime;
EXTERNC char parsedFPMessage[1024];
EXTERNC int startTime;
EXTERNC int frameCount;
EXTERNC int uiHoldSkinColor;
EXTERNC int uiSkinColor;
EXTERNC uiInfo_t uiInfo;
EXTERNC char holdSPString[MAX_STRING_CHARS];
EXTERNC char *defaultMenu;

CCALL void UI_DrawConnectScreen(qboolean overlay);
CCALL void UI_MouseEvent(int dx,int dy);
CCALL void UI_KeyEvent(int key,qboolean down);
CCALL void UI_Refresh(int realtime);
CCALL void UI_Init(qboolean inGameLoad);
CCALL void ui_rescale();
CCALL qboolean Language_UsesSpaces(void);
CCALL qboolean Language_IsAsian(void);
CCALL void UI_SaberAttachToChar(itemDef_t *item);
CCALL void UI_SiegeInit(void);
CCALL void UI_LoadForceConfig_List(void);
CCALL int UI_PlayCinematic(const char *name,float x,float y,float w,float h);
CCALL int Q_isgraph(int c);
CCALL int Q_isprintext(int c);
CCALL qboolean UI_hasSkinForBase(const char *base,const char *team);
CCALL void UI_SetSiegeTeams(void);
CCALL void UI_UpdateSiegeStatusIcons(void);
CCALL void UI_ClampMaxPlayers(void);
CCALL void UI_UpdateCvarsForClass(const int team,const int baseClass,const int index);
CCALL void UI_SiegeSetCvarsForClass(siegeClass_t *scl);
CCALL int UI_SiegeClassNum(siegeClass_t *scl);
CCALL qboolean UI_FeederSelection(float feederFloat,int index,itemDef_t *item);
CCALL void WP_SaberGetHiltInfo(const char *singleHilts[MAX_SABER_HILTS],const char *staffHilts[MAX_SABER_HILTS]);
CCALL qboolean UI_SaberProperNameForSaber(const char *saberName,char *saberProperName);
CCALL void UI_UpdateCharacterSkin(void);
CCALL qboolean ItemParse_model_g2anim_go(itemDef_t *item,const char *animName);
CCALL const char *SaberColorToString(saber_colors_t color);
CCALL qboolean ItemParse_model_g2skin_go(itemDef_t *item,const char *skinName);
CCALL qboolean ItemParse_asset_model_go(itemDef_t *item,const char *name,int *runTimeLength);
CCALL qboolean UI_SaberSkinForSaber(const char *saberName,char *saberSkin);
CCALL saber_colors_t TranslateSaberColor(const char *name);
CCALL void UI_UpdateSiegeObjectiveGraphics(void);
CCALL void UI_FindCurrentSiegeTeamClass(void);
CCALL void UI_SetSiegeObjectiveGraphicPos(menuDef_t *menu,const char *itemName,const char *cvarName);
CCALL void UI_GetVideoSetup(void);
CCALL void UI_UpdateVideoSetup(void);
CCALL void UI_ServersSort(int column,qboolean force);
CCALL void Item_RunScript(itemDef_t *item,const char *s);
CCALL void UpdateForceStatus();
CCALL void UpdateBotButtons(void);
CCALL qboolean UI_TrueJediEnabled(void);
CCALL qboolean UI_HasSetSaberOnly(const char *info,const int gametype);
CCALL const char *UI_FilterDir(int value);
CCALL const char *UI_FilterDescription(int value);
CCALL char sJediAcademy[30];
CCALL char sAll[15];
CCALL void UI_Load(void);
CCALL qboolean Load_Menu(int handle);
CCALL void UI_ParseMenu(const char *menuFile);
CCALL void UI_Report(void);
CCALL qboolean Asset_Parse(int handle);
CCALL char *GetMenuBuffer(const char *filename);
CCALL void UI_Shutdown(void);
CCALL void UI_FreeAllSpecies(void);
CCALL void UI_FreeAllSpecies(void);
CCALL void UI_CleanupGhoul2(void);
CCALL void UI_SetColor(const float *rgba);
CCALL void Text_PaintCenter(float x,float y,float scale,vec4_t color,const char *text,float adjust,int iMenuFont);
CCALL void Text_PaintCenter(float x,float y,float scale,vec4_t color,const char *text,float adjust,int iMenuFont);
CCALL void UI_DrawCenteredPic(qhandle_t image,int w,int h);
CCALL void UI_SetActiveMenu(uiMenuCommand_t menu);
CCALL void UI_LoadMenus(const char *menuFile,qboolean reset);
CCALL void UI_LoadNonIngame();
CCALL void Text_PaintWithCursor(float x,float y,float scale,vec4_t color,const char *text,int cursorPos,char cursor,int limit,int style,int iMenuFont);
CCALL void Text_Paint(float x,float y,float scale,vec4_t color,const char *text,float adjust,int limit,int style,int iMenuFont);
CCALL int Text_Height(const char *text,float scale,int iMenuFont);
CCALL int Text_Width(const char *text,float scale,int iMenuFont);
CCALL int MenuFontToHandle(int iMenuFont);
CCALL void _UI_DrawRect(float x,float y,float width,float height,float size,const float *color);
CCALL void _UI_DrawTopBottom(float x,float y,float w,float h,float size);
CCALL void _UI_DrawSides(float x,float y,float w,float h,float size);
CCALL void AssetCache(void);
CCALL int UI_SourceForLAN(void);
CCALL const char *UI_TeamName(int team);
CCALL const char *UI_GetStringEdString(const char *refSection,const char *refName);
CCALL const char *UI_GetStringEdString(const char *refSection,const char *refName);
CCALL void UpdateForceUsed();
CCALL void Menu_ShowItemByName(menuDef_t *menu,const char *p,qboolean bShow);
CCALL int UI_ParseAnimationFile(const char *filename,animation_t *animset,qboolean isHumanoid);
CCALL animation_t *UI_AnimsetAlloc(void);