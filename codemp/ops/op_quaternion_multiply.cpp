#include "op.h"
#include "op_quaternion_multiply.h"

#include "rd-rend2/matrix.h"


void OpQuaternionMultiply::Init() {
	Op::Init();
	size = ImVec2(200, 90);
	for (int i=0; i<16; i++) {
		InitLink(i, "Q", OP_TYPE_QUAT);
	}
	InitLinkOutput(0, "Q", OP_TYPE_QUAT);
	number_of_inputs = 2;
	number_of_outputs = 1;
}

#include "../imgui/imgui_fixedarea.h"

void OpQuaternionMultiply::Render() {
	Op::PreRender();
	FixedArea fa(pos, size, 4);
	//if (ImGui::PrintQuat(&fa, default_link_outputs[0].quat))
	//	default_link_inputs[0].changed++;
	Op::PostRender();
}

void OpQuaternionMultiply::Update() {

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

	default_link_outputs[0].quat = default_link_inputs[0].quat * default_link_inputs[1].quat;

	//mat_multiply(default_link_outputs[0].matrix, matrix_a, matrix_b);

	for (int i=2; i<number_of_inputs; i++) {

		if (default_link_inputs[i].cached_backlinks->size() == 0)
			continue;
		// dont calculate inputs with no connection, so we can just leave some empty spaces to try&error stuff inbetween them for fast testing

		//mat_multiply(default_link_outputs[0].matrix,default_link_outputs[0].matrix, default_link_inputs[i].matrix);
		default_link_outputs[0].quat *= default_link_inputs[i].quat;
	}
	
	
	// todo: if (has op which expects matrix as output) {
	auto tmpmat = glm::mat4(default_link_outputs[0].quat);
	matcpy(default_link_outputs[0].matrix, glm::value_ptr(tmpmat));

	default_link_outputs[0].changed++;
}

void OpQuaternionMultiply::RenderEditor() {
	Op::RenderEditor();
	ImGui::DragInt("inputs", &number_of_inputs, 1.0f, 2, 16);
	// ImGui will change the value to whatever the user types in, so we need to force the legal range
	if (number_of_inputs > 16)
		number_of_inputs = 16;
}

std::string OpQuaternionMultiply::WriteExtraData() {
	char buf[1024];
	snprintf(buf, sizeof buf, "inputs %d",
		number_of_inputs
	);
	return std::string(buf);
}

void OpQuaternionMultiply::OnLinkDisconnect(int id) {
	// reset matrix when we remove the link, so we cont need this std::vector shit to detect the first two "real" matrices... we just calculate all
	// multiplying by identity doesnt matters
	mat_identity(default_link_inputs[id].matrix);
	forcereload++;
}

void OpQuaternionMultiply::ReadExtraData(char *line) {
	sscanf(line, "inputs %d",
		&number_of_inputs
	);
	size = ImVec2(200, 90); // just force it for now
}

OpQuaternionMultiply::OpQuaternionMultiply() {
	Init();
}
