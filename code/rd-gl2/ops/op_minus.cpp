#include "op.h"
#include "op_minus.h"

void OpMinus::Init() {
	Op::Init();
	size = ImVec2(200, 30);
	pos = ImVec2(250, 300);
	strcpy( name, "OpMinus" );
	InitLink(0, "#", OP_TYPE_FLOAT);
	InitLink(1, "#", OP_TYPE_FLOAT);
	InitLinkOutput(0, "#", OP_TYPE_FLOAT);
	number_of_inputs = 2;
	number_of_outputs = 1;
	//ResizeMinimal();
	showtitle = 0;
}

void OpMinus::Render() {
	Op::PreRender();
	
	ImGui::SetCursorPos(pos + ImVec2(5,5));
	ImGui::PushID(this);
	ImGui::PushItemWidth(80);
	ImGui::DragFloat(name, &tmp_val);
	ImGui::PopItemWidth();
	ImGui::PopID();

	Op::PostRender();
}

void OpMinus::Update() {
	tmp_val = val_a - val_b;
	auto *ol = default_link_outputs + 0;
	for (auto il : *ol->inputlinks) {
		il->val_f = tmp_val;
		if (type == OpType::OP_TYPE_SENDER)
			il->owner->Update();
	}
}

void OpMinus::RenderEditor() {
	Op::RenderEditor();
}

OpMinus::OpMinus() {
	Init();
}