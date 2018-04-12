#include <math.h>
#include "qcommon/q_shared.h"
#include "game/g_local.h"

CCALL qboolean tri_tri_intersect(vec3_t V0,vec3_t V1,vec3_t V2,vec3_t U0,vec3_t U1,vec3_t U2);
CCALL qboolean coplanar_tri_tri(vec3_t N,vec3_t V0,vec3_t V1,vec3_t V2,vec3_t U0,vec3_t U1,vec3_t U2);
