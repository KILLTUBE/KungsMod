#ifndef OP_QUATERNION_INVERSE_H
#define OP_QUATERNION_INVERSE_H

#include "op.h"

class OpQuaternionInverse : public Op {
public:

	OpQuaternionInverse();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
};

#endif