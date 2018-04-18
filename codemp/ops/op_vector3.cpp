#include "op.h"
#include "op_vector3.h"
#include "../imgui/imgui_fixedarea.h"

void OpVector3::Init() {
	Op::Init();
	size = ImVec2(200, 30);
	pos = ImVec2(250, 300);
	
	InitLink(0, "#", OP_TYPE_VECTOR3);
	InitLinkOutput(0, "#", OP_TYPE_VECTOR3);
	number_of_inputs = 1;
	number_of_outputs = 1;
	vector3[0] = 0.0f;
	vector3[1] = 0.0f;
	vector3[2] = 0.0f;
}


void OpVector3::Render() {
	Op::PreRender();
	

	FixedArea fa(pos, size, 3);
	if (ImGui::PrintVector3(&fa, default_link_inputs[0].vector3))
		default_link_inputs[0].changed++;


	Op::PostRender();
}

void OpVector3::Update() {
	default_link_outputs[0].vector4[0] = default_link_inputs[0].vector3[0];
	default_link_outputs[0].vector4[1] = default_link_inputs[0].vector3[1];
	default_link_outputs[0].vector4[2] = default_link_inputs[0].vector3[2];
	default_link_outputs[0].vector4[3] = 1.0f;

	memcpy(default_link_outputs[0].vector3, default_link_inputs[0].vector3, 3 * sizeof(float));
	default_link_outputs[0].changed++;
}

void OpVector3::RenderEditor() {
	Op::RenderEditor();
}

std::string OpVector3::WriteExtraData() {
	char buf[1024];
	snprintf(buf, sizeof buf, "values %f %f %f",
		vector3[0],
		vector3[1],
		vector3[2]
	);
	return std::string(buf);
}

void OpVector3::ReadExtraData(char *line) {
	sscanf(line, "values %f %f %f",
		&vector3[0],
		&vector3[1],
		&vector3[2]
	);
	ResizeMinimal();
	size = ImVec2(200, 30);
}

OpVector3::OpVector3() {
	Init();
}








void OpVector3Dot::Init() {
	Op::Init();
	size = ImVec2(100, 30);
	pos = ImVec2(250, 300);
	
	InitLink(0, "#", OP_TYPE_VECTOR3);
	InitLink(1, "#", OP_TYPE_VECTOR3);
	InitLinkOutput(0, "#", OP_TYPE_FLOAT);
	number_of_inputs = 2;
	number_of_outputs = 1;
	vector3[0] = 0.0f;
	vector3[1] = 0.0f;
	vector3[2] = 0.0f;
	default_link_outputs[0].val_f = 0.0f;
}


void OpVector3Dot::Render() {
	Op::PreRender();
	
	ImGui::SetCursorPos(pos);
	ImGui::PushItemWidth(size.x);
	ImGui::PushID(this);
	if (ImGui::DragFloat("", &default_link_outputs[0].val_f))
		default_link_inputs[0].changed++;
	ImGui::PopID();
	ImGui::PopItemWidth();

	Op::PostRender();
}

void OpVector3Dot::Update() {
	float *a = default_link_inputs[0].vector3;
	float *b = default_link_inputs[1].vector3;

	float dot = a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
	default_link_outputs[0].val_f = dot;
}

void OpVector3Dot::RenderEditor() {
	Op::RenderEditor();
}

std::string OpVector3Dot::WriteExtraData() {
	char buf[1024];
	snprintf(buf, sizeof buf, "values %f %f %f",
		vector3[0],
		vector3[1],
		vector3[2]
	);
	return std::string(buf);
}

void OpVector3Dot::ReadExtraData(char *line) {
	sscanf(line, "values %f %f %f",
		&vector3[0],
		&vector3[1],
		&vector3[2]
	);
	ResizeMinimal();
	size = ImVec2(200, 30);
}

OpVector3Dot::OpVector3Dot() {
	Init();
}