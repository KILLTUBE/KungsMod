#include "op.h"
#include "op_idtech3_image.h"

extern "C" {
//#include <renderergl2\tr_local.h>
//#include <server\server.h>
}

#include "../imgui/imgui_fixedarea.h"

#include "../rd-rend2/tr_local.h"

void OpIDTech3Image::Init() {
	Op::Init();
	size = ImVec2(128, 128);
	pos = ImVec2(250, 300);
	number_of_inputs = 0;
	InitLink(0, "#", OP_TYPE_IMAGE);
	number_of_outputs = 1;
	InitLinkOutput(0, "#", OP_TYPE_IMAGE);
	


	showtitle = 1;
}

void OpIDTech3Image::Render() {
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

	if (image_out >= 0 && image_out <= 4095) {
		image_t *image = tr.images + image_out;
		if (image != NULL) {
			ImGui::Image((ImTextureID)image->texnum, size - ImVec2(2,2));
		} else {
			ImGui::Text("image_out == NULL");
		}
	} else {
		ImGui::Text("image_id must be 0 to 4095");
	}
	Op::PostRender();
}

void OpIDTech3Image::Update() {
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
extern int CACHE_IMAGE;
bool OpIDTech3Image::LoadFilename(const char *filename) {
	byte *dataPic;
	int width;
	int height;
	

#if 0
	// the 259 flag also generates a normal map
	CACHE_IMAGE = 1;
	image_t *image = R_FindImageFile(filename, IMGTYPE_COLORALPHA, 259);
	CACHE_IMAGE = 0;
	image_out = image->id;
	return true;
#endif

	R_LoadImage(filename, &dataPic, &width, &height);
	imgui_log("shortname=%s data=%p width=%d height=%d\n", filename, dataPic, width, height);
	if (dataPic) {
		image_t *image = R_CreateImage(filename, (byte *)dataPic, width, height, IMGTYPE_COLORALPHA, IMGFLAG_NONE, GL_RGBA8);
		image_out = image->id;
		image->data = dataPic; // dont free anymore, keep a copy around...
		//R_Free(dataPic);
		return true;
	}
	return false;
}

void OpIDTech3Image::RenderEditor() {
	if (ImGui::Button("load models/map_objects/pbr_test/Body.jpg"))
		LoadFilename("models/map_objects/pbr_test/Body.jpg");

	if (ImGui::Button("load models/map_objects/pbr_test/Body_Normal.tga"))
		LoadFilename("models/map_objects/pbr_test/Body_Normal.tga");

	if (ImGui::Button("load models/map_objects/pbr_test/Body_RMO.jpg"))
		LoadFilename("models/map_objects/pbr_test/Body_RMO.jpg");

	Op::RenderEditor();
}

OpIDTech3Image::OpIDTech3Image() {

	Init();
}