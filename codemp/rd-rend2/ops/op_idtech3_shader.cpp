#include "op.h"
#include "op_idtech3_shader.h"

extern "C" {
//#include <renderergl2\tr_local.h>
//#include <server\server.h>
}

#include "../imgui/imgui_fixedarea.h"

#include "../tr_local.h"

void OpIDTech3Shader::Init() {
	Op::Init();
	size = ImVec2(128, 128);
	pos = ImVec2(250, 300);
	number_of_inputs = 4;
	InitLink(0, "shader", OP_TYPE_SHADER);
	InitLink(1, "diffuse", OP_TYPE_IMAGE);
	InitLink(2, "normal", OP_TYPE_IMAGE);
	InitLink(3, "specular", OP_TYPE_IMAGE);
	number_of_outputs = 0;
	InitLinkOutput(0, "diffuse opacity", OP_TYPE_IMAGE);
	InitLinkOutput(1, "normal height", OP_TYPE_IMAGE);
	InitLinkOutput(2, "specular gloss", OP_TYPE_IMAGE);
	
	
	showtitle = 1;
}

void OpIDTech3Shader::Render() {
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

byte *R_GetImageData(int id);

#include "../include_console.h"

void OpIDTech3Shader::OnLinkConnect(int id) {

	if (id == 0) {
		//todo: set the shader_t images to the inputs, so we could see the bound images

	}

	shader_t *shader = tr.shaders[ handle_in_shader ];
	if (shader != NULL) {
		shader->stages[0]->bundle[TB_DIFFUSEMAP ].image[0] = tr.images + handle_image_in_diffuse ;
		shader->stages[0]->bundle[TB_NORMALMAP  ].image[0] = tr.images + handle_image_in_normal  ;
		shader->stages[0]->bundle[TB_SPECULARMAP].image[0] = tr.images + handle_image_in_specular;
	}

	// now we can generate the three shaders rend2 is using internally, which are:
	// stage[0]->texturebundle[0] = 

	/*
	TB_DIFFUSEMAP  = TB_COLORMAP    = 0
	TB_NORMALMAP   = 2
	TB_SPECULARMAP = 4,	
	*/
	//TB_NORMALMAP
}

void OpIDTech3Shader::Update() {
	
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



void OpIDTech3Shader::RenderEditor() {

	Op::RenderEditor();
}

OpIDTech3Shader::OpIDTech3Shader() {

	Init();
}