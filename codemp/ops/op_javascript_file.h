#ifndef OP_JAVASCRIPT_FILE_H
#define OP_JAVASCRIPT_FILE_H

#include "op.h"

class OpJavaScriptFile : public Op {
public:
	char filename[256] = {"assets/javascript/ops/hello.js"};
	char code[4096] = {""};
	OpJavaScriptFile();

	// directly using call_opsystemrebuild now
	//int mode = 0; // 0 == each frame, 1 == only on opsystemrebuild

	void Init();
	void Render();
	void Update();
	void RenderEditor();
	std::string WriteExtraData();
	void ReadExtraData(char * line);
	void OnOpSystemRebuild();
};

#endif