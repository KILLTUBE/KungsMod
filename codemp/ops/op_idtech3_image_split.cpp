#include "op.h"
#include "op_idtech3_image_split.h"

extern "C" {
//#include <renderergl2\tr_local.h>
//#include <server\server.h>
}

#include "../imgui/imgui_fixedarea.h"

#include "../rd-rend2/tr_local.h"

qhandle_t R_CreateImageRGBA(char *name, int width, int height, byte r, byte g, byte b, byte a);
void R_UpdateImageFromBuffer(image_t *image);
byte *R_GetImageData(int id);

void OpIDTech3ImageSplit::Init() {
	Op::Init();
	size = ImVec2(128, 128);
	pos = ImVec2(250, 300);
	number_of_inputs = 1;
	InitLink(0, "#", OP_TYPE_IMAGE);
	number_of_outputs = 4;
	InitLinkOutput(0, "r", OP_TYPE_IMAGE);
	InitLinkOutput(1, "g", OP_TYPE_IMAGE);
	InitLinkOutput(2, "b", OP_TYPE_IMAGE);
	InitLinkOutput(3, "a", OP_TYPE_IMAGE);

	
	handle_out_red   = R_CreateImageRGBA("OpImageSplit red"    , 2048, 2048, 255,   0,   0, 255);
	handle_out_green = R_CreateImageRGBA("OpImageSplit green"  , 2048, 2048,   0, 255,   0, 255);
	handle_out_blue  = R_CreateImageRGBA("OpImageSplit blue"   , 2048, 2048,   0,   0, 255, 255);
	handle_out_alpha = R_CreateImageRGBA("OpImageSplit alpha"  , 2048, 2048,   0,   0,   0, 255);


	showtitle = 1;
}

#include "../include_console.h"

void OpIDTech3ImageSplit::OnLinkConnect(int id) {

}

void OpIDTech3ImageSplit::Render() {
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

			
			image_t *image_red   = tr.images + handle_out_red  ;
			image_t *image_green = tr.images + handle_out_green;
			image_t *image_blue  = tr.images + handle_out_blue ;
			image_t *image_alpha = tr.images + handle_out_alpha;
			
			auto halfsize = size / 2;
			float halfwidth = size.x / 2;
			float halfheight = size.y / 2;
			ImGui::SetCursorPos(pos);
			ImGui::Image((ImTextureID)image_red->texnum, halfsize ); // - ImVec2(2,2)
			ImGui::SetCursorPos(pos + ImVec2(halfwidth,0));
			ImGui::Image((ImTextureID)image_green->texnum, halfsize ); // - ImVec2(2,2)
			ImGui::SetCursorPos(pos + ImVec2(0,halfheight));
			ImGui::Image((ImTextureID)image_blue->texnum, halfsize ); // - ImVec2(2,2)
			ImGui::SetCursorPos(pos + ImVec2(halfwidth,halfheight));
			ImGui::Image((ImTextureID)image_alpha->texnum, halfsize ); // - ImVec2(2,2)
		} else {
			ImGui::Text("image == NULL");
		}
	} else {
		ImGui::Text("image_id must be 0 to 4095");
	}
	Op::PostRender();
}

void OpIDTech3ImageSplit::Update() {
	
	if (DidInputsChange()) {

		imgui_log("%s->Update();\n", name);
		SetInputsUnchanged();

		// now the annoying thing...
		// we only get the image_id... but the image RGBA data itself is nowhere saved... so we read the name and simply load the image again from disc
		// atm i can think about 3 solutions:
		// 1) simply dont we the image, e.g. a new flag called IMGFLAG_CACHED
		// 2) get get of CPU image manipulation and start using the GPU, the advantage is one can even write new operators at runtime, using GLSL (highly dynamic), but thats a bit too complex atm
		// 3) render image->texnum to FBO and read the pixels from that

		// probably longterm, option 2 is best... or different operator sets use their own strategy

		image_t *toSplit = tr.images + image_id;
		if (toSplit == NULL) {
			imgui_log("cant split image_id=%d, its a NULL image_t\n", image_id);
			return;
		}
		const char *input_shader_name = toSplit->imgName;

		byte *dataPic = R_GetImageData(image_id);
		//int width;
		//int height;
		//R_LoadImage(input_shader_name, &dataPic, &width, &height);
		//imgui_log("splitting... shortname=%s data=%p width=%d height=%d\n", input_shader_name, dataPic, width, height);
		if (dataPic == NULL) {
			imgui_log("dataPic == NULL, ending\n");
			return;
		}


		int hdrFormat = GL_RGBA8;
		//if (r_hdr->integer)
		//	hdrFormat = GL_RGBA16F;
		int w = toSplit->width;
		int h = toSplit->height;
		byte	*data = NULL;
		//Com_Memset(data, 255, sizeof(data));


		// we are saving every channel into RED, so everything is going to look red...
		// its like splitting 4 channel images in gimp and every channel is just monochrome black/white, but im using the red channel for that, easiest atm

		data = R_GetImageData(handle_out_red);
		if (data) {
			for (int i=0; i<w*h*4; i+=4) {
				data[i+0] = dataPic[i+0];
				data[i+1] = 0;
				data[i+2] = 0;
				data[i+3] = 255;
			}
			R_UpdateImageFromBuffer(tr.images + handle_out_red);
		}
		
		data = R_GetImageData(handle_out_green);
		if (data) {
			for (int i=0; i< w*h*4; i+=4) {
				data[i+0] = dataPic[i+1];
				data[i+1] = 0;
				data[i+2] = 0;
				data[i+3] = 255;
			}
			R_UpdateImageFromBuffer(tr.images + handle_out_green);
		}

		data = R_GetImageData(handle_out_blue);
		if (data) {
			for (int i=0; i< w*h*4; i+=4) {
				data[i+0] = dataPic[i+2];
				data[i+1] = 0;
				data[i+2] = 0;
				data[i+3] = 255;
			}
			R_UpdateImageFromBuffer(tr.images + handle_out_blue);
		}
		
		data = R_GetImageData(handle_out_alpha);
		if (data) {
			for (int i=0; i< w*h*4; i+=4) {
				data[i+0] = dataPic[i+3];
				data[i+1] = 0;
				data[i+2] = 0;
				data[i+3] = 255;
			}
			R_UpdateImageFromBuffer(tr.images + handle_out_alpha);
		}

	}

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

void OpIDTech3ImageSplit::RenderEditor() {
	Op::RenderEditor();
}

OpIDTech3ImageSplit::OpIDTech3ImageSplit() {

	Init();
}