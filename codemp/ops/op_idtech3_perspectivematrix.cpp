#include "op.h"
#include "op_idtech3_perspectivematrix.h"

#include "rd-rend2/matrix.h"

extern "C" void renderer_get_mvp(float *out_mvp);
extern "C" void renderer_get_perspective(float *out_matrix);
extern "C" void renderer_get_modelview(float *out_matrix);

#include "../include_ccall.h"

// todo bind to real renderer values, atm just fixing linking errors
float matrix_mvp[16];
float matrix_projection[16];
float matrix_modelview[16];

EXTERNC float matrix_mvp[16];
EXTERNC float matrix_projection[16];
EXTERNC float matrix_modelview[16];

void OpIDTech3ProjectionMatrix::Init() {
	Op::Init();
	size = ImVec2(200, 30);
	pos = ImVec2(250, 300);
	InitLinkOutput(0, "#", OP_TYPE_MATRIX);
	number_of_inputs = 0;
	number_of_outputs = 1;
	ResizeMinimal();
}
void OpIDTech3ProjectionMatrix::Render() {
	Op::PreRender();
	Op::PostRender();
}
void OpIDTech3ProjectionMatrix::Update() {
	//renderer_get_perspective(default_link_outputs[0].matrix);

	
	matcpy(default_link_outputs[0].matrix, matrix_projection);

	default_link_outputs[0].changed++;
}
void OpIDTech3ProjectionMatrix::RenderEditor() {
	Op::RenderEditor();
}
OpIDTech3ProjectionMatrix::OpIDTech3ProjectionMatrix() {
	Init();
}




void OpIDTech3ModelViewMatrix::Init() {
	Op::Init();
	size = ImVec2(200, 30);
	pos = ImVec2(250, 300);
	InitLinkOutput(0, "#", OP_TYPE_MATRIX);
	number_of_inputs = 0;
	number_of_outputs = 1;
	ResizeMinimal();
}
void OpIDTech3ModelViewMatrix::Render() {
	Op::PreRender();
	Op::PostRender();
}
void OpIDTech3ModelViewMatrix::Update() {
	//renderer_get_modelview(default_link_outputs[0].matrix);
	// backEnd.viewParms.world.modelMatrix
	//matcpy(matrix_modelview, default_link_outputs[0].matrix);
	//matcpy(matrix_modelview, backEnd.viewParms.world.modelMatrix);

	matcpy(default_link_outputs[0].matrix, matrix_modelview);
	default_link_outputs[0].changed++;
}
void OpIDTech3ModelViewMatrix::RenderEditor() {
	Op::RenderEditor();
}
OpIDTech3ModelViewMatrix::OpIDTech3ModelViewMatrix() {
	Init();
}





void OpIDTech3ModelViewProjectionMatrix::Init() {
	Op::Init();
	size = ImVec2(200, 30);
	pos = ImVec2(250, 300);
	InitLinkOutput(0, "#", OP_TYPE_MATRIX);
	number_of_inputs = 0;
	number_of_outputs = 1;
	ResizeMinimal();
}
void OpIDTech3ModelViewProjectionMatrix::Render() {
	Op::PreRender();
	Op::PostRender();
}
void OpIDTech3ModelViewProjectionMatrix::Update() {
	//renderer_get_mvp(default_link_outputs[0].matrix);

	matcpy(default_link_outputs[0].matrix, matrix_mvp);

	default_link_outputs[0].changed++;
}
void OpIDTech3ModelViewProjectionMatrix::RenderEditor() {
	Op::RenderEditor();
}
OpIDTech3ModelViewProjectionMatrix::OpIDTech3ModelViewProjectionMatrix() {
	Init();
}