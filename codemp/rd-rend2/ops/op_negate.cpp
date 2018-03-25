#include "op.h"
#include "op_negate.h"

void OpNegate::Init() {
	Op::Init();
	size = ImVec2(200, 30);
	pos = ImVec2(250, 300);
	strcpy( name, "OpNegate" );
	
	InitLink(0, "#", OP_TYPE_FLOAT);
	InitLinkOutput(0, "#", OP_TYPE_FLOAT);
	number_of_inputs = 1;
	number_of_outputs = 1;
	//ResizeMinimal();
	showtitle = 0;
}

void OpNegate::Render() {
	Op::PreRender();
	
	ImGui::SetCursorPos(pos + ImVec2(5,5));
	ImGui::PushID(this);
	ImGui::PushItemWidth(80);
	ImGui::DragFloat(name, &out);
	ImGui::PopItemWidth();
	ImGui::PopID();

	Op::PostRender();
}

void OpNegate::Update() {
	default_link_outputs[0].SetValue( -in );
}

void OpNegate::RenderEditor() {
	Op::RenderEditor();
}

OpNegate::OpNegate() {
	Init();
}