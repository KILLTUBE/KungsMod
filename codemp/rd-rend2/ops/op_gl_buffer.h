#ifndef OP_GL_BUFFER_H
#define OP_GL_BUFFER_H

#include "op.h"

class OpGLBuffer : public Op {
public:
	std::vector<float> buffercontent;

	OpGLBuffer();
	void MakeBuffer();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
};

#endif