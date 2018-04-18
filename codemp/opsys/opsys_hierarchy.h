#ifndef OPSYSTEM_HIERARCHY_H_
#define OPSYSTEM_HIERARCHY_H_

#include <string>
#include <vector>

#include "opsys.h"

class Node {
public:
	//OpSystem *opsystem = NULL;
	OpSystem opsystem;
	int id;
	int selected = 0;
	std::vector<Node *> childs;
	char name[256];
	Node *parent = NULL;
	Node(char *name_, char *opsystem_filename_);
	int hasNodeAsParent(Node *node);
	int detachFromParent();
	int addChild(Node *child);
	Node *SearchChild(char *nodename);
};

// I cannot check via ImGui::IsItemClicked() if a TreeNode was just opened or actually clicked, so I need a way to toggle the node
// Hence I just toggle node->selected in ImGui.cpp directly... for some reason I cannot do it via "int was_treenode_toggled", what I tried before
// Maybe the values are "one frame off"
extern Node *node_current_rendering;

void render_hierarchy();
void update_nodes(Node *node);
void update_nodes_3d(Node *node);

extern Node *root;
extern Node *selected_node;
extern Node *node_current_rendering;
extern int framecounter;
extern Node *node_dragged;
extern Node *node_dragged_target;

void opsystem_hierarchy_add_javascript_bindings();

#endif