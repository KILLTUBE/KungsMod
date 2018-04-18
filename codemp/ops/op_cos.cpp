#include "op.h"
#include "op_cos.h"

void OpCos::Init() {
	Op::Init();
	size = ImVec2(200, 30);
	pos = ImVec2(250, 300);
	InitLink(0, "#", OP_TYPE_FLOAT);
	InitLinkOutput(0, "#", OP_TYPE_FLOAT);
	number_of_inputs = 1;
	number_of_outputs = 1;
	//ResizeMinimal();
	showtitle = 0;
}

void OpCos::Render() {
	Op::PreRender();

	ImGui::SetCursorPos(pos + ImVec2(5,5));
	ImGui::PushID(this);
	ImGui::PushItemWidth(80);
	ImGui::DragFloat(name, &tmp_val);
	ImGui::PopItemWidth();
	ImGui::PopID();

	Op::PostRender();
}

void OpCos::Update() {
	tmp_val = ::cosf(val);
	default_link_outputs[0].SetValue(tmp_val);
}

void OpCos::RenderEditor() {
	Op::RenderEditor();
}

OpCos::OpCos() {
	Init();
}