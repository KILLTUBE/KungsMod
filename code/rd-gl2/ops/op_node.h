#ifndef OP_NODE_H
#define OP_NODE_H

//#include <opsys/opsystem_hierarchy.h>
#include "op.h"

#include "../opsys/opsys_link_matrices.h"
class OpNode;

class NodeForOp {
public:


	// Meh, wanted to have a generic/reuseable Node class, but this template aids is not worth it
	// Maybe when I port this to C# :^)
	glm::vec3 localPosition;
	glm::quat localRotation;
	glm::vec3 localScale = glm::vec3(1,1,1);
	// these are non-local aka global:
	// they are recalculated when local rot/pos changes
	glm::vec3 position;
	glm::quat rotation;
	glm::vec3 scale = glm::vec3(1,1,1);
	glm::mat4 localToWorld;
	glm::mat4 localMatrix;
	glm::mat4 bindpose;
	// its nice to have the hierarchy to recursivly calculate the child global pos/rot,
	// but I guess it can be highly optimized by "flatten" the hierarhcy in something like a lookup-table without function stacks
	// we need to recursively go over the childs, to at first we need a little recurse function:
	void RecursiveRecalc(NodeForOp *parent);
	void recalculateGlobalPositionAndRotation();

	OpNode *owner;
	//OpSystem *opsystem = NULL;
	//OpSystem opsystem;
	int id;
	int selected = 0;
	std::vector<NodeForOp *> childs;
	char name[256];
	NodeForOp *parent = NULL;
	NodeForOp(char *name_, OpNode *owner);
	int hasNodeAsParent(NodeForOp *node);
	int detachFromParent();
	int addChild(NodeForOp *child);
};




class OpNode : public Op {
public:
	int drawsort; // based on position, maybe handcode it
	int next_node_id;
	NodeForOp *node;

	NodeForOp *selected_node = NULL;
	NodeForOp *node_current_rendering = NULL;
	int treenode_toggled;
	int framecounter;
	NodeForOp *node_dragged = NULL;
	NodeForOp *node_dragged_target = NULL;

	float &axisscale = default_link_inputs[0].val_f = 0.01f;
	
	GLuint modelaxis_vertexbuffer;
	GLuint modelaxis_indexbuffer;

	
	ArrayOfMatrices *matrices;
	
	NodeForOp **nodes = NULL;

	OpNode();
	void DrawInScene();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
	std::string WriteExtraData();
	void ReadExtraData(char * line);

};

#endif