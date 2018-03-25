#ifndef OP_COS_H
#define OP_COS_H

#include "op.h"

class OpCos : public Op {
public:
	float &val = default_link_inputs[0].val_f;
	float tmp_val;

	OpCos();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
};

#endif