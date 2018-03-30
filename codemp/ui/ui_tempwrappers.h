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

CCALL int G_SoundIndex( const char *name );
CCALL qhandle_t SV_RE_RegisterSkin( const char *name );

CCALL void G_SetAnimalVehicleFunctions( vehicleInfo_t *pVehInfo );
CCALL void G_SetSpeederVehicleFunctions( vehicleInfo_t *pVehInfo );
CCALL void G_SetWalkerVehicleFunctions( vehicleInfo_t *pVehInfo );
CCALL void G_SetFighterVehicleFunctions( vehicleInfo_t *pVehInfo );

CCALL int G_ModelIndex( const char *name );

CCALL int G_EffectIndex( const char *name );

CCALL void G_SetSharedVehicleFunctions( vehicleInfo_t *pVehInfo );

#endif