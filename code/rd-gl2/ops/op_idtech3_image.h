#ifndef OP_IDTECH3_IMAGE_H
#define OP_IDTECH3_IMAGE_H

#include "op.h"

class OpIDTech3Image : public Op {
public:
	OpIDTech3Image();
	int image_id = 0; // handle into tr.images
	void Init();
	void Render();
	void Update();
	void RenderEditor();
};

#endif