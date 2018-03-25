#include "op.h"
#include "op_idtech3_mdxm.h"

extern "C" {
//#include <renderergl2\tr_local.h>
//#include <server\server.h>
}

#include "../imgui/imgui_fixedarea.h"

#include "../tr_local.h"

#include "../compose_models.h"
#include "../matrix.h"
void OpMDXM::Init() {
	Op::Init();
	size = ImVec2(128, 128);
	pos = ImVec2(250, 300);
	number_of_inputs = 4;
	InitLink(0, "model_id",   OP_TYPE_INT  );
	InitLink(1, "lod_id",     OP_TYPE_INT  );
	InitLink(2, "surface_id", OP_TYPE_INT  );
	InitLink(3, "matrix"    , OP_TYPE_MATRIX);
	mat_identity(default_link_inputs[3].matrix);

	number_of_outputs = 0;
	InitLinkOutput(0, "r", OP_TYPE_INT);
	InitLinkOutput(1, "g", OP_TYPE_INT);
	InitLinkOutput(2, "b", OP_TYPE_INT);
	InitLinkOutput(3, "a", OP_TYPE_INT);
	showtitle = 1;
}

mdxmHeader_t *mdxmHeaderSafe(model_t *mod) {
	if (mod->type != MOD_MDXM)
		return NULL;
	mdxmData_t *glm = mod->data.glm;
	return glm->header;
}

//qboolean model_upload_mdxm_to_gpu_special(model_t *mod, mdxmSurface_t *specialSurface, float scale);
qboolean model_upload_mdxm_to_gpu_special(model_t *mod, mdxmSurface_t *specialSurface, float matrix[16]);

void OpMDXM::Render() {
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
	
	model_id   = default_link_inputs[0].val_i;
	lod_id     = default_link_inputs[1].val_i;
	surface_id = default_link_inputs[2].val_i;
	scale      = default_link_inputs[3].val_f;

	if (model_id >= 0 && model_id <= 1023) {
		model_t *mod = tr.models[model_id];
		if (mod != NULL) {
			mdxmHeader_t *mdxmHeader = mdxmHeaderSafe( mod );
			if (mdxmHeader != NULL) {
				if (lod_id >= 0 && lod_id < mdxmHeader->numLODs) {
					if (surface_id >= 0 && surface_id < mdxmHeader->numSurfaces) {
						mdxmLOD_t *mdxmLod = firstLod(mdxmHeader);
						// todo: next() to the lod_id or make some lookup table
					
						mdxmSurface_t *mdxmSurface = firstSurface(mdxmHeader, mdxmLod);
						// todo: lookup table...
						for (int i=0; i<surface_id; i++)
							mdxmSurface = next(mdxmSurface);
						ImGui::Text("numVerts: %d", mdxmSurface->numVerts);
						
						//model_upload_mdxm_to_gpu_special(mod, mdxmSurface, scale);
						model_upload_mdxm_to_gpu_special(mod, mdxmSurface, default_link_inputs[3].matrix);


					} else {
						ImGui::Text("Invalid surface_id, must be 0 to %d", mdxmHeader->numSurfaces - 1);
					}
				} else {
					ImGui::Text("Invalid lod_id, must be 0 to %d", mdxmHeader->numLODs - 1);
				}
			} else {
				ImGui::Text("model_id is no MDXM model");
			}
		} else {
			ImGui::Text("tr.models[model_id] == NULL");
		}
	} else {
		ImGui::Text("Invalid model_id, must be 0 to 1023");
	}

	Op::PostRender();
}

void OpMDXM::Update() {
	//image_id = default_link_inputs[0].val_f;
	//if (image_id < 0)
	//	image_id = 0;
	//if (image_id >= 4096)
	//	image_id = 4095;

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

void OpMDXM::RenderEditor() {
	Op::RenderEditor();
}

OpMDXM::OpMDXM() {

	Init();
}