#ifndef OP_MATRIX_MULTIPLY_POINT_H
#define OP_MATRIX_MULTIPLY_POINT_H

#include "op.h"

class OpMatrixMultiplyPoint : public Op {
public:
	float *matrix = default_link_inputs[0].matrix;

	OpMatrixMultiplyPoint();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
	std::string WriteExtraData();
	void ReadExtraData(char * line);
};

#endif