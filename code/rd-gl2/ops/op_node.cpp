#include "../include_gl.h"
//#include "craftstructs.h"
#include "../include_imgui.h"
//#include "imgui_impl_glfw.h"
#include <stdio.h>
//#include "libs\glfw\include\GLFW/glfw3.h"
#include <list>
#include "op.h"
#include "op_node.h"
#include "../opsys/opsys.h"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtx/quaternion.hpp"
#include "../include_console.h"

void NodeCalcLocalToWorld(NodeForOp *node, int depth=0);

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

#include "../utils_opengl/debuglines.h"


typedef struct boneweight_s {
	int boneindex0;
	int boneindex1;
	int boneindex2;
	int boneindex3;
	float boneweight0;
	float boneweight1;
	float boneweight2;
	float boneweight3;
} boneweight_t;

typedef unsigned int glIndex_t;

NodeForOp::NodeForOp(char *name_, OpNode *owner)
{
	//id = owner->next_node_id++;
	// i have no clue anymore why I added an ID in the first place... maybe reenable later
	id = 11223344;
	strcpy(name, name_);
	//childs = std::vector<NodeForOp *>();
}

	int NodeForOp::hasNodeAsParent(NodeForOp *node) {
		NodeForOp *currentNode = this;
		do {
			if (currentNode == node)
				return true;
		} while (currentNode = currentNode->parent);
		return false;
	}
	
	int NodeForOp::detachFromParent() {
		if ( ! this->parent)
			return true;
		//int idx = this->parent->childs.remo(this)
		
		// remove this node out of this->parent->childs

		// whatever: http://stackoverflow.com/questions/39912/how-do-i-remove-an-item-from-a-stl-vector-with-a-certain-value
		//auto &parentchilds = this->parent->childs;

		//auto ret1 = std::remove(childs.begin(), childs.end(), this);
		//// Return Value: An iterator pointing to the new location of the element that followed the last element erased by the function call.
		//// This is the container end if the operation erased the last element in the sequence.
		//
		//auto ret = childs.erase(ret1, childs.end());
		int i=0;
		for (auto it : this->parent->childs)
		{
			if (it == this) {
				this->parent->childs.erase(this->parent->childs.begin() + i);
				break;
			}
			i++;
		}

		//auto toRemove = std::find(this->parent->childs.begin(), this->parent->childs.end(), this);
		//this->parent->childs.erase(toRemove);
		//
		//if (toRemove != this->parent->childs.end()) {
		//	imgui_log("successfully deleted node out of parents childs array\n");
		//} else {
		//	imgui_log("warning, %s is child of %s, but not in the parents childs array\n", this->name.c_str(), this->parent->name.c_str());
		//}

		// fuckin bullshit, no clue how to check if the container actually deleted something.. cba for std::find now
		return 1;


		//if (idx != -1) {
		//	this.parent.childs.splice(idx, 1) // remove inplace
		//	return true;
		//}
		//log("warning, %s is child of %s, but not in the parents childs array\n", this->name.c_str(), this->parent->name.c_str());
		return false;
	}

int NodeForOp::addChild(NodeForOp *child) {
	if (this->hasNodeAsParent(child)) {
		imgui_log("Can't add a parent as child\n");
		return 0;
	}
	child->detachFromParent();
	child->parent = this;
	childs.push_back(child);
	return 1;
}


NodeForOp *loadBones(bone_t *bones, int bonescount) {
		// warning/todo: this code assumes:
		// first bone is root (iterate and add all -1 bones to "node" of opnode)
		// all indexes are valid, no checks (just for/continue for invalid parents + warning)

		// lets create all the nodes beforehand,
		// so we can quickly access specific nodes by id
		NodeForOp **nodes = (NodeForOp **) malloc(bonescount * sizeof(NodeForOp *));
		//NodeForOp *nodes[70];
		for (int i=0; i<bonescount; i++) {
			bone_t *bone = bones + i;
			nodes[i] = new NodeForOp(bone->name, NULL);
			nodes[i]->localPosition = glm::vec3(bone->x, bone->y, bone->z);
			nodes[i]->localRotation = glm::quat(bone->quat_w, bone->quat_x, bone->quat_y, bone->quat_z);
		}

		//// first bone, root, is always just added
		//node->addChild(nodes[0]);

		// now just loop over all bones and link them to their corresponding parent via index lookup
		for (int i=1; i<bonescount; i++) {
			bone_t *bone = bones + i;
			nodes[bone->parentid]->addChild(nodes[i]);
		}

		// calculate the GLOBAL positions based on eachs nodes local pos/rot
		nodes[0]->recalculateGlobalPositionAndRotation();

		// before we free, save the root bones, so we can return it
		NodeForOp *ret = nodes[0];

		// guess what this does
		free(nodes);

		return ret;
}

NodeForOp *LoadMaila(bone_t *bones, int bonesCount, OpNode *opnode) {
	// warning/todo: this code assumes:
	// first bone is root (iterate and add all -1 bones to "node" of opnode)
	// all indexes are valid, no checks (just for/continue for invalid parents + warning)

	// lets create all the nodes beforehand,
	// so we can quickly access specific nodes by id
	NodeForOp **nodes = (NodeForOp **) malloc(bonesCount * sizeof(NodeForOp *));
	//NodeForOp *nodes[70];
	NodeForOp *rootnode = NULL;
	for (int i=0; i<bonesCount; i++) {
		bone_t *bone = bones + i;
		nodes[i] = new NodeForOp(bone->name, NULL);
		nodes[i]->localPosition = glm::vec3(bone->x, bone->y, bone->z);
		nodes[i]->localRotation = glm::quat(bone->quat_w, bone->quat_x, bone->quat_y, bone->quat_z);
		if (bone->parentid == -1)
			rootnode = nodes[i];
	}


	// now just loop over all bones and link them to their corresponding parent via index lookup
	for (int i=0; i<bonesCount; i++) {
		bone_t *bone = bones + i;
		if (rootnode == nodes[i])
			continue;

		//if (i==11) {
		//__asm int 3;
		//}

		nodes[bone->parentid]->addChild(nodes[i]);
	}

	//rootnode->localRotation = glm::inverse(glm::quat(0.706f, 0.043f, 0.043f, 0.706f)) * rootnode->localRotation;
	rootnode->localRotation *= glm::quat(0.705499f, -0.706359f, -0.050055f, 0.035936f);
	// calculate the GLOBAL positions based on eachs nodes local pos/rot
	rootnode->recalculateGlobalPositionAndRotation();
	//node->recalculateGlobalPositionAndRotation();

	NodeCalcLocalToWorld(rootnode, 0);

	for (int i=0; i<bonesCount; i++)
	{
		NodeForOp *node = nodes[i];
		//glm::mat4 localToWorldasd = glm::translate(node->position) * glm::toMat4(node->rotation);
		// localToWorld is calculated via rootnode->recalculateGlobalPositionAndRotation();
		node->bindpose = glm::inverse(node->localToWorld);
	}

	// so OpAxis can axis our bones via link
	opnode->nodes = nodes;


	// guess what this does
	//free(nodes);

	// todo: handle multiple root bones
	//node->addChild(rootnode);
	return rootnode;
}

void OpNode::Init() {

	Op::Init();
	//strcpy( name, "OpNode" );
	size = ImVec2(256, 256);
	pos = ImVec2(250, 250);
	
	number_of_inputs = 6;
	InitLink(0, "AxisScale", OP_TYPE_FLOAT );
	InitLink(1, "Vertices", OP_TYPE_INT );
	InitLink(2, "prog", OP_TYPE_INT );
	InitLink(3, "matrix", OP_TYPE_MATRIX );
	InitLink(4, "origin", OP_TYPE_VECTOR3 );
	InitLink(5, "scale", OP_TYPE_VECTOR3 );
	number_of_outputs = 1;
	InitLinkOutput(0, "Matrices", OP_TYPE_CUSTOMCLASS );

	next_node_id = 0;
	node = new NodeForOp("skeleton", this);
	
	//node->localRotation = glm::quat(0.707f, 0.0f, 0.0f, 0.707f);
	//node->localRotation = glm::quat(0.706f, 0.043f, 0.043f, 0.706f);

	default_link_outputs[0].customclass = new ArrayOfMatrices();
	matrices = (ArrayOfMatrices *)default_link_outputs[0].customclass;


	//NodeForOp *a = new NodeForOp("a", this);
	//NodeForOp *aa = new NodeForOp("aa", this);
	//a->addChild(aa);
	//NodeForOp *b = new NodeForOp("b", this);
	//NodeForOp *bb = new NodeForOp("bb", this);
	//b->addChild(bb);
	//NodeForOp *c = new NodeForOp("c", this);
	//NodeForOp *cc = new NodeForOp("cc", this);
	//c->addChild(cc);
	//node->addChild(a);
	//node->addChild(b);
	//node->addChild(c);
	
	//ModelAxis modelaxis;
	//NodeForOp *modelaxisbones = loadBones(modelaxis.bones, modelaxis.bonesCount);
	//node->addChild(modelaxisbones);

	//node = LoadMaila(bones, bonesCount);
	
	//node->addChild(LoadMaila(bones, bonesCount, this));
	
	//node->localPosition = glm::vec3(-37, 188, 112);
	//node->localScale = glm::vec3(25, 25, 25);
	//node->localPosition = glm::vec3(-129, 223, 67);
	//node->localScale = glm::vec3(40, 40, 40);
	
#if 0
	float scale = 1;
	a->localPosition = glm::vec3(scale, 0, 0);
	aa->localPosition = glm::vec3(scale, 0, 0);
	b->localPosition = glm::vec3(0, scale, 0);
	bb->localPosition = glm::vec3(0, scale, 0);
	c->localPosition = glm::vec3(0, 0, scale);
	cc->localPosition = glm::vec3(0, 0, scale);
#endif

	shallDrawInScene = 1;
}

#ifdef SHITTY_OPNODE
#include <imgui/op_treenode.h>
#endif

void opnode_render_subnodes(NodeForOp *node, OpNode *op);

void OpNode::Render() {
	Op::PreRender();
	
	ImGui::SetCursorPos(pos);

#ifdef SHITTY_OPNODE
	// in this variable our Treenode ImGui version is saving temporary variables to fix some issues
	// the hackery to make this work is in kung/imgui_utils/op_treenode.cpp
	ImGui::opnode = this;
	opnode_render_subnodes(node, this);
	ImGui::opnode = NULL;
#endif
	Op::PostRender();
}


//extern std::list<Mesh *> meshes;




void opnode_render_subnodes(NodeForOp *node, OpNode *op) {
#ifdef SHITTY_OPNODE
	if (node == NULL) {
		ImGui::Text("probably no root set, node==NULL");
		return;
	}
	ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_DefaultOpen;

	
	if (op->selected_node && node==op->selected_node)
	//if (node->selected)
		node_flags ^= ImGuiTreeNodeFlags_Selected;

	//ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, ImGui::GetFontSize()*3); // Increase spacing to differentiate leaves from expanded contents.

	// Node
	op->node_current_rendering = node;



	// normally it will restart on the very left of the window, but we force it to the left of the OpNode here via SetCursorPos
	/*
		void ImGui::Indent(float indent_w)
		{
			ImGuiContext& g = *GImGui;
			ImGuiWindow* window = GetCurrentWindow();
			window->DC.IndentX += (indent_w > 0.0f) ? indent_w : g.Style.IndentSpacing;
			window->DC.CursorPos.x = window->Pos.x + window->DC.IndentX + window->DC.ColumnsOffsetX;
		}	
	*/
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	ImGui::SetCursorPos( ImVec2(op->pos.x + window->DC.IndentX, ImGui::GetCursorPosY()) );

	bool node_open = ImGui::TreeNodeExOperator((void*)(intptr_t)node, node_flags, "%s", node->name);
	op->node_current_rendering = NULL;

	if (ImGui::IsItemHoveredRect() && ImGui::IsMouseDragging(0, 1.0f) && op->node_dragged==NULL) {
		//log("drag node: %s\n",)
		op->node_dragged = node;
	}

	if (ImGui::IsItemHoveredRect() && ImGui::IsMouseReleased(0) && op->node_dragged) {
		imgui_log("add %s to %s\n", op->node_dragged->name, node->name);

		op->node_dragged_target = node;
		op->node_dragged = NULL;
	}
	
	// kung/imgui_utils/op_treenode.cpp line 106, fix at some point..
	if (/*op->treenode_toggled==0 &&*/ ImGui::IsItemClicked()) {
		//node_clicked = i;
		//node->selected = !node->selected; // this is set in ImGui.cpp aswell, to TOGGLE it... so fucked up... framecounter has a difference of 2-6 frames
		
		// either deselect, if already selected, or select the node
		if (op->selected_node && node==op->selected_node)
			op->selected_node = NULL;
		else {
			imgui_log("Selected node: %s\n", node->name);
			op->selected_node = node;
			//OpSystem::SetCurrent(&op->selected_node->opsystem);
		}
		//log("node clicked: %d framecounter=%d\n", treenode_toggled, framecounter);
	}
	if (node_open)
	{		
		for (auto child : node->childs) {
			opnode_render_subnodes(child, op);
		}

		ImGui::TreePop();
	}



	//ImGui::PopStyleVar();
#endif
}


void CalcShit(NodeForOp *node) {
	if (node->parent) {
		
		node->scale = node->parent->scale * node->localScale;

		node->rotation = node->parent->rotation * node->localRotation;

		auto localPos = node->localPosition * node->scale;
		node->position = node->parent->position + node->parent->rotation * localPos;
	} else {
		node->position = node->localPosition;
		node->rotation = node->localRotation;
		node->scale = node->localScale;
	}
}

void NodeForOp::RecursiveRecalc(NodeForOp *parent) {

	//glm::vec3 rotated_pos = localRotation * localPosition;
	//
	//position = parent->position + rotated_pos * position;
	//rotation = parent->rotation * localRotation;

	CalcShit(parent);



	int n = childs.size();
	for (int i=0; i<n; i++) {
		this->RecursiveRecalc(childs[i]);
	}
}
void calc_DrawInScene(NodeForOp *node);
void NodeForOp::recalculateGlobalPositionAndRotation() {
	calc_DrawInScene(this);
	//this->RecursiveRecalc(this);
	//// we dont need to calculate anything for the root node, just it childs
	//int n = childs.size();
	//for (int i=0; i<n; i++) {
	//
	//	// childs[0].RecursiveRecalc(this)???
	//	childs[i]->RecursiveRecalc(this);
	//}
}


#include "../imgui/imgui_fixedarea.h"

void node_renderposition(FixedArea *fa, NodeForOp *node) {
	fa->SetCol(0);
	ImGui::Text("Position");
	fa->SetCol(1);
	ImGui::PushID(&node->localPosition[0]);
	ImGui::DragFloat("", &node->localPosition[0]);
	ImGui::PopID();
	fa->SetCol(2);
	ImGui::PushID(&node->localPosition[1]);
	ImGui::DragFloat("", &node->localPosition[1]);
	ImGui::PopID();
	fa->SetCol(3);
	ImGui::PushID(&node->localPosition[2]);
	ImGui::DragFloat("", &node->localPosition[2]);
	ImGui::PopID();

	fa->NextRow();

	fa->SetCol(0);
	ImGui::Text("Global Pos");
	fa->SetCol(1);
	ImGui::PushID(&node->position[0]);
	ImGui::DragFloat("", &node->position[0]);
	ImGui::PopID();
	fa->SetCol(2);
	ImGui::PushID(&node->position[1]);
	ImGui::DragFloat("", &node->position[1]);
	ImGui::PopID();
	fa->SetCol(3);
	ImGui::PushID(&node->position[2]);
	ImGui::DragFloat("", &node->position[2]);
	ImGui::PopID();
}
void node_renderscale(FixedArea *fa, NodeForOp *node) {
	fa->NextRow();

	fa->SetCol(0);
	ImGui::Text("Scale");
	fa->SetCol(1);
	ImGui::PushID(&node->localScale[0]);
	ImGui::DragFloat("", &node->localScale[0]);
	ImGui::PopID();
	fa->SetCol(2);
	ImGui::PushID(&node->localScale[1]);
	ImGui::DragFloat("", &node->localScale[1]);
	ImGui::PopID();
	fa->SetCol(3);
	ImGui::PushID(&node->localScale[2]);
	ImGui::DragFloat("", &node->localScale[2]);
	ImGui::PopID();

	fa->NextRow();

	fa->SetCol(0);
	ImGui::Text("Global Scale");
	fa->SetCol(1);
	ImGui::PushID(&node->scale[0]);
	ImGui::DragFloat("", &node->scale[0]);
	ImGui::PopID();
	fa->SetCol(2);
	ImGui::PushID(&node->position[1]);
	ImGui::DragFloat("", &node->scale[1]);
	ImGui::PopID();
	fa->SetCol(3);
	ImGui::PushID(&node->position[2]);
	ImGui::DragFloat("", &node->scale[2]);
	ImGui::PopID();
}


void node_renderrotation(FixedArea *fa, NodeForOp *node) {
	// It's nice to see the Quaternion values
	// [3] seems to be [w]..., no clue about the others. I will just using .w .x .y .z
	//node->localRotation = glm::quat();
	fa->NextRow();
	fa->SetCol(0);
	ImGui::PushID(&node->localRotation.w);
	ImGui::DragFloat("", &node->localRotation.w, 0.01f, -1.0f, 1.0f);
	ImGui::PopID();
	fa->SetCol(1);
	ImGui::PushID(&node->localRotation.x);
	ImGui::DragFloat("", &node->localRotation.x, 0.01f, -1.0f, 1.0f);
	ImGui::PopID();
	fa->SetCol(2);
	ImGui::PushID(&node->localRotation.y);
	ImGui::DragFloat("", &node->localRotation.y, 0.01f, -1.0f, 1.0f);
	ImGui::PopID();
	fa->SetCol(3);
	ImGui::PushID(&node->localRotation.z);
	ImGui::DragFloat("", &node->localRotation.z, 0.01f, -1.0f, 1.0f);
	ImGui::PopID();

	// Show the euler angles converted from quat and then convert euler to quat again
	fa->NextRow();
	fa->SetCol(0);
	ImGui::Text("Rot Euler");
	glm::vec3 euler = glm::eulerAngles(node->localRotation);
	euler *= 57.29577951308232; // rad to degree
	fa->SetCol(1);
	ImGui::PushID(&euler[0]);
	ImGui::DragFloat("", &euler[0]);
	ImGui::PopID();
	fa->SetCol(2);
	ImGui::PushID(&euler[1]);
	ImGui::DragFloat("", &euler[1]);
	ImGui::PopID();
	fa->SetCol(3);
	ImGui::PushID(&euler[2]);
	ImGui::DragFloat("", &euler[2]);
	ImGui::PopID();
	node->localRotation = glm::quat(euler * 0.017453292519943295f); // deg 2 rad
}



void OpNode::RenderEditor() {
	Op::RenderEditor();
	

	if (selected_node) {
		FixedArea fa(ImGui::GetCursorPos(), ImGui::GetWindowSize() - ImVec2(10,0), 4); // -10 for scrollbar
		ImGui::PushItemWidth(fa.GetColWidth() - 5); // dont take all the width, looks ugly next to each other without a bit of padding
		node_renderposition(&fa, selected_node);
		node_renderrotation(&fa, selected_node);
		node_renderscale(&fa, selected_node);
		ImGui::PopItemWidth();
		fa.NextRow();
		fa.NextRow();
		ImGui::Text("localToWorld");
		ImGui::PrintMatrix(&fa, glm::value_ptr(selected_node->localToWorld));
		fa.NextRow();
		ImGui::Text("bindpose");
		ImGui::PrintMatrix(&fa, glm::value_ptr(selected_node->bindpose));


		
		fa.NextRow();
		ImGui::Text("ltw_bindpose");
		glm::mat4 ltw_bindpose = selected_node->localToWorld * selected_node->bindpose;
		ImGui::PrintMatrix(&fa, glm::value_ptr(ltw_bindpose));

	}


	//ImGui::Text("textureid: %x", op->textureid);
	ImGui::Text("op->next_node_id: %d", next_node_id);
	ImGui::Text("op->node->childs.size(): %d", node->childs.size());

	
	if (ImGui::Button("Load Maila")) {
		
		//node->addChild(LoadMaila(bones, bonesCount, this));

	}

}

std::string OpNode::WriteExtraData() {
	//fprintf(f, "x %f y %f z %f n %f",
	//	op->x,
	//	op->y,
	//	op->z,
	//	op->n
	//);
	return std::string("");
}

void OpNode::ReadExtraData(char *line) {
	//sscanf(line, "x %f y %f z %f n %f",
	//	&op->x,
	//	&op->y,
	//	&op->z,
	//	&op->n
	//);
}

extern std::vector<float> points;



void RenderLineRecursive(NodeForOp *child) {


	NodeForOp *parent = child->parent;
	
	if (parent == NULL)
		return;

	glm::vec3 from = parent->position;

	

	//from *= 100.0f;
	glm::vec3 to = child->position;
	//to *= 100.0f;
	glm::vec3 color_from = glm::vec3(1, 0, 0);
	glm::vec3 color_to = glm::vec3(0, 1, 1);
	kungdebuglines.AddLine(from, color_from, to, color_to);

	
	for (int i=0; i<child->childs.size(); i++) { 
		RenderLineRecursive(child->childs[i]);
	}

}

void RenderLines(NodeForOp *root) {
	for (int i=0; i<root->childs.size(); i++) {
		RenderLineRecursive(root->childs[i]);
	}
}

void OpNode::Update() {
	if (nodes == NULL)
		return;


	// first we only calc childs[0], so the localToWorld matrix 
	// I only do this to so the global position isnt merge in this localToWorld matrix
	glm::vec3 oldpos = node->position;
	node->position = glm::vec3(0,0,0);
	calc_DrawInScene(node->childs[0]);
	node->position = oldpos;

	
	NodeCalcLocalToWorld(node->childs[0], 0);

//	//matrices->SetAmount(bonesCount);
//
//	for (int i=0; i<bonesCount; i++) {
//
//		NodeForOp *node = nodes[i];
//#if 1
//		glm::mat4 tmpmul = node->bindpose * node->localToWorld;
//#else
//		glm::mat4 tmpmul = node->localToWorld * node->bindpose;
//#endif
//
//
//		//tmpmul = glm::inverse(tmpmul);
//		//tmpmul = node->localToWorld;
//		//nodes[i]->ro
//		float *tmp = glm::value_ptr(tmpmul);
//		matrices->Add(tmp, i);
//	}
	
	memcpy(glm::value_ptr(node->localPosition), default_link_inputs[4].vector3, 3 * sizeof(float));
	memcpy(glm::value_ptr(node->localScale), default_link_inputs[5].vector3, 3 * sizeof(float));

	default_link_outputs[0].changed++;

}

void NodeCalcLocalToWorld(NodeForOp *node, int depth) {

	if (depth == 0) {
		node->localToWorld = node->localMatrix;
	} else {
		node->localToWorld = node->parent->localToWorld * node->localMatrix;
	}

	for (auto c : node->childs) {
		NodeCalcLocalToWorld(c, depth + 1);
	}
}
void calc_DrawInScene(NodeForOp *node) {

	//glm::mat4 test;
	//glm::vec4 testb;
	//auto ret = test * testb;

	if (node->parent) {
		
		node->scale = node->parent->scale * node->localScale;

		node->rotation = node->parent->rotation * node->localRotation;

		auto localPos = node->localPosition * node->scale;
		node->position = node->parent->position + node->parent->rotation * localPos;
		//node->position = node->parent->position + node->rotation * localPos;
		//node->position = node->parent->position + localPos;
	} else {
		node->position = node->localPosition;
		node->rotation = node->localRotation;
		node->scale = node->localScale;
	}

	node->localMatrix = glm::translate(node->localPosition) * glm::toMat4(node->localRotation);

	//node->localToWorld = glm::inverse(glm::translate(node->position) * glm::toMat4(node->rotation));
	//node->localToWorld = glm::toMat4(node->rotation) * glm::translate(node->position);
	

	for (auto c : node->childs) {
		calc_DrawInScene(c);
	}
}
void render_nodes_via_DrawInScene(NodeForOp *node, float axisscale) {




	
	//glm::vec3 x = node->localPosition + node->localRotation * glm::vec3(20,0,0);
	//glm::vec3 y = node->localPosition + node->localRotation * glm::vec3(0,20,0);
	//glm::vec3 z = node->localPosition + node->localRotation * glm::vec3(0,0,20);
	float scale = axisscale;
	glm::vec3 x = node->position + node->rotation * glm::vec3(node->scale.x * scale,0,0);
	glm::vec3 y = node->position + node->rotation * glm::vec3(0,node->scale.y * scale,0);
	glm::vec3 z = node->position + node->rotation * glm::vec3(0,0,node->scale.z * scale);
	
	glm::vec3 red = glm::vec3(1,0,0);
	glm::vec3 green = glm::vec3(0,1,0);
	glm::vec3 blue = glm::vec3(0,0,1);
	
	kungdebuglines.AddLine(node->position, red, x, red);
	kungdebuglines.AddLine(node->position, green, y, green);
	kungdebuglines.AddLine(node->position, blue, z, blue);

	
	for (auto c : node->childs) {
		render_nodes_via_DrawInScene(c, axisscale);
	}

}

void OpNode::DrawInScene() {
	
	calc_DrawInScene(node);
	RenderLines(node);


	//static int first = 1;
	//if (first) {
	//	first = 0;
	//	for (int i=0; i<bonesCount; i++)
	//	{
	//		NodeForOp *node = nodes[i];
	//		glm::mat4 localToWorld = glm::translate(node->position) * glm::toMat4(node->rotation);
	//		node->bindpose = glm::inverse(localToWorld);
	//	}
	//}
	render_nodes_via_DrawInScene(node, axisscale);
}

OpNode::OpNode() {
	Init();
}
