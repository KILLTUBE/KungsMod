#include "op.h"
#include "op_idtech3_image_scale.h"

extern "C" {
//#include <renderergl2\tr_local.h>
//#include <server\server.h>
}

#include "../imgui/imgui_fixedarea.h"

#include "../rd-rend2/tr_local.h"

void OpIDTech3ImageScale::Init() {
	Op::Init();
	size = ImVec2(128, 128);
	pos = ImVec2(250, 300);
	number_of_inputs = 5;
	InitLink(0, "#", OP_TYPE_IMAGE);
	InitLink(1, "sr", OP_TYPE_FLOAT);
	InitLink(2, "sg", OP_TYPE_FLOAT);
	InitLink(3, "sb", OP_TYPE_FLOAT);
	InitLink(4, "sa", OP_TYPE_FLOAT);
	number_of_outputs = 1;
	InitLinkOutput(0, "#", OP_TYPE_IMAGE);
	showtitle = 1;
}

void OpIDTech3ImageScale::Render() {
	Op::PreRender();
	
	//ImGui::SetCursorPos(pos + ImVec2(5,5));
	//ImGui::PushID(this);
	//ImGui::PushItemWidth(80);
	//float tmp_val;
	//ImGui::DragFloat(name, &tmp_val);
	//ImGui::PopItemWidth();
	//ImGui::PopID();

	//FixedArea fa(pos, size, 3);
	//
	//ImGui::PrintVector3(&fa, default_link_outputs[0].vector3);
	//fa.NextRow();
	//ImGui::PrintVector3(&fa, default_link_outputs[1].vector3);
	
	ImGui::SetCursorPos(pos + ImVec2(1,1));

	if (image_id >= 0 && image_id <= 4095) {
		image_t *image = tr.images + image_id;
		if (image != NULL) {
			ImGui::Image((ImTextureID)image->texnum, size - ImVec2(2,2));
		} else {
			ImGui::Text("image == NULL");
		}
	} else {
		ImGui::Text("image_id must be 0 to 4095");
	}
	Op::PostRender();
}

void OpIDTech3ImageScale::Update() {
	//image_id = default_link_inputs[0].val_f;
	//if (image_id < 0)
	//	image_id = 0;
	//if (image_id >= 4096)
	//	image_id = 4095;

	//default_link_outputs[0].SetValue();

	//if (sv.gentities && !sv.restarting && sv.state == SS_GAME) {
	//	
	//	auto org = sv.gentities[0].r.currentOrigin;
	//	auto ang = sv.gentities[0].r.currentAngles;
	//	ang = sv.gameClients->viewangles;
	//	// backEnd.refdef.vieworg[0];tr.refdef.vieworg[0]
	//	default_link_outputs[0].SetVector3(org); 
	//	default_link_outputs[1].SetVector3(ang);
	//}
	
}

#include "../include_console.h"

void OpIDTech3ImageScale::RenderEditor() {
	Op::RenderEditor();
}

OpIDTech3ImageScale::OpIDTech3ImageScale() {
	Init();
}