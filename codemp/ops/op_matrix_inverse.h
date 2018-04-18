#ifndef OP_MATRIX_INVERSE_H
#define OP_MATRIX_INVERSE_H

#include "op.h"

class OpMatrixInverse : public Op {
public:
	OpMatrixInverse();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
};

#endif