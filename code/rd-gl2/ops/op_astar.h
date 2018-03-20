#ifndef OP_ASTAR_H
#define OP_ASTAR_H

#include "op.h"

class AstarNode {
public:
	float x,y,z;
	GLuint buffer;
	float data[12 * 9];
};

class OpAStar : public Op {
public:
	float &x = default_link_inputs[0].val_f;
	float &y = default_link_inputs[1].val_f;
	float &z = default_link_inputs[2].val_f;
	float &n = default_link_inputs[3].val_f;
	
	//float data[72];
	float data[12 * 9];

	std::vector<AstarNode *> nodes;

	OpAStar();
	void AddNode(float x, float y, float z);

	void Init();
	void Render();
	void Update();
	void RenderEditor();
	std::string WriteExtraData();
	void ReadExtraData(char * line);
};

#endif