#ifndef OP_PERSPECTIVE_H
#define OP_PERSPECTIVE_H

#include "op.h"

class OpPerspective : public Op {
public:
	float &fov = default_link_inputs[0].val_f;
	float &aspect = default_link_inputs[1].val_f;
	float &znear = default_link_inputs[2].val_f;
	float &zfar = default_link_inputs[3].val_f;
	float *tmp_matrix = default_link_outputs[0].matrix;

	OpPerspective();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
};

#endif