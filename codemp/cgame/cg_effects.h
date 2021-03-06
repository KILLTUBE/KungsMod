#pragma once

#include "cg_local.h"

CCALL void CG_LaunchGib(vec3_t origin,vec3_t velocity,qhandle_t hModel);
CCALL void CG_SurfaceExplosion(vec3_t origin,vec3_t normal,float radius,float shake_speed,qboolean smoke);
CCALL localEntity_t *CG_MakeExplosion(vec3_t origin,vec3_t dir,qhandle_t hModel,int numFrames,qhandle_t shader,int msec,qboolean isSprite,float scale,int flags);
CCALL void CG_ScorePlum(int client,vec3_t org,int score);
CCALL void CG_Chunks(int owner,vec3_t origin,const vec3_t normal,const vec3_t mins,const vec3_t maxs,float speed,int numChunks,material_t chunkType,int customChunk,float baseScale);
CCALL void CG_MiscModelExplosion(vec3_t mins,vec3_t maxs,int size,material_t chunkType);
CCALL void CG_ExplosionEffects(vec3_t origin,float intensity,int radius,int time);
CCALL void CG_GlassShatter(int entnum,vec3_t dmgPt,vec3_t dmgDir,float dmgRadius,int maxShards);
CCALL void CG_DoGlass(vec3_t verts[4],vec3_t normal,vec3_t dmgPt,vec3_t dmgDir,float dmgRadius,int maxShards);
CCALL void CG_InitGlass(void);
CCALL void CG_TestLine(vec3_t start,vec3_t end,int time,unsigned int color,int radius);
CCALL int CGDEBUG_SaberColor(int saberColor);
CCALL localEntity_t *CG_SmokePuff(const vec3_t p,const vec3_t vel,float radius,float r,float g,float b,float a,float duration,int startTime,int fadeInTime,int leFlags,qhandle_t hShader);
CCALL void CG_BubbleTrail(vec3_t start,vec3_t end,float spacing);
