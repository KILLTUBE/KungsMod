#ifndef OP_IDTECH3_SHADER_PBR_H
#define OP_IDTECH3_SHADER_PBR_H

#include "op.h"

class OpIDTech3ShaderPBR : public Op {
public:
	OpIDTech3ShaderPBR();
	// handles into tr.images
	int &shader_id      = default_link_inputs[0].val_i = 0;
	void Init();
	void Render();
	void Update();
	void RenderEditor();
};

#endif