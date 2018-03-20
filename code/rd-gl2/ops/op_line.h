#ifndef OP_LINE_H
#define OP_LINE_H

#include "op.h"

class OpLine : public Op {
public:
	float *line_from     = default_link_inputs[0].vector4;
	float *line_from_col = default_link_inputs[1].vector4;
	float *line_to       = default_link_inputs[2].vector4;
	float *line_to_col   = default_link_inputs[3].vector4;

	OpLine();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
	std::string WriteExtraData();
	void ReadExtraData(char * line);
};

#endif