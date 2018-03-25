#ifndef OP_IDTECH3_IMAGE_SPLIT_H
#define OP_IDTECH3_IMAGE_SPLIT_H

#include "op.h"

class OpIDTech3ImageSplit : public Op {
public:
	OpIDTech3ImageSplit();
	// handles into tr.images
	int &image_id = default_link_inputs[0].val_i = 0;
	int &handle_out_red      = default_link_outputs[0].val_i = 0;
	int &handle_out_green    = default_link_outputs[1].val_i = 0;
	int &handle_out_blue     = default_link_outputs[2].val_i = 0;
	int &handle_out_alpha    = default_link_outputs[3].val_i = 0;
	void Init();
	void Render();
	void Update();
	void RenderEditor();
	void OnLinkConnect(int id);
};

#endif