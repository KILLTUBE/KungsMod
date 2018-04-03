#pragma once

#include "../qcommon/q_shared.h"

#define XCVAR_PROTO
	#include "ui_xcvar.h"
#undef XCVAR_PROTO

CCALL void UI_RegisterCvars( void );
CCALL void UI_UpdateCvars( void );