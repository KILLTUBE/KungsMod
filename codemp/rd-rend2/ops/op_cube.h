#ifndef OP_CUBE_H
#define OP_CUBE_H

#include "op.h"

class OpCube : public Op {
public:
	float &x = default_link_inputs[0].val_f;
	float &y = default_link_inputs[1].val_f;
	float &z = default_link_inputs[2].val_f;
	float &n = default_link_inputs[3].val_f;
	
	OpCube();

	//float data[72];
	float data[12 * 9];
	void Init();
	void Render();
	void Update();
	void RenderEditor();
	std::string WriteExtraData();
	void ReadExtraData(char * line);
	void DrawInScene();
};


#endif