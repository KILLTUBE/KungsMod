#ifndef OP_RANDOM_SHIT_H
#define OP_RANDOM_SHIT_H

#include "op.h"

class OpRandomShit : public Op {
public:

	OpRandomShit();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
	std::string WriteExtraData();
	void ReadExtraData(char * line);
};

#endif