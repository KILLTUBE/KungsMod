#ifndef OP_FRAMEBUFFER_H
#define OP_FRAMEBUFFER_H

#include "op.h"

class OpFramebuffer : public Op {
public:
	//char filename[128] = {"shaders/line2_fragment.glsl"};
	//// inputs
	//GLuint &fragmentshader = default_link_inputs[0].opengl_id;
	//GLuint &vertexshader = default_link_inputs[1].opengl_id;
	//// outputs
	//GLuint &program = default_link_outputs[0].opengl_id;
	//int haserror = 0;



	// Framebuffer stuff
	GLuint framebuffer;
	GLuint texture;
	GLuint depthbuffer;

	int resx = 100;
	int resy = 200;

	OpFramebuffer();
	void OnLinkDisconnect(int id);
	void OnLinkUpdate(int id);

	void Init();
	void Render();
	void Update();
	void RenderEditor();
};

#endif