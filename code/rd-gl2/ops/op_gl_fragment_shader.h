#ifndef OP_FRAGMENT_SHADER_H
#define OP_FRAGMENT_SHADER_H

#include "op.h"

class OpFragmentShader : public Op {
public:
	char filename[128] = {"shaders/line2_fragment.glsl"};
	GLuint &fragmentshader = default_link_outputs[0].opengl_id;
	int haserror = 0;

	OpFragmentShader();
	void MakeShader();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
	std::string WriteExtraData();
	void ReadExtraData(char * line);
};

#endif