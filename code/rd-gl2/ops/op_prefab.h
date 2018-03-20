#ifndef OP_PREFAB_H
#define OP_PREFAB_H

#include "op.h"
#include <vector>

class OpPrefab : public Op {
public:
	OpSystem *subsys;
	std::vector<LinkOutput *> internal_outputs;
	char filename[64];

	OpPrefab();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
	std::string WriteExtraData();
	void ReadExtraData(char * line);
};

#endif