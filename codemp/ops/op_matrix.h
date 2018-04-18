#ifndef OP_MATRIX_H
#define OP_MATRIX_H

#include "op.h"

class OpMatrix : public Op {
public:
	float *matrix = default_link_inputs[0].matrix;

	OpMatrix();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
	std::string WriteExtraData();
	void ReadExtraData(char * line);
};

#endif