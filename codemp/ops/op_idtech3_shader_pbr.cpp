#include "op.h"
#include "op_idtech3_shader_pbr.h"

extern "C" {
//#include <renderergl2\tr_local.h>
//#include <server\server.h>
}

#include "../imgui/imgui_fixedarea.h"
#include "../rd-rend2/tr_local.h"
#include "../include_console.h"

qhandle_t R_CreateImageRGBA(char *name, int width, int height, byte r, byte g, byte b, byte a);
void R_UpdateImageFromBuffer(image_t *image);
byte *R_GetImageData(int id);

void OpIDTech3ShaderPBR::Init() {
	Op::Init();
	size = ImVec2(128, 128);
	pos = ImVec2(250, 300);
	number_of_inputs = 7;
	InitLink(0, "shader", OP_TYPE_SHADER);
	InitLink(1, "diffuse (rgb)", OP_TYPE_IMAGE);
	InitLink(2, "specular (rgb)", OP_TYPE_IMAGE);
	InitLink(3, "normal (rgb)", OP_TYPE_IMAGE);
	InitLink(4, "opacity (red)", OP_TYPE_IMAGE);
	InitLink(5, "gloss (red)", OP_TYPE_IMAGE);
	InitLink(6, "height (red)", OP_TYPE_IMAGE);
	number_of_outputs = 3;
	InitLinkOutput(0, "diffuse opacity", OP_TYPE_IMAGE);
	InitLinkOutput(1, "normal height", OP_TYPE_IMAGE);
	InitLinkOutput(2, "specular gloss", OP_TYPE_IMAGE);
	
	
	
	handle_image_out_diffuse_opacity = R_CreateImageRGBA("handle_image_out_diffuse_opacity", 2048, 2048, 255,   0,   0, 255); // red
	handle_image_out_normal_height   = R_CreateImageRGBA("handle_image_out_normal_height"  , 2048, 2048,   0, 255,   0, 255); // green
	handle_image_out_specular_gloss  = R_CreateImageRGBA("handle_image_out_specular_gloss" , 2048, 2048,   0,   0, 255, 255); // blue... as default values

	showtitle = 1;
}

void OpIDTech3ShaderPBR::Render() {
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


void OpIDTech3ShaderPBR::OnLinkConnect(int id) {

}

void OpIDTech3ShaderPBR::Update() {


	if (DidInputsChange()) {
		SetInputsUnchanged();
		//imgui_log("%s->Update();\n", name);


		/*
			int &handle_image_in_diffuse       = default_link_inputs[0].val_i = 0; // rgb channel
			int &handle_image_in_specular      = default_link_inputs[1].val_i = 0; // rgb channel
			int &handle_image_in_normal        = default_link_inputs[2].val_i = 0; // rgb channel
			int &handle_image_in_opacity       = default_link_inputs[3].val_i = 0; // only red channel
			int &handle_image_in_gloss         = default_link_inputs[4].val_i = 0; // only red channel
			int &handle_image_in_height        = default_link_inputs[5].val_i = 0; // only red channel
		*/
	
			int hdrFormat = GL_RGBA8;

			byte *data_diffuse   = R_GetImageData(handle_image_in_diffuse);
			byte *data_specular  = R_GetImageData(handle_image_in_specular);
			byte *data_normal    = R_GetImageData(handle_image_in_normal);
			byte *data_opacity   = R_GetImageData(handle_image_in_opacity);
			byte *data_height    = R_GetImageData(handle_image_in_height);
			byte *data_gloss     = R_GetImageData(handle_image_in_gloss);

	
			if (data_diffuse  == NULL) { imgui_log("data_diffuse  == NULL\n"); return; }
			if (data_specular == NULL) { imgui_log("data_specular == NULL\n"); return; }
			if (data_normal   == NULL) { imgui_log("data_normal   == NULL\n"); return; }
			if (data_opacity  == NULL) { imgui_log("data_opacity  == NULL\n"); return; }
			if (data_height   == NULL) { imgui_log("data_height   == NULL\n"); return; }
			if (data_gloss    == NULL) { imgui_log("data_gloss    == NULL\n"); return; }

			int w = 2048;
			int h = 2048;
	
			//byte	*data_diffuse_opacity = (byte *)malloc(w * h * 4);
			//byte	*data_normal_height = (byte *)malloc(w * h * 4);
			//byte	*data_specular_gloss = (byte *)malloc(w * h * 4);


			byte	*data_diffuse_opacity = R_GetImageData(handle_image_out_diffuse_opacity);
			byte	*data_normal_height   = R_GetImageData(handle_image_out_normal_height);
			byte	*data_specular_gloss  = R_GetImageData(handle_image_out_specular_gloss);
	
	

			//Com_Memset(data, 255, sizeof(data));
			if (data_diffuse_opacity) {
				for (int i=0; i<w*h*4; i+=4) {
					// diffuse into rgb
					data_diffuse_opacity[i+0] = data_diffuse[i+0];
					data_diffuse_opacity[i+1] = data_diffuse[i+1];
					data_diffuse_opacity[i+2] = data_diffuse[i+2];
					// red channel from opacity into alpha
					data_diffuse_opacity[i+3] = data_opacity[i+0];
				}
				//image_t *image_diffuse_opacity = R_CreateImage("OpShaderPBR diffuse opacity out", (byte *)data_diffuse_opacity, w, h, IMGTYPE_COLORALPHA, IMGFLAG_NONE, hdrFormat);
				R_UpdateImageFromBuffer( tr.images + handle_image_out_diffuse_opacity);
			}

			if (data_normal_height) {
				for (int i=0; i<w*h*4; i+=4) {
					// normal into rgb
					data_normal_height[i+0] = data_normal[i+0];
					data_normal_height[i+1] = data_normal[i+1];
					data_normal_height[i+2] = data_normal[i+2];
					// red channel from height into alpha
					data_normal_height[i+3] = data_height[i+0];
				}
				//image_t *image_normal_height = R_CreateImage("OpShaderPBR normal height out", (byte *)data_normal_height, w, h, IMGTYPE_COLORALPHA, IMGFLAG_NONE, hdrFormat);
				R_UpdateImageFromBuffer( tr.images + handle_image_out_normal_height);
			}

			if (data_specular_gloss) {
				for (int i=0; i<w*h*4; i+=4) {
					// normal into rgb
					data_specular_gloss[i+0] = data_specular[i+0];
					data_specular_gloss[i+1] = data_specular[i+1];
					data_specular_gloss[i+2] = data_specular[i+2];
					// red channel from gloss into alpha
					data_specular_gloss[i+3] = data_gloss[i+0];
				}
				//image_t *image_specular_gloss = R_CreateImage("OpShaderPBR specular gloss out", (byte *)data_normal_height, w, h, IMGTYPE_COLORALPHA, IMGFLAG_NONE, hdrFormat);
				R_UpdateImageFromBuffer( tr.images + handle_image_out_specular_gloss);
			}


			/*
			int &handle_image_out_diffuse_opacity       = default_link_outputs[0].val_i = 0; // rgba, diffuse=rgb, opacity=alpha
			int &handle_image_out_normal_height         = default_link_outputs[1].val_i = 0; // rgba, normal=rgb, height=alpha
			int &handle_image_out_specular_gloss        = default_link_outputs[2].val_i = 0; // rgba, specular=rgb, gloss=alpha
			*/
			//handle_image_out_diffuse_opacity = image_diffuse_opacity->id;
			//handle_image_out_normal_height   = image_normal_height->id;
			//handle_image_out_specular_gloss  = image_specular_gloss->id;


			// now we can generate the three shaders rend2 is using internally, which are:
			// stage[0]->texturebundle[0] = 

			/*
			TB_DIFFUSEMAP  = TB_COLORMAP    = 0
			TB_NORMALMAP   = 2
			TB_SPECULARMAP = 4,	
			*/
			//TB_NORMALMAP
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



void OpIDTech3ShaderPBR::RenderEditor() {

	Op::RenderEditor();
}

OpIDTech3ShaderPBR::OpIDTech3ShaderPBR() {

	Init();
}