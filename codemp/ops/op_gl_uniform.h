#ifndef OP_GL_UNIFORM_H
#define OP_GL_UNIFORM_H

#include "op.h"

class OpGLUniform : public Op {
public:
	char uniformname[128] = {0};

	OpGLUniform();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
	std::string WriteExtraData();
	void ReadExtraData(char * line);
};

#endif