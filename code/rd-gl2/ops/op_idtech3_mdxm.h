#ifndef OP_OPENJK_MDXM
#define OP_OPENJK_MDXM

#include "op.h"

class OpMDXM : public Op {
public:
	OpMDXM();
	int model_id = 0; // handle into tr.models
	int lod_id = 0;
	int surface_id = 0;
	float &scale = default_link_inputs[3].val_f = 1.0;
	void Init();
	void Render();
	void Update();
	void RenderEditor();
};

#endif