#include "op.h"
#include "op_perspective.h"

#include "rd-rend2/matrix.h"

void OpPerspective::Init() {
	Op::Init();
	size = ImVec2(256, 256);
	pos = ImVec2(250, 300);
	strcpy( name, "OpPerspective" );
	InitLink(0, "Fov", OP_TYPE_FLOAT);
	InitLink(1, "Aspect", OP_TYPE_FLOAT);
	InitLink(2, "ZNear", OP_TYPE_FLOAT);
	InitLink(3, "ZFar", OP_TYPE_FLOAT);
	InitLinkOutput(0, "Matrix", OP_TYPE_MATRIX);
	number_of_inputs = 4;
	number_of_outputs = 1;
	ResizeMinimal();
}

void OpPerspective::Render() {
	Op::PreRender();
	Op::PostRender();
}

void OpPerspective::Update() {
	mat_perspective(tmp_matrix, fov, aspect, znear, zfar);
	default_link_outputs[0].changed++;
}

void OpPerspective::RenderEditor() {
	Op::RenderEditor();
}

OpPerspective::OpPerspective() {
	Init();
}