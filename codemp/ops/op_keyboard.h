#ifndef OP_KEYBOARD_H
#define OP_KEYBOARD_H

#include "op.h"

class OpKeyboard : public Op {
public:
	std::list<char *> events;

	OpKeyboard();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
	void Destroy();
};

extern std::list<OpKeyboard *> keyboards;

#endif