#include "op.h"
#include "op_idtech3_rmo.h"

extern "C" {
//#include <renderergl2\tr_local.h>
//#include <server\server.h>
}

#include <imgui/imgui_fixedarea.h>

#include "tr_local.h"


qhandle_t R_CreateImageRGBA(char *name, int width, int height, byte r, byte g, byte b, byte a) {
	byte *data = (byte *)R_Malloc(width * height * 4, TAG_GP2, qfalse);
	for (int i=0; i<width*height*4; i+=4) {
		data[i+0] = r;
		data[i+1] = g;
		data[i+2] = b;
		data[i+3] = a;
	}
	image_t *image = R_CreateImage(name, data, width, height, IMGTYPE_COLORALPHA, IMGFLAG_NONE, GL_RGBA8);
	//R_Free(data);
	image->data = data;
	return image->id;
}

void OpIDTech3RMO::Init() {
	Op::Init();
	size = ImVec2(128, 128);
	pos = ImVec2(250, 300);
	number_of_inputs = 2;
	InitLink(0, "base", OP_TYPE_IMAGE);
	InitLink(1, "rmo", OP_TYPE_IMAGE);
	number_of_outputs = 2;
	InitLinkOutput(0, "diff", OP_TYPE_IMAGE);
	InitLinkOutput(1, "spec", OP_TYPE_IMAGE);
	
	// just create two shitty images, so we have the handle at least... later just update
	image_out_diff = R_CreateImageRGBA("image_out_diff", 128, 128, 255,   0, 255, 255); // red+blue
	image_out_spec = R_CreateImageRGBA("image_out_spec", 128, 128,   0, 255, 255, 255); // green+blue

	showtitle = 1;
}

void OpIDTech3RMO::Render() {
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

void OpIDTech3RMO::Update() {
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

byte *R_GetImageData(int id) {
	image_t *image = tr.images[ id ];
	if (image == NULL)
		return NULL;
	return (byte *)image->data;
}


void OpIDTech3RMO::OnLinkConnect(int id) {
	byte *baseColorPic = R_GetImageData(image_in_base);
	byte *rmoPic       = R_GetImageData(image_in_rmo);

	if (baseColorPic == NULL) {
		imgui_log("baseColorPic\n");
		return;
	}
	if (rmoPic == NULL) {
		imgui_log("rmoPic\n");
		return;
	}

	imgui_log("id base=%d, ptr=%p, id rmo=%d, ptr=%p\n", image_in_base, baseColorPic, image_in_rmo, rmoPic);

	//if (width != rmoWidth || height != rmoHeight)
	//{
	//	ri.Printf(PRINT_ALL, "WARNING: Can't build Specular Map for %s (different texture sizes for baseColor and rmo)\n", name);
	//	return;
	//}

	// todo... dynamic
	int width = 2048;
	int height = 2048;

	byte *specGlossPic = (byte *)R_Malloc(width * height * 4, TAG_GP2, qfalse);
	byte *diffusePic   = (byte *)R_Malloc(width * height * 4, TAG_GP2, qfalse);

	//const float gamma = 2.2f;
	//const float inverseGamma = 1.0f / 2.2f;
	const int size = width * height * 4;

	for (int i = 0; i < size; i += 4)
	{
		const float aoStrength = 0.5f;
		float roughness = ByteToFloat(rmoPic[i + 0]);
		float gloss		= (1.0 - roughness) + (0.04 * roughness);
		float metalness = ByteToFloat(rmoPic[i + 1]);
		float ao		= ByteToFloat(rmoPic[i + 2]);
		ao += (1.0 - ao) * (1.0 - aoStrength);
		float specAo	= (1.0f * gloss * gloss) + (ao * (1.0f - gloss * gloss));
		 
		float color[3];
		color[0] = ByteToFloat(baseColorPic[i + 0]);
		color[1] = ByteToFloat(baseColorPic[i + 1]);
		color[2] = ByteToFloat(baseColorPic[i + 2]);

		// diffuse Color = baseColor * (1.0 - metalness) * occlusion 
		diffusePic[i + 0] = color[0] * (1.0f - metalness) * ao * 255.0f;
		diffusePic[i + 1] = color[1] * (1.0f - metalness) * ao * 255.0f;
		diffusePic[i + 2] = color[2] * (1.0f - metalness) * ao * 255.0f;
		diffusePic[i + 3] = baseColorPic[i + 3];

		// specular Color = mix(baseSpecular, baseColor, metalness)
		float baseSpecular  = 56.0f / 255.0f;
		specGlossPic[i + 0] = (baseSpecular * (1.0f - metalness) + color[0] * metalness) * specAo * 255.0f;
		specGlossPic[i + 1] = (baseSpecular * (1.0f - metalness) + color[1] * metalness) * specAo * 255.0f;
		specGlossPic[i + 2] = (baseSpecular * (1.0f - metalness) + color[2] * metalness) * specAo * 255.0f;
		specGlossPic[i + 3] = gloss * 255.0f;
		//specGlossPic[i + 3] = 100;
	}

	
	image_t *image_diff = tr.images[ image_out_diff ];
	image_t *image_spec = tr.images[ image_out_spec ];




	//R_UpdateSubImage(image_diff,   diffusePic, 0, 0, width, height);
	//R_UpdateSubImage(image_spec, specGlossPic, 0, 0, width, height);

	
	int flags = IMGFLAG_NONE;
	//if (!shader.noMipMaps)
		flags |= IMGFLAG_MIPMAP;
	//if (!shader.noPicMip)
		flags |= IMGFLAG_PICMIP;
	//if (shader.noTC)
	//	flags |= IMGFLAG_NO_COMPRESSION;

	image_t *diff = R_CreateImage("diff", diffusePic, width, height, IMGTYPE_COLORALPHA, flags, 0);
	image_t *spec = R_CreateImage("specGloss", specGlossPic, width, height, IMGTYPE_COLORALPHA, flags, 0);

	image_out_diff = diff->id;
	image_out_spec = spec->id;

	R_Free(diffusePic);
	R_Free(specGlossPic);
	//R_Free(baseColorPic);
	//R_Free(rmoPic);
}

void OpIDTech3RMO::RenderEditor() {

	Op::RenderEditor();
}

OpIDTech3RMO::OpIDTech3RMO() {

	Init();
}