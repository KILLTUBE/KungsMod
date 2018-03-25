#ifndef OP_MESH_EDITOR_H
#define OP_MESH_EDITOR_H

#include "op.h"

class OpMeshEditor : public Op {
public:

	OpMeshEditor();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
};

#endif