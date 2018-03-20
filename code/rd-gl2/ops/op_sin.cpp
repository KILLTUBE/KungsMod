#include "op.h"
#include "op_sin.h"

void OpSin::Init() {
	Op::Init();
	size = ImVec2(200, 30);
	pos = ImVec2(250, 300);
	strcpy( name, "OpSin" );
	
	InitLink(0, "#", OP_TYPE_FLOAT);
	InitLinkOutput(0, "#", OP_TYPE_FLOAT);
	number_of_inputs = 1;
	number_of_outputs = 1;
	//ResizeMinimal();
	showtitle = 0;
}

void OpSin::Render() {
	Op::PreRender();
	
	ImGui::SetCursorPos(pos + ImVec2(5,5));
	ImGui::PushID(this);
	ImGui::PushItemWidth(80);
	ImGui::DragFloat(name, &tmp_val);
	ImGui::PopItemWidth();
	ImGui::PopID();

	Op::PostRender();
}

void OpSin::Update() {
	//log("matrix: %d", default_link_inputs[0].val_i);
	//log("got value: %f", val);
	tmp_val = ::sinf(val);
	auto *ol = default_link_outputs + 0;
	for (auto il : *ol->inputlinks) {
		il->val_f = tmp_val;
		if (type == OpType::OP_TYPE_SENDER)
			il->owner->Update();
	}
}

void OpSin::RenderEditor() {
	Op::RenderEditor();
}

OpSin::OpSin() {
	Init();
}