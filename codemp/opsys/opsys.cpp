#include "../opsys/opsys.h"
#include "../ops/op_expression.h"
#include "../ops/op_prefab.h"
#include "../ops/op_prefab_input.h"
#include "../ops/op_prefab_output.h"
#include "../ops/op_switch.h"
#include "../ops/op_keyboard.h"
#include "../ops/op_logger.h"
#include "../ops/op_javascript.h"
#include "../ops/op_astar.h"

#include <vector>
#include <map>

#ifdef USE_DUKTAPE
#include <kung/include_duktape.h>
#endif

#include "../imgui_docks/dock_console.h"
#include "../ops/op_prefab_input.h"
#include "../ops/op_prefab_output.h"

#include "../ops/op_gl_legacy.h"
//#include "ops/op_xmodel.h"
#include "../opsys/opsys_hierarchy.h"

std::list<OpSystem *> systems;

//OpSystem perm("opsystem/perm.opsys", 1);
//OpSystem sys_ortho("ortho.txt", 1);
//OpSystem menu("opsystem/menu.opsys", 0);
//OpSystem tmp1("opsystem/tmp1.opsys", 0);
//OpSystem tmp2("opsystem/tmp2.opsys", 0);
//OpSystem GLHacker("glhacker.txt", 0);
//OpSystem GLHacker2("glhacker2.txt", 0);
//OpSystem GLHacker3("glhacker3.txt", 0);
//OpSystem sky("opsystem/sky.opsys", 0);
//OpSystem *cursys = &perm;
OpSystem *cursys = NULL;

void init_systems() {
	for (auto sys : systems) {
		sys->loadFile(sys->name);
		if (sys->run_on_start)
			sys->regenerateCallGraphs();
	}
}


OpSystem::OpSystem(char *filename_) {
	editor = new OpSystemEditor(this);

	// don't add to systems, because we are going to call them outselves while iterating over all nodes
	strcpy(name, filename_);
	loadFile(name);
}

OpSystem::OpSystem(char *name, int run_on_start_) {
	editor = new OpSystemEditor(this);
	run_on_start = run_on_start_;
	strcpy(this->name, name);
	// do NOT load perm.txt here
	// otherwise the perm sys hasnt even the opcodes set yet by op_all.cpp
	// it will load perm.txt once they are added
	//if (strcmp(name, "perm.txt"))
	//	loadFile(name);
	//systems.push_back(this);
}

OpSystem::OpSystem(char *name, OpPrefab *prefab_) {
	editor = new OpSystemEditor(this);
	prefab = prefab_;
	prefab->subsys = NULL;
	strcpy(this->name, name);
	isPrefab = 1;
}

extern char opseditor_filename[64];
void OpSystem::SetCurrent(OpSystem *sys) {
	strcpy(opseditor_filename, sys->name);
	cursys = sys;
}

void OpSystem::render() {
	for (auto op : all) {
		op->Render();
	}
}

void OpSystem::update() {
#ifdef USE_DUKTAPE
	for (auto op : expressions) {
		char *code = ((OpExpression *)op)->code;
		duk_push_string(ctx, op->name);
		int ret = duk_eval_raw(ctx, code, 0, DUK_COMPILE_EVAL | DUK_COMPILE_SAFE | DUK_COMPILE_NOSOURCE | DUK_COMPILE_STRLEN);
		//op->val = duk_get_number(ctx, -1);
		//if (ret == 0)
		//op->color = 0x00FF00FF;
		//else
		//op->color = 0x0000FFFF;
		//log("ret: %d", ret);
		duk_pop(ctx);
	}
#endif
	for (auto op : all) {
		switch (op->type) {
			case OpType::OP_TYPE_REQUESTER:
				op->Request(); // Updates the whole call graph
				break;
			case OpType::OP_TYPE_SENDER:
				op->Update(); // A Sender will call other nodes itself, which then call other nodes etc. like snowball effect
				break;
			case OpType::OP_TYPE_NONE:
				op->Update();
				op->forcereload = 0;
				break;
		}
	}

	// Notify all outputs that the Op called op_changed()
	// This will e.g. cause OpProgram to rebuild the shader program, when either OpVertexShader or OpFragmentShader calls op_changed()
	// It needs to happen on the end of the OpSystem::Update(), because otherwise the other shader might not have finished building its shader yet on startup
	for (auto op : changed_ops) {
		for (int i=0; i<op->number_of_outputs; i++) {
			auto *ol = op->default_link_outputs + i;
			for (auto il : *ol->inputlinks) {
				il->owner->OnLinkUpdate(il->local_id);
			}
		}
	}
	changed_ops.clear();
}

int count_ingoing_connections(Op *op) {
	int ret = 0;
	for (int i=0; i<op->number_of_inputs; i++) {
		Link *il = op->default_link_inputs + i;
		ret += il->cached_backlinks->size();
	}
	return ret;
}

int count_outgoing_connections(Op *op) {
	int outgoing_links = 0;
	for (int i=0; i<op->number_of_outputs; i++) {
		LinkOutput *output = op->default_link_outputs + i;
		// I cannot just add the inputlinks->size() anymore, because I need to filter the Metas
		//outgoing_links += output->inputlinks->size();
		for (auto inputlink : *output->inputlinks) {
			Op *owner = inputlink->owner;
			if (inputlink->owner->type == OP_TYPE_META)
				continue;
			outgoing_links++;
		}
	}
	return outgoing_links;
}

void OpSystem::updateRequesterList() {
	requesters.clear();
	for (auto op : all) {
		if (op->type != OP_TYPE_NONE)
			continue;
		// If a op has no output links and some input links, it will be a requester
		if (op->cache_outgoing_connections == 0 && op->cache_ingoing_connections > 0) {
			op->type = OP_TYPE_REQUESTER;
			//log("%s: outgoing links: %d\n", op->name, outgoing_links);
			requesters.push_back(op);
		}
	}
}

void OpSystem::generateBacklinks() {
	// first clear all cached data in every input link
	// iteration order: op -> input links
	for (auto op : all) {
		for (int i=0; i<op->number_of_inputs; i++) {
			Link *input = op->default_link_inputs + i;
			input->cached_backlinks->clear();
		}
	}

	// now add all output links inside the input links
	// iteration order: op -> output links -> input links
	for (auto op : all) {
		
		// We do not generate backlinks from a normal Op to OpPrefabInput
		// But OpPrefabOutput backlinks *are* generated, because I need them to quickly retrieve the inputs for op_post_render()
		if (op->type == OP_TYPE_META)
			continue;

		for (int i=0; i<op->number_of_outputs; i++) {
			LinkOutput *output = op->default_link_outputs + i;
			//log("check %d inputs of output %s", output->inputlinks->size(), op->name);
			// iterate all links the output points to
			for (auto inputs : *output->inputlinks) {
				// cache the output link in the linkinput, so we can quickly iterate from input links to the connected outputs
				inputs->cached_backlinks->push_back( output );
			}
		}
	}
}

void flood_fill_childs_to_receiver(Op *op) {
	for (int i=0; i<op->number_of_outputs; i++) {
		LinkOutput *lo = op->default_link_outputs + i;
		for (auto il : *lo->inputlinks) {
			il->owner->type = OP_TYPE_RECEIVER;
			flood_fill_childs_to_receiver(il->owner);
		}
	}
}

void OpSystem::regenerateCallGraphs() {
	// Reset all types, we will rebuild the types based on the present graph
	// Exception 1) OpKeyboard is always a Sender, because the data originates from it
	// Exception 2) OpSwitch is always a Sender, because it has multiple outputs. This method would detect each of them as Requesters
	// Exception 3) OpExpression/OpPrefabInput/OpPrefabOutput are always Metas
	// The type of an Op depends on its graph position
	// generateBacklinks() depends on the OP_TYPE_META information, to skip the backlink generation for Metas
	for (auto op : all) {
		if ( op->isExpression || op->isPrefabInput || op->isPrefabOutput ) {
			op->type = OP_TYPE_META;
			//// Meta ops can have connections, but they do not interact with the callgraph regeneration
			//op->cache_ingoing_connections = 0;
			//op->cache_outgoing_connections = 0;
		} else
			op->type = OP_TYPE_NONE;
	}

	// op_generate_callgraph(***) and count_ingoing_connections(Op *) depend on precalculated backlinks, so lets cache them:
	generateBacklinks();

	// Cache the count of the ingoing/outgoing connections. 
	for (auto op : all) {
		//if (op->type == OP_TYPE_META)
		//	continue;
		op->cache_ingoing_connections = count_ingoing_connections(op);
		op->cache_outgoing_connections = count_outgoing_connections(op);
	}

	// A OpKeyboard/OpSwitch without any inputs is a sender and its children Receivers
	for (auto op : all) {
		if ( ( op->isSwitch || op->isKeyboard ) && op->cache_ingoing_connections==0 ) {
			op->type = OP_TYPE_SENDER;
			flood_fill_childs_to_receiver(op);
		}
	}

	// This method only checks ops with OP_TYPE_NONE, because the Metas and Senders/Receivers are already handled
	updateRequesterList();

	// clear all call graphs, even of non-Requesters, because they could have been a Requester in the past
	for (auto op : all)
		op->update_ops_this_order.clear();

	// Generate the call graph for every Requester
	for (auto op : requesters) {
		Op::GenerateCallgraph(op, &op->update_ops_this_order);
		// ...and make the members of the callgraph a deliverer
		for (auto deliverer : op->update_ops_this_order)
			deliverer->type = OP_TYPE_DELIVERER;
	}

	// E.g. OpCheckerboard doesn't work otherwise, because its not updated by OpSystem::Update()
	// I can't update() all Nones, because a OpLogger with no inputs would spam all the time
	// Maybe call them OP_TYPE_ORPHAN? And update() them nonetheless
	// Any Op needs to check op->cache_input_connections and quit the update(), if it would spam otherwise
	// for now, I'm going to update all Nones
	//for (auto op : all)
	//	if(op->type == OP_TYPE_NONE && op->make_sender_when_type_none)
	//		op->type = OP_TYPE_SENDER;

	updateExecIDs();
	updatePrefabInputIDs();
	updatePrefabOutputIDs();
	updateRenderers();
	updateRenderables();
	updateRenderablesLegacy();
	updateAStars();

	fixNameCollisions();

	if (isPrefab) {
		prefab->number_of_inputs  = prefabinputs.size();
		prefab->number_of_outputs = prefaboutputs.size();	
	}

	// dispatch these "events", only used for OpJavaScriptfile so far
	for (auto op : all) {
		if (op->call_opsystemrebuild)
			op->OnOpSystemRebuild();
	}

}


void OpSystem::deleteOp(Op *op) {
	auto iterator = all.begin();
	while (iterator != all.end()) {
		if (op == *iterator) {
			op->Destroy();
			if (contextMenuOp == op) { // make sure we wont derefence this op anymore from context menu once its deleted... wouldnt have such bugs with a int-handle-only system
				contextMenuOp = NULL;
			}
			iterator = all.erase(iterator);
			break;
		}
		iterator++;
	}
}

void OpSystem::deleteSelectedOps() {

	// first only delete the from/to links of every delete candidate
	for (auto op : all) {
		if (op->selected && ! op->is_permanent) {
			op->DeleteAllLinks();
		}
	}
	
	auto iterator = all.begin();
	while (iterator != all.end()) {
		auto op = *iterator;
		if (op->selected && ! op->is_permanent) {
			op->Destroy();
			if (contextMenuOp == op) { // make sure we wont derefence this op anymore from context menu once its deleted... wouldnt have such bugs with a int-handle-only system
				contextMenuOp = NULL;
			}
			iterator = all.erase(iterator);
		} else {
			iterator++;
		}
	}
	// update all stuff, otherwise the deleted op might still be in requester list and would crash
	regenerateCallGraphs();
}



void OpSystem::renderEditor() {
	if (ImGui::Button("Delete selected Ops")) {
		deleteSelectedOps();		
	}


	for (auto op : all) {
		if (op->selected) {
			ImGui::PushID((ImGuiID)op);
			op->RenderEditor();
			ImGui::PopID();
		}
	}
}

void OpSystem::add(Op *op) {
	if (this == NULL) {
		imgui_log("system is NULL, select a system first");
		return;
	}
	all.push_back(op);
	op->system = this;
}

void OpSystem::makeOpButtons() {
}

void OpSystem::clearScene() {
	std::vector<Op *>::iterator track = all.begin();

	// delete ALL links, inclusivly the permanent ones, they just won't be deleted later
	for (auto op : all) {
		op->DeleteAllLinks();
	}

	regenerateCallGraphs();

	// now we can delete the actual ops, without link interference
	while (track != all.end()) {
		Op *op = *track;
		if (op->is_permanent) {
			track++;
			continue;
		}
		op->Destroy();
		track = all.erase(track);
	}
	// otherwise the old call graph will reference to non-existig ops -> crash on op->request()
	regenerateCallGraphs();
}
void OpSystem::unselectAll() {
	for (auto op : all)
		op->selected = 0;
}
static int between(int min, int val, int max) {
	return (min <= val) && (max >= val);
}
void op_create_link(Op *from, int output_id, Op *to, int input_id) {
	
	if (from == NULL) {
		imgui_log("op_system> from is NULL\n");
		return;
	}
	if (to == NULL) {
		imgui_log("op_system> to is NULL\n");
		return;
	}
	
	LinkOutput *output_list = from->GetOutput(output_id);
	for (auto il : *output_list->inputlinks) {
		if (il->owner == to) {
			if (il == to->default_link_inputs + input_id) {
				//log("found double connection, return");
				return;
			}
		}
	}
	if ( ! output_list)
		return; // getOutput is supposed to write a specialized error message
	Link *input_link = to->GetInput(input_id);
	if ( ! input_link)
		return; // getInput is supposed to write a specialized error message
	output_list->inputlinks->push_back( input_link );
}


//extern int was_already_in_system;


Op *OpSystem::op_from_string(char *line, int forceRecreation) {

	char firstword[128];
	sscanf(line, "%s", firstword);
	//log("Type: %s", firstword);

	oplist_t *found = NULL;
	// compare "firstword" with all available ops and call from_string() to create it


	imgui_log("op_from_string> todo: make some kind of hashmap of all available docks, so i can still get a reference by string to them");
	return NULL;
	//for (oplist_t *avail=available_ops; avail->name; avail++) {
	//	if ( ! strcmp(avail->name, firstword)) {
	//		//return avail->from_string(line);
	//		found = avail;
	//		continue;
	//	}
	//}

	if ( ! found)
		return NULL;
	
	Op *op = NULL;

	char buf[1024];
	int ret = sprintf(buf, "%63s enabled %%d pos %%f %%f size %%f %%f selected %%d perm %%d name %%63s %%[^\n]", firstword);
	
	int enabled;
	float pos_x;
	float pos_y;
	float size_x;
	float size_y;
	int selected;
	int is_permanent;
	char name[64];
	char extra[1024] = {0};

	sscanf(line, buf,
		&enabled,
		&pos_x,
		&pos_y,
		&size_x,
		&size_y,
		&selected,
		&is_permanent,
		name,
		extra
	);

	//log("extra for %s: %s", name, extra);


	// never look for existing ops, when we cant to create the op from string only
	if ( ! forceRecreation) {
		// find op by name
		// this will find either the permanent ops or the same-id one (we will only update then)
		for (auto asd : all) {
			//log("search for \"%s\", asd->name =\"%s\"", name, asd->name);
			if ( ! strcmp(asd->name, name)) {
				op = asd;
				was_already_in_system = 1;
			}
		}
	}

	// if op wasnt found by previous for loop, create it
	if ( ! op ) {
		op = found->create_op();
		was_already_in_system = 0;
	}

	if ( ! op) {
		imgui_log("could not create op via found->create_op() method, line:%s", line);
		return NULL;
	}


	// only set values when sscanf was sucessfull parsing all shit
	//if (ret == 5)
	{
		//log("x %.0f y %.0f selected %d name %s", pos_x, pos_y, selected, name);
		op->enabled = enabled;
		op->pos.x = pos_x;
		op->pos.y = pos_y;
		op->size.x = size_x;
		op->size.y = size_y;
		op->selected = selected;
		strcpy(op->name, name);
		op->ReadExtraData(extra);
	}
	// we dont set is_permanent here, because only the C++ code is allowed to set it (not via user input), because they cannot be freed e.g.
	// we basically just updated the permanent op, so it has the perm.txt values... its still added to "perm" nonetheless
	//if (is_permanent)
	//	return NULL;
	return op;
}

//#include <include_physfs.h>
//#include <imgui/MagicFile.cpp/magicfile.h>

void OpSystem::loadFile(char *filename) {
#if 0
//#if 1
//	FILE *f;
//#else
//	PHYSFS_File *f;
//#endif
	char *line;

	id2op.clear();
	loaded_ops.clear();
	
	char *content;
	size_t content_bytes;
	int ret = file_get_contents(filename, &content, &content_bytes);





//#if 1
//	char filename_tmp[256];
//	sprintf(filename_tmp, "baseq3/%s", filename);
//	f = fopen(filename_tmp, "r");
//#else
//	f = PHYSFS_openRead(filename);
//#endif

	//if ( ! content) {
	if (ret == 0) {
		imgui_log("Can't open %s\n", filename);
		return;
	}
	
	line = strtok(content, "\n");

	imgui_log("load system: %s\n", filename);


//#if 1
//	while ( fgets (line, sizeof line, f) != NULL ) {
//#else
//	while ( PHYSFS_fgets (line, sizeof line, f) != NULL ) {
//#endif
		
	while (line != NULL) {
		LoadLine(line);
		line = strtok(NULL, "\n");
	}

	// now add all ops into OpSystem
	for (auto op : loaded_ops) {
		// so this op will be initialized by the next OpSystem::Update()
		op->forcereload = 1;
		add(op);
	}
	imgui_log("Loaded %d ops into %s\n", loaded_ops.size(), name);
//#if 1
//	fclose(f);
//#else
//	PHYSFS_close(f);
//#endif

#endif
	regenerateCallGraphs();
}


void OpSystem::LoadLine(char *line) {
			//log("line: %s", line);

		// op_from_string() needs cursys set
		//cursys = this;
		Op *op = this->op_from_string(line);


		if (op) {
			// dont re-insert permanent ops, because we don't delete them aswell, the same pointers would be inserted multiple times
			// neither insert already existing ones
			if ( ! was_already_in_system) {

				loaded_ops.push_back(op);
			} else {
				//log("do not add %s to loaded_ops", op->name);
			}
			// but we actually need the name2op reference, so we can link them by name-id
			id2op[std::string(op->name)] = op;
		} else {
			// its probably a link
			//log("OpSystem::loadFile> op_from_string(%s) is NULL", line);
		}
		



		char type[128];
		sscanf(line, "%s", type);
		
		if (strcmp("Link",        type)==0) {
			// Link op=2 link=0 to op=3 link=3
			char name_from[64];
			char name_to[64];
			int output_id, input_id;
			sscanf(line, "Link %s [ %d ] to %s [ %d ]",
				name_from,
				&output_id,
				name_to,
				&input_id
			);
			//log("Link %s [ %d ] to %s [ %d ]", name_from, output_id, name_to, input_id);
			
			Op *in = id2op[std::string(name_from)];

			
			if ( ! in) {
				imgui_log("Op named \"%s\" doesnt exist\n", name_from);
				return;
			}
			Op *out = id2op[std::string(name_to)];
			if ( ! in) {
				imgui_log("Op named \"%s\" doesnt exist\n", name_to);
				return;
			}


			op_create_link(in, output_id, out, input_id);
		}
}

void OpSystem::fixNameCollisions() {
	std::map<std::string, Op *> id2op;
	for (auto op : all) {
		std::string key(op->name);
		// if there is already such a name...
		if (id2op.find(key) != id2op.end()) {
			// ... then rename by adding its address to his normal name (that should prevent name-collision)
			char newname[64];

			char *oldaddress = strrchr(op->name, '#');
			if (oldaddress && strlen(oldaddress)==9) {
				//log("got old address: %s length=%d\n", oldaddress, strlen(oldaddress));
				oldaddress[0] = '\0'; // turn "OpMatrix#00112233" into "OpMatrix" e.g.
			}


			snprintf(newname, sizeof op->name, "%s#%x", op->name, op);
			imgui_log("name collision for %s, renaming to %s\n", op->name, newname);
			strncpy(op->name, newname, sizeof op->name);
			key = op->name;
		}
		id2op[key] = op;
	}
}

void OpSystem::saveFile(char *filename) {

	//PHYSFS_File *f = PHYSFS_openWrite(filename);
	////FILE *f = fopen(filename, "w");
	//
	//if ( ! f) {
	//	imgui_log("Can't open file to write: \"%s\" Error: %s\n", filename, PHYSFS_getLastError());
	//	return;
	//}
	//fixNameCollisions();
	//for (auto op : all) {
	//	std::string opstring = op->DumpToString();
	//	PHYSFS_fprintf(f, "%s\n", opstring.c_str());
	//}
	//for (auto op : all) {
	//	std::string links = op->DumpLinksToString();
	//	PHYSFS_fprintf(f, "%s", links.c_str());
	//}
	//log("Dumped %d ops into %s\n", all.size(), filename);
	////fclose(f);
	//PHYSFS_close(f);
}

OpValue *OpSystem::createValue(char *name, int is_permanent) {
	OpValue *ret = new OpValue();
	ret->is_permanent = is_permanent;
	strcpy(ret->name, name);
	add((Op *)ret);
	return ret;
}
OpMatrix *OpSystem::createMatrix(char *name, int is_permanent) {
	OpMatrix *ret = new OpMatrix();
	ret->is_permanent = is_permanent;
	strcpy(ret->name, name);
	add((Op *)ret);
	return ret;
}

bool compare_op_position          (const Op         *first, const Op         *second) { return first->pos.y < second->pos.y; }
bool compare_op_position_renderer (const OpRenderer *first, const OpRenderer *second) { return first->pos.y < second->pos.y; }
//bool compare_op_position_cube     (const OpCube     *first, const OpCube     *second) { return first->pos.y < second->pos.y; }

void OpSystem::updateExecIDs() {
	
	expressions.clear();
	for (auto op : all) {
		if (op->isExpression) {
			//log("Found expression: %s\n", op->name);
			expressions.push_back( op );
		}
	}
	expressions.sort(compare_op_position);
	int i = 0;
	for (auto op : expressions) {
		((OpExpression *)op)->execid = i;
		//log("sorted: %s\n",  op->name);
		i++;
	}
}
void OpSystem::updatePrefabInputIDs() {
	
	prefabinputs.clear();
	for (auto op : all) {
		if (op->isPrefabInput) {
			//log("Found expression: %s\n", op->name);
			prefabinputs.push_back( op );
		}
	}
	prefabinputs.sort(compare_op_position);
	int i = 0;
	for (auto op : prefabinputs) {
		((OpPrefabInput *)op)->inputid = i;
		//log("sorted: %s\n",  op->name);
		i++;
	}
}
void OpSystem::updatePrefabOutputIDs() {
	
	prefaboutputs.clear();
	for (auto op : all) {
		if (op->isPrefabOutput) {
			//log("Found expression: %s\n", op->name);
			prefaboutputs.push_back( op );
		}
	}
	prefaboutputs.sort(compare_op_position);
	int i = 0;
	for (auto op : prefaboutputs) {
		((OpPrefabOutput *)op)->outputid = i;
		//log("sorted: %s\n",  op->name);
		i++;
	}
}
void OpSystem::updateRenderers() {

	// is a Renderable now aswell
	return;
	renderers.clear();
	for (auto op : all) {
		if (op->isRenderer) {
			//log("Found expression: %s\n", op->name);
			renderers.push_back( (OpRenderer *)op );
		}
	}
	renderers.sort(compare_op_position_renderer);
	int i = 0;
	for (auto renderer : renderers) {
		renderer->drawsort = i;
		i++;
	}
}
void OpSystem::updateRenderables() {
	
	renderables.clear();
	for (auto op : all) {
		if (op->shallDrawInScene) {
			//log("Found expression: %s\n", op->name);
			renderables.push_back( op );
		}
	}
	//cubes.sort(compare_op_position_cube);
	//int i = 0;
	//for (auto cube : cubes) {
	//	//cube->drawsort = i;
	//	i++;
	//}
}


void render_legacy(Node *node) {
	for (auto op : node->opsystem.renderablesLegacy) {
		//renderable->draw_in_scene(renderable);
		if (op->isGLLegacy) {
			((OpGLLegacy *) op)->RenderLegacyCode();
		}
		//if (op->isXmodel) {
		//	((OpXModel *) op)->RenderLegacyCode();
		//}
	}
	//for (auto cube : node->opsystem.cubes) {
	//	op_cube_draw_in_scene(cube, NULL);
	//}
	for (auto child : node->childs) {
		render_legacy(child);
	}
}

void OpSystem::updateRenderablesLegacy() {
	
	renderablesLegacy.clear();
	for (auto op : all) {
		if (op->isGLLegacy || op->isXmodel) {
			//log("Found expression: %s\n", op->name);
			renderablesLegacy.push_back( op );
		}
	}
	//cubes.sort(compare_op_position_cube);
	//int i = 0;
	//for (auto cube : cubes) {
	//	//cube->drawsort = i;
	//	i++;
	//}
}
void OpSystem::updateAStars() {
	
	astars.clear();
	for (auto op : all) {
		if (op->isAstar) {
			//log("Found expression: %s\n", op->name);
			astars.push_back( (OpAStar *)op );
		}
	}
	//astars.sort(compare_op_position_cube);
	//int i = 0;
	//for (auto cube : cubes) {
	//	//cube->drawsort = i;
	//	i++;
	//}
}