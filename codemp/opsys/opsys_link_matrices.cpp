#include "../opsys/opsys_link_matrices.h"

LinkMatrices::LinkMatrices() {
	
}

void ArrayOfMatrices::Clear() {
	//if (matrices)
	//	free(matrices);
	//matrices = NULL;
	//count = 0;
}
void ArrayOfMatrices::SetAmount(int amount) {
	if (matrices)
		return;
	matrices = (float *)malloc(16 * sizeof(float) * amount);
	count = amount;
}

void ArrayOfMatrices::Add(float *matrix, int i) {
	//else
	//	matrices = (float *)realloc(matrices, 16 * sizeof(float));
	int address = (int)matrices;
	address += 16 * sizeof(float) * i;
	matcpy((float *)address, matrix);
	//count++;
}