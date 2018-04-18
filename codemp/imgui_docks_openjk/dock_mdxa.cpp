#include "dock_mdxa.h"
#include "../imgui_docks/dock_console.h"
#include "../imgui_openjk/gluecode.h"
#include "../imgui_openjk/imgui_openjk_default_docks.h"
#include "../rd-rend2/compose_models.h"

//void DockMDXA::imgui_list_surfhierarchy() {
//	mdxmSurfHierarchy_t *surfHierarchy = firstSurfHierarchy(header);
// 	for (int surface_id=0 ; surface_id<header->numSurfaces; surface_id++) {
//		/*
//			char		name[MAX_QPATH];
//			unsigned int flags;
//			char		shader[MAX_QPATH];
//			int			shaderIndex;		// for in-game use (carcass defaults to 0)
//			int			parentIndex;		// this points to the index in the file of the parent surface. -1 if null/root
//			int			numChildren;		// number of surfaces which are children of this one
//			int			childIndexes[1];	// [mdxmSurfHierarch_t->numChildren] (variable sized)		
//		*/
//		char tmp[512];
//		snprintf(tmp, sizeof(tmp), "mdxmSurfHierarchy[%d] name=%s flags=%d shader=%s shaderIndex=%d parentIndex=%d numChildren=%d childIndexes[0]=%d",
//			surface_id,
//			surfHierarchy->name,
//			surfHierarchy->flags,
//			surfHierarchy->shader,
//			surfHierarchy->shaderIndex,
//			surfHierarchy->parentIndex,
//			surfHierarchy->numChildren,
//			surfHierarchy->childIndexes[0]
//		);
//		if (ImGui::CollapsingHeader(tmp)) {
//		}
//		
//		surfHierarchy = next(surfHierarchy);
//	}
//}

//void DockMDXA::imgui_surface_vertices(mdxmSurface_t *surf) {
//	mdxmVertex_t *vert = firstVertex(surf);
//
//	//ImGui::Text("verts=%p type=%s numVerts=%d numTriangles=%d numBoneReferences=%d", 
//	//	vert->,
//	//	surfacetypeToString((surfaceType_t)surf->ident),
//	//	surf->numVerts,
//	//	surf->numTriangles,
//	//	surf->numBoneReferences
//	//);
//
//	for (int vert_id=0; vert_id<surf->numVerts; vert_id++) {
//		char dragString[128];
//
//		snprintf(dragString, sizeof(dragString), "verts[%i]", vert_id);
//		ImGui::DragFloat3(dragString, vert->vertCoords);
//		vert++;
//	}
//}

//void DockMDXA::imgui_surface(mdxmSurface_t *surf) {
//	ImGui::PushID(surf);
//
//	char strBoneReferences[128];
//	snprintf(strBoneReferences, sizeof(strBoneReferences), "%d bone references", surf->numBoneReferences);
//	if (ImGui::CollapsingHeader(strBoneReferences)) {
//		
//		int *boneRef = (int *) ( (byte *)surf + surf->ofsBoneReferences);
//		for (int j=0 ; j<surf->numBoneReferences; j++) {
//			char tmpName[128];
//			snprintf(tmpName, sizeof(tmpName), "boneReference[%d]", j);
//			ImGui::DragInt(tmpName, boneRef + j);
//			if (boneRef[j] < 0)
//				boneRef[j] = 0;
//			if (boneRef[j] >= header->numBones)
//				boneRef[j] = header->numBones - 1;
//		}
//	}
//
//	char strVerts[128];
//	snprintf(strVerts, sizeof(strVerts), "%d vertices", surf->numVerts);
//	if (ImGui::CollapsingHeader(strVerts)) {
//
//		if (ImGui::Button("verts *= 2")) {
//			scaleVertices(surf, 2.0);
//			model_upload_mdxm_to_gpu(mod);
//		}
//		ImGui::SameLine();
//		if (ImGui::Button("verts /= 2")) {
//			scaleVertices(surf, 0.5);
//			model_upload_mdxm_to_gpu(mod);
//		}
//
//		imgui_mdxm_surface_vertices(surf);
//	}
//
//	ImGui::PopID();
//}

//void DockMDXA::imgui_list_lods() {
//	mdxmLOD_t *lod = firstLod(header);
//	for (int lod_id=0; lod_id<header->numLODs; lod_id++) {
//		char tmp[512];
//		snprintf(tmp, sizeof(tmp), "mdxmLOD_t[%d] ofsEnd=%d", lod_id, lod->ofsEnd );
//		if (ImGui::CollapsingHeader(tmp)) {
//			mdxmSurface_t *surf = firstSurface(header, lod);
//			for (int i=0; i<header->numSurfaces; i++) {
//
//
//
//				if (ImGui::CollapsingHeader(toString(surf, lookupSurfNames[i]))) {
//					imgui_surface(surf);
//				}
//				surf = next(surf);
//			}
//		}
//		lod = next(lod);
//	}
//}
void Inverse_Matrix(mdxaBone_t *src, mdxaBone_t *dest);
void Create_Matrix(const float *angle, mdxaBone_t *matrix);


typedef struct ghoulbone_s {
	char name[64];
	unsigned int flags;
	int parent;
	float basePoseMat[3][4];
	float basePoseMatInv[3][4];
} ghoulbone_t;

bool DockMDXA::exportBones() {
	mdxaSkel_t *skel;
	mdxaSkelOffsets_t *offsets = (mdxaSkelOffsets_t *)((byte *)header + sizeof(mdxaHeader_t));
	if (header->numBones == 0) {
		imgui_log("dont know how to export numBones==0\n");
		return false;
	}
	int bytes = header->numBones * sizeof(ghoulbone_t);
	ghoulbone_t *mem = (ghoulbone_t *) malloc(bytes);
	ghoulbone_t *iterator = mem;
	if (mem == NULL) {
		imgui_log("mem == NULL, couldnt allocate %d bytes for %d bones\n", bytes, header->numBones);
		return false;
	}
 	for (int bone_id = 0; bone_id < header->numBones; bone_id++) {
 		skel = (mdxaSkel_t *)((byte *)header + sizeof(mdxaHeader_t) + offsets->offsets[bone_id]);
		memcpy(iterator->name, skel->name, sizeof(iterator->name));
		iterator->flags = skel->flags;
		iterator->parent = skel->parent;
		memcpy(iterator->basePoseMat, skel->BasePoseMat.matrix, 3 * 4 * sizeof(float));
		memcpy(iterator->basePoseMatInv, skel->BasePoseMatInv.matrix, 3 * 4 * sizeof(float));
		iterator++;
	}
	FILE *f = fopen("C:\\unity\\dump\\humanoid.ghoulbones", "wb");
	if (f == NULL) {
		imgui_log("couldnt open file dawg\n");
		free(mem);
		return false;	
	}
	fwrite(mem, 1, bytes, f);
	fclose(f);
	free(mem);
	return true;
}


void UnCompressBone(float mat[3][4], int iBoneIndex, const mdxaHeader_t *pMDXAHeader, int iFrame);

bool DockMDXA::exportFrames() {
	char filename[256];
	int numBones = header->numBones;
	int numFrames = header->numFrames;
	int bytesPerFrame = numBones * sizeof(mdxaBone_t);
	// each frame has numBones mdxaBones, so prepare some memory to dump them into
	mdxaBone_t *oneFrame = (mdxaBone_t *) malloc(bytesPerFrame);
		for (int frame_id=0; frame_id<numFrames; frame_id++) {
		
		for (int bone_id=0; bone_id<numBones; bone_id++) {
			mdxaBone_t *thisBone = oneFrame + bone_id;
			UnCompressBone(thisBone->matrix, bone_id, header, frame_id);
		}


		snprintf(filename, sizeof(filename), "C:\\unity\\dump\\frames\\frame_%d", frame_id);


		FILE *f = fopen(filename, "wb");
		if (f == NULL) {
			imgui_log("couldnt open %s dawg\n", filename);
			return false;
		}
		fwrite(oneFrame, 1, bytesPerFrame, f);
		fclose(f);
	}

	free(oneFrame);

	
}

void DockMDXA::imgui_skeleton() {
	mdxaSkel_t *skel;
	mdxaSkelOffsets_t *offsets = (mdxaSkelOffsets_t *)((byte *)header + sizeof(mdxaHeader_t));

	if (ImGui::Button("Export all frames")) {
		exportFrames();
	}

	if (ImGui::Button("Export Bones")) {
		exportBones();


	}

 	for (int bone_id = 0; bone_id < header->numBones; bone_id++) {
 		skel = (mdxaSkel_t *)((byte *)header + sizeof(mdxaHeader_t) + offsets->offsets[bone_id]);

		ImGui::PushID(skel);
		//typedef struct mdxaSkel_s {
		//	char		name[MAX_QPATH];	// name of bone
		//	unsigned int flags;
		//	int			parent;				// index of bone that is parent to this one, -1 = NULL/root
		//	mdxaBone_t	BasePoseMat;		// base pose
		//	mdxaBone_t	BasePoseMatInv;		// inverse, to save run-time calc
		//	int			numChildren;		// number of children bones
		//	int			children[1];		// [mdxaSkel_t->numChildren] (variable sized)
		//} mdxaSkel_t;	// struct size = (int)( &((mdxaSkel_t *)0)->children[ mdxaSkel_t->numChildren ] );

		char tmp[256];
		snprintf(tmp, sizeof(tmp), "bone_id=%d name=%s flags=%d parent=%d numChildren=%d",
			bone_id,
			skel->name,
			skel->flags,
			skel->parent,
			skel->numChildren
		);

		if (ImGui::CollapsingHeader(tmp)) {
			ImGui::DragFloat4("BasePoseMat[0]", skel->BasePoseMat.matrix[0]);
			ImGui::DragFloat4("BasePoseMat[1]", skel->BasePoseMat.matrix[1]);
			ImGui::DragFloat4("BasePoseMat[2]", skel->BasePoseMat.matrix[2]);

			ImGui::DragFloat4("BasePoseMatInv[0]", skel->BasePoseMatInv.matrix[0]);
			ImGui::DragFloat4("BasePoseMatInv[1]", skel->BasePoseMatInv.matrix[1]);
			ImGui::DragFloat4("BasePoseMatInv[2]", skel->BasePoseMatInv.matrix[2]);
			

			if (ImGui::Button("Regenerate Inv")) {
				Inverse_Matrix(&skel->BasePoseMat, &skel->BasePoseMatInv);
			}

			static float fromAngles[3];
			ImGui::DragFloat3("fromAngles", fromAngles);
			if (ImGui::Button("From Angles")) {
				//void Inverse_Matrix(mdxaBone_t *src, mdxaBone_t *dest);
				//void Create_Matrix(const float *angle, mdxaBone_t *matrix);
				Create_Matrix(fromAngles, &skel->BasePoseMat);
			}

		}

		ImGui::PopID();
	}

}



void DockMDXA::imgui_frames() {
	// meh no clue atm, seems the frames are ripped out, using bone cache now or something...
	//header->ofsFrames
}

inline mdxaHeader_t *mdxaHeader(model_t *mod) {
	return mod->data.gla;
}


DockMDXA::DockMDXA(model_t *mod_) {
	mod = mod_;
	add_dock(this);
	header = mdxaHeader(mod_);
	//auto surfHierarchy = firstSurfHierarchy(header);
	//for (int i=0; i<header->numSurfaces; i++) {
	//	strcpy(lookupSurfNames[i], surfHierarchy->name);
	//	surfHierarchy = next(surfHierarchy);
	//}
}

const char *DockMDXA::label() {
	return "MDXA";
}

void DockMDXA::imgui() {
	ImGui::Text("%s", mod->name);
	if (ImGui::CollapsingHeader("Skeleton")) {
		imgui_skeleton();
	}
	//if (ImGui::CollapsingHeader("lods")) {
	//	imgui_list_lods();
	//}
}
