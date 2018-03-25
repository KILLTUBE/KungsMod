#ifndef OP_IDTECH3_SHADER_H
#define OP_IDTECH3_SHADER_H

#include "op.h"

class OpIDTech3Shader : public Op {
public:
	OpIDTech3Shader();
	// handles into tr.images
	int &handle_in_shader            = default_link_inputs[0].val_i = 0;
	int &handle_image_in_diffuse     = default_link_inputs[1].val_i = 0; // rgb channel
	int &handle_image_in_normal      = default_link_inputs[2].val_i = 0; // rgb channel
	int &handle_image_in_specular    = default_link_inputs[3].val_i = 0; // rgb channel

	//// those are the merged ones from the upper ones
	//int &handle_image_out_diffuse_opacity       = default_link_outputs[0].val_i = 0; // rgba, diffuse=rgb, opacity=alpha
	//int &handle_image_out_normal_height         = default_link_outputs[1].val_i = 0; // rgba, normal=rgb, height=alpha
	//int &handle_image_out_specular_gloss        = default_link_outputs[2].val_i = 0; // rgba, specular=rgb, gloss=alpha

	void Init();
	void Render();
	void Update();
	void RenderEditor();
	void OnLinkConnect(int id);
};

#endif