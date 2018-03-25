#include "op.h"
#include "op_logger.h"

#include "../include_console.h"

void OpLogger::Init() {
	Op::Init();
	size = ImVec2(256, 256);
	pos = ImVec2(250, 300);
	strcpy( name, "OpLogger" );
	strcpy( default_link_inputs[0].name, "Text");
	strcpy( default_link_inputs[0].val_str, "no value set");
	number_of_inputs = 1;
	number_of_outputs = 0;
	ResizeMinimal();
}

void OpLogger::Render() {
	Op::PreRender();
	
	Op::PostRender();
}

void OpLogger::Update() {
	if (cache_ingoing_connections == 0)
		return;
	imgui_log("OpLogger: %s", default_link_inputs[0].val_str);
}

void OpLogger::RenderEditor() {
	Op::RenderEditor();

}

OpLogger::OpLogger() {
	Init();
}