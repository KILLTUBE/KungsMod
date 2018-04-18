#ifndef OP_SKELETON_H
#define OP_SKELETON_H

#include "op.h"
#include "rd-rend2/matrix.h"

#include <vector>
#include <array>

// Maybe extend some CustomClass? So I could add some "customclass->IsArrayOfMatrices()" etc.

#include "../opsys/opsys_link_matrices.h"

class Joint {
public:
	glm::mat4 localMatrix;
	glm::mat4 bindpose;
	glm::mat4 localToWorld;
	glm::mat4 worldToLocal;
	glm::vec3 localPosition;
	glm::quat localRotation;
};

class OpSkeleton : public Op {
public:
	float *matrix_a = default_link_inputs[0].matrix;
	float *matrix_b = default_link_inputs[1].matrix;

	Joint skeleton[70];

	ArrayOfMatrices *matrices;

	OpSkeleton();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
	std::string WriteExtraData();
	void ReadExtraData(char * line);

	void OnLinkDisconnect(int id);
};

#endif