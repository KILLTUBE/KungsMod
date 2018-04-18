#ifndef OP_GL_LEGACY_H
#define OP_GL_LEGACY_H

#include "op.h"

class OpGLLegacy : public Op {
public:
	OpGLLegacy();
	void RenderLegacyCode();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
};


#endif