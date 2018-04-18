//#include "craftstructs.h"

#include "../include_imgui.h"

//#include "imgui_impl_glfw.h"
#include <stdio.h>
//#include "libs\glfw\include\GLFW/glfw3.h"
#include <list>

#include "op.h"
#include "op_random_shit.h"



void OpRandomShit::Init() {

	Op::Init();
	strcpy( name, "OpRandomShit" );
	size = ImVec2(256, 256);
	pos = ImVec2(250, 250);
	
	number_of_inputs = 1;
	InitLink(0, "Mesh", OP_TYPE_MESH );
	number_of_outputs = 1;
	InitLinkOutput(0, "Mesh", OP_TYPE_MESH );

	type             = OpType::OP_TYPE_REQUESTER;
}

class FixedArea {
public:
	ImVec2 initoffset;
	ImVec2 pos;
	ImVec2 size;
	int cols;
	FixedArea(ImVec2 pos_, ImVec2 size_, int cols_) {
		pos = pos_;
		size = size_;
		cols = cols_;
		initoffset = ImGui::GetCursorPos();
	}

	// returns width and height of the element
	ImVec2 SetPos(int row, int col) {
		float x = (size.x / cols) * col;
		float y = row * 20;
		ImGui::SetCursorPos(initoffset + pos + ImVec2(x, y));
		return ImVec2(size.x / cols, 20);
	}
};

//extern Model *g;

void OpRandomShit::Render() {
	Op::PreRender();
#if 0
	ImGui::SetCursorPos(pos + ImVec2(5,5));
	ImGui::Text("g->chunk_count: %d", g->chunk_count);
	
	FixedArea fa(pos, size, 3);

	static int from = 0;
	static int amount = 20;
	
	ImGui::DragInt("from", &from);
	ImGui::DragInt("amount", &amount);

	int fromzero = 0;
	for (int i=from; i<from+amount; i++, fromzero++) {


		for (int j=0; j<3; j++) {

			ImGui::SetCursorPos(pos + ImVec2(5, (float)fromzero*20.0f));
			//ImGui::Text("%d, %d", i, j);
			int offset = i * 3 + j;
			
			ImGui::PushID(i);
			//ImGui::DragFloat("", address, 0.01f);

			Chunk *c = g->chunks + i;
			ImGui::Text("chunk i=%d faces=%d p=%d q=%d buffer=%d datasize=%d datacopy=%d", i, c->faces, c->p, c->q, c->buffer, c->datasize, c->datacopy);

			ImGui::PopID();
		}
	}
#endif



	Op::PostRender();
}

void OpRandomShit::Update() {
	auto *ol = default_link_outputs + 0;
	for (auto il : *ol->inputlinks) {
		//il->mesh = default_link_inputs[0].mesh;
		//if (type == OpType::OP_TYPE_SENDER)
		//	il->owner->update(il->owner);
	}

}

void OpRandomShit::RenderEditor() {
	Op::RenderEditor();
	//ImGui::Text("Mesh: %x", default_link_inputs[0].mesh);
	//ImGui::Text("textureid: %x", textureid);
}

std::string OpRandomShit::WriteExtraData() {
	//fprintf(f, "x %f y %f z %f n %f",
	//	x,
	//	y,
	//	z,
	//	n
	//);
	return std::string("");
}

void OpRandomShit::ReadExtraData(char *line) {
	//sscanf(line, "x %f y %f z %f n %f",
	//	&x,
	//	&y,
	//	&z,
	//	&n
	//);
}

OpRandomShit::OpRandomShit() {
	Init();
}