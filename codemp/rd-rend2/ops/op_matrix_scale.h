#ifndef OP_MATRIX_SCALE_H
#define OP_MATRIX_SCALE_H

#include "op.h"

class OpMatrixScale : public Op {
public:
	float tmp_matrix[16];
	float &dx = default_link_inputs[0].val_f;
	float &dy = default_link_inputs[1].val_f;
	float &dz = default_link_inputs[2].val_f;

	OpMatrixScale();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
};

#endif