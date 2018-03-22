#include "op.h"
#include "op_idtech3_shader_pbr.h"

extern "C" {
//#include <renderergl2\tr_local.h>
//#include <server\server.h>
}

#include <imgui/imgui_fixedarea.h>

#include "tr_local.h"

void OpIDTech3ShaderPBR::Init() {
	Op::Init();
	size = ImVec2(128, 128);
	pos = ImVec2(250, 300);
	number_of_inputs = 1;
	InitLink(0, "shader", OP_TYPE_SHADER);
	number_of_outputs = 0;
	InitLinkOutput(0, "#", OP_TYPE_IMAGE);
	


	showtitle = 1;
}

void OpIDTech3ShaderPBR::Render() {
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

	//if (image_out >= 0 && image_out <= 4095) {
	//	image_t *image = tr.images[image_out];
	//	if (image != NULL) {
	//		ImGui::Image((ImTextureID)image->texnum, size - ImVec2(2,2));
	//	} else {
	//		ImGui::Text("image_out == NULL");
	//	}
	//} else {
	//	ImGui::Text("image_id must be 0 to 4095");
	//}
	Op::PostRender();
}

void OpIDTech3ShaderPBR::Update() {
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

#include "include_console.h"



void OpIDTech3ShaderPBR::RenderEditor() {

	Op::RenderEditor();
}

OpIDTech3ShaderPBR::OpIDTech3ShaderPBR() {

	Init();
}