#include "op.h"
#include "op_prefab_output.h"


void OpPrefabOutput::Init() {
	Op::Init();
	size = ImVec2(300, 30);
	pos = ImVec2(250, 300);
	strcpy( name, "OpPrefabOutput" );

	outputid = 0;
	
	number_of_inputs = 1;
	InitLink(0, "Out", OP_TYPE_PREFAB_OUTPUT);
	number_of_outputs = 0;
	ResizeMinimal();
	isPrefabOutput = 1;
}

void OpPrefabOutput::Render() {
	Op::PreRender();

	ImGui::SetCursorPos(pos + ImVec2(5,5));
	ImGui::Text("%d", outputid);

	Op::PostRender();
}

void OpPrefabOutput::Update() {
}

void OpPrefabOutput::RenderEditor() {
	Op::RenderEditor();
	ImGui::Text("input[0].valf=%.2f", default_link_inputs[0].val_f);
}

std::string OpPrefabOutput::WriteExtraData() {
	//fprintf(f, "code %s",
	//	code
	//);
	return std::string("");
}

void OpPrefabOutput::ReadExtraData(char *line) {
	//sscanf(line, "code %[^\n]",
	//	&code
	//);
}

OpPrefabOutput::OpPrefabOutput() {
	Init();
}