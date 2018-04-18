#include "op.h"
#include "op_value.h"

void OpValue::Init() {
	Op::Init();
	size = ImVec2(150, 30);
	pos = ImVec2(250, 300);
	strcpy( name, "OpValue" );

	InitLink(0, "#", OP_TYPE_FLOAT);
	InitLinkOutput(0, "#", OP_TYPE_FLOAT);
	number_of_inputs = 1;
	number_of_outputs = 1;
	//ResizeMinimal();
	showtitle = 0;
}

void OpValue::Render() {
	Op::PreRender();
	
	ImGui::SetCursorPos(pos + ImVec2(5,5));
	ImGui::PushID(this);
	ImGui::PushItemWidth(80);
	default_link_inputs[0].changed += (int)ImGui::DragFloat(name, &val, 0.2f, 0.0f, 0.0f, "%.3f");
	ImGui::PopItemWidth();
	ImGui::PopID();

	Op::PostRender();
}

void OpValue::Update() {
	default_link_outputs[0].SetValue(val);
}

void OpValue::RenderEditor() {
	Op::RenderEditor();
}

std::string OpValue::WriteExtraData() {
	char buf[1024];
	snprintf(buf, sizeof buf, "value %f",
		val
	);
	return std::string(buf);
}

void OpValue::ReadExtraData(char *line) {
	sscanf(line, "value %f",
		&val
	);
}

OpValue::OpValue() {
	Init();
}