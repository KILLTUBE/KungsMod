#define _CRT_SECURE_NO_WARNINGS

#ifndef OP_H
#define OP_H

//#include "craftstructs.h"
#include "../imgui/include_imgui.h"

//#include "imgui_impl_glfw.h"
#include <stdio.h>
//#include "libs\glfw\include\GLFW/glfw3.h"

//#include "glfw\include\GLFW/glfw3.h"
//#include <Windows.h>
#include <list>
#include <queue>
#include <string>

//#include <mesh.h>


#include "../include_glm.h"
#include "../include_gl.h"

//#include <include_physfs.h>

#define OP_TYPE_FLOAT 1
#define OP_TYPE_INT 2
#define OP_TYPE_MATRIX 3
#define OP_TYPE_MESH 4
#define OP_TYPE_VERTEXSHADER 5
#define OP_TYPE_FRAGMENTSHADER 6
#define OP_TYPE_PROGRAM 7
#define OP_TYPE_GLBUFFER 8
#define OP_TYPE_PREFAB_INPUT 9
#define OP_TYPE_PREFAB_OUTPUT 10
#define OP_TYPE_GLATTRIB 11
#define OP_TYPE_GLUNIFORM 12
#define OP_TYPE_GLDRAWMODE 13
#define OP_TYPE_CUSTOMCLASS 14
#define OP_TYPE_VECTOR4 15
#define OP_TYPE_QUAT 16
#define OP_TYPE_VECTOR3 17
#define OP_TYPE_VECTOR2 18
#define OP_TYPE_MATRICES 19
#define OP_TYPE_IMAGE 20
#define OP_TYPE_SHADER 21

void DrawLine(float a_x, float a_y, float b_x, float b_y);
void DrawRect(float a_x, float a_y, float b_x, float b_y);

class Op;

class LinkOutput;

class Link {
public:
	// management stuff
	ImVec2 pos; // so a node knows where to draw the line to (and from, calculated only once) could even be dynamically located per editor
	Op *owner;
	int local_id = 0; // e.g. Color Op: r=0 g=1 b=2 a=3, to reassign the links at save/load time
	char name[64] = {"?"};
	int changed = 1; // OpValue will set this to 1 if changed 
	int type = OP_TYPE_FLOAT;
	std::list<LinkOutput *> *cached_backlinks;
	
	// Actual data, the same data needs to be in LinkOutput, because an Op only saves the calculated data in its LinkOutputs
	// The OpSystem::Update() will then distribute the LinkOutput value into the LinkInputs
	float val_f = 0.0;
	int val_i = 0;
	char val_str[128] = {"no text set"};
	float matrix[16] = {0.0f};
	float vector2[2] = {0.0f};
	float vector3[3] = {0.0f};
	float vector4[4] = {0.0f};
	glm::mat4x4 glm_matrix;
	glm::quat quat;
	//Mesh *mesh = NULL;
	GLuint opengl_id = 0; 	// make advanced classes for Program/Vertex/Fragment?
	void *customclass = NULL;

	void SetValue(float val) {
		val_f = val;
		changed++;
	}

	void clean() {
		//val_f = 0.0;
		//val_i = 0;
		//strcpy(val_str, "no text set");
		opengl_id = 0;
	}
	void *javascript_this = NULL;
	void *javascript_vector1 = NULL;
	void *javascript_vector2 = NULL;
	void *javascript_vector3 = NULL;
	void *javascript_vector4 = NULL;
	void *javascript_matrix = NULL;
	void *javascript_object = NULL;
	void *javascript_int = NULL;
};



typedef struct linkline_s {
	LinkOutput *from;
	Link *to;
	//ImVec2 *line_start;
	//ImVec2 *line_end;
} linkline_t;

extern std::list<linkline_t> linklines;

extern LinkOutput *link_from;
extern Link *link_to;

class LinkOutput {
public:
	std::list<Link *> *inputlinks;
	ImVec2 pos;
	char name[64] = {"?"};
	int type;
	Op *owner;
	int local_id; // prefab remapping
	//void setMatrix(glm::mat4x4 matrix);
	void setMatrix(float *matrix);
	int changed = 0;

	// Actual data, the same data needs to be in LinkOutput, because an Op only saves the calculated data in its LinkOutputs
	// The OpSystem::Update() will then distribute the LinkOutput value into the LinkInputs
	float val_f = 0.0;
	int val_i = 0;
	char val_str[128] = {"no text set"};
	float matrix[16] = {0.0f};
	float vector2[2] = {0.0f};
	float vector3[3] = {0.0f};
	float vector4[4] = {0.0f};
	glm::mat4x4 glm_matrix;
	glm::quat quat;
	//Mesh *mesh = NULL;
	GLuint opengl_id = 0; 	// make advanced classes for Program/Vertex/Fragment?
	void *customclass = NULL;
	
	void SetValue(int val) {
		val_i = val;
		changed++;
	}
	void SetValue(float val) {
		val_f = val;
		changed++;
	}
	void SetVector2(float *val) {
		memcpy(vector2, val, 2 * sizeof(float));
		changed++;
	}
	void SetVector3(float *val) {
		memcpy(vector3, val, 3 * sizeof(float));
		changed++;
	}
	void SetVector4(float *val) {
		memcpy(vector4, val, 4 * sizeof(float));
		changed++;
	}

	void *javascript_this = NULL;
	void *javascript_vector1 = NULL;
	void *javascript_vector2 = NULL;
	void *javascript_vector3 = NULL;
	void *javascript_vector4 = NULL;
	void *javascript_matrix = NULL;
	void *javascript_object = NULL;
	void *javascript_int = NULL;
};

typedef enum {
	OP_TYPE_NONE,		// Set op->make_sender_when_type_none=1 in op_$type_init(), e.g. OpCheckerboard doesn't work otherwise
	OP_TYPE_SENDER,		// update() is called every system->update(). An Op is a Sender when it has 0 incoming connections (OpKeyboard is always a Sender).
	OP_TYPE_RECEIVER,	// op->update() is called by a Sender, then the Receiver actively calls update() on choosen childs to keep the flow (e.g. OpSwitch)
	OP_TYPE_REQUESTER,	// A op without outputs is often a Requester, the Requester has the call graph for all Deliverers and calls them on op->request(op)
	OP_TYPE_DELIVERER,	// A Deliverer only updates the values on the outgoing connections, will not call any other op->update().
	OP_TYPE_META		// These Op's help to add meta information to an OpSystem, e.g. OpExpression, OpPrefabInput, OpPrefabOutput
} OpType;

class OpSystem;


class Op {
public:
	int enabled = 1;
	char name[64];
	ImVec2 pos;
	ImVec2 size;
	int selected = 0;
	OpType type;
	unsigned int color;
	int imgui_was_dragged = 0;
	LinkOutput default_link_outputs[16];
	Link default_link_inputs[16];
	int number_of_inputs = 0;
	int number_of_outputs = 0;
	int is_permanent = 0;
	int showtitle = 1;
	std::list<Op *> update_ops_this_order;
	OpSystem *system;
	int cache_ingoing_connections;
	int cache_outgoing_connections;
	int forcereload = 0;

	const char *GetClassname();

	virtual std::string DumpToString();
	virtual std::string DumpLinksToString();
	virtual std::string DumpLinksToString(std::vector<Op*> *selectedOps);
	virtual std::string WriteExtraData();


	// each class can assign id's to their individual Link's, maybe I can make it way more generic at some point, but specialized is nice as well
	virtual LinkOutput *GetOutput(int id);
	virtual Link *	GetInput(int id);
	virtual void	Init();
	virtual void	InitLink(int id, char *name, int type /* ,..., maybe as default value */);
	virtual void	InitLinkOutput(int id, char *name, int type /* , ..., maybe as default value */);
	virtual int		DidInputsChange();
	virtual void	SetInputsUnchanged();
	virtual void	PreRender();
	virtual void	PostRender();
	virtual void	Render();
	virtual void	Update();
	virtual void	Changed();
	virtual void	RenderEditor();
	virtual void	ResizeMinimal();
	virtual void	Destroy();
	virtual void	Request();
	virtual void	ReadExtraData(char *line);
	virtual void	DeleteAllLinks();
	virtual void	OnLinkConnect(int id);
	virtual void	OnLinkDisconnect(int id);
	virtual void	OnLinkUpdate(int id);
	virtual void	DrawInScene        (); // uhm, this should be NULL, so the if (DrawInScene) works lol, gotta fix
	virtual void	PropagateData();

	int call_opsystemrebuild = 0;
	virtual void OnOpSystemRebuild();


	void *javascript_this = NULL;
	void *javascript_heapptr_init = NULL;
	void *javascript_heapptr_update = NULL;
	void *javascript_heapptr_render_canvas = NULL;
	void *javascript_heapptr_render_editor = NULL;
	virtual void	UpdateDuktapeHeappointers();
	
	bool IsSelectedByPoint(ImVec2 point);
	virtual int IsSelectedByRect(ImVec2 rect_from, ImVec2 rect_to);

	static char *TypeToString   (OpType type);
	static void	GenerateCallgraph(Op *op, std::list<Op *> *callgraph);


	// todo: set those values in each Init() so we know...
	int isExpression = 0;
	int isPrefab = 0;
	int isPrefabInput = 0;
	int isPrefabOutput = 0;
	int isKeyboard = 0;
	int isSwitch = 0;
	int isRenderer = 0;
	int isGLLegacy = 0;
	int isXmodel = 0;
	int isAstar = 0;

	int shallDrawInScene = 0;
};



extern Op *dragged_op;

#endif