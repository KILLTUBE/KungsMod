#pragma once

#include "cg_local.h"
#include "qcommon/q_shared.h"

CCALL void CG_DrawScaledProportionalString(int x,int y,const char *str,int style,vec4_t color,float scale);
CCALL void CG_DrawProportionalString(int x,int y,const char *str,int style,vec4_t color);
CCALL void CG_DrawNumField(int x,int y,int width,int value,int charWidth,int charHeight,int style,qboolean zeroFill);
CCALL void CG_ColorForHealth(vec4_t hcolor);
CCALL void CG_ColorForGivenHealth(vec4_t hcolor,int health);
CCALL float *CG_FadeColor(int startMsec,int totalMsec);
CCALL void CG_TileClear(void);
CCALL int CG_DrawStrlen(const char *str);
CCALL void CG_DrawSmallStringColor(int x,int y,const char *s,vec4_t color);
CCALL void CG_DrawSmallString(int x,int y,const char *s,float alpha);
CCALL void CG_DrawBigStringColor(int x,int y,const char *s,vec4_t color);
CCALL void CG_DrawBigString(int x,int y,const char *s,float alpha);
CCALL void CG_DrawStringExt(int x,int y,const char *string,const float *setColor,qboolean forceColor,qboolean shadow,int charWidth,int charHeight,int maxChars);
CCALL void CG_DrawChar(int x,int y,int width,int height,int ch);
CCALL void CG_DrawRotatePic2(float x,float y,float width,float height,float angle,qhandle_t hShader);
CCALL void CG_DrawRotatePic(float x,float y,float width,float height,float angle,qhandle_t hShader);
CCALL void CG_DrawPic(float x,float y,float width,float height,qhandle_t hShader);
CCALL void CG_FillRect(float x,float y,float width,float height,const float *color);
CCALL void CG_FillRect2(float x,float y,float width,float height,const float *color);
CCALL void CG_GetColorForHealth(int health,int armor,vec4_t hcolor);
CCALL void CG_DrawSides(float x,float y,float w,float h,float size);
CCALL void CG_DrawTopBottom(float x,float y,float w,float h,float size);
CCALL void CG_DrawRect(float x,float y,float width,float height,float size,const float *color);
