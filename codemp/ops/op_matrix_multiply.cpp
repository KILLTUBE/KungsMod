#include "op.h"
#include "op_matrix_multiply.h"

#include "rd-rend2/matrix.h"


void OpMatrixMultiply::Init() {
	Op::Init();
	size = ImVec2(200, 90);
	strcpy( name, "OpMatrixMultiply" );
	for (int i=0; i<16; i++) {
		InitLink(i, "#", OP_TYPE_MATRIX);
	}
	InitLinkOutput(0, "#", OP_TYPE_MATRIX);
	number_of_inputs = 2;
	number_of_outputs = 1;
}

#include "../imgui/imgui_fixedarea.h"

void OpMatrixMultiply::Render() {
	Op::PreRender();
	
	FixedArea fa(pos, size, 4);
	ImGui::PrintMatrix(&fa, default_link_outputs[0].matrix);
	Op::PostRender();
}

void OpMatrixMultiply::Update() {

	// I dont know why, but this doesn't update when links are removed/added, when Inputs/Outputs arent shown... so lets just update all the time lol

	//if ( ! forcereload)
	//	return;

	//if (!strcmp(name, "MatMulHurr"))
	//	imgui_log("upddate matrix multiply\n");

	// multiply first 2 matrices together (always exist)

	//std::vector<int> valid_inputs(16);
	//for (int i=0; i<number_of_inputs; i++) {
	//	if (default_link_inputs[i].cached_backlinks->size() == 0)
	//		continue;
	//
	//	valid_inputs.push_back(i);
	//}
	//
	//
	//// we cant calculate anything without at least 2 matrices
	//if (valid_inputs.size() < 2)
	//	return;

	mat_multiply(default_link_outputs[0].matrix, matrix_a, matrix_b);

	for (int i=2; i<number_of_inputs; i++) {

		if (default_link_inputs[i].cached_backlinks->size() == 0)
			continue;
		// dont calculate inputs with no connection, so we can just leave some empty spaces to try&error stuff inbetween them for fast testing

		mat_multiply(default_link_outputs[0].matrix,default_link_outputs[0].matrix, default_link_inputs[i].matrix);
	}
	
	default_link_outputs[0].changed++;
}

void OpMatrixMultiply::RenderEditor() {
	Op::RenderEditor();
	ImGui::DragInt("inputs", &number_of_inputs, 1.0f, 2, 16);
	// ImGui will change the value to whatever the user types in, so we need to force the legal range
	if (number_of_inputs > 16)
		number_of_inputs = 16;
}

std::string OpMatrixMultiply::WriteExtraData() {
	char buf[1024];
	snprintf(buf, sizeof buf, "inputs %d",
		number_of_inputs
	);
	return std::string(buf);
}

void OpMatrixMultiply::OnLinkDisconnect(int id) {
	// reset matrix when we remove the link, so we cont need this std::vector shit to detect the first two "real" matrices... we just calculate all
	// multiplying by identity doesnt matters
	mat_identity(default_link_inputs[id].matrix);
	forcereload++;
}

void OpMatrixMultiply::ReadExtraData(char *line) {
	sscanf(line, "inputs %d",
		&number_of_inputs
	);
	size = ImVec2(200, 90); // just force it for now
}

OpMatrixMultiply::OpMatrixMultiply() {
	Init();
}
