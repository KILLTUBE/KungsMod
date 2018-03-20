#ifndef OP_Negate_H
#define OP_Negate_H

#include "op.h"

class OpNegate : public Op {
public:
	float &in = default_link_inputs[0].val_f;
	float &out = default_link_outputs[0].val_f;

	OpNegate();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
};

#endif