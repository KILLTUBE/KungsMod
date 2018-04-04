#include "dock_frames.h"
#include "../imgui_docks/dock_console.h"
#include "../imgui_openjk/gluecode.h"

DockFrames::DockFrames() {}

const char *DockFrames::label() {
	return "Frames";
}

EXTERNC  animation_t		bgHumanoidAnimations[MAX_TOTALANIMATIONS];
EXTERNC	centity_t		cg_entities[MAX_GENTITIES];


namespace ImGui {
	bool DragUShort(const char *str, unsigned short *val);
	bool DragShort(const char *str, short *val);
	bool DragChar(const char *str, signed char *val);
}

#include "../../ghoul2/g2_local.h"
#include "../../ghoul2/Ghoul2InfoArray.h"
#include "../../ghoul2/CBoneCache.h"

IGhoul2InfoArray &TheGhoul2InfoArray();
extern Ghoul2InfoArray *singleton;


void DockFrames::imgui() {

	static int frame_id = 0;
	static int bone_id = 0;

	
	ImGui::DragInt("frame_id", &frame_id);
	ImGui::DragInt("bone_id", &bone_id);

	//for (int i=0; i<MAX_GENTITIES; i++) {
	//	centity_t *cent = cg_entities + i;
	//
	//	if (cent->ghoul2) {
	//		CGhoul2Info_v *info = (CGhoul2Info_v *)cent->ghoul2;
	//		ImGui::Text("cent[%d] size=%d", i, info->size());
	//
	//		
	//		auto infovector = singleton->mInfos[info->mItem];
	//
	//
	//		for (int j=0; j<infovector.size(); j++) {
	//			CGhoul2Info &ghoul = infovector[j];
	//			auto bc = ghoul.mBoneCache;
	//
	//			ImGui::Text("hasUncompressedBones=%d", bc->hasUncompressedBones?1:0);
	//
	//		}
	//
	//	}
	//
	//}


	for (int i=0; i<1024; i++) {
		auto infovector = singleton->mInfos[i];
		ImGui::PushID(i);

		char infotmp[256];
		snprintf(infotmp, sizeof(infotmp), "infovector[%d] size=%d", i, infovector.size());
		//if (ImGui::CollapsingHeader(infotmp))
		ImGui::Text(infotmp);
		{


			//for (int info_id=0; info_id<info.size(); i++) {
			int info_id = 0;
			for (auto &info : infovector) {
				ImGui::PushID(info_id);

				auto bc = info.mBoneCache;
				if (bc) {
					ImGui::Text("hasUncompressedBones=%d", bc->hasUncompressedBones?1:0);


					if (bc->hasUncompressedBones) {
						mdxaBone_t *bone = bc->uncompressedBones + (frame_id * bc->header->numBones) + bone_id;

					
						ImGui::DragFloat4("matrix[0]", bone->matrix[0]);
						ImGui::DragFloat4("matrix[1]", bone->matrix[1]);
						ImGui::DragFloat4("matrix[2]", bone->matrix[2]);
				
				
					}
				}
				ImGui::PopID();
				info_id++;
			}
		}

		ImGui::PopID();
	}
}

