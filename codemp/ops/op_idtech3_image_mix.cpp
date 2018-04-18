#include "op.h"
#include "op_idtech3_image_mix.h"

extern "C" {
//#include <renderergl2\tr_local.h>
//#include <server\server.h>
}

#include "../imgui/imgui_fixedarea.h"

#include "../rd-rend2/tr_local.h"

void OpIDTech3ImageMix::Init() {
	Op::Init();
	size = ImVec2(128, 128);
	pos = ImVec2(250, 300);
	number_of_inputs = 2;
	InitLink(0, "#", OP_TYPE_IMAGE);
	InitLink(1, "#", OP_TYPE_IMAGE);
	number_of_outputs = 1;
	InitLinkOutput(0, "#", OP_TYPE_IMAGE);

	
	//int hdrFormat = GL_RGBA8;
	////if (r_hdr->integer)
	////	hdrFormat = GL_RGBA16F;
	//byte	*data = (byte *)malloc(2048 * 2048 * 4);
	////Com_Memset(data, 255, sizeof(data));
	//int w = 2048;
	//int h = 2048;
	//
	//for (int i=0; i<w*h*4; i+=4) {
	//	data[i+0] = 255;
	//	data[i+1] = 0;
	//	data[i+2] = 0;
	//	data[i+3] = 255;
	//}
	//tr.whiteImage = R_CreateImage("op red out", (byte *)data, 2048, 2048, IMGTYPE_COLORALPHA, IMGFLAG_NONE, hdrFormat);
	//red = tr.numImages - 1;
	//
	//for (int i=0; i< w*h*4; i+=4) {
	//	data[i+0] = 0;
	//	data[i+1] = 255;
	//	data[i+2] = 0;
	//	data[i+3] = 255;
	//}
	//tr.whiteImage = R_CreateImage("op green out", (byte *)data, 2048, 2048, IMGTYPE_COLORALPHA, IMGFLAG_NONE, hdrFormat);
	//green = tr.numImages - 1;
	//
	//for (int i=0; i< w*h*4; i+=4) {
	//	data[i+0] = 0;
	//	data[i+1] = 0;
	//	data[i+2] = 255;
	//	data[i+3] = 255;
	//}
	//tr.whiteImage = R_CreateImage("op blue out", (byte *)data, 2048, 2048, IMGTYPE_COLORALPHA, IMGFLAG_NONE, hdrFormat);
	//blue = tr.numImages - 1;
	//
	//for (int i=0; i< w*h*4; i+=4) {
	//	data[i+0] = 0;
	//	data[i+1] = 0;
	//	data[i+2] = 0;
	//	data[i+3] = 0;
	//}
	//tr.whiteImage = R_CreateImage("op alpha out", (byte *)data, 2048, 2048, IMGTYPE_COLORALPHA, IMGFLAG_NONE, hdrFormat);
	//alpha = tr.numImages - 1;


	showtitle = 1;
}

void OpIDTech3ImageMix::Render() {
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

	//if (image_id >= 0 && image_id <= 4095) {
	//	image_t *image = tr.images[image_id];
	//	if (image != NULL) {
	//		ImGui::Image((ImTextureID)image->texnum, size - ImVec2(2,2));
	//	} else {
	//		ImGui::Text("image == NULL");
	//	}
	//} else {
	//	ImGui::Text("image_id must be 0 to 4095");
	//}
	Op::PostRender();
}

void OpIDTech3ImageMix::Update() {
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

void OpIDTech3ImageMix::RenderEditor() {
	

	if (ImGui::Button("from texture jpg")) {

		char *shortname = "models/map_objects/pbr_test/Body.jpg";

		byte *dataPic;
		int width;
		int height;
		R_LoadImage(shortname, &dataPic, &width, &height);
		imgui_log("shortname=%s data=%p width=%d height=%d\n", shortname, dataPic, width, height);


		//int hdrFormat = GL_RGBA8;
		////if (r_hdr->integer)
		////	hdrFormat = GL_RGBA16F;
		//byte	*data = (byte *)malloc(2048 * 2048 * 4);
		////Com_Memset(data, 255, sizeof(data));
		//int w = width;
		//int h = height;
		//
		//for (int i=0; i<w*h*4; i+=4) {
		//	data[i+0] = dataPic[i+0];
		//	data[i+1] = 0;
		//	data[i+2] = 0;
		//	data[i+3] = 255;
		//}
		//tr.whiteImage = R_CreateImage("op red out", (byte *)data, 2048, 2048, IMGTYPE_COLORALPHA, IMGFLAG_NONE, hdrFormat);
		//red = tr.numImages - 1;
		//
		//for (int i=0; i< w*h*4; i+=4) {
		//	data[i+0] = 0;
		//	data[i+1] = dataPic[i+1];
		//	data[i+2] = 0;
		//	data[i+3] = 255;
		//}
		//tr.whiteImage = R_CreateImage("op green out", (byte *)data, 2048, 2048, IMGTYPE_COLORALPHA, IMGFLAG_NONE, hdrFormat);
		//green = tr.numImages - 1;
		//
		//for (int i=0; i< w*h*4; i+=4) {
		//	data[i+0] = 0;
		//	data[i+1] = 0;
		//	data[i+2] = dataPic[i+2];
		//	data[i+3] = 255;
		//}
		//tr.whiteImage = R_CreateImage("op blue out", (byte *)data, 2048, 2048, IMGTYPE_COLORALPHA, IMGFLAG_NONE, hdrFormat);
		//blue = tr.numImages - 1;
		//
		//for (int i=0; i< w*h*4; i+=4) {
		//	data[i+0] = 0;
		//	data[i+1] = 0;
		//	data[i+2] = 0;
		//	data[i+3] = dataPic[i+3];
		//}
		//tr.whiteImage = R_CreateImage("op alpha out", (byte *)data, 2048, 2048, IMGTYPE_COLORALPHA, IMGFLAG_NONE, hdrFormat);
		//alpha = tr.numImages - 1;

	}


	Op::RenderEditor();
}

OpIDTech3ImageMix::OpIDTech3ImageMix() {
	Init();
}
