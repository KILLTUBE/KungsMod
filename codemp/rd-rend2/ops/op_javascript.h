#ifndef OP_JAVASCRIPT_H
#define OP_JAVASCRIPT_H

#include "op.h"

class OpJavaScript : public Op {
public:
	char code[128] = {"log(\"JS\")"};

	OpJavaScript();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
	std::string WriteExtraData();
	void ReadExtraData(char * line);
};

#endif