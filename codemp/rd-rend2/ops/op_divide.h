#ifndef OP_DIVIDE_H
#define OP_DIVIDE_H

#include "op.h"

class OpDivide : public Op {
public:
	float &val_a = default_link_inputs[0].val_f;
	float &val_b = default_link_inputs[1].val_f;
	float tmp_val;

	OpDivide();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
};

#endif