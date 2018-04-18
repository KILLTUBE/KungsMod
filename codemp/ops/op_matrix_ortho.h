#ifndef OP_ORTHO_H
#define OP_ORTHO_H

#include "op.h"

class OpOrtho : public Op {
public:
	float &left   = default_link_inputs[0].val_f;
	float &right  = default_link_inputs[1].val_f;
	float &bottom = default_link_inputs[2].val_f;
	float &top    = default_link_inputs[3].val_f;
	float &znear  = default_link_inputs[4].val_f;
	float &zfar   = default_link_inputs[5].val_f;

	OpOrtho();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
};

#endif