#include "op.h"
#include "op_keyboard.h"

std::list<OpKeyboard *> keyboards;

void OpKeyboard::Init() {
	Op::Init();
	size = ImVec2(256, 256);
	pos = ImVec2(250, 300);
	strcpy( name, "OpKeyboard" );
	number_of_inputs = 0;
	number_of_outputs = 1;
	strcpy(default_link_outputs[0].name, "Text");
	ResizeMinimal();
	type = OpType::OP_TYPE_SENDER;
	keyboards.push_back(this);
	isKeyboard = 1;
}

void OpKeyboard::Render() {
	Op::PreRender();
	Op::PostRender();
}

void OpKeyboard::Update() {
	LinkOutput *output = default_link_outputs + 0;
	for (auto text : events) {
		for (auto il : *output->inputlinks) {
			strcpy(il->owner->default_link_inputs->val_str, text);
			il->owner->Update();
		}
		free(text);
	}
	events.clear();
}

void OpKeyboard::RenderEditor() {
	Op::RenderEditor();
}


void OpKeyboard::Destroy() {
	Destroy();
	keyboards.remove(this);
}

OpKeyboard::OpKeyboard() {
	Init();
}