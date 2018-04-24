#include "dock_clients.h"
#include "../imgui_docks/dock_console.h"
#include "../imgui_openjk/gluecode.h"

DockClients::DockClients() {}

const char *DockClients::label() {
	return "Clients";
}

EXTERNC  animation_t		bgHumanoidAnimations[MAX_TOTALANIMATIONS];
EXTERNC	centity_t		cg_entities[MAX_GENTITIES];


namespace ImGui {
	bool DragUShort(const char *str, unsigned short *val);
	bool DragShort(const char *str, short *val);
	bool DragChar(const char *str, signed char *val);
}

#include "../ghoul2/g2_local.h"
#include "../ghoul2/Ghoul2InfoArray.h"
#include "../ghoul2/CBoneCache.h"

IGhoul2InfoArray &TheGhoul2InfoArray();
extern Ghoul2InfoArray *singleton;


CCALL int ghoul2_mitem(void **ghoul2_ptr) {

	if (*ghoul2_ptr == NULL)
		return -1;

	void *ghoul2 = *ghoul2_ptr;
	CGhoul2Info_v *info = (CGhoul2Info_v *)ghoul2;
	//auto infovector = singleton->mInfos[info->mItem];
	//ImGui::Text("cent[%d] size=%d info->mItem=%d (masked=%d)", i, info->size(), info->mItem, info->mItem & G2_INDEX_MASK);
	return info->mItem & G2_INDEX_MASK;
}


void DockClients::imgui() {

	for (int i=0; i<MAX_GENTITIES; i++) {
		centity_t *cent = cg_entities + i;

		if (cent->ghoul2) {
			CGhoul2Info_v *info = (CGhoul2Info_v *)cent->ghoul2;

			//auto infovector = singleton->mInfos[info->mItem];
			ImGui::Text("cent[%d] size=%d info->mItem=%d (masked=%d)", i, info->size(), info->mItem, info->mItem & G2_INDEX_MASK);
	
			
			std::vector<CGhoul2Info> &infos = singleton->mInfos[ info->mItem & G2_INDEX_MASK ];

			int i = 0;
			for (auto &info : infos) {
				ImGui::PushID(&info);
				ImGui::Text("std::vector<CGhoul2Info> infos[%d]", i);

				if (ImGui::Button("Clear Surfaces")) {
					info.mSlist.clear();
				}
				
				int surface_id = 0;
				for (auto &surface : info.mSlist) {
					ImGui::PushID(&surface);
					ImGui::Text("surfaceInfo_t id in info.mSlist=%d", surface_id);
					ImGui::DragInt("offFlags", &surface.offFlags);
					ImGui::DragInt("surface", &surface.surface);
					ImGui::DragFloat("genBarycentricJ", &surface.genBarycentricJ);
					ImGui::DragFloat("genBarycentricI", &surface.genBarycentricI);
					ImGui::DragInt("genPolySurfaceIndex", &surface.genPolySurfaceIndex);
					ImGui::DragInt("genLod", &surface.genLod);
					ImGui::PopID();
					surface_id++;
				}

				int bolt_id = 0;
				for (boltInfo_t &bolt : info.mBltlist) {
					ImGui::PushID(&bolt);
					ImGui::Text("boltInfo_t id in info.mBltlist=%d", bolt_id);
					ImGui::DragInt("boneNumber", &bolt.boneNumber);
					ImGui::DragInt("surfaceNumber", &bolt.surfaceNumber);
					ImGui::DragInt("surfaceType", &bolt.surfaceType);
					ImGui::DragInt("boltUsed", &bolt.boltUsed);
					ImGui::PopID();
					bolt_id++;
				}

				ImGui::PopID();
				i++;
			}
			//auto info = info[i];
			

			if (0)
			for (int surface_id=0; surface_id<MAX_G2_MODELS; surface_id++) {
				auto infovector = singleton->mInfos[info->mItem];
	
	
				for (int j=0; j<infovector.size(); j++) {
					CGhoul2Info &ghoul = infovector[j];
					auto bc = ghoul.mBoneCache;
	
					ImGui::Text("hasUncompressedBones=%d", bc->hasUncompressedBones?1:0);
	
				}
			}
		}
	}
}

