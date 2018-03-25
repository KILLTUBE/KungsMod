#ifndef OP_NOP_H
#define OP_NOP_H

#include "op.h"

class OpNop : public Op {
public:
	OpNop();
	int hasError = 0;
	void Init();
	void Render();
	void Update();
	void RenderEditor();
	void UpdateDuktapeHeappointers();
};

#endif