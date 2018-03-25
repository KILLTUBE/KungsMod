#ifndef OP_VERTEX_SHADER_H
#define OP_VERTEX_SHADER_H

#include "op.h"

class OpVertexShader : public Op {
public:
	char filename[128] = {"shaders/line2_vertex.glsl"};
	GLuint &vertexshader = default_link_outputs[0].opengl_id;
	int haserror = 0;

	OpVertexShader();
	void MakeShader();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
	std::string WriteExtraData();
	void ReadExtraData(char * line);
};

#endif