#ifndef OP_MATRIX_DECOMPOSE_H
#define OP_MATRIX_DECOMPOSE_H

#include "op.h"

class OpMatrixDecompose : public Op {
public:
	float *matrix = default_link_inputs[0].matrix;

	OpMatrixDecompose();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
	std::string WriteExtraData();
	void ReadExtraData(char * line);
};

#endif