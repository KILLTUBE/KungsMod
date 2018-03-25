#ifndef OP_PREFAB_INPUT_H
#define OP_PREFAB_INPUT_H

#include "op.h"

class OpPrefabInput : public Op {
public:
	int inputid;

	OpPrefabInput();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
	std::string WriteExtraData();
	void ReadExtraData(char * line);
};

#endif