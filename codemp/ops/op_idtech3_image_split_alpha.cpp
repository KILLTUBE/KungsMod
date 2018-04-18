#include "op.h"
#include "op_idtech3_image_split_alpha.h"

extern "C" {
//#include <renderergl2\tr_local.h>
//#include <server\server.h>
}

#include "../imgui/imgui_fixedarea.h"

#include "../rd-rend2/tr_local.h"

void OpIDTech3ImageSplitAlpha::Init() {
	Op::Init();
	size = ImVec2(128, 128);
	pos = ImVec2(250, 300);
	number_of_inputs = 1;
	InitLink(0, "#", OP_TYPE_IMAGE);
	number_of_outputs = 2;
	InitLinkOutput(0, "rgb", OP_TYPE_IMAGE);
	InitLinkOutput(1, "a", OP_TYPE_IMAGE);
	showtitle = 1;
}

#include "../include_console.h"

void OpIDTech3ImageSplitAlpha::OnLinkConnect(int id) {
	// now the annoying thing...
	// we only get the image_id... but the image RGBA data itself is nowhere saved... so we read the name and simply load the image again from disc
	// atm i can think about 3 solutions:
	// 1) simply dont we the image, e.g. a new flag called IMGFLAG_CACHED
	// 2) get get of CPU image manipulation and start using the GPU, the advantage is one can even write new operators at runtime, using GLSL (highly dynamic), but thats a bit too complex atm
	// 3) render image->texnum to FBO and read the pixels from that

	// probably longterm, option 2 is best... or different operator sets use their own strategy

	image_t *toSplit = tr.images + handle_in_rgba;
	if (toSplit == NULL) {
		imgui_log("cant split image_id=%d, its a NULL image_t\n", handle_in_rgba);
		return;
	}
	const char *input_shader_name = toSplit->imgName;


	if (toSplit->data == NULL) {
		imgui_log("toSplit->data == NULL\n");
		return;
	}

	byte *dataPic = (byte *)toSplit->data;
	int width = toSplit->width;
	int height = toSplit->height;
	//R_LoadImage(input_shader_name, &dataPic, &width, &height);
	//imgui_log("splitting... shortname=%s data=%p width=%d height=%d\n", input_shader_name, dataPic, width, height);
	//if (dataPic == NULL) {
	//	imgui_log("dataPic == NULL, ending\n");
	//	return;
	//}


	int hdrFormat = GL_RGBA8;
	//if (r_hdr->integer)
	//	hdrFormat = GL_RGBA16F;
	int w = toSplit->width;
	int h = toSplit->height;
	byte	*data = (byte *)malloc(w * h * 4);
	//Com_Memset(data, 255, sizeof(data));

	for (int i=0; i<w*h*4; i+=4) {
		data[i+0] = dataPic[i+0];
		data[i+1] = dataPic[i+1];
		data[i+2] = dataPic[i+2];
		data[i+3] = 255;
	}
	image_t *image_rgb = R_CreateImage("OpImageSplitAlpha rgb out", (byte *)data, w, h, IMGTYPE_COLORALPHA, IMGFLAG_NONE, hdrFormat);
	handle_out_rgb = image_rgb->id;
	
	// output.red = input.alpha
	for (int i=0; i< w*h*4; i+=4) {
		data[i+0] = dataPic[i+3];
		data[i+1] = 0;
		data[i+2] = 0;
		data[i+3] = 255;
	}
	image_t *alpha = R_CreateImage("OpImageSplitAlpha alpha out", (byte *)data, w, h, IMGTYPE_COLORALPHA, IMGFLAG_NONE, hdrFormat);
	handle_out_alpha = alpha->id;
}

void OpIDTech3ImageSplitAlpha::Render() {
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

	if (handle_in_rgba >= 0 && handle_in_rgba <= 4095) {
		image_t *image = tr.images + handle_in_rgba;
		if (image != NULL) {
			ImGui::Image((ImTextureID)image->texnum, size - ImVec2(2,2));
		} else {
			ImGui::Text("image == NULL");
		}
	} else {
		ImGui::Text("handle_in_rgba must be 0 to 4095");
	}
	Op::PostRender();
}

void OpIDTech3ImageSplitAlpha::Update() {
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

void OpIDTech3ImageSplitAlpha::RenderEditor() {
	Op::RenderEditor();
}

OpIDTech3ImageSplitAlpha::OpIDTech3ImageSplitAlpha() {

	Init();
}