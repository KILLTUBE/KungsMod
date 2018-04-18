#include "op.h"
#include "op_matrix_scale.h"

#include "rd-rend2/matrix.h"

void OpMatrixScale::Init() {
	Op::Init();
	size = ImVec2(256, 256);
	pos = ImVec2(250, 300);
	strcpy( name, "OpMatrixScale" );
	InitLink(0, "dx", OP_TYPE_FLOAT);
	InitLink(1, "dy", OP_TYPE_FLOAT);
	InitLink(2, "dz", OP_TYPE_FLOAT);
	InitLinkOutput(0, "Matrix", OP_TYPE_MATRIX);
	number_of_inputs = 3;
	number_of_outputs = 1;
	ResizeMinimal();
}

void OpMatrixScale::Render() {
	Op::PreRender();
	
	Op::PostRender();
}

void OpMatrixScale::Update() {
	if ( ! forcereload)
		return;
	mat_scale(default_link_outputs[0].matrix, dx, dy, dz);
	default_link_outputs[0].changed++;
}

void OpMatrixScale::RenderEditor() {
	Op::RenderEditor();
}

OpMatrixScale::OpMatrixScale() {
	Init();
}