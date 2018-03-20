#include "op.h"
#include "op_prefab_input.h"

void OpPrefabInput::Init() {
	Op::Init();
	size = ImVec2(300, 30);
	pos = ImVec2(250, 300);
	strcpy( name, "OpPrefabInput" );
	inputid = 0;
	
	number_of_inputs = 0;
	number_of_outputs = 1;
	InitLinkOutput(0, "In", OP_TYPE_PREFAB_INPUT);
	ResizeMinimal();
	isPrefabInput = 1;
}

void OpPrefabInput::Render() {
	Op::PreRender();

	ImGui::SetCursorPos(pos + ImVec2(5,5));
	ImGui::Text("%d", inputid);

	Op::PostRender();
}

void OpPrefabInput::Update() {
}

void OpPrefabInput::RenderEditor() {
	Op::RenderEditor();

}

std::string OpPrefabInput::WriteExtraData() {
	//fprintf(f, "code %s",
	//	code
	//);
	return std::string("");
}

void OpPrefabInput::ReadExtraData(char *line) {
	//sscanf(line, "code %[^\n]",
	//	&code
	//);
}

OpPrefabInput::OpPrefabInput() {
	Init();
}