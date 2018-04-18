#ifndef OP_VECTOR3_H
#define OP_VECTOR3_H

#include "op.h"

class OpVector3 : public Op {
public:
	float *vector3 = default_link_inputs[0].vector3;

	OpVector3();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
	std::string WriteExtraData();
	void ReadExtraData(char * line);
};

class OpVector3Dot : public Op {
public:
	float *vector3 = default_link_inputs[0].vector3;

	OpVector3Dot();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
	std::string WriteExtraData();
	void ReadExtraData(char * line);
};

#endif