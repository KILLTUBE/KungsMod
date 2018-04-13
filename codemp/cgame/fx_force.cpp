#include "fx_force.h"

// Any dedicated force oriented effects
// This effect is not generic because of possible enhancements

void FX_ForceDrained(vec3_t origin, vec3_t dir) {
	VectorScale(dir, -1.0, dir);
	FX_PlayEffectID(cgs.effects.forceDrained, origin, dir, -1, -1, qfalse);
}
