#include "../include_imgui.h"
#include "../include_gl.h"

//#include "imgui_impl_glfw.h"
#include <stdio.h>
//#include "libs\glfw\include\GLFW/glfw3.h"
#include <list>
#include "rd-rend2/matrix.h"
#include "../opsys/opsys_utils.h"

#include "../include_console.h"

//void DrawLine(float a_x, float a_y, float b_x, float b_y) {
void DrawLine(float a_x, float a_y, float b_x, float b_y) {
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	ImVec2 winpos = ImGui::GetWindowPos();
	ImVec2 a = ImVec2(a_x, a_y);
	ImVec2 b = ImVec2(b_x, b_y);
	a += winpos;
	b += winpos;
	float thickness = 1.0f;
	a -= window->Scroll;
	b -= window->Scroll;
	window->DrawList->AddLine(a, b, 0xffffffff, thickness);
}
void DrawRect(float a_x, float a_y, float b_x, float b_y) {
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	ImVec2 winpos = ImGui::GetWindowPos();
	ImVec2 a = ImVec2(a_x, a_y);
	ImVec2 b = ImVec2(b_x, b_y);
	// lines are absolute and dont care about window pos, this makes it relative to window
	a += winpos;
	b += winpos;
	// this mind boggling shit is needed to take scroll into account
	a -= window->Scroll;
	b -= window->Scroll;
	// and draw the shitty rect
	float thickness = 1.0f;
	window->DrawList->AddRect(a, b, 0xffffffff, thickness);
}

#include "op_all.h"
#include "op_prefab.h"
#include "op_prefab_input.h"
#include "op_prefab_output.h"
Op *dragged_op = NULL;


// new link system
LinkOutput *link_from;
Link *link_to;

std::list<linkline_t> linklines;

//void LinkOutput::setMatrix(glm::mat4x4 matrix) {
void LinkOutput::setMatrix(float *matrix) {
	for (auto link_end : *inputlinks) {
		// link_end->matrix = matrix;
		memcpy((void *) link_end->matrix, (void *) matrix, 16);
		link_end->changed = 1;
	}
}

void Op::Init() {
	pos = ImVec2(100.0f, 100.0f);
	size.x = 40.0f;
	size.y = 40.0f;
	strcpy(name, GetClassname());
	selected = 0;
	is_permanent = 0;
	type = OpType::OP_TYPE_RECEIVER;
	char *names[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p"};
	color = 0xffffFFFF;
	system = NULL; // system the op belongs to, not the OpPrefab->subsys
	isPrefab = 0;
	// init the default input links
	for (int i=0; i<16; i++) {
		Link *in = default_link_inputs + i;
		// set default names
		//strcpy(in->name, names[i]);
		// set owner to this op
		in->owner = this;
		// kinda force update, for ops who check: if ( ! did_inputs_change() ) return;
		in->changed = 1;
		in->local_id = i; // the load/save system depends on this
		in->cached_backlinks = new std::list<LinkOutput *>();
	}
	// init the default output links
	for (int i=0; i<16; i++) {
		LinkOutput *lo = default_link_outputs + i;
		strcpy(lo->name, names[i]);
		lo->owner = this;
		lo->inputlinks = new std::list<Link*>();
		lo->local_id = i; // need it for prefab remapping
	}

	//log("Constructor called for %s", name);
}

void Op::DrawInScene() {
	// Do in Init(): shallDrawInScene = 1;
	// collected in OpSystem::renderables
	// inherited classes may draw/render something
}

void Op::InitLink(int id, char *name, int type /* maybe ... as default value */) {
	Link *current = default_link_inputs + id;
	strcpy(current->name, name);
	current->type = type;

	switch (type) {
		case OP_TYPE_MATRIX: mat_identity(current->matrix); break;
	}
	//if (strcmp(firstword,   "int") == 0) *ptr = (void *)&current->val_i;
	//if (strcmp(firstword, "float") == 0) *ptr = (void *)&current->val_f;
}
void Op::InitLinkOutput(int id, char *name, int type) {
	LinkOutput *current = default_link_outputs + id;
	strcpy(current->name, name);
	current->type = type;
}

int Op::DidInputsChange() {
	int changed = 0;
	//changed += changed;
	for (int i=0; i<number_of_inputs; i++)
		changed += default_link_inputs[i].changed;
	return changed;
}
void Op::SetInputsUnchanged() {
	for (int i=0; i<number_of_inputs; i++)
		default_link_inputs[i].changed = 0;
}

// Op::PropagateData is called in Op::Request()

#include "rd-rend2/compose_images.h"

void Op::PropagateData() {
	for (int i=0; i<number_of_outputs; i++) {
		LinkOutput *lo = default_link_outputs + i;

		// man, this is so annoying, always gotta do this for everything... and kinda annoying when changing it via buffer from js
		// makes it too complex and i want it easy... maybe enable later again, when performance becomes an issue
		// probably it would also work to make all these values an UNION, so the struct is pretty small
		// or even just one heapptr and javascript handles all values?
		//if ( ! lo->changed)
		//	continue;

		for (auto li : *lo->inputlinks) {
			switch (lo->type) {
				case OP_TYPE_FLOAT:
					if (li->val_f != lo->val_f) {
						li->val_f = lo->val_f;
						li->val_i = (int)lo->val_f; // so i can use float sliders as int/handle lol

						li->changed++;
					}
					continue;
				case OP_TYPE_IMAGE:
					// even tho the image id is the same, it might have been changed, so gotta check hasImageChanged(...)
					if (li->val_i != lo->val_i || hasImageChanged(lo->val_i)) {
						li->val_i = lo->val_i;
						li->changed++;
					}
					continue;
			
			}
			// probably its better at some point to copy the whole class at once lol
			//li->val_f = lo->val_f;
			li->val_i = lo->val_i;
			
			li->opengl_id = lo->opengl_id;
			matcpy(li->matrix, lo->matrix);
			memcpy(li->vector2, lo->vector2, 2 * sizeof(float));
			memcpy(li->vector3, lo->vector3, 3 * sizeof(float));
			memcpy(li->vector4, lo->vector4, 4 * sizeof(float));
			
			li->customclass = lo->customclass;
			li->quat = lo->quat;

			// if we update a link, the op can check forcereload to reevaluate his outputs
			li->owner->forcereload++;
			li->changed++;
		}
	}
}


bool Op::IsSelectedByPoint(ImVec2 point) {
	float left   = pos.x;
	float right  = pos.x + size.x;
	float top    = pos.y;
	float bottom = pos.y + size.y;
	int a = between(left, point.x, right);
	int b = between( top, point.y, bottom);
	if (a && b)
		return true;
	return false;
}
int Op::IsSelectedByRect(ImVec2 rect_from, ImVec2 rect_to) {
	float box_left   = rect_from.x;
	float box_right  = rect_to.x;
	float box_top    = rect_from.y;
	float box_bottom = rect_to.y;
	float left   = pos.x;
	float right  = pos.x + size.x;
	float top    = pos.y;
	float bottom = pos.y + size.y;
	int a = between(box_left,  left, box_right );
	int b = between(box_left, right, box_right );
	int c = between(box_top,    top, box_bottom);
	int d = between(box_top, bottom, box_bottom);
	// did the op cage the selectbox instead? aka being in middle of it
	int e = between(left, box_left  , right);
	int f = between(left, box_right , right);
	int g = between( top, box_top   , bottom);
	int h = between( top, box_bottom, bottom);
	// cornered a vertical and a horizontal line?
	if (a+b && c+d) {
		//op->color = rand32();
		return 1;
	}
	if (e && f && (c || d)) {
		return 1;
	}
	if (g && h && (a || b)) {
		return 1;
	}
	return 0;
}

void Op::Request() {
	// update childs in correct order
	// when we clearscene(), always update these references, otherwise crash

	if ( ! enabled)
		return;

	for (auto tmp : update_ops_this_order) {
		//if (tmp->forcereload)
		{
			tmp->Update();
			// we only copy over the values if there was actually a change
			//if (tmp->forcereload)
				tmp->PropagateData();
			tmp->forcereload = 0;
		}
	}
	// now our op has it's inputs set, so update ourselves now
	Update();
	forcereload = 0;

}

// every op can implement on_link_update
// tho we dont call it directly
// the OpSystem will collect the op_changed calls
// and when every sub-op was updated, we are going to dispatch the on_link_updates
// otherwise e.g. "Prog" has "Vert" and "Frag" as inputs
// if Vert calls op_changed(), Prog would try to rebuild the shader
// but Frag wasn't even evaluated yet
void Op::Changed   () {
	system->changed_ops.push_back( this );
}

void Op::PreRender() {
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	ImVec2 winpos = ImGui::GetWindowPos() - window->Scroll;
	ImRect op_item = ImRect(winpos + pos, winpos + pos + size);
	ImGuiContext& g = *GImGui;
	unsigned int color2 = selected ? 0xff00ff00 : color;


	// format: 0xALPHA,B,G,R
	if (!enabled)
		color2 = 0xff0000FF; // not enabled = red

	if (!enabled && selected)
		color2 = 0xff4499FF; // not enabled and selected = orange
	
	// we draw the border 1 pixel outside, so the contents can use all space
	window->DrawList->AddRect(op_item.Min + ImVec2(-1,-1), op_item.Max + ImVec2(1,1), color2);
}



// post_render does the mouse movement interaction, otherwise the childrens items are "disabled", because this one would "eat" them
void Op::PostRender() {


	
	
	OpPrefab *prefab = NULL;
	if (isPrefab)
		prefab = (OpPrefab *)this;
	if ( ! prefab) {
		for (int i=0; i<number_of_inputs; i++) {
			Link *in = default_link_inputs + i;
			in->pos = pos + ImVec2(-20, (float)i * 20);
			ImGui::SetCursorPos(in->pos);
			ImGui::Button(in->name);
			if (ImGui::IsItemHoveredRect()) {
				link_to = in;
			}
		}

		for (int i=0; i<number_of_outputs; i++) {
			LinkOutput *lo = default_link_outputs + i;

			// print the output buttons
			lo->pos = pos + ImVec2(size.x, (float)i * 20);
			ImGui::SetCursorPos(lo->pos);
			ImGui::Button(lo->name);
			if (ImGui::IsItemClicked(0)) {
				link_from = lo;
			}
		}
	} else if (prefab->subsys) {

		

		int i=0;
		for (auto op : prefab->subsys->prefabinputs) {
			OpPrefabInput *prefabinput = (OpPrefabInput *)op;

			// This is the output of prefabinput
			LinkOutput *asd = prefabinput->default_link_outputs + 0;
			
			Link *prefablink = prefab->default_link_inputs + i;
			ImVec2 linkpos = prefab->pos + ImVec2(-20, i * 20);
			prefablink->pos = linkpos;
			ImGui::SetCursorPos(linkpos);

			if (asd->inputlinks->size() == 0) {
				ImGui::Button("no link");
			} else {
				Link *reallink = asd->inputlinks->front();
				ImGui::Button(reallink->name);
			}
			if (ImGui::IsItemHoveredRect()) {
				// we do not link to the real links
				// Instead prefab->update() will copy the needed input value into the subsystem values
				// so the systems do not mix and it feels way less awkward
				//link_to = reallink;
				link_to = prefablink;
			}
			i++;
		}

	
		i = 0;
		for (auto op : prefab->subsys->prefaboutputs) {
			OpPrefabOutput *prefaboutput = (OpPrefabOutput *)op;
			Link *polink = prefaboutput->default_link_inputs + 0;
			
			LinkOutput *prefablinkout = prefab->default_link_outputs + i;
			ImVec2 linkoutputpos = prefab->pos + ImVec2(prefab->size.x, 20 * i);
			prefablinkout->pos = linkoutputpos;
			ImGui::SetCursorPos(linkoutputpos);
			if (polink->cached_backlinks->size()) {
				LinkOutput *reallinkoutput = polink->cached_backlinks->front();
				ImGui::Button(reallinkoutput->name);
			} else {
				ImGui::Button("no link");
			}
			if (ImGui::IsItemClicked(0)) {
				//link_from = reallinkoutput;
				link_from = prefablinkout;
			}
			i++;
		}

	} else {
		// subsys is NULL, do nothing... prefab has no inputs/outputs
	}

	// Draw the output lines
	for (int i=0; i<number_of_outputs; i++) {
		LinkOutput *lo = default_link_outputs + i;
		for (auto link_end : *lo->inputlinks) {
			linkline_t ll;
			ll.from = lo;
			ll.to = link_end;
			linklines.push_back(ll);
		}
	}

	if (showtitle) {
		ImGui::SetCursorPos(pos + ImVec2(0,-20));
		ImGui::Text("%s", name);
	}

	//if ( ! ImGui::IsAnyItemHovered())
	{

		//g.ActiveId = (ImGuiID)this;


		ImGuiContext& g = *GImGui;
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		ImVec2 winpos = ImGui::GetWindowPos() - window->Scroll;
		ImRect op_item = ImRect(winpos + pos, winpos + pos + size);

		ImGuiID id = (int)this;
		ImGui::PushID(id);
		ImGui::ItemAdd(op_item, id);



		if (ImGui::IsMouseClicked(0))
			imgui_was_dragged = 0;
		if (ImGui::IsMouseDragging(0))
			imgui_was_dragged = 1;
		

		//ImGui::Text("g.IO.MouseDownDuration[0] = %.2f", g.IO.MouseDownDuration[0]);

		//if (ImGui::IsMouseReleased(0))
		//	imgui_log("released this=%d", this);
		//
		//if (g.IO.MouseDownDuration[0] >= 0.0f)
		//	imgui_log("g.IO.MouseDownDuration[0] >= 0.0f %.2f", g.IO.MouseDownDuration[0]);
		if (ImGui::IsItemHovered() && ImGui::IsMouseReleased(0) && g.IO.MouseDownDurationPrev[0] >= 0.0f && !imgui_was_dragged) {
			

			if (ImGui::GetIO().KeyCtrl) {
				// ctrl+mouse = add to selection
				selected = !selected;
			} else {
				// single mouse click = only select clicked one
				system->unselectAll();
				selected = 1;
			}
			//log("selected = !selected;");
		}

		if (ImGui::IsMouseReleased(0))
			imgui_was_dragged = 0;
		
		if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(0)) {
			dragged_op = this;
		}

		if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(1)) {
			system->contextMenuOp = this; // so we can show editor for this op in context menu
		}

		if (dragged_op == this) {
			ImGui::SetHoveredID(id);
			if (ImGui::IsMouseDragging(0)) {


				pos += ImGui::GetMouseDragDelta();
				//selected = 1;

				// if the op was selected, move the whole "selection group", otherwise just the unselected one
				if (selected) {

					for (auto i : system->all) {
						if (i->selected && i != this) // dont move twice
							i->pos += ImGui::GetMouseDragDelta();
					}
				}
				ImGui::ResetMouseDragDelta();
			}
		}

		if (ImGui::IsMouseReleased(0))
		{
			dragged_op = NULL;
		}

		ImGui::PopID();
	}
}

char *Op::TypeToString(OpType type) {
	char *ret = "fix op_type_to_string";
	switch (type) {
		case OpType::OP_TYPE_SENDER   : ret = "Sender"   ; break;
		case OpType::OP_TYPE_RECEIVER : ret = "Receiver" ; break;
		case OpType::OP_TYPE_REQUESTER: ret = "Requester"; break;
		case OpType::OP_TYPE_DELIVERER: ret = "Deliverer"; break;
		case OpType::OP_TYPE_META     : ret = "Meta"     ; break;
		case OpType::OP_TYPE_NONE     : ret = "None"     ; break;
	}
	return ret;
}

void Op::GenerateCallgraph(Op *op, std::list<Op *> *callgraph) {
	for (int i=0; i<op->number_of_inputs; i++) {
		Link *input = op->default_link_inputs + i;

		for (auto backlink : *input->cached_backlinks) {
			Op::GenerateCallgraph(backlink->owner, callgraph);
			callgraph->push_back(backlink->owner);
			//log("Owner of backlink: %s", backlink->owner->name);
		}
}
}

void generate_js(Op *op) {
	for (auto g : op->update_ops_this_order)
		imgui_log("call: %s", g->name);
}


bool BeginButtonDropDown(const char* label, ImVec2 buttonSize)
{
    ImGui::SameLine(0.f, 0.f);

    ImGuiWindow* window = ImGui::GetCurrentWindow();
    //ImGui::GetStateStorage &g = *GImGui;
    const ImGuiStyle& style = GImGui->Style;

    float x = ImGui::GetCursorPosX();
    float y = ImGui::GetCursorPosY();

    ImVec2 size(20, buttonSize.y);
    bool pressed = ImGui::Button("##", size);

    // Arrow
    ImVec2 center(window->Pos.x + x + 10, window->Pos.y + y + buttonSize.y / 2);
    float r = 8.f;
    center.y -= r * 0.25f;
    ImVec2 a = center + ImVec2(0, 1) * r;
    ImVec2 b = center + ImVec2(-0.866f, -0.5f) * r;
    ImVec2 c = center + ImVec2(0.866f, -0.5f) * r;

    window->DrawList->AddTriangleFilled(a, b, c, ImGui::GetColorU32(ImGuiCol_Text));

    // Popup

    ImVec2 popupPos;

    popupPos.x = window->Pos.x + x - buttonSize.x;
    popupPos.y = window->Pos.y + y + buttonSize.y;

    ImGui::SetNextWindowPos(popupPos);

    if (pressed)
    {
        ImGui::OpenPopup(label);
    }

    if (ImGui::BeginPopup(label))
    {
        ImGui::PushStyleColor(ImGuiCol_FrameBg, style.Colors[ImGuiCol_Button]);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, style.Colors[ImGuiCol_Button]);
        ImGui::PushStyleColor(ImGuiCol_ChildWindowBg, style.Colors[ImGuiCol_Button]);
        return true;
    }

    return false;
}

void EndButtonDropDown()
{
    ImGui::PopStyleColor(3);
    ImGui::EndPopup();
}


typedef struct openglmodes {
	char *str;
	int val;
} openglmodes_t;

openglmodes_t glmodes[] = {
	{"GL_POINTS"                           , GL_POINTS						},
	{"GL_LINES"                            , GL_LINES						},
	{"GL_LINE_LOOP"                        , GL_LINE_LOOP					},
	{"GL_LINE_STRIP"                       , GL_LINE_STRIP					},
	{"GL_TRIANGLES"                        , GL_TRIANGLES					},
	{"GL_TRIANGLE_STRIP"                   , GL_TRIANGLE_STRIP				},
	{"GL_TRIANGLE_FAN"                     , GL_TRIANGLE_FAN				},
	//{"GL_LINES_ADJACENCY"                  , GL_LINES_ADJACENCY				},
	//{"GL_LINE_STRIP_ADJACENCY"             , GL_LINE_STRIP_ADJACENCY		},
	//{"GL_TRIANGLES_ADJACENCY"              , GL_TRIANGLES_ADJACENCY			},
	//{"GL_TRIANGLE_STRIP_ADJACENCY"         , GL_TRIANGLE_STRIP_ADJACENCY	},
	//{"GL_PATCHES"                          , GL_PATCHES						},
	{NULL, NULL}
};

char *glmodetostr(int mode) {
	openglmodes_t *cur = glmodes;
	while (cur->str) {
		if (cur->val == mode) {
			return cur->str;
		}
		cur++;
	}
	return "no glmode found";
}

#include "../op_types/op_type_image.h"

void imgui(LinkOutput *ol) {
	// only increase il->changed, do not set to 1
	// otherwise previous changed flags will be overwritten (this "bug" made me rewrite this system in C, because I thought it's a initializer bug in C++ lol)
	switch ( ol->type ) {
		case OP_TYPE_FLOAT:
			ImGui::PushID(ol);
			ol->changed += ImGui::DragFloat(ol->name, &ol->val_f);
			ImGui::PopID();
			break;
		case OP_TYPE_INT:
			ImGui::PushID(ol);
			ol->changed += ImGui::DragInt(ol->name, &ol->val_i);
			ImGui::PopID();
			break;
		case OP_TYPE_MATRIX:
			ImGui::PushID(ol);
			ImGui::PushItemWidth(50);
			ol->changed += ImGui::DragFloat("aa", ol->matrix +  0 + 0, 0.01); ImGui::SameLine(0, 5);
			ol->changed += ImGui::DragFloat("ab", ol->matrix +  4 + 0, 0.01); ImGui::SameLine(0, 5);
			ol->changed += ImGui::DragFloat("ac", ol->matrix +  8 + 0, 0.01); ImGui::SameLine(0, 5);
			ol->changed += ImGui::DragFloat("ad", ol->matrix + 12 + 0, 0.01);
			ol->changed += ImGui::DragFloat("ba", ol->matrix +  0 + 1, 0.01); ImGui::SameLine(0, 5);
			ol->changed += ImGui::DragFloat("bb", ol->matrix +  4 + 1, 0.01); ImGui::SameLine(0, 5);
			ol->changed += ImGui::DragFloat("bc", ol->matrix +  8 + 1, 0.01); ImGui::SameLine(0, 5);
			ol->changed += ImGui::DragFloat("bd", ol->matrix + 12 + 1, 0.01);
			ol->changed += ImGui::DragFloat("ca", ol->matrix +  0 + 2, 0.01); ImGui::SameLine(0, 5);
			ol->changed += ImGui::DragFloat("cb", ol->matrix +  4 + 2, 0.01); ImGui::SameLine(0, 5);
			ol->changed += ImGui::DragFloat("cc", ol->matrix +  8 + 2, 0.01); ImGui::SameLine(0, 5);
			ol->changed += ImGui::DragFloat("cd", ol->matrix + 12 + 2, 0.01);
			ol->changed += ImGui::DragFloat("da", ol->matrix +  0 + 3, 0.01); ImGui::SameLine(0, 5);
			ol->changed += ImGui::DragFloat("db", ol->matrix +  4 + 3, 0.01); ImGui::SameLine(0, 5);
			ol->changed += ImGui::DragFloat("dc", ol->matrix +  8 + 3, 0.01); ImGui::SameLine(0, 5);
			ol->changed += ImGui::DragFloat("dd", ol->matrix + 12 + 3, 0.01);
			ImGui::PopItemWidth();
			ImGui::PopID();
			break;
		case OP_TYPE_VERTEXSHADER:
		case OP_TYPE_FRAGMENTSHADER:
		case OP_TYPE_PROGRAM:
		case OP_TYPE_GLBUFFER:
		case OP_TYPE_GLATTRIB:
		case OP_TYPE_GLUNIFORM:
			ImGui::PushID(ol);
			ol->changed += ImGui::DragInt(ol->name, (int *)&ol->opengl_id);
			ImGui::PopID();
			break;
		case OP_TYPE_GLDRAWMODE: {
			ImGui::PushID(ol);
			ol->changed += ImGui::DragFloat(ol->name,&ol->val_f);

			ImGui::Text("Mode: %s", glmodetostr((int)ol->val_f));

			// fuckin shit doesnt work
			//ImVec2 size(200, 20);
			////ImGui::Button(glmodetostr(il->val_i), size);
			//ImGui::Button("muh", size);
			//if (BeginButtonDropDown("##sprtdd", size)) {
			//	openglmodes_t *cur = glmodes;
			//	while (cur->str) {
			//		ImGui::PushID(cur);
			//		if (ImGui::Button(cur->str, size)) {
			//			imgui_log("test1 %d\n", cur->val);
			//		}
			//		ImGui::PopID();
			//		cur++;
			//	}
			//	EndButtonDropDown();
			//}

			ImGui::PopID();
			break;
		}

		
		case OP_TYPE_IMAGE: {
			
			op_type_image_imgui(ol);
		}

		default:
			ImGui::PushID(ol);
			ImGui::Text("op_render_editor: input.type: %d", ol->type);
			//ImGui::DragFloat(il->name, &il->val_f);
			ImGui::PopID();
				
	}	// end switch

	if (ol->changed) {
		ol->owner->forcereload++;
	}
}



void imgui(Link *il) {
	// only increase il->changed, do not set to 1
	// otherwise previous changed flags will be overwritten (this "bug" made me rewrite this system in C, because I thought it's a initializer bug in C++ lol)
	switch ( il->type ) {
		case OP_TYPE_FLOAT:
			ImGui::PushID(il);
			il->changed += ImGui::DragFloat(il->name, &il->val_f);
			ImGui::PopID();
			break;
		case OP_TYPE_INT:
			ImGui::PushID(il);
			il->changed += ImGui::DragInt(il->name, &il->val_i);
			ImGui::PopID();
			break;
		case OP_TYPE_MATRIX:
			ImGui::PushID(il);				
			ImGui::PushItemWidth(50);
			il->changed += ImGui::DragFloat("aa", il->matrix +  0 + 0, 0.01); ImGui::SameLine(0, 5);
			il->changed += ImGui::DragFloat("ab", il->matrix +  4 + 0, 0.01); ImGui::SameLine(0, 5);
			il->changed += ImGui::DragFloat("ac", il->matrix +  8 + 0, 0.01); ImGui::SameLine(0, 5);
			il->changed += ImGui::DragFloat("ad", il->matrix + 12 + 0, 0.01);
			il->changed += ImGui::DragFloat("ba", il->matrix +  0 + 1, 0.01); ImGui::SameLine(0, 5);
			il->changed += ImGui::DragFloat("bb", il->matrix +  4 + 1, 0.01); ImGui::SameLine(0, 5);
			il->changed += ImGui::DragFloat("bc", il->matrix +  8 + 1, 0.01); ImGui::SameLine(0, 5);
			il->changed += ImGui::DragFloat("bd", il->matrix + 12 + 1, 0.01);
			il->changed += ImGui::DragFloat("ca", il->matrix +  0 + 2, 0.01); ImGui::SameLine(0, 5);
			il->changed += ImGui::DragFloat("cb", il->matrix +  4 + 2, 0.01); ImGui::SameLine(0, 5);
			il->changed += ImGui::DragFloat("cc", il->matrix +  8 + 2, 0.01); ImGui::SameLine(0, 5);
			il->changed += ImGui::DragFloat("cd", il->matrix + 12 + 2, 0.01);
			il->changed += ImGui::DragFloat("da", il->matrix +  0 + 3, 0.01); ImGui::SameLine(0, 5);
			il->changed += ImGui::DragFloat("db", il->matrix +  4 + 3, 0.01); ImGui::SameLine(0, 5);
			il->changed += ImGui::DragFloat("dc", il->matrix +  8 + 3, 0.01); ImGui::SameLine(0, 5);
			il->changed += ImGui::DragFloat("dd", il->matrix + 12 + 3, 0.01);
			ImGui::PopItemWidth();
			ImGui::PopID();
			break;
		case OP_TYPE_VERTEXSHADER:
		case OP_TYPE_FRAGMENTSHADER:
		case OP_TYPE_PROGRAM:
		case OP_TYPE_GLBUFFER:
		case OP_TYPE_GLATTRIB:
		case OP_TYPE_GLUNIFORM:
			ImGui::PushID(il);
			il->changed += ImGui::DragInt(il->name, (int *)&il->opengl_id);
			ImGui::PopID();
			break;
		case OP_TYPE_GLDRAWMODE: {
			ImGui::PushID(il);
			il->changed += ImGui::DragFloat(il->name,&il->val_f);

			ImGui::Text("Mode: %s", glmodetostr((int)il->val_f));

			// fuckin shit doesnt work
			//ImVec2 size(200, 20);
			////ImGui::Button(glmodetostr(il->val_i), size);
			//ImGui::Button("muh", size);
			//if (BeginButtonDropDown("##sprtdd", size)) {
			//	openglmodes_t *cur = glmodes;
			//	while (cur->str) {
			//		ImGui::PushID(cur);
			//		if (ImGui::Button(cur->str, size)) {
			//			imgui_log("test1 %d\n", cur->val);
			//		}
			//		ImGui::PopID();
			//		cur++;
			//	}
			//	EndButtonDropDown();
			//}

			ImGui::PopID();
			break;
		}

		default:
			ImGui::PushID(il);
			ImGui::Text("op_render_editor: type: %d", il->type);
			//ImGui::DragFloat(il->name, &il->val_f);
			ImGui::PopID();
				
	}	// end switch

	if (il->changed) {
		il->owner->forcereload++;
	}
}


void Op::RenderEditor() {
	if (ImGui::BeginMenu("debug")) {

		bool tmp = enabled;
		ImGui::Checkbox("Enabled", &tmp);
		enabled = tmp;

		ImGui::InputText("Name", name, sizeof name);
		ImGui::Text("Class %s", GetClassname());
		ImGui::Text("Type %s", Op::TypeToString(type));
		ImGui::Text("Connections: In=%d Out=%d", cache_ingoing_connections, cache_outgoing_connections);
		if (ImGui::Button("Update")) {
			Update();
		}


		if (ImGui::BeginMenu("callgraph")) {
			std::list<Op *> *callgraph = new std::list<Op *>();
			Op::GenerateCallgraph(this, callgraph);
			int j = 0;
			for (auto i : *callgraph) {
				ImGui::Text("callgraph[%d]: %s\n", j, i->name);
				j++;
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("backlinks")) {
			for (int i=0; i<number_of_inputs; i++) {
				Link *input = default_link_inputs + i;
				int j=0;
				for (auto backlink : *input->cached_backlinks) {
					ImGui::Text("input[%d].backlink[%d]: %s\n", i, j, backlink->owner->name);
					j++;
				}
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenu();
	}
	ImGui::Separator();
	ImGui::Text("%s %s", GetClassname(), name);

	if (ImGui::BeginMenu("settings")) {
		ImGui::DragFloat2("size", &size.x, 1.0f, 0.0f, 0.0f, "%.3f");
		ImGui::DragFloat2("pos", &pos.x, 1.0f, 0.0f, 0.0f, "%.3f");
		ImGui::EndMenu();
	}

	if (ImGui::BeginMenu("inputs")) {
		for (int i=0; i<number_of_inputs; i++) {
			Link *il = default_link_inputs + i;
			char menuName[256];
			snprintf(menuName, sizeof(menuName), "in[%d] %s", i, il->name);
			if (ImGui::BeginMenu(menuName)) {
				imgui(il);
				ImGui::EndMenu();
			}
		} // end for
		ImGui::EndMenu();
	}


		//if ()
		//{
		//ImGui::MenuItem("Metrics", NULL, &show_app_main_menu_bar);
		//ImGui::MenuItem("Style Editor", NULL, &show_app_main_menu_bar);
		//ImGui::MenuItem("About ImGui", NULL, &show_app_main_menu_bar);
		//
		//}

	if (ImGui::BeginMenu("outputs")) {

		for (int i=0; i<number_of_outputs; i++) {
			LinkOutput *ol = default_link_outputs + i;
			char menuName[256];
			snprintf(menuName, sizeof(menuName), "out[%d] %s", i, ol->name);
			if (ImGui::BeginMenu(menuName)) {
				imgui(ol);
				ImGui::EndMenu();
			}
		} // end for

		ImGui::EndMenu();
	}

	//if (op_did_inputs_change(op)) {
	//	forcereload++;
	//	op_set_inputs_unchanged(op);
	//}
	
}


#include <typeinfo>
const char *Op::GetClassname() {
	http://stackoverflow.com/questions/3649278/how-can-i-get-the-class-name-from-a-c-object
	char *classname = (char *)typeid(*this).name();
	// classname is something like "class OpNode"
	// So remove the "class " part:
	classname += 6;
	return classname;
}




LinkOutput *Op::GetOutput(int id) {
	if ( ! between_faster_version(0, id, 16) )
		return NULL;
	return &default_link_outputs[id];
}
Link *Op::GetInput(int id) {
	if ( ! between_faster_version(0, id, 16) )
		return NULL;
	return &default_link_inputs[id];
}

std::string Op::DumpToString() {
	char buf[4096];
	snprintf(buf, sizeof buf, "%s enabled %d pos %.0f %.0f size %.0f %.0f selected %d perm %d name %s ",
		GetClassname(),
		!!enabled,
		pos.x,
		pos.y,
		size.x,
		size.y,
		selected,
		is_permanent,
		name
	);
	std::string defaultpart(buf);
	std::string extra = WriteExtraData(); // Add the custom op data aswell
	return defaultpart + extra;
}


int DoesVectorContainsOp(std::vector<Op *> *searchIn, Op *toSearch) {
	for (auto op : *searchIn)
		if (op == toSearch)
			return 1;
	return 0;
}

std::string Op::DumpLinksToString(std::vector<Op *> *selectedOps) {
	std::string tmp("");
	char buf[1024];
	for (int i=0; i<number_of_outputs; i++) {
		LinkOutput *lo = default_link_outputs + i;
		for (auto link : *lo->inputlinks) {
			
			// Only dump the links which are inside the selectedOps, so copy/pasting in same system doesn't automatically adds the links again
			if ( ! DoesVectorContainsOp(selectedOps, link->owner))
				continue;

			snprintf(buf, sizeof buf, "Link %s [%d] to %s [%d]\n",
					this->name,
					i,
					link->owner->name,
					link->local_id
			);
			tmp += buf;
		}
	}
	return tmp;
}

std::string Op::DumpLinksToString() {
	std::string tmp("");
	char buf[1024];
	for (int i=0; i<number_of_outputs; i++) {
		LinkOutput *lo = default_link_outputs + i;
		for (auto link : *lo->inputlinks) {
			
			snprintf(buf, sizeof buf, "Link %s [%d] to %s [%d]\n",
					this->name,
					i,
					link->owner->name,
					link->local_id
			);
			tmp += buf;
		}
	}
	return tmp;
}

void Op::ResizeMinimal() {
	this->size.x = (float)strlen(this->name) * 7.0f;
	if (size.x < 60.0f)
		size.x = 60.0f;
	int max = number_of_inputs;
	if (number_of_outputs > max)
		max = number_of_outputs;
	size.y = (float)max * 20.0f;
}

void Op::DeleteAllLinks() {
	// delete out links
	default_link_outputs->inputlinks->clear();

	// delete all in links
	for (int i=0; i<number_of_inputs; i++) {
		Link *in = default_link_inputs + i;

		for (auto output : *in->cached_backlinks) {
			output->inputlinks->remove(in);
		}
	}
}

void Op::Destroy() {
	delete this;
}

void Op::Render() {}
void Op::Update() {}

std::string Op::WriteExtraData() { return ""; }
void Op::ReadExtraData(char *line) {}

void Op::OnLinkConnect(int id) {}
void Op::OnLinkDisconnect(int id) {}
void Op::OnLinkUpdate(int id) {}
void Op::OnOpSystemRebuild() {}
void Op::UpdateDuktapeHeappointers() {}