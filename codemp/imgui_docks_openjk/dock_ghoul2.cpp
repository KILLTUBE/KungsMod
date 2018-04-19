
#include "dock_ghoul2.h"
#include "../imgui_docks/dock_console.h"
#include "../imgui_openjk/gluecode.h"

#include "ghoul2/G2.h"
#include "../ghoul2/g2_local.h"
#include "../ghoul2/Ghoul2InfoArray.h"
#include "../ghoul2/CBoneCache.h"

extern Ghoul2InfoArray *singleton;
IGhoul2InfoArray &TheGhoul2InfoArray();

DockGhoul2::DockGhoul2() {}


// return G2API_AddBolt( *((CGhoul2Info_v *)ghoul2), modelIndex, boneName );


const char *DockGhoul2::label() {
	return "Ghoul2";
}

void imgui_boneinfo(boneInfo_t &boneinfo, int bone_id) {
	char boneinfotext[256];
	snprintf(boneinfotext, sizeof(boneinfotext), "CGhoul2Info.mBlist[%d] boneNumber=%d flags=%d startFrame=%d endFrame=%d",
		bone_id,
		boneinfo.boneNumber,
		boneinfo.flags,
		boneinfo.startFrame,
		boneinfo.endFrame
	);
	if (ImGui::CollapsingHeader(boneinfotext)) {
		ImGui::PushID(&boneinfo);
		ImGui::DragInt("boneNumber", &boneinfo.boneNumber);
		// todo edit boneinfo.matrix
		ImGui::DragInt("flags", &boneinfo.flags);
		ImGui::DragInt("startFrame", &boneinfo.startFrame);
		ImGui::DragInt("endFrame", &boneinfo.endFrame);
		ImGui::DragInt("startTime", &boneinfo.startTime);
		ImGui::DragInt("pauseTime", &boneinfo.pauseTime);
		ImGui::DragFloat("animSpeed", &boneinfo.animSpeed);
		ImGui::DragFloat("blendFrame", &boneinfo.blendFrame);
		ImGui::DragInt("blendLerpFrame", &boneinfo.blendLerpFrame);
		ImGui::DragInt("blendTime", &boneinfo.blendTime);
		ImGui::DragInt("blendStart", &boneinfo.blendStart);
		ImGui::DragInt("boneBlendTime", &boneinfo.boneBlendTime);
		ImGui::DragInt("boneBlendStart", &boneinfo.boneBlendStart);
		ImGui::DragInt("lastTime", &boneinfo.lastTime);
		// todo boneinfo.newMatrix
		ImGui::DragInt("lastTimeUpdated", &boneinfo.lastTimeUpdated);
		ImGui::DragInt("lastContents", &boneinfo.lastContents);
		ImGui::DragFloat3("lastPosition", boneinfo.lastPosition);
		ImGui::DragFloat3("velocityEffector", boneinfo.velocityEffector);
		ImGui::DragFloat3("lastAngles", boneinfo.lastAngles);
		ImGui::DragFloat3("minAngles", boneinfo.minAngles);
		ImGui::DragFloat3("maxAngles", boneinfo.maxAngles);
		ImGui::DragFloat3("currentAngles", boneinfo.currentAngles);
		ImGui::DragFloat3("anglesOffset", boneinfo.anglesOffset);
		ImGui::DragFloat3("positionOffset", boneinfo.positionOffset);
		ImGui::DragFloat("radius", &boneinfo.radius);
		ImGui::DragFloat("weight", &boneinfo.weight);
		ImGui::DragInt("ragIndex", &boneinfo.ragIndex);
		ImGui::DragFloat3("velocityRoot", boneinfo.velocityRoot);
		ImGui::DragInt("ragStartTime", &boneinfo.ragStartTime);
		ImGui::DragInt("firstTime", &boneinfo.firstTime);
		ImGui::DragInt("firstCollisionTime", &boneinfo.firstCollisionTime);
		ImGui::DragInt("restTime", &boneinfo.restTime);
		ImGui::DragInt("RagFlags", &boneinfo.RagFlags);
		ImGui::DragInt("DependentRagIndexMask", &boneinfo.DependentRagIndexMask);
		// 3x mdxaBone todo
		ImGui::DragFloat3("currentAngles", boneinfo.currentAngles);
		ImGui::DragFloat3("anglesOffset", boneinfo.anglesOffset);
		ImGui::DragFloat3("positionOffset", boneinfo.positionOffset);
		// 4x mdxaBone pointer todo

		ImGui::DragInt("hasAnimFrameMatrix", &boneinfo.hasAnimFrameMatrix);
		ImGui::DragInt("airTime", &boneinfo.airTime);
		ImGui::PopID();
	}
}

void DockGhoul2::imgui() {
	for (int i=0; i<1024; i++) {
		auto &infovector = singleton->mInfos[i];
		

		char infotmp[256];
		snprintf(infotmp, sizeof(infotmp), "infovector[%d] size=%d", i, infovector.size());
		if (ImGui::CollapsingHeader(infotmp))
		//ImGui::Text(infotmp);
		{


			//for (int info_id=0; info_id<info.size(); i++) {
			int info_id = 0;
			for (CGhoul2Info &info : infovector) {
				ImGui::PushID(info_id);
				
				// todo info.aHeader crashes too often, its either NULL or garbage it seems..
				//ImGui::Text("aHeader->name=%s animModel=%p currentAnimModelSize=%d", info.aHeader ? info.aHeader->name : "aHeader==NULL", info.animModel, info.currentAnimModelSize);
				
				ImGui::Text("currentModel=%p currentModelSize=%d", info.currentModel, info.currentModelSize);
				
				
				ImGui::DragInt("mModelindex",       &info.mModelindex       );
				ImGui::DragInt("mCustomShader",     &info.mCustomShader     );
				ImGui::DragInt("mCustomSkin",       &info.mCustomSkin       );
				ImGui::DragInt("mModelBoltLink",    &info.mModelBoltLink    );
				ImGui::DragInt("mSurfaceRoot",      &info.mSurfaceRoot      );
				ImGui::DragInt("mLodBias",          &info.mLodBias          );
				ImGui::DragInt("mNewOrigin",        &info.mNewOrigin        );
				ImGui::DragInt("mGoreSetTag",       &info.mGoreSetTag       );
				ImGui::DragInt("mModel",            &info.mModel            );
				ImGui::DragInt("mAnimFrameDefault", &info.mAnimFrameDefault );
				ImGui::DragInt("mSkelFrameNum",     &info.mSkelFrameNum     );
				ImGui::DragInt("mMeshFrameNum",     &info.mMeshFrameNum     );
				ImGui::DragInt("mFlags",            &info.mFlags            );
				ImGui::InputText("mFileName",       info.mFileName, sizeof(info.mFileName));


				ImGui::Text("info.mBlist.size=%d", info.mBlist.size());
				int bone_id = 0;
				for (boneInfo_t &boneinfo : info.mBlist) {
					imgui_boneinfo(boneinfo, bone_id);
					bone_id++;
				}

				ImGui::PopID();
				info_id++;
			}
			
		}
	}
}

