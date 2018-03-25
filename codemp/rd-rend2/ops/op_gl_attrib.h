#ifndef OP_GL_ATTRIB_H
#define OP_GL_ATTRIB_H

#include "op.h"

class OpGLAttrib : public Op {
public:
	char attrib[128] = {0};

	OpGLAttrib();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
	std::string WriteExtraData();
	void ReadExtraData(char * line);
};

#endif