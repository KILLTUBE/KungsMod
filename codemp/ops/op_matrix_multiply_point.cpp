#include "op.h"
#include "op_matrix_multiply_point.h"
#include "rd-rend2/matrix.h" // matcpy
#include "../imgui/imgui_fixedarea.h"

void OpMatrixMultiplyPoint::Init() {
	Op::Init();
	size = ImVec2(200, 90);
	pos = ImVec2(250, 300);
	
	number_of_inputs = 2;
	InitLink(0, "Mat", OP_TYPE_MATRIX);
	InitLink(1, "Vec4", OP_TYPE_VECTOR4);
	number_of_outputs = 1;
	InitLinkOutput(0, "Vec4", OP_TYPE_VECTOR4);
}


void OpMatrixMultiplyPoint::Render() {
	Op::PreRender();
	

	//FixedArea fa(pos, size, 4);
	//if (ImGui::PrintMatrix(&fa, default_link_inputs[0].matrix))
	//	default_link_inputs[0].changed++;


	Op::PostRender();
}

void OpMatrixMultiplyPoint::Update() {
	

	glm::vec4 tmp = glm::make_mat4(default_link_inputs[0].matrix) * glm::make_vec4(default_link_inputs[1].vector4);
	memcpy(default_link_outputs[0].vector4, glm::value_ptr(tmp), 4 * sizeof(float));

	default_link_outputs[0].changed++;
}

void OpMatrixMultiplyPoint::RenderEditor() {
	Op::RenderEditor();
}

std::string OpMatrixMultiplyPoint::WriteExtraData() {
	float *mat = default_link_inputs[0].matrix;
	char buf[1024];
	snprintf(buf, sizeof buf, "values %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f",
		mat[0],
		mat[1],
		mat[2],
		mat[3],
		mat[4],
		mat[5],
		mat[6],
		mat[7],
		mat[8],
		mat[9],
		mat[10],
		mat[11],
		mat[12],
		mat[13],
		mat[14],
		mat[15]
	);
	return std::string(buf);
}

void OpMatrixMultiplyPoint::ReadExtraData(char *line) {
	float *mat = default_link_inputs[0].matrix;
	sscanf(line, "values %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f",
		&mat[0],
		&mat[1],
		&mat[2],
		&mat[3],
		&mat[4],
		&mat[5],
		&mat[6],
		&mat[7],
		&mat[8],
		&mat[9],
		&mat[10],
		&mat[11],
		&mat[12],
		&mat[13],
		&mat[14],
		&mat[15]
	);
}

OpMatrixMultiplyPoint::OpMatrixMultiplyPoint() {
	Init();
}