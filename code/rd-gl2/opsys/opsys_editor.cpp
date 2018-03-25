//#include <include_duktape.h>
#include "../include_console.h"
#include "opsys_utils.h"
#include "../ops/op_prefab.h"
#include <list>
#include "../imgui/imgui_dock.h"
#include "opsys_hierarchy.h"
#include "opsys_explorer.h"
#include "../ops/op_file.h"


//#include <globals.h>

// bla headers..

#include <string>
#include "opsys_editor.h"
#include "opsys.h"
#include "opsys_utils.h"

const char *get_filename_ext(const char *filename);
#include "../ops/op_file.h"
#include "../imgui/include_imgui.h"

OpSystemEditor::OpSystemEditor(OpSystem *opsys_) {
	opsys = opsys_;
}

void OpSystemEditor::SetupSomeValues() {
		
	ImGuiWindow* window = ImGui::GetCurrentWindowRead();


	winpos = ImGui::GetWindowPos(); // e.g. 200,200
	absolutemousepos = ImGui::GetMousePos(); // when mouse is at 10,10 in window, this will be 210,210
	relativemousepos = absolutemousepos - winpos; // this will be at 10,10 now, window coordinates
	//mousepos = relativemousepos + window->Scroll; // 
	mousepos = relativemousepos + userscrollposition;
		

	//ImGui::SetCursorPos(ImVec2(100,100));
	//ImGui::Text("ImGui::GetWindowPos(): %.2f %.2f", winpos.x, winpos.y);
	//ImGui::Text("ImGui::GetMousePos(): %.2f %.2f", absolutemousepos.x, absolutemousepos.y);
	//ImGui::Text("relativemousepos: %.2f %.2f", relativemousepos.x, relativemousepos.y);
	//ImGui::Text("mousepos: %.2f %.2f", mousepos.x, mousepos.y);

	//ImGui::SetCursorPos(ImVec2(0, 100));
	//ImGui::DragFloat("userscrollposition.x", &userscrollposition.x);
	//ImGui::SetCursorPos(ImVec2(0, 120));
	//ImGui::DragFloat("userscrollposition.y", &userscrollposition.y);
	//if (ImGui::Button("scroll right 10px") ) {
	//	GImGui->CurrentWindow->Scroll.y += 10;
	//}

}

void OpSystemEditor::DoBreadcrumbNavigation() {
	ImGui::Button("Parent: ");
	if (opsys->prefab) {
		ImGui::SameLine(0, 5);
		if (ImGui::Button(opsys->prefab->system->name))
			OpSystem::SetCurrent(opsys->prefab->system);
	}	
}



void OpSystemEditor::DoMouseScissoring() {
	if (ImGui::IsMouseClicked(0)) {
		scissor_from = mousepos;
		scissor_to = mousepos; // reset end pos, otherwise it might fuck up shit
		scissor_active = 1;
	}
	if (ImGui::IsMouseReleased(0) && ImGui::IsWindowFocused()) {
		if (scissor_from == mousepos) {
			opsys->unselectAll();
			//ops_tab = 0;
		}
	}
	if (ImGui::IsMouseDragging(0) && scissor_active) {
		scissor_to = mousepos;
		if (scissor_active) {
			DrawLine(scissor_from.x, scissor_from.y, scissor_to.x, scissor_to.y);
		}
	}
	if (ImGui::IsMouseReleased(0) && scissor_active) {
		int hits = 0;
		for (auto ll : linklines) {
			ImVec2 intersection;
			int ret = get_line_intersection(
			
				ll.from->pos.x,
				ll.from->pos.y + 10.0f,
				ll.to->pos.x,
				ll.to->pos.y + 10.0f,
				scissor_from.x,
				scissor_from.y,
				scissor_to.x,
				scissor_to.y,
				&intersection.x,
				&intersection.y
			);
			if (ret) {
				hits++;
				ll.from->inputlinks->remove(ll.to);
				ll.to->owner->OnLinkDisconnect(ll.to->local_id);
				// currently this only cleans the shader opengl_id, so we can invalidate the program
				//ll->to->clean();
			}
		}
		scissor_active = 0;
		if (hits) {
			imgui_log("Deleted %d links, regenerate call graphs\n", hits);
			opsys->regenerateCallGraphs();
		}
	}
}



void OpSystemEditor::DoMouseRectSelection() {
	// this is middle mouse button, right mouse is already context menu
	if (ImGui::IsMouseClicked(2)) {
		rect_from = mousepos;
		rect_to = mousepos; // reset end pos, otherwise it might fuck up shit
		rect_active = 1;
	}
	if (ImGui::IsMouseDragging(2) && rect_active) {
		rect_to = mousepos;
		DrawRect(rect_from.x, rect_from.y, rect_to.x, rect_to.y);
		for (auto op : opsys->all) {
			//op->color = 0xffffffff;
			op->selected = 0;
		}
		for (auto op : opsys->all) {
			if (op->IsSelectedByRect(rect_from, rect_to))
				op->selected = 1;
		}
	}	
}

void OpSystemEditor::DrawLinkLines() {
	for (auto ll : linklines) {
		if (ll.to) {
			if (ll.from->owner->system != ll.to->owner->system) {
				// this case is true when output is connected to op in a prefab subsys
				ImVec2 projected_pos = ll.from->owner->system->prefab->default_link_outputs[0].pos;
				DrawLine(projected_pos.x, projected_pos.y + 10.0f, ll.to->pos.x, ll.to->pos.y + 10.0f);
			} else {
				DrawLine(ll.from->pos.x, ll.from->pos.y + 10.0f, ll.to->pos.x, ll.to->pos.y + 10.0f);
			}
		}
	}
}


void OpSystemEditor::HandleLinkCreating() {
	if (link_from && link_to && ImGui::IsMouseReleased(0)) {
		imgui_log("connect link_from->owner=%s (isprefab=%d) link_to->owner=%s (isprefab=%d)\n",
			link_from->owner->name,
			link_from->owner->isPrefab,
			link_to->owner->name,
			link_to->owner->isPrefab
		);
		//if (link_from->owner->isprefab) {
		//	OpPrefab *prefab = (OpPrefab *) link_from->owner;
		//	imgui_log("prefab[%d] maps to %s[%d]\n",
		//		link_from->local_id, 
		//		prefab->internal_outputs[0]->owner->name, 0
		//	);
		//
		//	// when connecting a prefab->linkoutput to op->link, we actually do two links
		//	// 1) The normal prefab link, but this one is just for the drawline and load/save
		//	// 2) the internal one: from the subsys to the upper system, which actually does the work
		//
		//	// make the internal link:
		//	prefab->internal_outputs[0]->inputlinks->push_back( link_to );
		//}

		link_from->inputlinks->push_back(link_to);
		link_to->changed += 1; // make op_did_inputs_change work on linking
		
		//link_to->owner->forcereload += 1;
		opsys->regenerateCallGraphs();
		link_from->owner->PropagateData(); // first make sure that the receiving op knows about the new input data
		link_to->owner->OnLinkConnect(link_to->local_id); // then in OnLinkConnect the op can act upon it

		link_from = NULL;
	}
	// link_to is set based on if(ishovered()), so we gotta reset it all time so hover resets it all time
	link_to = NULL;	
}



std::string *dragdrop_file = NULL;

void OpSystemEditor::DragAndDrop() {
	// DRAG DROP support for Explorer
	extern std::string *dragdrop_file;
	if (ImGui::IsMouseHoveringWindow() && ImGui::IsMouseReleased(0) && dragdrop_file) {
		
		imgui_log("OPS pphysfs has dragdrop_file: %s\n", dragdrop_file->c_str());

		char *filename = (char *) dragdrop_file->c_str();
		const char *extension = get_filename_ext(filename);
		if (strstr("xmodel", extension) != 0) {
			//log("read xmodel: %s\n", filename);
			//
			//char buf[256] = {0};
			//sprintf(buf, "filename %s", filename);
			//OpXModel *tmp = new OpXModel();
			//tmp->ReadExtraData(buf);
			//opsys->add((Op *)tmp);
			//opsys->regenerateCallGraphs();
			////auto xmodel = Format::CallOfDuty2::XModel::getByFilename(op->filename);
			////xmodel->load_xmodel((char *)op->filename);
		} else {

			OpFile *file = new OpFile();
			opsys->add((Op *)file);
			opsys->regenerateCallGraphs();
			file->pos = ImGui::GetMousePos() - ImGui::GetWindowPos();
		
			file->ReadExtraData((char *)(std::string("filename ") + *dragdrop_file).c_str());
			// op_file_ReadExtraData possible deletes OpFile *file, so do not touch it anymore here
		}
		dragdrop_file = NULL;
		delete dragdrop_file;
	}	
}

	
void OpSystemEditor::HandleMiddleMouseScroll() {
	if(ImGui::IsMouseDragging(2)) {
		userscrollposition -= ImGui::GetMouseDragDelta(2);
		//ImVec2 tmp = ImGui::GetMouseDragDelta(2);
		//log("%.2f %.2f\n", tmp.x, tmp.y);
		ImGui::ResetMouseDragDelta(2);
	}
	ImGuiWindow* window = ImGui::GetCurrentWindowRead();
}


int keyboard_ctrlc = 0;
int keyboard_ctrlv = 0;

#include <map>

// function is in opsystem.cpp... probably should make this a static OpSystem function
void op_create_link(Op *from, int output_id, Op *to, int input_id);

void OpSystemEditor::HandleCopyPaste() {
	ImGuiIO& io = ImGui::GetIO();
	//if (io.KeyCtrl && ImGui::IsKeyPressed('c'))
	
	//if (keyboard_ctrlc) {
	//	keyboard_ctrlc = 0;
	//	imgui_log("strg c pressed\n");
	//}
	//if (keyboard_ctrlv) {
	//	keyboard_ctrlv = 0;
	//	imgui_log("strg v pressed\n");
	//}
	
	if (ImGui::IsKeyPressed('C', false) && io.KeyCtrl) {
		std::vector<Op *> selectedOps;

		for (auto op: opsys->all) {
			if (op->selected)
				selectedOps.push_back(op);
		}

		if (selectedOps.size() == 0) {
			imgui_log("no operators selected to copy\n");
			return;
		}

		std::string buffer("");

		for (auto op: selectedOps) {
			//log("copy: %s data: %s\n", op->name, op->DumpToString().c_str());
			buffer += op->DumpToString() + "\n";
		}
		
		for (auto op: selectedOps) {
			//log("%s", op->DumpLinksToString().c_str());
			buffer += op->DumpLinksToString(&selectedOps);
		}
		imgui_log("Copied %d ops into clipboard (%d bytes)\n", selectedOps.size(), buffer.size());

		ImGui::SetClipboardText(buffer.c_str());
	}
	if (ImGui::IsKeyPressed('V', false) && io.KeyCtrl) {
		char *buffer = (char *)ImGui::GetClipboardText();

		std::list<std::string> lines;
		
		// basically: lines = explode(buffer, "\n");
		int n = strlen(buffer);
		char *from = buffer;
		for (int i=0; i<n; i++) {

			if (buffer[i] == '\n') {
				std::string line(from, buffer + i - 1);
				// don't add empty lines
				if (line.size())
					lines.push_back(line);
				// set position for next line after this \n
				from = buffer + i + 1;
				
			}
		}
		// the case when "buffer" didn't end with a \n, then we still got a string, which we have to add
		if (strlen(from)) {
			std::string tmp(from);
			//printf("from: \"%s\"\n", tmp.c_str());
			lines.push_back( tmp );
		}



		
		std::vector<Op *> loaded_ops;
		std::map<std::string, Op *> id2op;

		for (auto linecpp : lines) {
			char *line = (char *)linecpp.c_str();
			//log("Line: \"%s\"\n", line);

			
			Op *op = opsys->op_from_string(line, 1);
			if (op) {
				loaded_ops.push_back(op);
				id2op[std::string(op->name)] = op;
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
					continue;
				}
				Op *out = id2op[std::string(name_to)];
				if ( ! in) {
					imgui_log("Op named \"%s\" doesnt exist\n", name_to);
					continue;
				}


				op_create_link(in, output_id, out, input_id);
			}

		}

		if (loaded_ops.size() == 0) {
			imgui_log("i parsed the clipboard, but the content didn't generate any operators... length of clipboard: %d lines=%d\n", n, lines.size());
			return;
		}

		// now we got all Ops loaded, we need to find the most left/top x,y coordinate, so we can place them relative to the user mouse
		float most_left = loaded_ops[0]->pos.x;
		float most_top = loaded_ops[0]->pos.y;
		for (int i=1; i<loaded_ops.size(); i++) {
			Op *current = loaded_ops[i];
			if (current->pos.x < most_left)
				most_left = current->pos.x;
			if (current->pos.y < most_top)
				most_top = current->pos.y;
		}

		
		for (auto op : loaded_ops) {

			// now we can make all ops relative to the most_left/most_top
			op->pos.x -= most_left;
			op->pos.y -= most_top;

			// and make the op position relative to the user mouse position
			op->pos += mousepos;
		}


		// now add all ops into OpSystem
		for (auto op : loaded_ops) {
			// so this op will be initialized by the next OpSystem::Update()
			op->forcereload = 1;
			opsys->add(op);
		}
		imgui_log("Loaded %d ops into %s via clipboard\n", loaded_ops.size(), opsys->name);
		opsys->regenerateCallGraphs();
		//log("Insert Buffer: %s, lines=%d\n", buffer, lines.size());
	}


}

void OpSystemEditor::DoFrame() {

	// this stuff is always done, even when window isnt hovered... just draw everything
	linklines.clear(); // I generate linklines each frame, so clear them now from last frame
	ImGui::GetCurrentWindow()->Scroll = userscrollposition;
	SetupSomeValues();
	DoBreadcrumbNavigation();
	opsys->render();
	DrawLinkLines();

	// the interaction with the canvas is only handled when the mouse is hovering the window
	if (ImGui::IsWindowHovered()) {
		HandleMiddleMouseScroll();
		if ( ! ImGui::IsAnyItemHovered()) {
			DoMouseScissoring(); // this depends on linklines filled with all connections
			DoMouseRectSelection();
		}
		if (ImGui::IsMouseReleased(0)) {
			opsys->updateExecIDs();
			opsys->updatePrefabInputIDs();
			opsys->updatePrefabOutputIDs();
		}
		HandleLinkCreating();
		DragAndDrop();

		if (ImGui::IsKeyPressed('A')) {
			if (showAddOpsMenu) {
				// if the showAddOpsMenu was already shown, hide it now
				showAddOpsMenu = 0;
			} else {
				showAddOpsMenu = 1;
				ImGui::SetNextWindowPos(absolutemousepos);
				positionForNewOp = mousepos;
			}
		}


		HandleCopyPaste();

		
		// Only delete ops when no item is active, otherwise pressed "Delete" key to delete characters in a DragFloat would delete the op
		if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Delete), false) && ! ImGui::IsAnyItemActive()) {
			//log("delete pressed\n");
			opsys->deleteSelectedOps();
		}


		bool inContextMenu = ! ImGui::IsMouseHoveringWindow();
		bool freeToClick = ! ImGui::IsAnyItemHovered();
		//const bool leftMouseClicked = ImGui::IsMouseClicked(0);
		bool leftMouseClicked = ImGui::IsMouseReleased(0);



		if (!inContextMenu && freeToClick && leftMouseClicked && dragged_op == NULL) {

			// simply go over every op and see if we touch any
			
			//bool fail = false;
			//for (auto op : opsys->all) {
			//	if (op->IsSelectedByPoint(mousepos)) {
			//		fail = true;
			//		break;
			//	}
			//}
			//if (! fail)
				positionForNewOp = mousepos;
		}

	}


	DrawLine(positionForNewOp.x-10, positionForNewOp.y-10, positionForNewOp.x+10, positionForNewOp.y+10);
	DrawLine(positionForNewOp.x+10, positionForNewOp.y-10, positionForNewOp.x-10, positionForNewOp.y+10);

	ContextMenu();
}

void addOp(OpSystem *opsys, Op *createdOp) {
	createdOp->pos = opsys->editor->positionForNewOp; // set saved position to created op which was set when 'a' was pressed
	opsys->add( createdOp ); // add this lovely operator to current OpSystem
	opsys->regenerateCallGraphs(); // will make the added op a Requester type probably
	opsys->editor->showAddOpsMenu = 0; // kill window when op was created
	opsys->editor->positionForNewOp.y += createdOp->size.y + 30; // dont place next op on same pos
}

void imgui(OpSystem *opsys, oplist_t *oplist, char *name) {
	if (ImGui::BeginMenu(name)) {
		for (oplist_t *i=oplist; i->name; i++) {
			if (ImGui::Button(i->name)) {
				addOp(opsys, i->create_op());
			}
		}
		ImGui::EndMenu();
	}
}

void OpSystemEditor::ContextMenu() {
	if (ImGui::BeginPopupContextWindow(opsys->name, 1, false)) {
		//static ImVec4 color = ImColor(0.8f, 0.5f, 1.0f, 1.0f);
		//ImGui::ColorButton("color", color);
		//if (ImGui::Selectable("Set to zero")) {}
		//if (ImGui::Selectable("Set to PI")) {}
		//ImGui::DragFloat("positionForNewOp", &positionForNewOp.x);
		//ImGui::ColorEdit3("##edit", (float*)&color);

		if (ImGui::BeginMenu("opsys...")) {
			if (ImGui::BeginMenu("requesters")) {
				for (auto op_ : opsys->all) {
					int outgoing_links = 0;
					for (int i=0; i<op_->number_of_outputs; i++) {
						LinkOutput *output = op_->default_link_outputs + i;
						outgoing_links += output->inputlinks->size();
					}
					if (outgoing_links == 0)
						ImGui::Text("%s: outgoing links: %d", op_->name, outgoing_links);
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("all ops")) {
				for (auto op_ : opsys->all) {
					ImGui::Text("%s", op_->name);
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		ImGui::Separator();

		imgui(opsys, ops_stuff     , "new: stuff...");
		imgui(opsys, ops_meta      , "new: meta...");
		imgui(opsys, ops_javascript, "new: javascript...");
		imgui(opsys, ops_math      , "new: math...");
		imgui(opsys, ops_float     , "new: float...");
		imgui(opsys, ops_opengl    , "new: opengl...");
		imgui(opsys, ops_idtech3   , "new: idtech3...");
		
		ImGui::Separator();

		if (opsys->contextMenuOp) {
			opsys->contextMenuOp->RenderEditor();
		}

		ImGui::Separator();

		if (ImGui::Button("[close this menu]"))
			ImGui::CloseCurrentPopup();

		//js_call(ctx, "contextmenu", "");


		ImGui::EndPopup();
	}
}