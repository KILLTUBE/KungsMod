#ifndef OP_SWITCH_H
#define OP_SWITCH_H

#include "op.h"

class OpSwitch : public Op {
public:

	OpSwitch();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
};

#endif