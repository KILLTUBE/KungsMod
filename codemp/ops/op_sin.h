#ifndef OP_SIN_H
#define OP_SIN_H

#include "op.h"

class OpSin : public Op {
public:
	float &val = default_link_inputs[0].val_f;
	float &out = default_link_outputs[0].val_f;

	OpSin();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
};

#endif