#include "op.h"
#include "op_idtech3_rmo.h"

extern "C" {
//#include <renderergl2\tr_local.h>
//#include <server\server.h>
}

#include "../imgui/imgui_fixedarea.h"

#include "../tr_local.h"

#include "../include_console.h"

byte *R_GetImageData(int id) {
	image_t *image = tr.images + id;
	if (image == NULL)
		return NULL;
	return (byte *)image->data;
}


void R_UpdateImageFromBuffer(image_t *image);
byte *R_GetImageData(int id);

void *R_Malloc( int iSize, memtag_t eTag, qboolean bZeroit );
//void *R_Malloc( int iSize, memtag_t eTag, qboolean bZeroit ) {
//	return Z_Malloc( iSize, eTag, bZeroit, 4 );
//}
qhandle_t R_CreateImageRGBA(char *name, int width, int height, byte r, byte g, byte b, byte a) {
	
	byte *data = (byte *)R_Malloc(width * height * 4, TAG_TEMP_IMAGE, qfalse);
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
	number_of_inputs = 6;
	InitLink(0, "base", OP_TYPE_IMAGE);
	InitLink(1, "roughness (red)", OP_TYPE_IMAGE);
	InitLink(2, "metal (red)", OP_TYPE_IMAGE);
	InitLink(3, "ao (red)", OP_TYPE_IMAGE);
	// todo... inverse link creation, so the default values are copied over to the INPUT
	// and a "reset default" button... or automatically reassign default value on link deletion
	InitLink(4, "ao strength", OP_TYPE_FLOAT);
	InitLink(5, "base spec", OP_TYPE_FLOAT);
	number_of_outputs = 2;
	InitLinkOutput(0, "diff", OP_TYPE_IMAGE);
	InitLinkOutput(1, "spec", OP_TYPE_IMAGE);
	
	// just create two shitty images, so we have the handle at least... later just update
	image_out_diff = R_CreateImageRGBA("image_out_diff", 2048, 2048, 255,   0, 0, 255); // red
	image_out_spec = R_CreateImageRGBA("image_out_spec", 2048, 2048,   0, 255, 0, 255); // green, just as default...

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

	if (DidInputsChange()) {
		SetInputsUnchanged();
		imgui_log("%s->Update()\n", name);

		byte *data_base        = R_GetImageData(handle_image_in_base);
		byte *data_roughness   = R_GetImageData(handle_image_in_roughness);
		byte *data_metal       = R_GetImageData(handle_image_in_metal);
		byte *data_ao          = R_GetImageData(handle_image_in_ao);

		if (data_base      == NULL) { imgui_log("data_base     \n"); return; }
		if (data_roughness == NULL) { imgui_log("data_roughness\n"); return; }
		if (data_metal     == NULL) { imgui_log("data_metal    \n"); return; }
		if (data_ao        == NULL) { imgui_log("data_ao       \n"); return; }

		//imgui_log("id base=%d, ptr=%p, id rmo=%d, ptr=%p\n", image_in_base, baseColorPic, image_in_rmo, rmoPic);

		//if (width != rmoWidth || height != rmoHeight)
		//{
		//	R_Printf(PRINT_ALL, "WARNING: Can't build Specular Map for %s (different texture sizes for baseColor and rmo)\n", name);
		//	return;
		//}

		// todo... dynamic
		int width = 2048;
		int height = 2048;

		byte *diffusePic   = R_GetImageData(image_out_diff);
		byte *specGlossPic = R_GetImageData(image_out_spec);
	
		if (diffusePic   == NULL) { imgui_log("diffusePic   == NULL\n"); return; }
		if (specGlossPic == NULL) { imgui_log("specGlossPic == NULL\n"); return; }

		//byte *specGlossPic = (byte *)R_Malloc(width * height * 4, TAG_GP2, qfalse);
		//byte *diffusePic   = (byte *)R_Malloc(width * height * 4, TAG_GP2, qfalse);

		//const float gamma = 2.2f;
		//const float inverseGamma = 1.0f / 2.2f;
		const int size = width * height * 4;
	
		const float aoStrength = in_ao_strength;
		const float baseSpecular  = in_base_specular;
		for (int i = 0; i < size; i += 4)
		{
			float roughness = ByteToFloat(data_roughness[i + 0]);
			float gloss		= (1.0 - roughness) + (0.04 * roughness);
			float metalness = ByteToFloat(data_metal[i + 0]);
			float ao		= ByteToFloat(data_ao[i + 0]);
			ao += (1.0 - ao) * (1.0 - aoStrength);
			float specAo	= (1.0f * gloss * gloss) + (ao * (1.0f - gloss * gloss));
		 
			float color[3];
			color[0] = ByteToFloat(data_base[i + 0]);
			color[1] = ByteToFloat(data_base[i + 1]);
			color[2] = ByteToFloat(data_base[i + 2]);

			// diffuse Color = baseColor * (1.0 - metalness) * occlusion 
			diffusePic[i + 0] = color[0] * (1.0f - metalness) * ao * 255.0f;
			diffusePic[i + 1] = color[1] * (1.0f - metalness) * ao * 255.0f;
			diffusePic[i + 2] = color[2] * (1.0f - metalness) * ao * 255.0f;
			//diffusePic[i + 3] = baseColorPic[i + 3];
			diffusePic[i + 3] = 255;

			// specular Color = mix(baseSpecular, baseColor, metalness)
		
			specGlossPic[i + 0] = (baseSpecular * (1.0f - metalness) + color[0] * metalness) * specAo * 255.0f;
			specGlossPic[i + 1] = (baseSpecular * (1.0f - metalness) + color[1] * metalness) * specAo * 255.0f;
			specGlossPic[i + 2] = (baseSpecular * (1.0f - metalness) + color[2] * metalness) * specAo * 255.0f;
			specGlossPic[i + 3] = gloss * 255.0f;
			//specGlossPic[i + 3] = 100;
		}

	
		image_t *image_diff = tr.images + image_out_diff;
		image_t *image_spec = tr.images + image_out_spec;




		//R_UpdateSubImage(image_diff,   diffusePic, 0, 0, width, height);
		//R_UpdateSubImage(image_spec, specGlossPic, 0, 0, width, height);

	
		int flags = IMGFLAG_NONE;
		//if (!shader.noMipMaps)
			flags |= IMGFLAG_MIPMAP;
		//if (!shader.noPicMip)
			flags |= IMGFLAG_PICMIP;
		//if (shader.noTC)
		//	flags |= IMGFLAG_NO_COMPRESSION;

		//image_t *diff = R_CreateImage("diff", diffusePic, width, height, IMGTYPE_COLORALPHA, flags, 0);
		//image_t *spec = R_CreateImage("specGloss", specGlossPic, width, height, IMGTYPE_COLORALPHA, flags, 0);
		//
		//image_out_diff = diff->id;
		//image_out_spec = spec->id;
		//
		//R_Free(diffusePic);
		//R_Free(specGlossPic);
		
		R_UpdateImageFromBuffer( tr.images + image_out_diff );
		R_UpdateImageFromBuffer( tr.images + image_out_spec );

		//R_Free(baseColorPic);
		//R_Free(rmoPic);
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


void OpIDTech3RMO::OnLinkConnect(int id) {

}

void OpIDTech3RMO::RenderEditor() {

	Op::RenderEditor();
}

OpIDTech3RMO::OpIDTech3RMO() {

	Init();
}