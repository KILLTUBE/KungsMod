
#include "primitives_3d.h"




void kung_cube(float *data, float x, float y, float z, glm::mat4x4 mat) {
	float positions[8][4] = {
		{0,1,0, 1},
		{0,1,1, 1},
		{1,1,1, 1},
		{1,1,0, 1},
		{0,0,0, 1},
		{0,0,1, 1},
		{1,0,1, 1},
		{1,0,0, 1}
	};


	

	for (int i=0; i<8; i++) {
		//positions[i][0] += x;
		//positions[i][1] += y;
		//positions[i][2] += z;

		auto pos = glm::make_vec4(positions[i]);
		auto pos2 = mat * pos;
		positions[i][0] = pos2[0];
		positions[i][1] = pos2[1];
		positions[i][2] = pos2[2];
		positions[i][3] = pos2[3];

	}

	int triangles[12][3] = {
		{0,1,2},
		{0,2,3},
		{0,4,5},
		{0,5,1},
		{1,5,6},
		{1,6,2},
		{2,6,7},
		{2,7,3},
		{3,7,4},
		{3,4,0},
		{5,4,7},
		{5,7,6}
	};

	float *start = data;
	for (int i=0; i<12; i++) {
		int *triangle = triangles[i];
		start[0] = positions[ triangle[0] ][0];
		start[1] = positions[ triangle[0] ][1];
		start[2] = positions[ triangle[0] ][2];
		start[3] = positions[ triangle[1] ][0];
		start[4] = positions[ triangle[1] ][1];
		start[5] = positions[ triangle[1] ][2];
		start[6] = positions[ triangle[2] ][0];
		start[7] = positions[ triangle[2] ][1];
		start[8] = positions[ triangle[2] ][2];
		start += 9;
	}
}