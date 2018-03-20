#ifndef OP_QUATERNION_H
#define OP_QUATERNION_H

#include "op.h"

class OpQuaternion : public Op {
public:
	//float *vector4 = default_link_inputs[0].vector4;
	glm::quat &quat = default_link_inputs[0].quat;
	OpQuaternion();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
	std::string WriteExtraData();
	void ReadExtraData(char * line);
};

#endif