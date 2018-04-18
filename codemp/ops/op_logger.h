#ifndef OP_LOGGER_H
#define OP_LOGGER_H

#include "op.h"

class OpLogger : public Op {
public:

	OpLogger();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
};


#endif