#ifndef OP_MATRIX_TRANSPOSE_H
#define OP_MATRIX_TRANSPOSE_H

#include "op.h"

class OpMatrixTranspose : public Op {
public:
	OpMatrixTranspose();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
};

#endif