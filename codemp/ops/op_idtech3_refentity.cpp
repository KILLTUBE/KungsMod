#include "op.h"
#include "op_idtech3_refentity.h"

extern "C" {
//#include <renderergl2\tr_local.h>
//#include <server\server.h>
}

//#include <tr_local.h>

#include "../imgui/imgui_fixedarea.h"
#include "../include_ccall.h"

OpIDTech3RefEntity *renderme = NULL;
CCALL void opsys_idtech3_render_refentities() {
	//if (renderme == NULL)
	//	return;
	//refEntity_t ent;
	//ent.origin[0] = renderme->default_link_inputs[0].vector3[0];
	//ent.origin[1] = renderme->default_link_inputs[0].vector3[1];
	//ent.origin[2] = renderme->default_link_inputs[0].vector3[2];
	//ent.axis[0][0] = 1;
	//ent.axis[0][1] = 0;
	//ent.axis[0][2] = 0;
	//ent.axis[1][0] = 0;
	//ent.axis[1][1] = 1;
	//ent.axis[1][2] = 0;
	//ent.axis[2][0] = 0;
	//ent.axis[2][1] = 0;
	//ent.axis[2][2] = 1;
	//ent.backlerp = renderme->default_link_inputs[1].val_f;
	//ent.hModel = (int)renderme->default_link_inputs[2].val_f;
	//ent.skinNum = (int)renderme->default_link_inputs[3].val_f;
	//ent.frame = (int)renderme->default_link_inputs[4].val_f;;
	//ent.oldframe = (int)renderme->default_link_inputs[5].val_f;
	//ent.reType = RT_MODEL;
	//ent.customShader = 0;
	//ent.customSkin = 0;
	////ent.
	////ent.axis[0]
	//
	//RE_AddRefEntityToScene(&ent);
}

void OpIDTech3RefEntity::Init() {
	renderme = this;
	Op::Init();
	size = ImVec2(200, 30);
	pos = ImVec2(250, 300);
	number_of_inputs = 6;
	InitLink(0, "Origin", OP_TYPE_VECTOR3);
	InitLink(1, "backlerp", OP_TYPE_FLOAT);
	InitLink(2, "model", OP_TYPE_FLOAT); // todo: make int
	InitLink(3, "skin", OP_TYPE_FLOAT); // todo: make int
	InitLink(4, "frame", OP_TYPE_FLOAT); // todo: make int
	InitLink(5, "oldframe", OP_TYPE_FLOAT); // todo: make int
	number_of_outputs = 0;
	InitLinkOutput(0, "Origin", OP_TYPE_VECTOR3);
	ResizeMinimal();
	showtitle = 1;
}

void OpIDTech3RefEntity::Render() {
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

void OpIDTech3RefEntity::Update() {

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

void OpIDTech3RefEntity::RenderEditor() {
	Op::RenderEditor();
}

OpIDTech3RefEntity::OpIDTech3RefEntity() {
	Init();
}