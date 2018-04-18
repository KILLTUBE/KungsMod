#ifndef OP_VALUE_H
#define OP_VALUE_H

#include "op.h"

class OpValue : public Op {
public:
	float &val = default_link_inputs[0].val_f;

	OpValue();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
	std::string WriteExtraData();
	void ReadExtraData(char * line);
};

#endif