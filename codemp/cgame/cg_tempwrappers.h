#ifndef CG_TEMPWRAPPERS
#define CG_TEMPWRAPPERS

//#include <client/client.h>
#include "../game/g_local.h"
#include <cgame/cg_local.h>

CCALL sfxHandle_t	S_RegisterSound( const char *name);

CCALL qhandle_t		R_RegisterFont						( const char *fontName );
CCALL qhandle_t		R_RegisterModel						( const char *name );
CCALL qhandle_t		R_RegisterShader					( const char *name );
CCALL qhandle_t		R_RegisterShaderNoMip				( const char *name );
CCALL qhandle_t		R_RegisterSkin						( const char *name );
CCALL int				FX_RegisterEffect					( const char *file );

CCALL qhandle_t SV_RE_RegisterSkin( const char *name );

CCALL void CG_GetVehicleCamPos( vec3_t camPos );
CCALL void NPC_SetAnim(gentity_t *ent, int setAnimParts, int anim, int setAnimFlags);

#endif