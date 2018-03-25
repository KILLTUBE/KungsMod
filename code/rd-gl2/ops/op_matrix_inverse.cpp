#include "op.h"
#include "op_matrix_inverse.h"
#include "../matrix.h"
#include "../imgui/imgui_fixedarea.h"

void OpMatrixInverse::Init() {
	Op::Init();
	size = ImVec2(200, 90);
	
	InitLink(0, "M", OP_TYPE_MATRIX);
	InitLinkOutput(0, "M", OP_TYPE_MATRIX);
	number_of_inputs = 1;
	number_of_outputs = 1;
}

void OpMatrixInverse::Render() {
	Op::PreRender();
	
	FixedArea fa(pos, size, 4);
	if (ImGui::PrintMatrix(&fa, default_link_outputs[0].matrix))
		default_link_outputs[0].changed++;

	Op::PostRender();
}

void OpMatrixInverse::Update() {
	//if ( ! forcereload)
	//	return;
	glm::mat4 a = glm::make_mat4(default_link_inputs[0].matrix);
	glm::mat4 ret = glm::inverse(a);

	matcpy(default_link_outputs[0].matrix, glm::value_ptr(ret));
	default_link_outputs[0].changed++;
}

void OpMatrixInverse::RenderEditor() {
	Op::RenderEditor();
}

OpMatrixInverse::OpMatrixInverse() {
	Init();
}