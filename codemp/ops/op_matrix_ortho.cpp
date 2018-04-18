#include "op.h"
#include "op_matrix_ortho.h"

#include "rd-rend2/matrix.h"

void OpOrtho::Init() {
	Op::Init();
	size = ImVec2(256, 256);
	pos = ImVec2(250, 300);
	strcpy( name, "OpOrtho" );
	
	InitLink(0, "Left"  , OP_TYPE_FLOAT);
	InitLink(1, "Right" , OP_TYPE_FLOAT);
	InitLink(2, "Bottom", OP_TYPE_FLOAT);
	InitLink(3, "Top"   , OP_TYPE_FLOAT);
	InitLink(4, "ZNear" , OP_TYPE_FLOAT);
	InitLink(5, "ZFar"  , OP_TYPE_FLOAT);
	InitLinkOutput(0, "Matrix", OP_TYPE_MATRIX);

	number_of_inputs = 6;
	number_of_outputs = 1;
	ResizeMinimal();
}

void OpOrtho::Render() {
	Op::PreRender();
	Op::PostRender();
}

void OpOrtho::Update() {
	for (int i=0; i<number_of_outputs; i++) {
		auto *ol = default_link_outputs + i;
		//log("persp has %d links on output %d", ol->inputlinks->size(), i);
		for (auto il : *ol->inputlinks) {
			// todo: calc once, then memcpy or so
			//mat_perspective(il->matrix, fov, aspect, znear, zfar);
			mat_ortho(il->matrix, left, right, bottom, top, znear, zfar);
			il->owner->Update();
		}
	}
}

void OpOrtho::RenderEditor() {
	Op::RenderEditor();
}

OpOrtho::OpOrtho() {
	Init();
}