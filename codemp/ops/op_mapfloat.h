#ifndef OP_MAPFLOAT_H
#define OP_MAPFLOAT_H

#include "op.h"

class OpMapFloat : public Op {
public:
	float &in       = default_link_inputs[0].val_f;
	float &add      = default_link_inputs[1].val_f = 0.5f;
	float &multiply = default_link_inputs[2].val_f = 0.5f;
	float &out = default_link_outputs[0].val_f;

	OpMapFloat();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
	std::string WriteExtraData();
	void ReadExtraData(char * line);
};

#endif