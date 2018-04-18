#include "op.h"
#include "op_matrix_transpose.h"

#include "rd-rend2/matrix.h"

#include "../imgui/imgui_fixedarea.h"

void OpMatrixTranspose::Init() {
	Op::Init();
	size = ImVec2(200, 90);
	
	InitLink(0, "M", OP_TYPE_MATRIX);
	InitLinkOutput(0, "M", OP_TYPE_MATRIX);
	number_of_inputs = 1;
	number_of_outputs = 1;
}

void OpMatrixTranspose::Render() {
	Op::PreRender();
	
	FixedArea fa(pos, size, 4);
	if (ImGui::PrintMatrix(&fa, default_link_outputs[0].matrix))
		default_link_outputs[0].changed++;

	Op::PostRender();
}

void OpMatrixTranspose::Update() {
	//if ( ! forcereload)
	//	return;
	glm::mat4 a = glm::make_mat4(default_link_inputs[0].matrix);
	glm::mat4 ret = glm::transpose(a);

	matcpy(default_link_outputs[0].matrix, glm::value_ptr(ret));
	default_link_outputs[0].changed++;
}

void OpMatrixTranspose::RenderEditor() {
	Op::RenderEditor();
}

OpMatrixTranspose::OpMatrixTranspose() {
	Init();
}