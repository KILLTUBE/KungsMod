#ifndef OP_IDTECH3_RMO_H
#define OP_IDTECH3_RMO_H

#include "op.h"

class OpIDTech3RMO : public Op {
public:
	OpIDTech3RMO();
	// handles into tr.images
	int &image_in_base      = default_link_inputs[0].val_i = 0;
	int &image_in_rmo       = default_link_inputs[1].val_i = 0;
	int &image_out_diff     = default_link_outputs[0].val_i = 0;
	int &image_out_spec     = default_link_outputs[1].val_i = 0;
	void Init();
	void Render();
	void Update();
	void RenderEditor();
	void OnLinkConnect(int id);
};

#endif