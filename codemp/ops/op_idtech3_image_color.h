#ifndef OP_IDTECH3_IMAGE_COLOR_H
#define OP_IDTECH3_IMAGE_COLOR_H

#include "op.h"

class OpIDTech3ImageColor : public Op {
public:
	OpIDTech3ImageColor();
	// handles into tr.images
	float &in_color_r      = default_link_inputs[0].val_f = 0.0;
	float &in_color_g      = default_link_inputs[1].val_f = 0.0;
	float &in_color_b      = default_link_inputs[2].val_f = 0.0;
	float &in_color_a      = default_link_inputs[3].val_f = 0.0;
	int &image_out      = default_link_outputs[0].val_i = 0;
	void Init();
	void Render();
	void Update();
	void RenderEditor();
	bool LoadFilename(const char *filename);
};

#endif