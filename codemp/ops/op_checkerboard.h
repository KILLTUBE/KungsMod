#ifndef OP_CHECKERBOARD_H
#define OP_CHECKERBOARD_H

#include "op.h"

// I don't wanna include GL headers for this little shit, because it causes always problems (thanks GLEW you bastard)
typedef unsigned char GLubyte;

class OpCheckerboard : public Op {
public:
	int textureid = -1;
	GLubyte *checkImage = NULL;
	int &width  = default_link_inputs[0].val_i;
	int &height = default_link_inputs[1].val_i;
	int &and_i  = default_link_inputs[2].val_i;
	int &and_j  = default_link_inputs[3].val_i;

	OpCheckerboard();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
	std::string WriteExtraData();
	void ReadExtraData(char * line);
	void MakeCheckImage();
	void GenerateTexture();
};

#endif