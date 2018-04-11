#pragma once

#include "cg_local.h"

typedef struct spawn_s {
	const char	*name;
	void		(*spawn)( void );
} spawn_t;

EXTERNC float cg_radarRange;
EXTERNC float cg_linearFogOverride;
EXTERNC qboolean cg_noFogOutsidePortal;
EXTERNC float cg_skyOriScale;
EXTERNC vec3_t cg_skyOriPos;
EXTERNC spawn_t spawns_cg[];
EXTERNC qboolean cg_skyOri;

CCALL void CG_ParseEntitiesFromString(void);
CCALL void SP_worldspawn_cg(void);
CCALL qboolean CG_ParseSpawnVars(void);
CCALL char *CG_AddSpawnVarToken(const char *string);
CCALL void CG_ParseEntityFromSpawnVars(void);
CCALL void SP_misc_weather_zone_cg(void);
CCALL void SP_misc_skyportal_orient_cg(void);
CCALL void SP_misc_skyportal_cg(void);
CCALL void SP_misc_model_static_cg(void);
CCALL qboolean CG_SpawnVector(const char *key,const char *defaultString,float *out);
CCALL qboolean CG_SpawnBoolean(const char *key,const char *defaultString,qboolean *out);
CCALL qboolean CG_SpawnInt(const char *key,const char *defaultString,int *out);
CCALL qboolean CG_SpawnFloat(const char *key,const char *defaultString,float *out);
CCALL qboolean CG_SpawnString(const char *key,const char *defaultString,char **out);
