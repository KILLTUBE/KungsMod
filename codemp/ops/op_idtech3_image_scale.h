#ifndef OP_IDTECH3_IMAGE_SCALE_H
#define OP_IDTECH3_IMAGE_SCALE_H

#include "op.h"

class OpIDTech3ImageScale : public Op {
public:
	OpIDTech3ImageScale();
	// handles into tr.images
	int   &image_id        = default_link_inputs[0].val_i = 0;
	float &scalar_red      = default_link_inputs[0].val_f = 1.0;
	float &scalar_green    = default_link_inputs[1].val_f = 1.0;
	float &scalar_blue     = default_link_inputs[2].val_f = 1.0;
	float &scalar_alpha    = default_link_inputs[3].val_f = 1.0;
	int   &out             = default_link_outputs[0].val_i = 0;
	void Init();
	void Render();
	void Update();
	void RenderEditor();
};

#endif