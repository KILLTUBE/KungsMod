#ifndef LINK_MATRICES_H
#define LINK_MATRICES_H

#include <vector>
#include "rd-rend2/matrix.h"

class LinkMatrices {
public:
	std::vector<float[16]> matrices;
	LinkMatrices();
};

class ArrayOfMatrices {
public:
	float *matrices = NULL;
	int count = 0;
	void Clear();
	void SetAmount(int amount);
	void Add(float *matrix, int i);
};

#endif