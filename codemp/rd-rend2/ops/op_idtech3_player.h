#ifndef OP_PLAYER_H
#define OP_PLAYER_H

#include "op.h"

class OpPlayer : public Op {
public:
	OpPlayer();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
};

#endif