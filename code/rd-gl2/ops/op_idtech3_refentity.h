#ifndef OP_IDTECH3_REFENTITY_H
#define OP_IDTECH3_REFENTITY_H

#include "op.h"

class OpIDTech3RefEntity : public Op {
public:
	OpIDTech3RefEntity();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
};

#endif