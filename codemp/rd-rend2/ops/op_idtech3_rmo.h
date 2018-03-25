#ifndef OP_IDTECH3_RMO_H
#define OP_IDTECH3_RMO_H

#include "op.h"

class OpIDTech3RMO : public Op {
public:
	OpIDTech3RMO();
	// handles into tr.images
	int &handle_image_in_base        = default_link_inputs[0].val_i = 0;
	int &handle_image_in_roughness   = default_link_inputs[1].val_i = 0;
	int &handle_image_in_metal       = default_link_inputs[2].val_i = 0;
	int &handle_image_in_ao          = default_link_inputs[3].val_i = 0;
	float &in_ao_strength            = default_link_inputs[4].val_f = 0.50f;
	float &in_base_specular          = default_link_inputs[5].val_f = 56.0f / 255.0f;
	int &image_out_diff     = default_link_outputs[0].val_i = 0;
	int &image_out_spec     = default_link_outputs[1].val_i = 0;
	void Init();
	void Render();
	void Update();
	void RenderEditor();
	void OnLinkConnect(int id);
};

#endif