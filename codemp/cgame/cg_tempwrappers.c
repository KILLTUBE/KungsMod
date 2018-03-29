#include "cg_tempwrappers.h"

CCALL sfxHandle_t		S_RegisterSound						( const char *sample ) {
	return trap->S_RegisterSound(sample);
}
