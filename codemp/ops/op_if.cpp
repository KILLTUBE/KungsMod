#include "op.h"
#include "op_if.h"

void OpIf::Init() {
	Op::Init();
	size = ImVec2(200, 30);
	pos = ImVec2(250, 300);
	strcpy( name, "OpIf" );
	
	InitLink(0, "a", OP_TYPE_FLOAT);
	InitLink(1, "b", OP_TYPE_FLOAT);
	InitLinkOutput(0, "Y", OP_TYPE_FLOAT);
	InitLinkOutput(1, "N", OP_TYPE_FLOAT);
	number_of_inputs = 2;
	number_of_outputs = 2;
	//ResizeMinimal();

}

void OpIf::Render() {
	Op::PreRender();
	
	ImGui::SetCursorPos(pos + ImVec2(5,5));
	ImGui::PushID(this);
	ImGui::PushItemWidth(150);
	ImGui::InputFloat(name, &tmp_val);
	ImGui::PopItemWidth();
	ImGui::PopID();

	Op::PostRender();
}

void OpIf::Update() {
	tmp_val = val_a - val_b;
	auto *ol = default_link_outputs + 0;
	for (auto il : *ol->inputlinks) {
		il->val_f = tmp_val;
		if (type == OpType::OP_TYPE_SENDER)
			il->owner->Update();
	}
}

void OpIf::RenderEditor() {
	Op::RenderEditor();
}

OpIf::OpIf() {
	Init();
}
