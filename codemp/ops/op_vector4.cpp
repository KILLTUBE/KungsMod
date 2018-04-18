#include "op.h"
#include "op_vector4.h"
#include "../imgui/imgui_fixedarea.h"

void OpVector4::Init() {
	Op::Init();
	size = ImVec2(200, 30);
	pos = ImVec2(250, 300);
	
	InitLink(0, "#", OP_TYPE_VECTOR4);
	InitLinkOutput(0, "#", OP_TYPE_VECTOR4);
	number_of_inputs = 1;
	number_of_outputs = 1;
	vector4[0] = 0.0f;
	vector4[1] = 0.0f;
	vector4[2] = 0.0f;
	vector4[3] = 0.0f;
}


void OpVector4::Render() {
	Op::PreRender();
	

	FixedArea fa(pos, size, 4);
	if (ImGui::PrintVector4(&fa, default_link_inputs[0].vector4))
		default_link_inputs[0].changed++;


	Op::PostRender();
}

void OpVector4::Update() {
	memcpy(default_link_outputs[0].vector4, default_link_inputs[0].vector4, 4 * sizeof(float));
	default_link_outputs[0].changed++;
}

void OpVector4::RenderEditor() {
	Op::RenderEditor();
}

std::string OpVector4::WriteExtraData() {
	char buf[1024];
	snprintf(buf, sizeof buf, "values %f %f %f %f",
		vector4[0],
		vector4[1],
		vector4[2],
		vector4[3]
	);
	return std::string(buf);
}

void OpVector4::ReadExtraData(char *line) {
	sscanf(line, "values %f %f %f %f",
		&vector4[0],
		&vector4[1],
		&vector4[2],
		&vector4[3]
	);
	ResizeMinimal();
	size = ImVec2(200, 30);
}

OpVector4::OpVector4() {
	Init();
}