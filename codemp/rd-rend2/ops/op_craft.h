#ifndef OP_CRAFT_H
#define OP_CRAFT_H

#include "op.h"

class OpCraft : public Op {
public:
	OpCraft();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
};

#endif