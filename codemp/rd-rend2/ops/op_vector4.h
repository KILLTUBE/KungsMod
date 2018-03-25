#ifndef OP_VECTOR4_H
#define OP_VECTOR4_H

#include "op.h"

class OpVector4 : public Op {
public:
	float *vector4 = default_link_inputs[0].vector4;

	OpVector4();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
	std::string WriteExtraData();
	void ReadExtraData(char * line);
};

#endif