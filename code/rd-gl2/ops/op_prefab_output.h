#ifndef OP_PREFAB_OUTPUT_H
#define OP_PREFAB_OUTPUT_H

#include "op.h"

class OpPrefabOutput : public Op {
public:
	int outputid;

	OpPrefabOutput();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
	std::string WriteExtraData();
	void ReadExtraData(char * line);
};

#endif