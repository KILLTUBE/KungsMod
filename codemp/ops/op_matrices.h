#ifndef OP_MATRICES_H
#define OP_MATRICES_H

#include "op.h"
#include "rd-rend2/matrix.h"

#include <vector>
#include <array>

// Maybe extend some CustomClass? So I could add some "customclass->IsArrayOfMatrices()" etc.

#include "../opsys/opsys_link_matrices.h"


class OpMatrices : public Op {
public:
	float *matrix_a = default_link_inputs[0].matrix;
	float *matrix_b = default_link_inputs[1].matrix;

	ArrayOfMatrices *matrices;

	OpMatrices();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
	std::string WriteExtraData();
	void ReadExtraData(char * line);

	void OnLinkDisconnect(int id);
};

#endif