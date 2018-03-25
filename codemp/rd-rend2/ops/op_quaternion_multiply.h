#ifndef OP_QUATERNION_MULTIPLY_H
#define OP_QUATERNION_MULTIPLY_H

#include "op.h"

class OpQuaternionMultiply : public Op {
public:
	float *matrix_a = default_link_inputs[0].matrix;
	float *matrix_b = default_link_inputs[1].matrix;

	OpQuaternionMultiply();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
	std::string WriteExtraData();
	void ReadExtraData(char * line);

	void OnLinkDisconnect(int id);
};

#endif