#ifndef OP_AXIS_H
#define OP_AXIS_H

#include "op.h"

typedef struct bone_s {
	int boneid;
	int parentid;
	float x;
	float y;
	float z;
	float quat_w;
	float quat_x;
	float quat_y;
	float quat_z;
	char *name;
} bone_t;

typedef unsigned int glIndex_t;
typedef struct boneweight_s {
	float boneindex0;
	float boneindex1;
	float boneindex2;
	float boneindex3;
	float boneweight0;
	float boneweight1;
	float boneweight2;
	float boneweight3;
} boneweight_t;

//#include <modeldata/axis.h>

typedef struct axisvertex_s {
	float vertexid; // so we can access specific vertices in shader code, normally integer, but that just caused problems...
	float x; // precalculated pos
	float y; // precalculated pos
	float z; // precalculated pos
	float u;
	float v;
	float boneindex0;
	float boneindex1;
	float boneindex2;
	float boneindex3;
	float boneweight0;
	float boneweight1;
	float boneweight2;
	float boneweight3;
} axisvertex_t;

class Buffer2 {
public:
	void *data;
	int length;
	void LoadFile(char *filename);
	~Buffer2();
};

class Model {
public:
	Buffer2 bufferVertices;
	Buffer2 bufferTriangles_0;
	Buffer2 bufferBoneweights;
	Buffer2 bufferUvs;
	int numberOfVertices = 0;
	int numberOfTriangles = 0;
	axisvertex_t *axisvertices;
	Model(char *filename);
	~Model();
	void GenerateMergedData();

	
	int highestBoneID = 0;

	GLuint vertexbuffer = 0;
	GLuint indexbuffer = 0;
	void UploadVerticesToGPU();
	void UploadIndicesToGPU();
	void UploadToGPU();

	GLuint vao = 0;
	int regenerateVao = 0;
	void MakeVAO(GLuint program);
	//void Render(); // Want some nice way to pass the needed stuff... program, uniforms, uniform values etc.
	void ImGuiEditor(ImVec2 pos, ImVec2 size);
};

class OpAxis : public Op {
public:
	float &axisscale = default_link_inputs[0].val_f = 0.01f;
	Model *model = NULL;
	// inputs
	GLuint &prog = default_link_inputs[0].opengl_id;
	float *inputmatrix = default_link_inputs[1].matrix;
	float &drawcount = default_link_inputs[2].val_f;
	GLuint &tex = default_link_inputs[4].opengl_id;
	// outputs
	//GLuint &modelaxis_vertexbuffer = default_link_outputs[0].opengl_id;
	//GLuint &modelaxis_indexbuffer = default_link_outputs[1].opengl_id;

	OpAxis();
	void DrawInScene();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
	std::string WriteExtraData();
	void ReadExtraData(char * line);

};

#endif