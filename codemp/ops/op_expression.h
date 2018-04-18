#ifndef OP_EXPRESSION_H
#define OP_EXPRESSION_H

#include "op.h"

class OpExpression : public Op {
public:
	char code[128];
	int execid;

	OpExpression();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
	std::string WriteExtraData();
	void ReadExtraData(char * line);
};

#endif