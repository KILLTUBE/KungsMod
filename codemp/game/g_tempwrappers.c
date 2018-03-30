#include "../cgame/cg_tempwrappers.h"

// these functions should probably never be called from GAME...

centity_t			cg_entities[MAX_GENTITIES];
cgs_t				cgs;

CCALL qhandle_t		R_RegisterFont						( const char *fontName ) {
	__debugbreak();
	return 0;
}

CCALL qhandle_t		R_RegisterModel						( const char *name ) {
	__debugbreak();
	return 0;
}

CCALL qhandle_t		R_RegisterShader					( const char *name ) {
	__debugbreak();
	return 0;
}

CCALL qhandle_t		R_RegisterShaderNoMip				( const char *name ) {
	__debugbreak();
	return 0;
}

CCALL qhandle_t		R_RegisterSkin						( const char *name ) {
	__debugbreak();
	return 0;
}

CCALL int				FX_RegisterEffect					( const char *file ) {
	__debugbreak();
	return 0;
}


CCALL void CG_GetVehicleCamPos( vec3_t camPos ) {
	__debugbreak();
}
