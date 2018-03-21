#ifndef OP_MULTIPLY_H
#define OP_MULTIPLY_H

#include "op.h"

class OpMultiply : public Op {
public:
	float &val_a = default_link_inputs[0].val_f;
	float &val_b = default_link_inputs[1].val_f;
	float &out = default_link_outputs[0].val_f;

	OpMultiply();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
};

#endif