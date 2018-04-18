#ifndef OP_MATRIX_ROTATE_H
#define OP_MATRIX_ROTATE_H

#include "op.h"

class OpMatrixRotate : public Op {
public:
	float *matrix_a = default_link_inputs[0].matrix;
	float *matrix_b = default_link_inputs[1].matrix;
	float &x = default_link_inputs[0].val_f;
	float &y = default_link_inputs[1].val_f;
	float &z = default_link_inputs[2].val_f;
	float &angle = default_link_inputs[3].val_f;
	float tmp_matrix[16];

	OpMatrixRotate();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
	std::string WriteExtraData();
	void ReadExtraData(char * line);
};

#endif