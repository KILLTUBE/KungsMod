#ifndef OP_SOIL_H
#define OP_SOIL_H

#include "op.h"

class OpSOIL : public Op {
public:
	GLuint &textureid = default_link_outputs[0].opengl_id;
	GLubyte *checkImage = NULL;
	int &width  = default_link_inputs[0].val_i;
	int &height = default_link_inputs[1].val_i;
	int &and_i  = default_link_inputs[2].val_i;
	int &and_j  = default_link_inputs[3].val_i;

	OpSOIL();
	void MakeCheckImage();
	void GenerateTexture();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
	std::string WriteExtraData();
	void ReadExtraData(char * line);
};

#endif