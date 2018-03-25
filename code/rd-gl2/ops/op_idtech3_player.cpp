#include "op.h"
#include "op_idtech3_player.h"

extern "C" {
//#include <renderergl2\tr_local.h>
//#include <server\server.h>
}

#include "../imgui/imgui_fixedarea.h"

void OpPlayer::Init() {
	Op::Init();
	size = ImVec2(200, 30);
	pos = ImVec2(250, 300);
	number_of_inputs = 0;
	InitLink(0, "#", OP_TYPE_FLOAT);
	number_of_outputs = 2;
	InitLinkOutput(0, "Origin", OP_TYPE_VECTOR3);
	InitLinkOutput(1, "Viewangles", OP_TYPE_VECTOR3);
	ResizeMinimal();
	showtitle = 1;
}

void OpPlayer::Render() {
	Op::PreRender();
	
	//ImGui::SetCursorPos(pos + ImVec2(5,5));
	//ImGui::PushID(this);
	//ImGui::PushItemWidth(80);
	//float tmp_val;
	//ImGui::DragFloat(name, &tmp_val);
	//ImGui::PopItemWidth();
	//ImGui::PopID();

	
	size.y = 50;

	FixedArea fa(pos, size, 3);

	ImGui::PrintVector3(&fa, default_link_outputs[0].vector3);
	fa.NextRow();
	ImGui::PrintVector3(&fa, default_link_outputs[1].vector3);


	Op::PostRender();
}

void OpPlayer::Update() {

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

void OpPlayer::RenderEditor() {
	Op::RenderEditor();
}

OpPlayer::OpPlayer() {
	Init();
}