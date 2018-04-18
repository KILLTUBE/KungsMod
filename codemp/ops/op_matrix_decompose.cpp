#include "op.h"
#include "op_matrix_decompose.h"
#include "rd-rend2/matrix.h" // matcpy
#include "../imgui/imgui_fixedarea.h"

#include "../glm/gtx/matrix_decompose.hpp"

void OpMatrixDecompose::Init() {
	Op::Init();
	size = ImVec2(200, 90);
	pos = ImVec2(250, 300);
	
	InitLink(0, "#", OP_TYPE_MATRIX);
	InitLinkOutput(0, "Scale", OP_TYPE_VECTOR4);
	InitLinkOutput(1, "Rotation", OP_TYPE_QUAT);
	InitLinkOutput(2, "Translation", OP_TYPE_VECTOR4);
	InitLinkOutput(3, "Skew", OP_TYPE_VECTOR4); // vec3 actually
	InitLinkOutput(4, "Perspective", OP_TYPE_VECTOR4);
	number_of_inputs = 1;
	number_of_outputs = 5;
}


void OpMatrixDecompose::Render() {
	Op::PreRender();
	

	FixedArea fa(pos, size, 4);
	if (ImGui::PrintMatrix(&fa, default_link_inputs[0].matrix))
		default_link_inputs[0].changed++;


	Op::PostRender();
}

void OpMatrixDecompose::Update() {

	matcpy(default_link_outputs[0].matrix, default_link_inputs[0].matrix);

		

	glm::vec3 scale;
	glm::quat rotation;
	glm::vec3 translation;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(glm::make_mat4(default_link_inputs[0].matrix), scale, rotation, translation, skew, perspective);

	// http://stackoverflow.com/questions/17918033/glm-decompose-mat4-into-translation-and-rotation
	// whyever... this flips the matrix kinda
	rotation = glm::conjugate(rotation);

	memcpy(default_link_outputs[0].vector4, glm::value_ptr(scale), 3 * sizeof(float));
	default_link_outputs[1].quat = rotation;
	memcpy(default_link_outputs[2].vector4, glm::value_ptr(translation), 3 * sizeof(float));
	memcpy(default_link_outputs[3].vector4, glm::value_ptr(skew), 3 * sizeof(float));
	memcpy(default_link_outputs[4].vector4, glm::value_ptr(perspective), 4 * sizeof(float));

	default_link_outputs[0].changed++;
	default_link_outputs[1].changed++;
	default_link_outputs[2].changed++;
	default_link_outputs[3].changed++;
	default_link_outputs[4].changed++;

}

void OpMatrixDecompose::RenderEditor() {
	Op::RenderEditor();
}

std::string OpMatrixDecompose::WriteExtraData() {
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

void OpMatrixDecompose::ReadExtraData(char *line) {
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

OpMatrixDecompose::OpMatrixDecompose() {
	Init();
}