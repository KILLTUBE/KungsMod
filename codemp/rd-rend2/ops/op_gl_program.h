#ifndef OP_PROGRAM_H
#define OP_PROGRAM_H

#include "op.h"

class OpProgram : public Op {
public:
	char filename[128] = {"shaders/line2_fragment.glsl"};
	// inputs
	GLuint &fragmentshader = default_link_inputs[0].opengl_id;
	GLuint &vertexshader = default_link_inputs[1].opengl_id;
	// outputs
	GLuint &program = default_link_outputs[0].opengl_id;
	int haserror = 0;

	OpProgram();
	void OnLinkUpdate(int id);
	void OnLinkDisconnect(int id);
	void MakeProgram();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
};

#endif