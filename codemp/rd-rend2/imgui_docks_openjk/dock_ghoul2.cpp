
#include "dock_ghoul2.h"
#include "../imgui_docks/dock_console.h"
#include "../imgui_openjk/gluecode.h"


#include "ghoul2/G2.h"
#include "ghoul2/g2_local.h"

IGhoul2InfoArray &TheGhoul2InfoArray();

// todo should be in header
// must be a power of two
#define MAX_G2_MODELS (1024)
#define G2_MODEL_BITS (10)
#define G2_INDEX_MASK (MAX_G2_MODELS-1)

class Ghoul2InfoArray : public IGhoul2InfoArray
{
public:
	std::vector<CGhoul2Info>	mInfos[MAX_G2_MODELS];
	int					mIds[MAX_G2_MODELS];
	std::list<int>			mFreeIndecies;
	void DeleteLow(int idx);
	Ghoul2InfoArray();

	size_t GetSerializedSize() const;

	size_t Serialize ( char *buffer ) const;

	size_t Deserialize ( const char *buffer, size_t size );

#if G2API_DEBUG
	~Ghoul2InfoArray();
#endif
	int New();
	bool IsValid(int handle) const;
	void Delete(int handle);
	std::vector<CGhoul2Info> &Get(int handle);
	const std::vector<CGhoul2Info> &Get(int handle) const;

#if G2API_DEBUG
	vector<CGhoul2Info> &GetDebug(int handle);
	void TestAllAnims();

#endif
};

extern Ghoul2InfoArray *singleton;













DockGhoul2::DockGhoul2() {}


const char *DockGhoul2::label() {
	return "Ghoul2";
}


void DockGhoul2::imgui() {
	for (int i=0; i<1024; i++) {
		auto infovector = singleton->mInfos[i];
		

		char infotmp[256];
		snprintf(infotmp, sizeof(infotmp), "infovector[%d] size=%d", i, infovector.size());
		//if (ImGui::CollapsingHeader(infotmp))
		ImGui::Text(infotmp);
		{


			//for (int info_id=0; info_id<info.size(); i++) {
			int info_id = 0;
			for (auto &info : infovector) {
				ImGui::PushID(info_id);
				ImGui::Text("aHeader->name=%s animModel=%p currentAnimModelSize=%d", info.aHeader ? info.aHeader->name : "aHeader==NULL", info.animModel, info.currentAnimModelSize);
				
				ImGui::Text("currentModel=%p currentModelSize=%d", info.currentModel, info.currentModelSize);
				
				
				ImGui::DragInt("mAnimFrameDefault", &info.mAnimFrameDefault);

				ImGui::Text("info.mBlist.size=%d", info.mBlist.size());
				int bone_id = 0;
				for (auto &boneinfo : info.mBlist) {
					ImGui::PushID(bone_id);
					ImGui::Text("boneinfo[%d]",
						bone_id
					);
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



					ImGui::DragInt("airTime", &boneinfo.airTime);
					ImGui::DragInt("airTime", &boneinfo.airTime);
					ImGui::PopID();
					bone_id++;
				}

				ImGui::PopID();
				info_id++;
			}
			
		}
	}
}

