#ifndef OP_IDTECH3_PERSPECTIVEMATRIX_H
#define OP_IDTECH3_PERSPECTIVEMATRIX_H

#include "op.h"

//namespace IDTech3 {

class OpIDTech3ProjectionMatrix : public Op {
public:
	OpIDTech3ProjectionMatrix();
	void Init();
	void Render();
	void Update();
	void RenderEditor();
};

class OpIDTech3ModelViewMatrix : public Op {
public:
	OpIDTech3ModelViewMatrix();
	void Init();
	void Render();
	void Update();
	void RenderEditor();
};

class OpIDTech3ModelViewProjectionMatrix : public Op {
public:
	OpIDTech3ModelViewProjectionMatrix();
	void Init();
	void Render();
	void Update();
	void RenderEditor();
};

//}

#endif