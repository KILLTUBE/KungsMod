#include "op.h"
#include "op_matrix_identity.h"

#include "rd-rend2/matrix.h"

void OpMatrixIdentity::Init() {
	Op::Init();
	size = ImVec2(256, 256);
	pos = ImVec2(250, 300);
	strcpy( name, "OpMatrixIdentity" );
	
	InitLinkOutput(0, "Matrix", OP_TYPE_MATRIX);
	number_of_inputs = 0;
	number_of_outputs = 1;
	ResizeMinimal();

}

void OpMatrixIdentity::Render() {
	Op::PreRender();
	
	Op::PostRender();
}

void OpMatrixIdentity::Update() {
	mat_identity(tmp_matrix);
	for (int i=0; i<number_of_outputs; i++) {
		auto *ol = default_link_outputs + i;
		for (auto il : *ol->inputlinks) {
			matcpy(il->matrix, tmp_matrix);
			il->owner->Update();
		}
	}
}

void OpMatrixIdentity::RenderEditor() {
	Op::RenderEditor();
}

OpMatrixIdentity::OpMatrixIdentity() {
	Init();
}