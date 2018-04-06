#include "dock_mdxm.h"
#include "../imgui_docks/dock_console.h"
#include "../imgui_openjk/gluecode.h"
#include "../imgui_openjk/imgui_openjk_default_docks.h"
#include "../compose_models.h"

qboolean model_upload_mdxm_to_gpu(model_t *mod);

void DockMDXM::imgui_mdxm_list_surfhierarchy() {
	mdxmSurfHierarchy_t *surfHierarchy = firstSurfHierarchy(header);
 	for (int surface_id=0 ; surface_id<header->numSurfaces; surface_id++) {
		/*
			char		name[MAX_QPATH];
			unsigned int flags;
			char		shader[MAX_QPATH];
			int			shaderIndex;		// for in-game use (carcass defaults to 0)
			int			parentIndex;		// this points to the index in the file of the parent surface. -1 if null/root
			int			numChildren;		// number of surfaces which are children of this one
			int			childIndexes[1];	// [mdxmSurfHierarch_t->numChildren] (variable sized)		
		*/
		char tmp[512];
		snprintf(tmp, sizeof(tmp), "mdxmSurfHierarchy[%d] name=%s flags=%d shader=%s shaderIndex=%d parentIndex=%d numChildren=%d childIndexes[0]=%d",
			surface_id,
			surfHierarchy->name,
			surfHierarchy->flags,
			surfHierarchy->shader,
			surfHierarchy->shaderIndex,
			surfHierarchy->parentIndex,
			surfHierarchy->numChildren,
			surfHierarchy->childIndexes[0]
		);
		if (ImGui::CollapsingHeader(tmp)) {
		}
		
		surfHierarchy = next(surfHierarchy);
	}
}


static inline float G2_GetVertBoneWeightNotSlow( const mdxmVertex_t *pVert, const int iWeightNum)
{
	float fBoneWeight;

	int iTemp = pVert->BoneWeightings[iWeightNum];

	iTemp|= (pVert->uiNmWeightsAndBoneIndexes >> (iG2_BONEWEIGHT_TOPBITS_SHIFT+(iWeightNum*2)) ) & iG2_BONEWEIGHT_TOPBITS_AND;

	fBoneWeight = fG2_BONEWEIGHT_RECIPROCAL_MULT * iTemp;

	return fBoneWeight;
}

void DockMDXM::imgui_mdxm_surface_vertices(mdxmSurface_t *surf) {
	mdxmVertex_t *vert = firstVertex(surf);

	//ImGui::Text("verts=%p type=%s numVerts=%d numTriangles=%d numBoneReferences=%d", 
	//	vert->,
	//	surfacetypeToString((surfaceType_t)surf->ident),
	//	surf->numVerts,
	//	surf->numTriangles,
	//	surf->numBoneReferences
	//);

	for (int vert_id=0; vert_id<surf->numVerts; vert_id++) {
		char dragString[128];

		snprintf(dragString, sizeof(dragString), "verts[%i]", vert_id);
		ImGui::DragFloat3(dragString, vert->vertCoords);
		ImGui::SameLine();
		
		float weight0 = G2_GetVertBoneWeightNotSlow(vert, 0);
		float weight1 = G2_GetVertBoneWeightNotSlow(vert, 1);
		float weight2 = G2_GetVertBoneWeightNotSlow(vert, 2);
		float weight3 = G2_GetVertBoneWeightNotSlow(vert, 3);
		int index0 = G2_GetVertBoneIndex(vert, 0);
		int index1 = G2_GetVertBoneIndex(vert, 1);
		int index2 = G2_GetVertBoneIndex(vert, 2);
		int index3 = G2_GetVertBoneIndex(vert, 3);
					//weights[w] = (byte)(weight * 255.0f);
					//bonerefs[w] = G2_GetVertBoneIndex(&v[k], w);

		ImGui::Text("bone %d=%.2f %d=%.2f %d=%.2f %d=%.2f",
			index0,
			weight0,
			index1,
			weight1,
			index2,
			weight2,
			index3,
			weight3
		);



		vert++;
	}
}

//qboolean model_upload_mdxm_to_gpu_special(model_t *mod, mdxmSurface_t *specialSurface, float scale);

void DockMDXM::imgui_mdxm_surface(mdxmSurface_t *surf, int surface_id) {
	ImGui::PushID(surf);

	char strBoneReferences[128];
	snprintf(strBoneReferences, sizeof(strBoneReferences), "%d bone references", surf->numBoneReferences);
	if (ImGui::CollapsingHeader(strBoneReferences)) {
		
		int *boneRef = (int *) ( (byte *)surf + surf->ofsBoneReferences);
		for (int j=0 ; j<surf->numBoneReferences; j++) {
			char tmpName[128];
			snprintf(tmpName, sizeof(tmpName), "boneReference[%d]", j);
			ImGui::DragInt(tmpName, boneRef + j);
			if (boneRef[j] < 0)
				boneRef[j] = 0;
			if (boneRef[j] >= header->numBones)
				boneRef[j] = header->numBones - 1;
		}
	}

	char strVerts[128];
	snprintf(strVerts, sizeof(strVerts), "surface[%d] %d vertices", surface_id, surf->numVerts);
	if (ImGui::CollapsingHeader(strVerts)) {

		if (ImGui::Button("verts *= 2")) {
			//scaleVertices(surf, 2.0);
			//model_upload_mdxm_to_gpu(mod);
			
			//model_upload_mdxm_to_gpu_special(mod, surf, 2.0);
		}
		ImGui::SameLine();
		if (ImGui::Button("verts /= 2")) {
			//scaleVertices(surf, 0.5);
			//model_upload_mdxm_to_gpu(mod);
			//model_upload_mdxm_to_gpu_special(mod, surf, 0.5);
		}

		imgui_mdxm_surface_vertices(surf);
	}

	ImGui::PopID();
}

typedef struct ghoulvertex_s {
	float x;
	float y;
	float z;
	int boneindex_0;
	int boneindex_1;
	int boneindex_2;
	int boneindex_3;
	float boneweight_0;
	float boneweight_1;
	float boneweight_2;
	float boneweight_3;
	float u;
	float v;
} ghoulvertex_t;

void exportSurface(mdxmSurface_t *surf, char *filename) {
	// the bone indicies are from 0-9 local to surface (couldnt find any higher)
	// to get the real bone number, lookup the 0-9 in boneRef, like boneRef[3]==32
	int *boneRef = (int *) ( (byte *)surf + surf->ofsBoneReferences);
	int bytes = surf->numVerts * sizeof(ghoulvertex_t);
	ghoulvertex_t *ghoulvertices = (ghoulvertex_t *) malloc(bytes);
	ghoulvertex_t *iterator = ghoulvertices;
	mdxmVertex_t *vert = firstVertex(surf);
	for (int vert_id=0; vert_id<surf->numVerts; vert_id++) {
		float weight0 = G2_GetVertBoneWeightNotSlow(vert, 0);
		float weight1 = G2_GetVertBoneWeightNotSlow(vert, 1);
		float weight2 = G2_GetVertBoneWeightNotSlow(vert, 2);
		float weight3 = G2_GetVertBoneWeightNotSlow(vert, 3);
		int index0 = G2_GetVertBoneIndex(vert, 0);
		int index1 = G2_GetVertBoneIndex(vert, 1);
		int index2 = G2_GetVertBoneIndex(vert, 2);
		int index3 = G2_GetVertBoneIndex(vert, 3);
		iterator->x = vert->vertCoords[0];
		iterator->y = vert->vertCoords[1];
		iterator->z = vert->vertCoords[2];
		iterator->boneweight_0 = weight0;
		iterator->boneweight_1 = weight1;
		iterator->boneweight_2 = weight2;
		iterator->boneweight_3 = weight3;
		iterator->boneindex_0 = boneRef[index0];
		iterator->boneindex_1 = boneRef[index1];
		iterator->boneindex_2 = boneRef[index2];
		iterator->boneindex_3 = boneRef[index3];
		mdxmVertexTexCoord_t *tc = (mdxmVertexTexCoord_t *)(firstVertex(surf) + surf->numVerts);
		iterator->u = tc[vert_id].texCoords[0];
		iterator->v = tc[vert_id].texCoords[1];
		iterator++;
		vert++;
	}
	FILE *f = fopen(filename, "wb");
	if (f == NULL) {
		imgui_log("couldnt open %s\n", filename);
		return;
	}
	fwrite(ghoulvertices, 1, bytes, f);
	fclose(f);
	free(ghoulvertices);
}

void exportSurfaceTriangles(mdxmSurface_t *surf, char *filename) {
	mdxmTriangle_t *triangles = (mdxmTriangle_t *)((byte *)surf + surf->ofsTriangles);
	int bytes = surf->numTriangles * sizeof(mdxmTriangle_t);
	FILE *f = fopen(filename, "wb");
	if (f == NULL) {
		imgui_log("couldnt open %s\n", filename);
		return;
	}
	fwrite(triangles, 1, bytes, f);
	fclose(f);
}

void DockMDXM::imgui_mdxm_list_lods() {
	mdxmLOD_t *lod = firstLod(header);
	for (int lod_id=0; lod_id<header->numLODs; lod_id++) {
		ImGui::PushID(lod_id);
		char tmp[512];
		snprintf(tmp, sizeof(tmp), "mdxmLOD_t[%d] ofsEnd=%d", lod_id, lod->ofsEnd );
		

		if (ImGui::Button("Export LOD surfaces")) {
			mdxmSurface_t *surf = firstSurface(header, lod);
			for (int surface_id=0; surface_id<header->numSurfaces; surface_id++) {
				char filename[256];
				snprintf(filename, sizeof(filename), "c:/unity/dump/lod_%d/%d.ghoulvertex_t", lod_id, surface_id); // meh, no name, the '*' char isnt allowed, lookupSurfNames[surface_id]);
				exportSurface(surf, filename);
				surf = next(surf);
			}
		}

		if (ImGui::Button("Export LOD triangles")) {
			mdxmSurface_t *surf = firstSurface(header, lod);
			for (int surface_id=0; surface_id<header->numSurfaces; surface_id++) {
				char filename[256];
				snprintf(filename, sizeof(filename), "c:/unity/dump/lod_%d/%d.tris", lod_id, surface_id);
				exportSurfaceTriangles(surf, filename);
				surf = next(surf);
			}
		}

		if (ImGui::CollapsingHeader(tmp)) {
			mdxmSurface_t *surf = firstSurface(header, lod);




			for (int i=0; i<header->numSurfaces; i++) {



				if (ImGui::CollapsingHeader(toString(surf, lookupSurfNames[i]))) {
					imgui_mdxm_surface(surf, i);
				}
				surf = next(surf);
			}
		}
		lod = next(lod);
		ImGui::PopID();
	}
}

DockMDXM::DockMDXM(model_t *mod_) {
	mod = mod_;
	add_dock(this);
	header = mdxmHeader(mod_);
	auto surfHierarchy = firstSurfHierarchy(header);
	for (int i=0; i<header->numSurfaces; i++) {
		strcpy(lookupSurfNames[i], surfHierarchy->name);
		surfHierarchy = next(surfHierarchy);
	}
}

const char *DockMDXM::label() {
	return "MDXM";
}

void DockMDXM::imgui() {
	ImGui::Text("%s", mod->name);
	if (ImGui::CollapsingHeader("mdxmSurfHierarchy_t")) {
		imgui_mdxm_list_surfhierarchy();
	}
	if (ImGui::CollapsingHeader("lods")) {
		imgui_mdxm_list_lods();
	}
}
