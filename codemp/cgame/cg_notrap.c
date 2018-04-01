
#include "cg_local.h"


CCALL int				PC_AddGlobalDefine					( char *define ) {
	return trap->PC_AddGlobalDefine(define);
}
CCALL int				PC_FreeSource						( int handle ) {
	return trap->PC_FreeSource(handle);
}
CCALL int				PC_LoadGlobalDefines					( const char* filename ) {
	return trap->PC_LoadGlobalDefines(filename);
}
CCALL int				PC_LoadSource						( const char *filename ) {
	return trap->PC_LoadSource(filename);
}
CCALL int				PC_ReadToken							( int handle, pc_token_t *pc_token ) {
	return trap->PC_ReadToken(handle, pc_token);
}
CCALL void			PC_RemoveAllGlobalDefines			( void ) {
	trap->PC_RemoveAllGlobalDefines();
}
CCALL int				PC_SourceFileAndLine					( int handle, char *filename, int *line ) {
	return trap->PC_SourceFileAndLine(handle, filename, line);
}

CCALL unsigned int R_AnyLanguage_ReadCharFromString( const char *psText, int *piAdvanceCount, qboolean *pbIsTrailingPunctuation ) {
	return R_AnyLanguage_ReadCharFromString(psText, piAdvanceCount, pbIsTrailingPunctuation);
}






CCALL void			R_AddLightToScene		( const vec3_t org, float intensity, float r, float g, float b ) {
	R_AddLightToScene(org, intensity, r, g, b);
}
CCALL void			R_AddPolysToScene		( qhandle_t hShader, int numVerts, const polyVert_t *verts, int num ) {
	R_AddPolysToScene(hShader, numVerts, verts, num);
}
CCALL void			R_AddRefEntityToScene	( const refEntity_t *re_ ) {
	trap->R_AddRefEntityToScene(re_);
}
CCALL void			R_ClearScene			( void ) {
	R_ClearScene();
}
CCALL void			R_StretchPic		( float x, float y, float w, float h, float s1, float t1, float s2, float t2, qhandle_t hShader ) {
	R_StretchPic(x, y, w, h, s1, t1, s2, t2, hShader);
}
CCALL int			R_Font_StrLenPixels		( const char *text, const int iFontIndex, const float scale ) {
	return R_Font_StrLenPixels(text, iFontIndex, scale);
}
CCALL int			R_Font_StrLenChars		( const char *text ) {
	return R_Font_StrLenChars(text);
}
CCALL int			R_Font_HeightPixels		( const int iFontIndex, const float scale ) {
	return R_Font_HeightPixels(iFontIndex, scale);
}
CCALL void			R_Font_DrawString		( int ox, int oy, const char *text, const float *rgba, const int setIndex, int iCharLimit, const float scale ) {
	R_Font_DrawString(ox, oy, text, rgba, setIndex, iCharLimit, scale);
}
CCALL int			R_LerpTag				( orientation_t *tag, clipHandle_t mod, int startFrame, int endFrame, float frac, const char *tagName ) {
	return R_LerpTag(tag, mod, startFrame, endFrame, frac, tagName);
}
CCALL void			R_ModelBounds			( clipHandle_t model, vec3_t mins, vec3_t maxs ) {
	R_ModelBounds(model, mins, maxs);
}
CCALL qhandle_t		R_RegisterModel			( const char *name ) {
	return R_RegisterModel(name);
}
CCALL qhandle_t		R_RegisterSkin			( const char *name ) {
	return R_RegisterSkin(name);
}
CCALL qhandle_t		R_RegisterShaderNoMip	( const char *name ) {
	return R_RegisterShaderNoMip(name);
}
CCALL qhandle_t		R_RegisterFont			( const char *fontName ) {
	return R_RegisterFont(fontName);
}
CCALL void			R_RemapShader			( const char *oldShader, const char *newShader, const char *timeOffset ) {
	R_RemapShader(oldShader, newShader, timeOffset);
}
CCALL void			R_RenderScene			( const refdef_t *fd ) {
	R_RenderScene(fd);
}
CCALL void			R_SetColor				( const float *rgba ) {
	 R_SetColor(rgba);
}
//CCALL void			R_ShaderNameFromIndex	( char *name, int index ) {
//	R_ShaderNameFromIndex(name, index);
//}



CCALL void		G2_ListModelSurfaces			( void *ghlInfo ) {
	trap->G2_ListModelSurfaces(ghlInfo);
}
CCALL void		G2_ListModelBones				( void *ghlInfo, int frame ) {
	trap->G2_ListModelBones(ghlInfo, frame);
}
CCALL void		G2_SetGhoul2ModelIndexes		( void *ghoul2, qhandle_t *modelList, qhandle_t *skinList ) {
	trap->G2_SetGhoul2ModelIndexes(ghoul2, modelList, skinList);
}
CCALL qboolean	G2_HaveWeGhoul2Models			( void *ghoul2 ) {
	return trap->G2_HaveWeGhoul2Models(ghoul2);
}





CCALL qboolean		G2API_GetBoltMatrix					( void *ghoul2, const int modelIndex, const int boltIndex, mdxaBone_t *matrix, const vec3_t angles, const vec3_t position, const int frameNum, qhandle_t *modelList, vec3_t scale ) {
	return trap->G2API_GetBoltMatrix(ghoul2, modelIndex, boltIndex, matrix, angles, position, frameNum, modelList, scale);
}
CCALL qboolean		G2API_GetBoltMatrix_NoReconstruct	( void *ghoul2, const int modelIndex, const int boltIndex, mdxaBone_t *matrix, const vec3_t angles, const vec3_t position, const int frameNum, qhandle_t *modelList, vec3_t scale ) {
	return trap->G2API_GetBoltMatrix_NoReconstruct(ghoul2, modelIndex, boltIndex, matrix, angles, position, frameNum, modelList, scale);
}
CCALL qboolean		G2API_GetBoltMatrix_NoRecNoRot		( void *ghoul2, const int modelIndex, const int boltIndex, mdxaBone_t *matrix, const vec3_t angles, const vec3_t position, const int frameNum, qhandle_t *modelList, vec3_t scale ) {
	return trap->G2API_GetBoltMatrix_NoRecNoRot(ghoul2, modelIndex, boltIndex, matrix, angles, position, frameNum, modelList, scale);
}
CCALL int			G2API_InitGhoul2Model				( void **ghoul2Ptr, const char *fileName, int modelIndex, qhandle_t customSkin, qhandle_t customShader, int modelFlags, int lodBias ) {
	return trap->G2API_InitGhoul2Model(ghoul2Ptr, fileName, modelIndex, customSkin, customShader, modelFlags, lodBias);
}
CCALL void			G2API_CollisionDetect				( CollisionRecord_t *collRecMap, void* ghoul2, const vec3_t angles, const vec3_t position, int frameNumber, int entNum, vec3_t rayStart, vec3_t rayEnd, vec3_t scale, int traceFlags, int useLod, float fRadius ) {
	trap->G2API_CollisionDetect(collRecMap, ghoul2, angles, position, frameNumber, entNum, rayStart, rayEnd, scale, traceFlags, useLod, fRadius);
}
CCALL void			G2API_CollisionDetectCache			( CollisionRecord_t *collRecMap, void* ghoul2, const vec3_t angles, const vec3_t position, int frameNumber, int entNum, vec3_t rayStart, vec3_t rayEnd, vec3_t scale, int traceFlags, int useLod, float fRadius ) {
	trap->G2API_CollisionDetectCache(collRecMap, ghoul2, angles, position, frameNumber, entNum, rayStart, rayEnd, scale, traceFlags, useLod, fRadius);
}
CCALL qboolean		G2API_SetSkin						( void *ghoul2, int modelIndex, qhandle_t customSkin, qhandle_t renderSkin ) {
	return trap->G2API_SetSkin(ghoul2, modelIndex, customSkin, renderSkin);
}
CCALL void			G2API_CleanGhoul2Models				( void **ghoul2Ptr ) {
	trap->G2API_CleanGhoul2Models(ghoul2Ptr);
}


CCALL qboolean Key_IsDown( int keynum ) {
	return Key_IsDown(keynum);

}

CCALL qboolean		CL_SE_GetStringTextString				( const char *text, char *buffer, int bufferLength ) {
	return CL_SE_GetStringTextString(text, buffer, bufferLength);
}