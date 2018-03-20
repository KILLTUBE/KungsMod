#include "debuglines.h"

DebugLines kungdebuglines;

extern "C" void kungdebugline_add(
	float from_x, float from_y, float from_z,
	float from_r, float from_g, float from_b,
	float to_x, float to_y, float to_z,
	float to_r, float to_g, float to_b

) {
	glm::vec3 from_pos (from_x, from_y, from_z);
	glm::vec3 from_col (from_r, from_g, from_b);
	glm::vec3 to_pos (to_x, to_y, to_z);
	glm::vec3 to_col (to_r, to_g, to_b);
	kungdebuglines.AddLine(from_pos, from_col, to_pos, to_col);
}

void DebugLines::AddLine(glm::vec3 from_pos, glm::vec3 from_color, glm::vec3 to_pos, glm::vec3 to_color) {
	DebugLine line;
	line.from_pos = from_pos;
	line.from_color = from_color;
	line.to_pos = to_pos;
	line.to_color = to_color;
	lines.push_back(line);

}

linedata_t *DebugLines::GetBuffer() {
	// calling GetBuffer() multiple times will free the previous buffer
	// so the user of this class has no filthy memory to manage
	if (buffer)
		free(buffer);

	// lets say we add 3 lines via AddLine
	// each lines has 2 points, start=pos/color end=pos/color
	// so for each "line" we need to allocate 2 linedata_t
	buffer = (linedata_t *)malloc(lines.size() * (sizeof(linedata_t)) * 2);

	// now we gotta fill the buffer
	// line 1 will use [0] and [1]
	// line 2 will use [2] and [3]
	// line 3 will use [4] and [5]
	for (int i=0; i<lines.size(); i++) {
		// since one line is 2 linedata_t, we need: i * 2
		// i*2 + 0 will be the 1st line
		// i*2 + 1 will be the 2nd line
		int bufferindex_a = i * 2 + 0;
		int bufferindex_b = i * 2 + 1;

		// swap data into the first line
		buffer[bufferindex_a].x = lines[i].from_pos[0];
		buffer[bufferindex_a].y = lines[i].from_pos[1];
		buffer[bufferindex_a].z = lines[i].from_pos[2];
		buffer[bufferindex_a].r = lines[i].from_color[0];
		buffer[bufferindex_a].g = lines[i].from_color[1];
		buffer[bufferindex_a].b = lines[i].from_color[2];

		// swap data into the second line
		buffer[bufferindex_b].x = lines[i].to_pos[0];
		buffer[bufferindex_b].y = lines[i].to_pos[1];
		buffer[bufferindex_b].z = lines[i].to_pos[2];
		buffer[bufferindex_b].r = lines[i].to_color[0];
		buffer[bufferindex_b].g = lines[i].to_color[1];
		buffer[bufferindex_b].b = lines[i].to_color[2];
	}

	// buffer contains now all lines, nicely packed for opengl to render
	return buffer;
}
	
int DebugLines::GetBufferSize() {
	// just as in GetBuffer() malloc, check it if you dont understand
	return lines.size() * (sizeof(linedata_t)) * 2;
}

GLuint *DebugLines::GetIndexes() {
	// ye right, call us as often as you want, we will regenerate the data all the time
	if (indexes)
		free(indexes);

	// when we have 3 lines, the 6 indexes will be:
	// {
	//   0, 1, // 1st line
	//   2, 3, // 2nd line
	//   4, 5, // 3rd line
	// }

	// hence we need to allocate 6 indexes for three lines
	int numberOfIndexes = lines.size() * 2;
	indexes = (GLuint *)malloc(numberOfIndexes * sizeof(GLuint));

	// probably this case of [i]=i could be optimized somehow via opengl api, but who gives a fuck
	for (int i=0; i<numberOfIndexes; i++) {
		indexes[i] = i;
	}

	return indexes;
}
	
int DebugLines::GetIndexesSize() {
	// 3 lines = 6 indexes = {0,1,2,3,4,5}
	return lines.size() * 2 * sizeof(GLuint);
}

int DebugLines::GetNumberOfIndexes() {
	return lines.size() * 2;
}

void DebugLines::ClearLines()
{
	lines.clear();
}

DebugLines::~DebugLines() {
	if (buffer)
		free(buffer);
	if (indexes)
		free(indexes);
}