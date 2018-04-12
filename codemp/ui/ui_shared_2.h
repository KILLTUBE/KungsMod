#pragma once

#include "cgame/cg_local.h"
#include "ui/ui_local.h"
#include "ui_shared.h"
#include "game/bg_public.h"
#include "game/anims.h"
#include "ghoul2/G2.h"
#include "ui_only_c_defines.h"
#include "botlib/botlib.h"

#define SCROLL_TIME_START					500
#define SCROLL_TIME_ADJUST					150
#define SCROLL_TIME_ADJUSTOFFSET			40
#define SCROLL_TIME_FLOOR					20

#define HASH_TABLE_SIZE 2048
#define MAX_DEFERRED_SCRIPT		2048

//#ifdef _CGAME
//#define MEM_POOL_SIZE  (128 * 1024)
//#else
#define MEM_POOL_SIZE  (4 * 1024 * 1024)
//#endif


#define COLOR_MAX 255.0f

#define KEYWORDHASH_SIZE	512

typedef struct keywordHash_s
{
	char *keyword;
	qboolean (*func)(itemDef_t *item, int handle);
	struct keywordHash_s *next;
} keywordHash_t;

typedef struct scrollInfo_s {
	int nextScrollTime;
	int nextAdjustTime;
	int adjustValue;
	int scrollKey;
	float xStart;
	float yStart;
	itemDef_t *item;
	qboolean scrollDir;
} scrollInfo_t;

typedef struct  itemFlagsDef_s {
	const char *string;
	int value;
} itemFlagsDef_t;

typedef struct stringDef_s {
	struct stringDef_s *next;
	const char *str;
} stringDef_t;

// from tr_local.h, todo: get rid
typedef enum {
	SSF_JPEG,
	SSF_TGA,
	SSF_PNG
} screenshotFormat_t;

typedef struct uiG2PtrTracker_s uiG2PtrTracker_t;

struct uiG2PtrTracker_s
{
	void *ghoul2;
	uiG2PtrTracker_t *next;
};

EXTERNC keywordHash_t *menuParseKeywordHash[KEYWORDHASH_SIZE];
EXTERNC keywordHash_t menuParseKeywords[];
EXTERNC keywordHash_t *itemParseKeywordHash[KEYWORDHASH_SIZE];
EXTERNC keywordHash_t itemParseKeywords[];
EXTERNC char currLanguage[32][128];
EXTERNC uiG2PtrTracker_t *ui_G2PtrTracker;
EXTERNC int scriptCommandCount;
EXTERNC commandDef_t commandList[];
EXTERNC itemDef_t *ui_deferredScriptItem;
EXTERNC char ui_deferredScript[MAX_DEFERRED_SCRIPT];
EXTERNC int FPMessageTime;
EXTERNC stringID_table_t animTable[MAX_ANIMATIONS+1];
EXTERNC itemFlagsDef_t itemFlags[];
EXTERNC botlib_export_t *botlib_export;
EXTERNC const char *HolocronIcons[NUM_FORCE_POWERS];
EXTERNC qboolean ui_saber_parms_parsed;
EXTERNC int openMenuCount;
EXTERNC menuDef_t *menuStack[MAX_OPEN_MENUS];
EXTERNC int menuCount;
EXTERNC menuDef_t Menus[MAX_MENUS];
EXTERNC displayContextDef_t *DC;
EXTERNC char g_nameBind[96];

CCALL void Display_CacheAll();
CCALL void Display_HandleKey(int key,qboolean down,int x,int y);
CCALL int Display_CursorType(int x,int y);
CCALL void *Display_CaptureItem(int x,int y);
CCALL displayContextDef_t *Display_GetContext();
CCALL void Menu_Reset(void);
CCALL void Menu_PaintAll();
CCALL int Menu_Count();
CCALL void Menu_New(int handle);
CCALL qboolean Menu_Parse(int handle,menuDef_t *menu);
CCALL qboolean MenuParse_appearanceIncrement(itemDef_t *item,int handle);
CCALL qboolean MenuParse_itemDef(itemDef_t *item,int handle);
CCALL qboolean MenuParse_fadeCycle(itemDef_t *item,int handle);
CCALL qboolean MenuParse_fadeAmount(itemDef_t *item,int handle);
CCALL qboolean MenuParse_fadeClamp(itemDef_t *item,int handle);
CCALL qboolean MenuParse_soundLoop(itemDef_t *item,int handle);
CCALL qboolean MenuParse_outOfBounds(itemDef_t *item,int handle);
CCALL qboolean MenuParse_popup(itemDef_t *item,int handle);
CCALL qboolean MenuParse_ownerdraw(itemDef_t *item,int handle);
CCALL qboolean MenuParse_ownerdrawFlag(itemDef_t *item,int handle);
CCALL qboolean MenuParse_cinematic(itemDef_t *item,int handle);
CCALL qboolean MenuParse_background(itemDef_t *item,int handle);
CCALL qboolean MenuParse_outlinecolor(itemDef_t *item,int handle);
CCALL qboolean MenuParse_disablecolor(itemDef_t *item,int handle);
CCALL qboolean MenuParse_focuscolor(itemDef_t *item,int handle);
CCALL qboolean MenuParse_bordercolor(itemDef_t *item,int handle);
CCALL qboolean MenuParse_forecolor(itemDef_t *item,int handle);
CCALL qboolean MenuParse_descColor(itemDef_t *item,int handle);
CCALL qboolean MenuParse_descScale(itemDef_t *item,int handle);
CCALL qboolean MenuParse_descY(itemDef_t *item,int handle);
CCALL qboolean MenuParse_descX(itemDef_t *item,int handle);
CCALL qboolean MenuParse_descAlignment(itemDef_t *item,int handle);
CCALL qboolean MenuParse_backcolor(itemDef_t *item,int handle);
CCALL qboolean MenuParse_borderSize(itemDef_t *item,int handle);
CCALL qboolean MenuParse_border(itemDef_t *item,int handle);
CCALL qboolean MenuParse_onESC(itemDef_t *item,int handle);
CCALL qboolean MenuParse_onAccept(itemDef_t *item,int handle);
CCALL qboolean MenuParse_onClose(itemDef_t *item,int handle);
CCALL qboolean MenuParse_onOpen(itemDef_t *item,int handle);
CCALL qboolean MenuParse_visible(itemDef_t *item,int handle);
CCALL qboolean MenuParse_style(itemDef_t *item,int handle);
CCALL qboolean MenuParse_rect(itemDef_t *item,int handle);
CCALL qboolean MenuParse_fullscreen(itemDef_t *item,int handle);
CCALL qboolean MenuParse_name(itemDef_t *item,int handle);
CCALL qboolean MenuParse_font(itemDef_t *item,int handle);
CCALL void Item_InitControls(itemDef_t *item);
CCALL qboolean Item_Parse(int handle,itemDef_t *item);
CCALL qboolean ItemParse_isSaber2(itemDef_t *item,int handle);
CCALL qboolean ItemParse_isSaber(itemDef_t *item,int handle);
CCALL qboolean ItemParse_Appearance_slot(itemDef_t *item,int handle);
CCALL qboolean ItemParse_hideCvar(itemDef_t *item,int handle);
CCALL qboolean ItemParse_showCvar(itemDef_t *item,int handle);
CCALL qboolean ItemParse_disableCvar(itemDef_t *item,int handle);
CCALL qboolean ItemParse_enableCvar(itemDef_t *item,int handle);
CCALL qboolean ItemParse_ownerdrawFlag(itemDef_t *item,int handle);
CCALL qboolean ItemParse_addColorRange(itemDef_t *item,int handle);
CCALL qboolean ItemParse_cvarFloatList(itemDef_t *item,int handle);
CCALL qboolean ItemParse_cvarStrList(itemDef_t *item,int handle);
CCALL void CL_SE_GetLanguageName(const int languageIndex,char *buffer);
CCALL qboolean ItemParse_cvarFloat(itemDef_t *item,int handle);
CCALL qboolean ItemParse_lineHeight(itemDef_t *item,int handle);
CCALL qboolean ItemParse_maxLineChars(itemDef_t *item,int handle);
CCALL qboolean ItemParse_maxPaintChars(itemDef_t *item,int handle);
CCALL qboolean ItemParse_maxChars(itemDef_t *item,int handle);
CCALL qboolean ItemParse_font(itemDef_t *item,int handle);
CCALL qboolean ItemParse_cvar(itemDef_t *item,int handle);
CCALL qboolean ItemParse_cvarTest(itemDef_t *item,int handle);
CCALL qboolean ItemParse_special(itemDef_t *item,int handle);
CCALL qboolean ItemParse_action(itemDef_t *item,int handle);
CCALL qboolean ItemParse_mouseExitText(itemDef_t *item,int handle);
CCALL qboolean ItemParse_mouseEnterText(itemDef_t *item,int handle);
CCALL qboolean ItemParse_mouseExit(itemDef_t *item,int handle);
CCALL qboolean ItemParse_mouseEnter(itemDef_t *item,int handle);
CCALL qboolean ItemParse_leaveFocus(itemDef_t *item,int handle);
CCALL qboolean ItemParse_onFocus(itemDef_t *item,int handle);
CCALL qboolean ItemParse_doubleClick(itemDef_t *item,int handle);
CCALL qboolean ItemParse_cinematic(itemDef_t *item,int handle);
CCALL qboolean ItemParse_background(itemDef_t *item,int handle);
CCALL qboolean ItemParse_outlinecolor(itemDef_t *item,int handle);
CCALL qboolean ItemParse_bordercolor(itemDef_t *item,int handle);
CCALL qboolean ItemParse_forecolor(itemDef_t *item,int handle);
CCALL qboolean ItemParse_backcolor(itemDef_t *item,int handle);
CCALL qboolean ItemParse_xoffset(itemDef_t *item,int handle);
CCALL qboolean ItemParse_invertyesno(itemDef_t *item,int handle);
CCALL qboolean ItemParse_textstyle(itemDef_t *item,int handle);
CCALL qboolean ItemParse_textscale(itemDef_t *item,int handle);
CCALL qboolean ItemParse_textaligny(itemDef_t *item,int handle);
CCALL qboolean ItemParse_textalignx(itemDef_t *item,int handle);
CCALL qboolean ItemParse_textalign(itemDef_t *item,int handle);
CCALL qboolean ItemParse_isCharacter(itemDef_t *item,int handle);
CCALL qboolean ItemParse_align(itemDef_t *item,int handle);
CCALL qboolean ItemParse_ownerdraw(itemDef_t *item,int handle);
CCALL qboolean ItemParse_visible(itemDef_t *item,int handle);
CCALL qboolean ItemParse_bordersize(itemDef_t *item,int handle);
CCALL qboolean ItemParse_border(itemDef_t *item,int handle);
CCALL qboolean ItemParse_columns(itemDef_t *item,int handle);
CCALL qboolean ItemParse_elementtype(itemDef_t *item,int handle);
CCALL qboolean ItemParse_feeder(itemDef_t *item,int handle);
CCALL qboolean ItemParse_elementheight(itemDef_t *item,int handle);
CCALL qboolean ItemParse_elementwidth(itemDef_t *item,int handle);
CCALL qboolean ItemParse_type(itemDef_t *item,int handle);
CCALL qboolean ItemParse_horizontalscroll(itemDef_t *item,int handle);
CCALL qboolean ItemParse_autowrapped(itemDef_t *item,int handle);
CCALL qboolean ItemParse_wrapped(itemDef_t *item,int handle);
CCALL qboolean ItemParse_scrollhidden(itemDef_t *item,int handle);
CCALL qboolean ItemParse_notselectable(itemDef_t *item,int handle);
CCALL qboolean ItemParse_decoration(itemDef_t *item,int handle);
CCALL qboolean ItemParse_style(itemDef_t *item,int handle);
CCALL qboolean ItemParse_flag(itemDef_t *item,int handle);
CCALL qboolean ItemParse_rect(itemDef_t *item,int handle);
CCALL qboolean ItemParse_rectcvar(itemDef_t *item,int handle);
CCALL qboolean ItemParse_model_g2skin_go(itemDef_t *item,const char *skinName);
CCALL qboolean ItemParse_model_g2anim(itemDef_t *item,int handle);
CCALL qboolean ItemParse_model_g2skin(itemDef_t *item,int handle);
CCALL qboolean ItemParse_model_g2scale(itemDef_t *item,int handle);
CCALL qboolean ItemParse_model_g2maxs(itemDef_t *item,int handle);
CCALL qboolean ItemParse_model_g2mins(itemDef_t *item,int handle);
CCALL qboolean ItemParse_model_angle(itemDef_t *item,int handle);
CCALL qboolean ItemParse_model_rotation(itemDef_t *item,int handle);
CCALL qboolean ItemParse_model_fovy(itemDef_t *item,int handle);
CCALL qboolean ItemParse_model_fovx(itemDef_t *item,int handle);
CCALL qboolean ItemParse_model_origin(itemDef_t *item,int handle);
CCALL qboolean ItemParse_asset_shader(itemDef_t *item,int handle);
CCALL qboolean ItemParse_asset_model(itemDef_t *item,int handle);
CCALL int UI_ParseAnimationFile(const char *filename,animation_t *animset,qboolean isHumanoid);
CCALL void UI_CleanupGhoul2(void);
CCALL void UI_ClearG2Pointer(void *ghoul2);
CCALL void UI_InsertG2Pointer(void *ghoul2);
CCALL qboolean ItemParse_group(itemDef_t *item,int handle);
CCALL qboolean ItemParse_text2aligny(itemDef_t *item,int handle);
CCALL qboolean ItemParse_text2alignx(itemDef_t *item,int handle);
CCALL qboolean ItemParse_text2(itemDef_t *item,int handle);
CCALL qboolean ItemParse_descText(itemDef_t *item,int handle);
CCALL qboolean ItemParse_text(itemDef_t *item,int handle);
CCALL qboolean ItemParse_focusSound(itemDef_t *item,int handle);
CCALL qboolean ItemParse_name(itemDef_t *item,int handle);
CCALL void Item_ValidateTypeData(itemDef_t *item);
CCALL void Menu_Paint(menuDef_t *menu,qboolean forcePaint);
CCALL void Item_Init(itemDef_t *item);
CCALL qboolean Menus_AnyFullScreenVisible(void);
CCALL void Menu_SetFeederSelection(menuDef_t *menu,int feeder,int index,const char *name);
CCALL void Menu_ScrollFeeder(menuDef_t *menu,int feeder,qboolean down);
CCALL itemDef_t *Menu_GetFocusedItem(menuDef_t *menu);
CCALL void Menu_Init(menuDef_t *menu);
CCALL void Item_Paint(itemDef_t *item);
CCALL void Item_OwnerDraw_Paint(itemDef_t *item);
CCALL void Item_ListBox_Paint(itemDef_t *item);
CCALL void Item_TextScroll_Paint(itemDef_t *item);
CCALL void Item_Image_Paint(itemDef_t *item);
CCALL void Item_Model_Paint(itemDef_t *item);
CCALL void UI_SaberAttachToChar(itemDef_t *item);
CCALL void UI_ScaleModelAxis(refEntity_t *ent);
CCALL qboolean Display_KeyBindPending(void);
CCALL void Item_Bind_Paint(itemDef_t *item);
CCALL void Item_Slider_Paint(itemDef_t *item);
CCALL void BindingFromName(const char *cvar);
CCALL void Controls_SetDefaults(void);
CCALL void Controls_SetConfig(void);
CCALL void Item_Multi_Paint(itemDef_t *item);
CCALL void Item_YesNo_Paint(itemDef_t *item);
CCALL void Item_TextField_Paint(itemDef_t *item);
CCALL void Item_Text_Paint(itemDef_t *item);
CCALL void Item_Text_Wrapped_Paint(itemDef_t *item);
CCALL void Item_Text_AutoWrapped_Paint(itemDef_t *item);
CCALL void Item_TextColor(itemDef_t *item,vec4_t *newColor);
CCALL void Item_SetTextExtents(itemDef_t *item,int *width,int *height,const char *text);
CCALL void Rect_ToWindowCoords(rectDef_t *rect,windowDef_t *window);
CCALL void ToWindowCoords(float *x,float *y,windowDef_t *window);
CCALL void Menu_HandleKey(menuDef_t *menu,int key,qboolean down);
CCALL void Menus_HandleOOBClick(menuDef_t *menu,int key,qboolean down);
CCALL int Display_VisibleMenuCount();
CCALL void Menu_HandleMouseMove(menuDef_t *menu,float x,float y);
CCALL void Item_Action(itemDef_t *item);
CCALL qboolean Item_HandleAccept(itemDef_t *item);
CCALL qboolean Item_HandleKey(itemDef_t *item,int key,qboolean down);
CCALL qboolean Item_Slider_HandleKey(itemDef_t *item,int key,qboolean down);
CCALL void Item_StopCapture(itemDef_t *item);
CCALL void Item_StartCapture(itemDef_t *item,int key);
CCALL void Item_TextField_Paste(itemDef_t *item);
CCALL qboolean Item_TextField_HandleKey(itemDef_t *item,int key);
CCALL qboolean Item_TextField_HandleKey(itemDef_t *item,int key);
CCALL void GetClipboardData(char *buf,int buflen);
CCALL void Leaving_EditField(itemDef_t *item);
CCALL qboolean Item_Multi_HandleKey(itemDef_t *item,int key);
CCALL const char *Item_Multi_Setting(itemDef_t *item);
CCALL int Item_Multi_FindCvarByValue(itemDef_t *item);
CCALL int Item_Multi_CountSettings(itemDef_t *item);
CCALL qboolean Item_YesNo_HandleKey(itemDef_t *item,int key);
CCALL qboolean Item_ListBox_HandleKey(itemDef_t *item,int key,qboolean down,qboolean force);
CCALL qboolean Item_OwnerDraw_HandleKey(itemDef_t *item,int key);
CCALL void Item_SetMouseOver(itemDef_t *item,qboolean focus);
CCALL itemDef_t *Menu_HitTest(menuDef_t *menu,float x,float y);
CCALL void Item_MouseLeave(itemDef_t *item);
CCALL void Item_MouseEnter(itemDef_t *item,float x,float y);
CCALL void Item_ListBox_MouseEnter(itemDef_t *item,float x,float y);
CCALL int Item_ListBox_OverLB(itemDef_t *item,float x,float y);
CCALL int Item_Slider_OverSlider(itemDef_t *item,float x,float y);
CCALL float Item_Slider_ThumbPosition(itemDef_t *item);
CCALL int Item_ListBox_ThumbDrawPosition(itemDef_t *item);
CCALL int Item_ListBox_ThumbPosition(itemDef_t *item);
CCALL int Item_ListBox_MaxScroll(itemDef_t *item);
CCALL qboolean Display_MouseMove(void *p,int x,int y);
CCALL qboolean Item_TextScroll_HandleKey(itemDef_t *item,int key,qboolean down,qboolean force);
CCALL void Item_TextScroll_MouseEnter(itemDef_t *item,float x,float y);
CCALL int Item_TextScroll_OverLB(itemDef_t *item,float x,float y);
CCALL int Item_TextScroll_ThumbDrawPosition(itemDef_t *item);
CCALL int Item_TextScroll_ThumbPosition(itemDef_t *item);
CCALL int Item_TextScroll_MaxScroll(itemDef_t *item);
CCALL qboolean Item_EnableShowViaCvar(itemDef_t *item,int flag);
CCALL qboolean Script_playLooped(itemDef_t *item,char **args);
CCALL qboolean Script_Play(itemDef_t *item,char **args);
CCALL qboolean Script_Exec(itemDef_t *item,char **args);
CCALL qboolean Script_SetCvarToCvar(itemDef_t *item,char **args);
CCALL qboolean Script_SetCvar(itemDef_t *item,char **args);
#if defined(_TRANS3)
CCALL qboolean Script_Transition3(itemDef_t *item,char **args);
#endif
CCALL qboolean Script_Transition2(itemDef_t *item,char **args);
CCALL qboolean ParseRect(const char **p,rectDef_t *r);
CCALL qboolean Script_SetPlayerModel(itemDef_t *item,char **args);
CCALL qboolean Script_SetFocus(itemDef_t *item,char **args);
CCALL qboolean Script_Orbit(itemDef_t *item,char **args);
CCALL qboolean Script_Scale(itemDef_t *item,char **args);
CCALL menuDef_t *Menu_GetFocused();
CCALL qboolean Script_Disable(itemDef_t *item,char **args);
CCALL void Menu_ItemDisable(menuDef_t *menu,const char *name,qboolean disableFlag);
CCALL void Menu_OrbitItemByName(menuDef_t *menu,const char *p,float x,float y,float cx,float cy,int time);
CCALL qboolean Script_Transition(itemDef_t *item,char **args);
CCALL qboolean Script_RunDeferred(itemDef_t *item,char **args);
CCALL qboolean Script_Defer(itemDef_t *item,char **args);
#if defined(_TRANS3)
void Menu_Transition3ItemByName(menuDef_t *menu,const char *p,const float minx,const float miny,const float minz,const float maxx,const float maxy,const float maxz,const float fovtx,const float fovty,const int time,const float amt);
#endif
CCALL void Menu_TransitionItemByName(menuDef_t *menu,const char *p,const rectDef_t *rectFrom,const rectDef_t *rectTo,int time,float amt);
CCALL qboolean Script_Close(itemDef_t *item,char **args);
CCALL qboolean Script_Open(itemDef_t *item,char **args);
CCALL qboolean Script_FadeOut(itemDef_t *item,char **args);
CCALL qboolean Script_FadeIn(itemDef_t *item,char **args);
CCALL qboolean Script_Hide(itemDef_t *item,char **args);
CCALL qboolean Script_Show(itemDef_t *item,char **args);
CCALL void Menus_CloseAll();
CCALL void Menus_CloseByName(const char *p);
CCALL menuDef_t *Menus_ActivateByName(const char *p);
CCALL void Menus_OpenByName(const char *p);
CCALL void Menus_Activate(menuDef_t *menu);
CCALL void Menus_ShowByName(const char *p);
CCALL menuDef_t *Menus_FindByName(const char *p);
CCALL void Menu_FadeItemByName(menuDef_t *menu,const char *p,qboolean fadeOut);
CCALL void Menu_ShowItemByName(menuDef_t *menu,const char *p,qboolean bShow);
CCALL void Menu_ShowGroup(menuDef_t *menu,const char *groupName,qboolean showFlag);
CCALL qboolean Script_SetItemRect(itemDef_t *item,char **args);
CCALL qboolean Script_SetItemColorCvar(itemDef_t *item,char **args);
CCALL qboolean Script_SetItemColor(itemDef_t *item,char **args);
CCALL qboolean Script_SetTeamColor(itemDef_t *item,char **args);
CCALL qboolean Script_SetItemText(itemDef_t *item,char **args);
CCALL void Menu_SetItemBackground(const menuDef_t *menu,const char *itemName,const char *background);
CCALL qboolean Script_SetItemBackground(itemDef_t *item,char **args);
CCALL itemDef_t *Menu_FindItemByName(menuDef_t *menu,const char *p);
CCALL qboolean Script_SetItemRectCvar(itemDef_t *item,char **args);
CCALL qboolean Script_SetBackground(itemDef_t *item,char **args);
CCALL qboolean Script_SetAsset(itemDef_t *item,char **args);
CCALL qboolean Script_SetColor(itemDef_t *item,char **args);
CCALL itemDef_t *Menu_GetMatchingItemByNumber(menuDef_t *menu,int index,const char *name);
CCALL int Menu_ItemsMatchingGroup(menuDef_t *menu,const char *name);
CCALL qboolean Rect_ContainsPoint(rectDef_t *rect,float x,float y);
CCALL qboolean IsVisible(int flags);
CCALL itemDef_t *Menu_ClearFocus(menuDef_t *menu);
CCALL void Menu_PostParse(menuDef_t *menu);
CCALL void Menu_UpdatePosition(menuDef_t *menu);
CCALL void Item_UpdatePosition(itemDef_t *item);
CCALL void Item_SetScreenCoords(itemDef_t *item,float x,float y);
CCALL void Window_Paint(windowDef_t *w,float fadeAmount,float fadeClamp,float fadeCycle);
CCALL void Fade(int *flags,float *f,float clamp,int *nextTime,int offsetTime,qboolean bFlags,float fadeAmount);
CCALL void Window_Init(windowDef_t *w);
CCALL void GradientBar_Paint(rectDef_t *rect,vec4_t color);
CCALL void Init_Display(displayContextDef_t *dc);
CCALL qboolean PC_Script_Parse(int handle,const char **out);
CCALL qboolean PC_String_Parse(int handle,const char **out);
CCALL qboolean String_Parse(char **p,const char **out);
CCALL qboolean PC_Rect_Parse(int handle,rectDef_t *r);
CCALL qboolean Rect_Parse(char **p,rectDef_t *r);
CCALL qboolean PC_Int_Parse(int handle,int *i);
CCALL qboolean Int_Parse(char **p,int *i);
CCALL qboolean PC_Color_Parse(int handle,vec4_t *c);
CCALL qboolean Color_Parse(char **p,vec4_t *c);
CCALL qboolean PC_Float_Parse(int handle,float *f);
CCALL qboolean Float_Parse(char **p,float *f);
CCALL void LerpColor(vec4_t a,vec4_t b,vec4_t c,float t);
CCALL void PC_SourceError(int handle,char *format,...);
CCALL void Controls_GetConfig(void);
CCALL void String_Init();
CCALL void String_Report();
CCALL const char *String_Alloc(const char *p);
CCALL qboolean UI_OutOfMemory(void);
CCALL void UI_InitMemory(void);
CCALL void *UI_Alloc(int size);
CCALL int MenuFontToHandle(int iMenuFont);
CCALL qboolean ItemParse_model_g2anim_go(itemDef_t *item,const char *animName);
CCALL qboolean ItemParse_model_g2anim_go(itemDef_t *item,const char *animName);
CCALL qboolean ItemParse_asset_model_go(itemDef_t *item,const char *name,int *runTimeLength);
CCALL qboolean ItemParse_asset_model_go(itemDef_t *item,const char *name,int *runTimeLength);
CCALL void Menu_SetItemText(const menuDef_t *menu,const char *itemName,const char *text);
CCALL void Menu_SetItemText(const menuDef_t *menu,const char *itemName,const char *text);
CCALL itemDef_t *Menu_SetNextCursorItem(menuDef_t *menu);
CCALL itemDef_t *Menu_SetNextCursorItem(menuDef_t *menu);
CCALL itemDef_t *Menu_SetPrevCursorItem(menuDef_t *menu);
CCALL itemDef_t *Menu_SetPrevCursorItem(menuDef_t *menu);
CCALL qboolean Item_Bind_HandleKey(itemDef_t *item,int key,qboolean down);
CCALL qboolean Item_Bind_HandleKey(itemDef_t *item,int key,qboolean down);
CCALL int BindingIDFromName(const char *name);
CCALL int BindingIDFromName(const char *name);
CCALL void Menu_SetupKeywordHash(void);
CCALL void Menu_SetupKeywordHash(void);
CCALL void Item_SetupKeywordHash(void);
CCALL void Item_SetupKeywordHash(void);
CCALL void Item_RunScript(itemDef_t *item,const char *s);
CCALL void Item_RunScript(itemDef_t *item,const char *s);
CCALL qboolean Item_SetFocus(itemDef_t *item,float x,float y);
CCALL qboolean Item_SetFocus(itemDef_t *item,float x,float y);
CCALL void UI_CacheSaberGlowGraphics(void);
CCALL void UI_SaberLoadParms(void);
CCALL void UI_SaberDrawBlades(itemDef_t *item,vec3_t origin,vec3_t angles);
CCALL void UI_UpdateCharacterSkin(void);
