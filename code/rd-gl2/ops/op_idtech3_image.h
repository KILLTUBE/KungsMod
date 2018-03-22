#ifndef OP_IDTECH3_IMAGE_H
#define OP_IDTECH3_IMAGE_H

#include "op.h"

class OpIDTech3Image : public Op {
public:
	OpIDTech3Image();
	// handles into tr.images
	int &image_id = default_link_inputs[0].val_i = 0;
	int &red      = default_link_outputs[0].val_i = 0;
	int &green    = default_link_outputs[1].val_i = 0;
	int &blue     = default_link_outputs[2].val_i = 0;
	int &alpha    = default_link_outputs[3].val_i = 0;
	void Init();
	void Render();
	void Update();
	void RenderEditor();
};

#endif