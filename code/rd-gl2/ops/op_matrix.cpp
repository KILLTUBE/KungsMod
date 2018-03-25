#include "op.h"
#include "op_matrix.h"
#include "../matrix.h" // matcpy
#include "../imgui/imgui_fixedarea.h"

void OpMatrix::Init() {
	Op::Init();
	size = ImVec2(200, 90);
	pos = ImVec2(250, 300);
	
	InitLink(0, "#", OP_TYPE_MATRIX);
	InitLinkOutput(0, "#", OP_TYPE_MATRIX);
	number_of_inputs = 1;
	number_of_outputs = 1;
}


void OpMatrix::Render() {
	Op::PreRender();
	

	FixedArea fa(pos, size, 4);
	if (ImGui::PrintMatrix(&fa, default_link_inputs[0].matrix))
		default_link_inputs[0].changed++;


	Op::PostRender();
}

void OpMatrix::Update() {
	matcpy(default_link_outputs[0].matrix, default_link_inputs[0].matrix);
	default_link_outputs[0].changed++;
}

void OpMatrix::RenderEditor() {
	Op::RenderEditor();
}

std::string OpMatrix::WriteExtraData() {
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

void OpMatrix::ReadExtraData(char *line) {
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

OpMatrix::OpMatrix() {
	Init();
}