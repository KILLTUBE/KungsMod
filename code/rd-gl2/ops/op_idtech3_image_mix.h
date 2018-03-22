#ifndef OP_IDTECH3_IMAGE_MIX_H
#define OP_IDTECH3_IMAGE_MIX_H

#include "op.h"

class OpIDTech3ImageMix : public Op {
public:
	OpIDTech3ImageMix();
	// handles into tr.images
	int &in_a = default_link_inputs[0].val_i = 0;
	int &in_b = default_link_inputs[1].val_i = 0;
	int &out      = default_link_outputs[0].val_i = 0;
	void Init();
	void Render();
	void Update();
	void RenderEditor();
};

#endif