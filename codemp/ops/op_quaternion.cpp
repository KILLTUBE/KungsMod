#include "op.h"
#include "op_quaternion.h"
#include "../imgui/imgui_fixedarea.h"

void OpQuaternion::Init() {
	Op::Init();
	size = ImVec2(200, 30);
	pos = ImVec2(250, 300);
	
	InitLink(0, "#", OP_TYPE_QUAT);
	InitLinkOutput(0, "#", OP_TYPE_QUAT);
	number_of_inputs = 1;
	number_of_outputs = 1;
	quat = glm::quat();
}



void OpQuaternion::Render() {
	Op::PreRender();
	FixedArea fa(pos, size, 4);
	//if (ImGui::PrintQuat(&fa, default_link_inputs[0].quat))
	//	default_link_inputs[0].changed++;
	Op::PostRender();
}

void OpQuaternion::Update() {
	memcpy(default_link_outputs[0].matrix, glm::value_ptr(glm::mat4_cast(quat)), 16 * sizeof(float));
	default_link_outputs[0].quat = quat;
	default_link_outputs[0].changed++;
}

void OpQuaternion::RenderEditor() {
	Op::RenderEditor();
	if (ImGui::Button("Reset to Identity")) {
		quat = glm::quat();
	}
}

std::string OpQuaternion::WriteExtraData() {
	char buf[1024];
	snprintf(buf, sizeof buf, "values %f %f %f %f",
		quat.w,
		quat.x,
		quat.y,
		quat.z
	);
	return std::string(buf);
}

void OpQuaternion::ReadExtraData(char *line) {
	sscanf(line, "values %f %f %f %f",
		&quat.w,
		&quat.x,
		&quat.y,
		&quat.z
	);
	ResizeMinimal();
	size = ImVec2(200, 30);
}

OpQuaternion::OpQuaternion() {
	Init();
}