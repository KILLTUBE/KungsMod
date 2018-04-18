#include "op.h"
#include "op_matrix_translate.h"

#include "rd-rend2/matrix.h"

void OpMatrixTranslate::Init() {
	Op::Init();
	size = ImVec2(256, 256);
	pos = ImVec2(250, 300);
	strcpy( name, "OpMatrixTranslate" );
	
	InitLink(0, "dx", OP_TYPE_FLOAT);
	InitLink(1, "dy", OP_TYPE_FLOAT);
	InitLink(2, "dz", OP_TYPE_FLOAT);
	InitLinkOutput(0, "Matrix", OP_TYPE_MATRIX);
	number_of_inputs = 3;
	number_of_outputs = 1;
	ResizeMinimal();
}

void OpMatrixTranslate::Render() {
	Op::PreRender();
	
	Op::PostRender();
}

void OpMatrixTranslate::Update() {
	if ( ! forcereload)
		return;
	mat_translate(default_link_outputs[0].matrix, dx, dy, dz);
	default_link_outputs[0].changed++;
}

void OpMatrixTranslate::RenderEditor() {
	Op::RenderEditor();
}

OpMatrixTranslate::OpMatrixTranslate() {
	Init();
}