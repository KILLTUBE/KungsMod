#include "op.h"
#include "op_craft.h"
#include "../include_console.h"

void OpCraft::Init() {
	Op::Init();
	size = ImVec2(256, 256);
	pos = ImVec2(250, 300);
	strcpy( name, "OpCraft" );
	strcpy( default_link_inputs[0].name, "Chunks X");
	strcpy( default_link_inputs[1].name, "Chunks Y");

	//op_init_link

	number_of_inputs = 2;
	number_of_outputs = 0;
	ResizeMinimal();

}

void OpCraft::Render() {
	Op::PreRender();
	
	Op::PostRender();
}

void OpCraft::Update() {
	if (cache_ingoing_connections == 0)
		return;
	imgui_log("new chunks i: %s\n", default_link_inputs[0].val_i);
	imgui_log("new chunks j: %s\n", default_link_inputs[1].val_i);
}

void OpCraft::RenderEditor() {
	Op::RenderEditor();

}

OpCraft::OpCraft() {
	Init();
}