#ifndef OP_MATRIX_SHEAR_H
#define OP_MATRIX_SHEAR_H

#include "op.h"

class OpMatrixShear : public Op {
public:
	float &a = default_link_inputs[0].val_f;
	float &b = default_link_inputs[1].val_f;
	float &c = default_link_inputs[2].val_f;
	float &d = default_link_inputs[3].val_f;
	float &e = default_link_inputs[4].val_f;
	float &f = default_link_inputs[5].val_f;

	OpMatrixShear();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
};

#endif