#ifndef LINK_MATRICES_H
#define LINK_MATRICES_H

#include <vector>
#include "../matrix.h"

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