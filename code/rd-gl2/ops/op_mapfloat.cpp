#include "op.h"
#include "op_mapfloat.h"

void OpMapFloat::Init() {
	Op::Init();
	size = ImVec2(200, 30);
	pos = ImVec2(250, 300);
	
	number_of_inputs = 3;
	InitLink(0, "F", OP_TYPE_FLOAT);
	InitLink(1, "Add", OP_TYPE_FLOAT);
	InitLink(2, "Multiply", OP_TYPE_FLOAT);
	number_of_outputs = 1;
	InitLinkOutput(0, "F", OP_TYPE_FLOAT);
	//ResizeMinimal();
	showtitle = 0;
}

void OpMapFloat::Render() {
	Op::PreRender();
	
	ImGui::SetCursorPos(pos + ImVec2(5,5));
	ImGui::PushID(this);
	ImGui::PushItemWidth(80);
	ImGui::DragFloat(name, &out);
	ImGui::PopItemWidth();
	ImGui::PopID();

	Op::PostRender();
}

void OpMapFloat::Update() {
	out = add + in * multiply;
	default_link_outputs[0].changed++;
}

void OpMapFloat::RenderEditor() {
	Op::RenderEditor();
}

std::string OpMapFloat::WriteExtraData() {
	char buf[1024];
	snprintf(buf, sizeof buf, "add %f multiply %f",
		add,
		multiply
	);
	return std::string(buf);
}

void OpMapFloat::ReadExtraData(char *line) {
	sscanf(line, "add %f multiply %f",
		&add,
		&multiply
	);
}

OpMapFloat::OpMapFloat() {
	Init();
}