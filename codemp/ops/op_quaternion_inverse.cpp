#include "op.h"
#include "op_quaternion_inverse.h"

#include "rd-rend2/matrix.h"


void OpQuaternionInverse::Init() {
	Op::Init();
	size = ImVec2(200, 90);
	number_of_inputs = 1;
	InitLink(0, "Q", OP_TYPE_QUAT);
	number_of_outputs = 1;
	InitLinkOutput(0, "Q", OP_TYPE_QUAT);
}

#include "../imgui/imgui_fixedarea.h"

void OpQuaternionInverse::Render() {
	Op::PreRender();
	FixedArea fa(pos, size, 4);
	//if (ImGui::PrintQuat(&fa, default_link_outputs[0].quat))
	//	default_link_inputs[0].changed++;
	Op::PostRender();
}

void OpQuaternionInverse::Update() {

	// I dont know why, but this doesn't update when links are removed/added, when Inputs/Outputs arent shown... so lets just update all the time lol
	//if ( ! forcereload)
	//	return;
	
	default_link_outputs[0].quat = glm::inverse(default_link_inputs[0].quat);
	default_link_outputs[0].changed++;

	// todo: if (has op which expects matrix as output) {
	auto tmpmat = glm::mat4(default_link_outputs[0].quat);
	matcpy(default_link_outputs[0].matrix, glm::value_ptr(tmpmat));
}

void OpQuaternionInverse::RenderEditor() {
	Op::RenderEditor();
}

OpQuaternionInverse::OpQuaternionInverse() {
	Init();
}
