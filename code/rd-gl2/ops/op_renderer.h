#ifndef OP_RENDERER_H
#define OP_RENDERER_H

#include "op.h"

class OpRenderer : public Op {
public:
	int drawsort; // based on position, maybe handcode it


	OpRenderer();
	void DrawInScene();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
	std::string WriteExtraData();
	void ReadExtraData(char * line);
};

#endif