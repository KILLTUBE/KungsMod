#ifndef OP_MATRIX_IDENTITY_H
#define OP_MATRIX_IDENTITY_H

#include "op.h"

class OpMatrixIdentity : public Op {
public:
	float tmp_matrix[16];

	OpMatrixIdentity();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
};

#endif