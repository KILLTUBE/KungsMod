#ifndef OP_PLUS_H
#define OP_PLUS_H

#include "op.h"

class OpPlus : public Op {
public:
	float &val_a = default_link_inputs[0].val_f;
	float &val_b = default_link_inputs[1].val_f;
	float tmp_val;

	OpPlus();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
};

#endif