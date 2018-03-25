#ifndef OP_TOFLOAT_H
#define OP_TOFLOAT_H

#include "op.h"

class OpToFloat : public Op {
public:
	char code[128];
	float &val = default_link_outputs[0].val_f;

	OpToFloat();
	void InitJsCode();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
	std::string WriteExtraData();
	void ReadExtraData(char * line);
};

#endif