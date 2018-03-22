#ifndef OP_IDTECH3_IMAGE_H
#define OP_IDTECH3_IMAGE_H

#include "op.h"

class OpIDTech3Image : public Op {
public:
	OpIDTech3Image();
	// handles into tr.images
	int &image_out      = default_link_outputs[0].val_i = 0;
	void Init();
	void Render();
	void Update();
	void RenderEditor();
	bool LoadFilename(const char *filename);
};

#endif