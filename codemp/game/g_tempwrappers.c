#include "../cgame/cg_tempwrappers.h"

// these functions should probably never be called from GAME...


CCALL qhandle_t		R_RegisterFont						( const char *fontName ) {
	assert(0);
	return 0;
}

CCALL qhandle_t		R_RegisterModel						( const char *name ) {
	assert(0);
	return 0;
}

CCALL qhandle_t		R_RegisterShader					( const char *name ) {
	assert(0);
	return 0;
}

CCALL qhandle_t		R_RegisterShaderNoMip				( const char *name ) {
	assert(0);
	return 0;
}

CCALL qhandle_t		R_RegisterSkin						( const char *name ) {
	assert(0);
	return 0;
}

CCALL int				FX_RegisterEffect					( const char *file ) {
	assert(0);
	return 0;
}
