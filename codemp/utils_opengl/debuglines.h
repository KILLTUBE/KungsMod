#ifdef __cplusplus


//#include <kung/include_gl.h>
typedef unsigned int GLuint;

#include <stdio.h>
#include <vector>
#include "../include_glm.h"

typedef struct linedata_s {
	float x, y, z;
	float r, g, b;
} linedata_t;

class DebugLine {
public:
	glm::vec3 from_pos;
	glm::vec3 from_color;
	glm::vec3 to_pos;
	glm::vec3 to_color;
};

class DebugLines {
public:
	std::vector<DebugLine> lines;
	linedata_t *buffer = NULL;
	GLuint *indexes = NULL;


	void AddLine(glm::vec3 from_pos, glm::vec3 from_color, glm::vec3 to_pos, glm::vec3 to_color);

	linedata_t *GetBuffer();
	
	int GetBufferSize();

	GLuint *GetIndexes();
	
	int GetIndexesSize();
	
	int GetNumberOfIndexes();
	void ClearLines();

	~DebugLines();
};

extern DebugLines kungdebuglines;
#endif

#include "../include_ccall.h"
// We might use the C api aswell in our C++ code
// But kungdebuglines.AddLine is probably nicer via glm vector class
CCALL void kungdebugline_add(
	float from_x, float from_y, float from_z,
	float from_r, float from_g, float from_b,
	float to_x, float to_y, float to_z,
	float to_r, float to_g, float to_b
);