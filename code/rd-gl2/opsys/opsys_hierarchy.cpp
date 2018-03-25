#include "../include_imgui.h"

#include "../imgui_docks/dock_console.h"
#include <vector>

#include "../opsys/opsys_hierarchy.h"

int next_node_id = 0;
#include <algorithm>


//#include <duktape/dukhelpers.h>

#include "../ops/op.h"
//#include <imgui/op_treenode.h>

Node::Node(char *name_, char *opsystem_filename_) : opsystem(opsystem_filename_)
{
	//opsystem = new OpSystem((char *)opsystem_filename_.c_str());
	id = next_node_id++;
	strcpy(name, name_);
	//strcpy(opsystem->name, opsystem_filename_.c_str());
}

	int Node::hasNodeAsParent(Node *node) {
		Node *currentNode = this;
		do {
			if (currentNode == node)
				return true;
		} while (currentNode = currentNode->parent);
		return false;
	}
	
	int Node::detachFromParent() {
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
	
int Node::addChild(Node *child) {
	if (this->hasNodeAsParent(child)) {
		imgui_log("Can't add a parent as child\n");
		return 0;
	}
	child->detachFromParent();
	child->parent = this;
	childs.push_back(child);
	return 1;
}
Node *Node::SearchChild(char *nodename) {
	// todo: recursive search
	for (auto c : childs) {
		if (strcmp(c->name, nodename) == 0)
			return c;
	}
	return NULL;
}

Node *root = NULL;
Node *selected_node = NULL;
Node *node_current_rendering = NULL;

extern int framecounter;
Node *node_dragged = NULL;
Node *node_dragged_target = NULL;

void render_subnodes(Node *node) {
	//if (node == NULL) {
	//	ImGui::Text("probably no root set, node==NULL");
	//	return;
	//}
	//ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_DefaultOpen;
	//
	//if (selected_node && node==selected_node)
	////if (node->selected)
	//	node_flags ^= ImGuiTreeNodeFlags_Selected;
	//
	////ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, ImGui::GetFontSize()*3); // Increase spacing to differentiate leaves from expanded contents.
	//
	//// Node
	//node_current_rendering = node;
	//bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)node, node_flags, "%s", node->name);
	//node_current_rendering = NULL;
	//
	//if (ImGui::IsItemHoveredRect() && ImGui::IsMouseDragging(0, 1.0f) && node_dragged==NULL) {
	//	//log("drag node: %s\n",)
	//	node_dragged = node;
	//}
	//
	//if (ImGui::IsItemHoveredRect() && ImGui::IsMouseReleased(0) && node_dragged) {
	//	imgui_log("add %s to %s\n", node_dragged->name, node->name);
	//
	//	node_dragged_target = node;
	//	//node_dragged = NULL;
	//}
	//
	//if (treenode_toggled==0 && ImGui::IsItemClicked()) {
	//	//node_clicked = i;
	//	//node->selected = !node->selected; // this is set in ImGui.cpp aswell, to TOGGLE it... so fucked up... framecounter has a difference of 2-6 frames
	//	
	//	// either deselect, if already selected, or select the node
	//	if (selected_node && node==selected_node)
	//		selected_node = NULL;
	//	else {
	//		selected_node = node;
	//		OpSystem::SetCurrent(&selected_node->opsystem);
	//		js_call(ctx, "OnChangeOpSystem", ""); // how could I add the opsys here as param? probably sanest would be to use the userpointer and make sure it exists already kinda
	//	}
	//	//log("node clicked: %d framecounter=%d\n", treenode_toggled, framecounter);
	//}
	//if (node_open)
	//{		
	//	for (auto child : node->childs) {
	//		render_subnodes(child);
	//	}
	//
	//	ImGui::TreePop();
	//}
	//
	//
	//
	////ImGui::PopStyleVar();
}

void update_nodes(Node *node) {
	node->opsystem.update();
	for (auto child : node->childs) {
		update_nodes(child);
	}
}

void update_nodes_3d(Node *node) {
	if (node == NULL)
		return;
	for (auto renderable : node->opsystem.renderables) {
		if (renderable->enabled)
			renderable->DrawInScene();
	}
	//for (auto cube : node->opsystem.cubes) {
	//	op_cube_draw_in_scene(cube, NULL);
	//}
	for (auto child : node->childs) {
		update_nodes_3d(child);
	}
}

void render_root() {
	render_subnodes(root);

	if (node_dragged && node_dragged_target) {
		node_dragged_target->addChild( node_dragged );
		node_dragged = NULL;
		node_dragged_target = NULL;
	}

	if (ImGui::IsMouseReleased(0)) {
		node_dragged = NULL;
		node_dragged_target = NULL;
	
	}
}

void dump_node(Node *node, FILE *f) {

	//if (node != root) {
	//	PHYSFS_fprintf(f, "\ttmp = new Node(\"%s\", \"%s\")\n", node->name, node->opsystem.name);
	//	PHYSFS_fprintf(f, "\tstack.peek().addChild( tmp );\n");
	//	PHYSFS_fprintf(f, "\tstack.push(tmp);\n");
	//}
	//for (auto child : node->childs) {
	//	dump_node(child, f);
	//}
	//
	//if (node != root)
	//	PHYSFS_fprintf(f, "\tstack.pop(); // %s\n", node->name);
}
void save_nodes(char *filename) {
	//char *savepath = "javascript/hierarchy_dumped.js";
	//PHYSFS_File *f = PHYSFS_openWrite(savepath);
	//
	//if (f == NULL) {
	//	imgui_log("Can't open %s for writing\n", savepath);
	//	return;
	//}
	//
	//PHYSFS_fprintf(f, "function add_hierarchy_to_root() {\n");
	//PHYSFS_fprintf(f, "\tcreate_hierarchy(root);\n");
	//PHYSFS_fprintf(f, "}\n");
	//
	//PHYSFS_fprintf(f, "function create_hierarchy(add_to) {\n");
	//PHYSFS_fprintf(f, "\tstack = new Stack();\n");
	//PHYSFS_fprintf(f, "\tstack.push(add_to);\n\n");
	//dump_node(root, f);
	//PHYSFS_fprintf(f, "\n\tstack.pop(); // pop add_to, not really needed\n");
	//PHYSFS_fprintf(f, "}\n");
	//PHYSFS_close(f);
	//log("Successfully wrote %s\n", savepath);
}
void load_nodes(char *filename) {
	//js_call(ctx, "add_hierarchy_to_root", "");
}
void render_hierarchy() {

	if (root == NULL) {
		ImGui::Button("root == NULL");
		return;
	}

	static int first = 1;



	if (first) {
		//Node *a = new Node("a");
		//Node *aa = new Node("aa");
		//a->addChild(aa);
		//Node *b = new Node("b");
		//Node *bb = new Node("bb");
		//b->addChild(bb);
		//Node *c = new Node("c");
		//Node *cc = new Node("cc");
		//c->addChild(cc);
		//root.addChild(a);
		//root.addChild(b);
		//root.addChild(c);
		//js_call("add_hierarchy_to_root", "");
		first = 0;
	}
	
	if (ImGui::Button("New")) {
		Node *newNode = new Node("newchild", "opsystem/default.opsys");
		if (selected_node)
			selected_node->addChild(newNode);
		else
			root->addChild(newNode);
	}
	ImGui::SameLine(0, 5);
	if (ImGui::Button("Delete")) {
		if (selected_node) {
			if (selected_node != root)
			{
				selected_node->detachFromParent();
				delete selected_node;
				selected_node = NULL;
			} else {
				imgui_log("cant delete root node\n");
			}
			
		} else {
			imgui_log("No node selected\n");
		}
	}
	static char filename[128] = {"nodes.txt"};
	ImGui::InputText("filename", filename, sizeof filename);
	if (ImGui::Button("Save")) {
		save_nodes(filename);
	}
	if (ImGui::Button("Load")) {
		load_nodes(filename);
	}
	if (ImGui::Button("Show Renderables of selected node")) {
		if (selected_node) {
			auto renderables = selected_node->opsystem.renderables;
			imgui_log("Renderables.size(): %d\n", renderables.size());
			for (auto r : renderables) {
				imgui_log("Renderable: %s\n", r->name);
			}
		}
	}
	
	render_root();
	ImGui::Text("Node.id = %d", root->id);
	if (node_dragged)
		ImGui::Text("node_dragged=%s", node_dragged->name);
}

#ifdef USE_DUKTAPE

int duk_func_node_new(duk_context *ctx) {
	char *name = (char *)duk_to_string(ctx, 0);
	char *opsystem_filename = (char *)duk_to_string(ctx, 1);
	Node *newNode = new Node(name, opsystem_filename);
	duk_push_int(ctx, (int)newNode);
	return 1;
}
int duk_func_node_get_root(duk_context *ctx) {
	duk_push_int(ctx, (int)root);
	return 1;
}
int duk_func_node_get_selected_node(duk_context *ctx) {
	duk_push_int(ctx, (int)selected_node);
	return 1;
}
int duk_func_node_add_child(duk_context *ctx) {
	
	Node *parent = (Node *)duk_to_int(ctx, 0);
	Node *newChild = (Node *)duk_to_int(ctx, 1);

	if (parent == NULL) {
		imgui_log("node_add_child: parent == NULL\n");
		return 0;
	}

	int ret = parent->addChild( newChild );
	duk_push_int(ctx, ret);
	return 1;
}

int duk_func_node_search_child(duk_context *ctx) {
	
	Node *node = (Node *)duk_to_int(ctx, 0);
	char *nodename = (char *)duk_to_string(ctx, 1);

	if (node == NULL) {
		imgui_log("node_search_child: node == NULL\n");
		return 0;
	}

	Node *found = node->SearchChild( nodename );
	duk_push_int(ctx, (int)found);
	return 1;
}

int duk_func_node_get_opsystem(duk_context *ctx) {
	Node *node = (Node *)duk_to_int(ctx, 0);
	if (node == NULL) {
		imgui_log("node_get_opsystem: node == NULL\n");
		return 0;
	}
	//duk_push_int(ctx, (int)&node->opsystem);
	duk_push_opsystem(ctx, &node->opsystem);
	return 1;
}

//int duk_func_opsystem_get_op(duk_context *ctx) {
//	OpSystem *opsystem = (OpSystem *)duk_to_int(ctx, 0);
//	char *opname = (char *)duk_to_string(ctx, 1);
//	if (opsystem == NULL) {
//		imgui_log("opsystem_get_op: opsystem == NULL\n");
//		return 0;
//	}
//	Op *ret = NULL;
//	for (auto op : opsystem->all) {
//		if (strcmp(op->name, opname) == 0) {
//			ret = op;
//			break;
//		}
//	}
//	duk_push_int(ctx, (int)ret);
//	return 1;
//}


int duk_func_opsystem_get_op(duk_context *ctx) {
	OpSystem *opsystem = (OpSystem *)duk_to_int(ctx, 0);
	char *opname = (char *)duk_to_string(ctx, 1);
	if (opsystem == NULL) {
		imgui_log("opsystem_get_op: opsystem == NULL\n");
		return 0;
	}
	Op *ret = NULL;
	for (auto op : opsystem->all) {
		if (strcmp(op->name, opname) == 0) {
			ret = op;
			break;
		}
	}

	if (ret == NULL) {
		duk_push_undefined(ctx);
		return 1;
	}

	duk_push_op(ctx, ret);

	return 1;
}

int duk_func_opsystem_rebuild(duk_context *ctx) {
	OpSystem *opsystem = (OpSystem *)duk_to_int(ctx, 0);
	if (opsystem == NULL) {
		imgui_log("opsystem_rebuild: opsystem == NULL\n");
		return 0;
	}
	opsystem->regenerateCallGraphs();
	return 0;
}



int duk_func_opsystem_get_new_op_pos(duk_context *ctx) {
	OpSystem *opsystem = (OpSystem *)duk_to_int(ctx, 0);
	if (opsystem == NULL) {
		imgui_log("opsystem_rebuild: opsystem == NULL\n");
		return 0;
	}
	// todo: make this external buffer like op.pos and op.size
	float *buf = js_push_vec2(ctx);
	buf[0] = opsystem->editor->positionForNewOp.x;
	buf[1] = opsystem->editor->positionForNewOp.y;
	return 1;
}

#include <ops/op_nop.h>

int duk_func_opsystem_new_op(duk_context *ctx) {
	OpSystem *opsystem = (OpSystem *)duk_to_int(ctx, 0);
	if (opsystem == NULL) {
		imgui_log("opsystem_rebuild: opsystem == NULL\n");
		return 0;
	}
	OpNop *nop = new OpNop();
	nop->pos = opsystem->editor->positionForNewOp;
	opsystem->add((Op *)nop);
	// ... op
	duk_push_op(ctx, (Op *)nop);
	return 1;
}

int duk_func_op_get_input(duk_context *ctx) {
	Op *op = (Op *)duk_to_int(ctx, 0);
	int id = duk_to_int(ctx, 1);
	if (op == NULL) {
		imgui_log("op_get_input: op == NULL\n");
		return 0;
	}
	Link *link = op->default_link_inputs + id;
	duk_push_input(ctx, link);
	return 1;
}

int duk_func_op_get_output(duk_context *ctx) {
	Op *op = (Op *)duk_to_int(ctx, 0);
	int id = duk_to_int(ctx, 1);
	if (op == NULL) {
		imgui_log("op_get_output: op == NULL\n");
		return 0;
	}
	LinkOutput *linkoutput = op->default_link_outputs + id;
	//duk_push_int(ctx, (int)linkoutput);
	duk_push_output(ctx, linkoutput);
	return 1;
}

// this function isnt used anymore
int duk_func_op_set_javascript_object(duk_context *ctx) {
	Op *op = (Op *)duk_to_int(ctx, 0);
	if (op == NULL) {
		imgui_log("op_set_javascript_object: op == NULL\n");
		return 0;
	}
	
	if (op->javascript_this)
		duk_unref_heapptr(ctx, op->javascript_this);
	if (op->javascript_heapptr_update)
		duk_unref_heapptr(ctx, op->javascript_heapptr_update);

	op->javascript_this           = duk_to_pointer(ctx, 1);
	op->javascript_heapptr_update = duk_to_pointer(ctx, 2);

	// if we got a pointer, we reference it, so it cannot be deleted from javascript
	if (op->javascript_this)
		duk_ref_heapptr(ctx, op->javascript_this);
	if (op->javascript_heapptr_update)
		duk_ref_heapptr(ctx, op->javascript_heapptr_update);

	// this is always 0 gnah
	//op->javascript_this           = duk_get_heapptr(ctx, 1);
	//op->javascript_heapptr_update = duk_get_heapptr(ctx, 2);
	return 0;
}


int duk_func_op_set_number_of_inputs(duk_context *ctx) {
	Op *op = (Op *)duk_to_int(ctx, 0);
	int num = duk_to_int(ctx, 1);
	if (op == NULL) {
		imgui_log("op_set_number_of_inputs: op == NULL\n");
		return 0;
	}
	if (num < 0)
		num = 0;
	if (num > 16)
		num = 16;
	op->number_of_inputs = num;
	return 0;
}

int duk_func_op_set_number_of_outputs(duk_context *ctx) {
	Op *op = (Op *)duk_to_int(ctx, 0);
	int num = duk_to_int(ctx, 1);
	if (op == NULL) {
		imgui_log("op_set_number_of_outputs: op == NULL\n");
		return 0;
	}
	if (num < 0)
		num = 0;
	if (num > 16)
		num = 16;
	op->number_of_outputs = num;
	return 0;
}

int duk_func_output_get_name(duk_context *ctx) {
	LinkOutput *linkoutput = (LinkOutput *)duk_get_userpointer(ctx, 0);
	if (linkoutput == NULL) {
		imgui_log("output_get_name: linkoutput == NULL\n");
		return 0;
	}
	duk_push_string(ctx, linkoutput->name);
	return 1;
}

int duk_func_output_set_name(duk_context *ctx) {
	LinkOutput *linkoutput = (LinkOutput *)duk_get_userpointer(ctx, 0);
	char *newname = (char *)duk_to_string(ctx, 1);
	if (linkoutput == NULL) {
		imgui_log("output_set_name: linkoutput == NULL\n");
		return 0;
	}
	// no strlcpy on VS2015... https://www.freebsd.org/cgi/man.cgi?query=strlcpy&sektion=3
	snprintf(linkoutput->name, sizeof linkoutput->name, "%s", newname);
	return 0;
}

int duk_func_input_get_name(duk_context *ctx) {
	Link *linkinput = (Link *)duk_get_userpointer(ctx, 0);
	if (linkinput == NULL) {
		imgui_log("input_get_name: linkinput == NULL\n");
		return 0;
	}
	duk_push_string(ctx, linkinput->name);
	return 1;
}

int duk_func_input_set_name(duk_context *ctx) {
	Link *linkinput = (Link *)duk_get_userpointer(ctx, 0);
	char *newname = (char *)duk_to_string(ctx, 1);
	if (linkinput == NULL) {
		imgui_log("input_set_name: linkinput == NULL\n");
		return 0;
	}
	// no strlcpy on VS2015... https://www.freebsd.org/cgi/man.cgi?query=strlcpy&sektion=3
	snprintf(linkinput->name, sizeof linkinput->name, "%s", newname);
	return 0;
}




int duk_func_node_get_childs(duk_context *ctx) {
	Node *node = (Node *)duk_to_int(ctx, 0);
	if (node == NULL) {
		imgui_log("node_get_childs: node == NULL\n");
		return 0;
	}
	duk_idx_t arr_idx;
	arr_idx = duk_push_array(ctx);
	int i = 0;
	for (auto child : node->childs) {
		duk_push_uint(ctx, (int)child);
		duk_put_prop_index(ctx, arr_idx, i);

		i++;
	}
	return 1;
}

int duk_func_node_rebuild(duk_context *ctx) {
	Node *node = (Node *)duk_to_int(ctx, 0);
	if (node == NULL) {
		imgui_log("node_get_childs: node == NULL\n");
		return 0;
	}
	node->opsystem.regenerateCallGraphs();
	return 0;
}


int duk_func_heapptr(duk_context *ctx) {
	void *heapptr = duk_to_pointer(ctx, 0);
	duk_push_int(ctx, (int)heapptr);
	return 1;
}

void RecursiveDuktapeRebuild(Node *parent) {
	OpSystem *opsys = &parent->opsystem;
	for (auto op : opsys->all) {
		op->UpdateDuktapeHeappointers();
	}
	for (auto child : parent->childs) {
		RecursiveDuktapeRebuild(child);
	}
}
int duk_func_rebuild(duk_context *ctx) {
	RecursiveDuktapeRebuild(root);
	return 0;
}

// not needed anymore, because I don't RECREATE the functions anymore
// like: function OpAdd() {} and then setting the prototype methods again...
// OpAdd = NewOp("OpAdd") returns the old function, when it already created
int duk_func_updateprototype(duk_context *ctx) {

	
	//log("(first) top=%d top_index=%d\n", duk_get_top(ctx), duk_get_top_index(ctx));

	void *ptr = duk_get_heapptr(ctx, 0);
	

	//log("top=%d top_index=%d\n", duk_get_top(ctx), duk_get_top_index(ctx));
	
	// [...] (because it would only REPLACE the 1st argument)
	//duk_to_object(ctx, 0);

	// [..., op]
	duk_push_heapptr(ctx, ptr);

	//log("(should be 2) top=%d top_index=%d\n", duk_get_top(ctx), duk_get_top_index(ctx));


	// [..., op, op.__proto__]
	duk_get_prototype(ctx, -1);

	
	//log("(should be 3) top=%d top_index=%d\n", duk_get_top(ctx), duk_get_top_index(ctx));

	
	// [..., op, op.__proto__, old OpAdd]
	duk_get_prop_string(ctx, -1, "constructor");

	void *old_prototype = duk_get_heapptr(ctx, -1);
	
	
	//log("(should be 4) top=%d top_index=%d\n", duk_get_top(ctx), duk_get_top_index(ctx));

	// [..., op, op.__proto__, old OpAdd, "OpAdd"]
	duk_get_prop_string(ctx, -1, "name");
	
	char *protostring = (char *) duk_get_string(ctx, -1);

	
	//log("(should be 5) top=%d top_index=%d\n", duk_get_top(ctx), duk_get_top_index(ctx));

	// [..., op, op.__proto__, old OpAdd]
	duk_pop(ctx);

	// [..., op, op.__proto__]
	duk_pop(ctx);
	// [..., op]
	duk_pop(ctx);
	
	//log("(should be 2) top=%d top_index=%d\n", duk_get_top(ctx), duk_get_top_index(ctx));

	// [..., op, the new OpAdd]
	duk_get_global_string(ctx, protostring);
	
	void *new_prototype = duk_get_heapptr(ctx, -1);
	


	if (old_prototype != new_prototype) {

		// [..., op, the new OpAdd, the new OpAdd.prototype]
		duk_get_prototype(ctx, -2);

		// [..., op, the new OpAdd]
		duk_set_prototype(ctx, -3);
		
		// [..., op]
		duk_pop(ctx);
	} else {
		// [..., op]
		duk_pop(ctx);
	}
	
	// [...]
	duk_pop(ctx);
	//log("(should be 1) top=%d top_index=%d\n", duk_get_top(ctx), duk_get_top_index(ctx));

#if 1
	imgui_log("op=%d old_prototype=%d protostring=%s new_prototype=%d\n",
		ptr,
		old_prototype,
		protostring,
		new_prototype
	);
#endif

	duk_push_heapptr(ctx, new_prototype);
	return 1;
}

/*
			// kung foo man: well, i actualy have no clue if this has negative side effects, but i need it...
			///if (!(desc.flags & DUK_PROPDESC_FLAG_WRITABLE)) {
			///	DUK_DD(DUK_DDPRINT("found existing own (non-inherited) plain property, but property is not writable"));
			///	goto fail_not_writable;
			///}
*/
int duk_func_SetFunctionName(duk_context *ctx) {
	// 0 = function
	// 1 = new name
	imgui_log("(should be 2) top=%d top_index=%d\n", duk_get_top(ctx), duk_get_top_index(ctx));
	
	
	void *func = duk_get_heapptr(ctx, 0);
	void *newname = duk_get_heapptr(ctx, 1);
	duk_push_heapptr(ctx, func);
	duk_push_heapptr(ctx, newname);

	duk_put_prop_string(ctx, -2, "name"); // pops the val

	duk_pop(ctx); // remove func object

	imgui_log("(should be 2) top=%d top_index=%d\n", duk_get_top(ctx), duk_get_top_index(ctx));
	return 0;
}


int duk_func_GetCurrentOpSystem(duk_context *ctx) {
	duk_push_opsystem(ctx, cursys);
	return 1;
}

void opsystem_hierarchy_add_javascript_bindings() {
	struct funcis funcs[] = {
		{"heapptr"                   , duk_func_heapptr                    },
		{"rebuild"                   , duk_func_rebuild                    },
		{"GetCurrentOpSystem"        , duk_func_GetCurrentOpSystem         },
		//{"updateprototype"           , duk_func_updateprototype            },
		//{"SetFunctionName"           , duk_func_SetFunctionName            },

		{"node_new"                  , duk_func_node_new                   },
		{"node_get_root"             , duk_func_node_get_root              },
		{"node_get_selected_node"    , duk_func_node_get_selected_node     },
		{"node_get_opsystem"         , duk_func_node_get_opsystem          },
		{"node_get_childs"           , duk_func_node_get_childs            },
		{"node_add_child"            , duk_func_node_add_child             },
		{"node_search_child"         , duk_func_node_search_child          },
		{"node_rebuild"              , duk_func_node_rebuild               },
		
		{"opsystem_get_op"           , duk_func_opsystem_get_op            },
		{"opsystem_rebuild"          , duk_func_opsystem_rebuild           },
		{"opsystem_get_new_op_pos"   , duk_func_opsystem_get_new_op_pos    },
		//{"opsystem_get_op_2"         , duk_func_opsystem_get_op_2        },
		{"opsystem_new_op"           , duk_func_opsystem_new_op            },
		
		{"op_set_javascript_object"  , duk_func_op_set_javascript_object   },

		{"op_get_input"              , duk_func_op_get_input               },
		{"op_get_output"             , duk_func_op_get_output              },
		{"op_set_number_of_inputs"   , duk_func_op_set_number_of_inputs    },
		{"op_set_number_of_outputs"  , duk_func_op_set_number_of_outputs   },
		
		{"input_get_name"            , duk_func_input_get_name             },
		{"input_set_name"            , duk_func_input_set_name             },
		
		{"output_get_name"           , duk_func_output_get_name            },
		{"output_set_name"           , duk_func_output_set_name            },
		{NULL, NULL}
	};

	for (int i=0; funcs[i].name; i++) {
		js_register_function(ctx, funcs[i].name, funcs[i].func);
	}

}

#endif