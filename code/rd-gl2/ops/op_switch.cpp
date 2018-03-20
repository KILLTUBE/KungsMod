#include "op.h"
#include "op_switch.h"

void OpSwitch::Init() {
	Op::Init();
	size = ImVec2(256, 256);
	pos = ImVec2(250, 300);
	strcpy( name, "OpSwitch" );
	strcpy( default_link_inputs[0].name, "Text");
	number_of_inputs = 1;
	number_of_outputs = 7;
	ResizeMinimal();
	isSwitch = 1;
}

void OpSwitch::Render() {
	Op::PreRender();
	char *switchlist[16] = {
		"Escape", "w", "a", "s", "d", "f", "g", "h", "", "", "", "", "", "", ""
	};
	for (int i=0; i<7; i++)
		sprintf(default_link_outputs[i].name, "On %s", switchlist[i]);
	ResizeMinimal();
	Op::PostRender();
}

void OpSwitch::Update() {
	//log("log: %s", default_link_inputs[0].val_str);
	if (cache_ingoing_connections == 0)
		return;
	char *switchlist[16] = {
		"Escape", "w", "a", "s", "d", "f", "g", "h", "", "", "", "", "", "", ""
	};
	for (int i=0; i<7; i++) {
		if ( ! strcmp(default_link_inputs[0].val_str, switchlist[i]) ) {
			for (auto il : *default_link_outputs[i].inputlinks) {
				il->owner->Update();
			}
		}
	}

}

void OpSwitch::RenderEditor() {
	Op::RenderEditor();
}

OpSwitch::OpSwitch() {
	Init();
}