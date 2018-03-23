#ifndef OP_IDTECH3_IMAGE_SPLIT_ALPHA_H
#define OP_IDTECH3_IMAGE_SPLIT_ALPHA_H

#include "op.h"

class OpIDTech3ImageSplitAlpha : public Op {
public:
	OpIDTech3ImageSplitAlpha();
	// handles into tr.images
	int &handle_in_rgba      = default_link_inputs[0].val_i = 0;
	int &handle_out_rgb      = default_link_outputs[0].val_i = 0;
	int &handle_out_alpha    = default_link_outputs[1].val_i = 0;
	void Init();
	void Render();
	void Update();
	void RenderEditor();
	void OnLinkConnect(int id);
};

#endif