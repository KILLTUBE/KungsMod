#include "op.h"
#include "op_plus.h"

void OpPlus::Init() {
	Op::Init();
	size = ImVec2(200, 30);
	pos = ImVec2(250, 300);
	strcpy( name, "OpPlus" );
	InitLink(0, "#", OP_TYPE_FLOAT);
	InitLink(1, "#", OP_TYPE_FLOAT);
	InitLinkOutput(0, "#", OP_TYPE_FLOAT);
	number_of_inputs = 2;
	number_of_outputs = 1;
	//ResizeMinimal();
	showtitle = 0;
}

void OpPlus::Render() {
	Op::PreRender();
	
	ImGui::SetCursorPos(pos + ImVec2(5,5));
	ImGui::PushID(this);
	ImGui::PushItemWidth(80);
	ImGui::DragFloat(name, &out);
	ImGui::PopItemWidth();
	ImGui::PopID();

	Op::PostRender();
}

void OpPlus::Update() {
	default_link_outputs[0].SetValue( val_a + val_b );
}

void OpPlus::RenderEditor() {
	Op::RenderEditor();
}

OpPlus::OpPlus() {
	Init();
}