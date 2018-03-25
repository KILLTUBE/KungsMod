#include "op.h"
#include "op_idtech3_image_color.h"

extern "C" {
//#include <renderergl2\tr_local.h>
//#include <server\server.h>
}

#include "../imgui/imgui_fixedarea.h"

#include "../tr_local.h"
#include "../include_console.h"
#include "../compose_images.h"

qhandle_t R_CreateImageRGBA(char *name, int width, int height, byte r, byte g, byte b, byte a);
byte *R_GetImageData(int id);
void Upload32(byte *data, int width, int height, imgType_t type, int flags, qboolean lightMap, GLenum internalFormat, int *pUploadWidth, int *pUploadHeight);
void R_UpdateImageFromBuffer(image_t *image) {
	GL_Bind(image);
	Upload32((byte *)image->data, image->width, image->height, image->type, image->flags, /*isLightmap*/qfalse, image->internalFormat, &image->uploadWidth, &image->uploadHeight);
	//qglTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, glWrapClampMode);
	//qglTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, glWrapClampMode);
	//GL_SelectTexture(0);
	markImageChanged(image->id);
}

void OpIDTech3ImageColor::Init() {
	Op::Init();
	size = ImVec2(128, 128);
	pos = ImVec2(250, 300);
	number_of_inputs = 4;
	InitLink(0, "r", OP_TYPE_FLOAT);
	InitLink(1, "g", OP_TYPE_FLOAT);
	InitLink(2, "b", OP_TYPE_FLOAT);
	InitLink(3, "a", OP_TYPE_FLOAT);
	number_of_outputs = 1;
	InitLinkOutput(0, "#", OP_TYPE_IMAGE);
	
	image_out = R_CreateImageRGBA("OpImageColor image out", 2048, 2048, 0, 255, 0, 255); // just make green default

	showtitle = 1;
}

void OpIDTech3ImageColor::Render() {
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
		image_t *image = tr.images[image_out];
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

void OpIDTech3ImageColor::Update() {

	if (DidInputsChange()) {
		byte *data = R_GetImageData(image_out);
		int width = 2048;
		int height = 2048;
		const float r = in_color_r;
		const float g = in_color_g;
		const float b = in_color_b;
		const float a = in_color_a;
		const int size = width * height * 4;
		for (int i = 0; i < size; i += 4) {
			data[i+0] = r;
			data[i+1] = g;
			data[i+2] = b;
			data[i+3] = a;
		}
		R_UpdateImageFromBuffer(tr.images[ image_out ]);
		//imgui_log("%s->Update();\n", name);
		SetInputsUnchanged();
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

extern int CACHE_IMAGE;
bool OpIDTech3ImageColor::LoadFilename(const char *filename) {
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



void OpIDTech3ImageColor::RenderEditor() {
	Op::RenderEditor();

	if (ImGui::Button("Update color")) {
		byte *data = R_GetImageData(image_out);
		int width = 2048;
		int height = 2048;
		const float r = in_color_r;
		const float g = in_color_g;
		const float b = in_color_b;
		const float a = in_color_a;
		const int size = width * height * 4;
		for (int i = 0; i < size; i += 4) {
			data[i+0] = r;
			data[i+1] = g;
			data[i+2] = b;
			data[i+3] = a;
		}
		R_UpdateImageFromBuffer(tr.images[ image_out ]);
	}
}

OpIDTech3ImageColor::OpIDTech3ImageColor() {

	Init();
}