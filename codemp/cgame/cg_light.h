#pragma once 

#include "cg_local.h"

typedef struct clightstyle_s {
	int				length;
	color4ub_t		value;
	color4ub_t		map[MAX_QPATH];
} clightstyle_t;

CCALL void CG_RunLightStyles(void);
CCALL void CG_SetLightstyle(int i);
CCALL void CG_ClearLightStyles(void);
