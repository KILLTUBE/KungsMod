//#include "craftstructs.h"
#include "../include_gl.h"
#include "../include_imgui.h"

//#include "imgui_impl_glfw.h"
#include <stdio.h>
//#include "libs\glfw\include\GLFW/glfw3.h"
#include <list>

#include "op.h"
#include "op_gl_attrib.h"

//float javascript_viewmatrix[16] = {0};
/*
buf = new Int32Array(16);
for (var i=0; i<16; i++)
buf[i] = i*i;
set_viewmatrix(buf)


memory_read_int(328846048 + 4*5)	

set_viewmatrix([1,2,3,4,5,6,7,8,9,10,11])

*/
// http://wiki.duktape.org/HowtoBuffers.html

//int duk_func_set_viewmatrix       (duk_context *ctx) {
//	unsigned int size;
//	struct duk_hbufferobject *buf;
//	buf = duk_to_buffer_kung(ctx, 0, &size, DUK_BUF_MODE_DONTCARE);



void OpGLAttrib::Init() {

	Op::Init();
	strcpy( name, "OpGLAttrib" );
	size = ImVec2(256, 256);
	pos = ImVec2(250, 250);
	
	number_of_inputs = 1;
	InitLink(0, "Prog", OP_TYPE_PROGRAM );
	number_of_outputs = 1;
	InitLinkOutput(0, "AttLoc", OP_TYPE_GLATTRIB );
	size = ImVec2(200, 40);
}

class FixedArea {
public:
	ImVec2 pos;
	ImVec2 size;
	int cols;
	FixedArea(ImVec2 pos_, ImVec2 size_, int cols_) {
		pos = pos_;
		size = size_;
		cols = cols_;
	}

	ImVec2 SetPos(int row, int col) {
		float x = (size.x / cols) * col;
		float y = row * 20;
		y += 20.0f; // first line is button
		ImGui::SetCursorPos(pos + ImVec2(x, y));
		return ImVec2(size.x / cols, 20);
	}
};

void OpGLAttrib::Render() {
	Op::PreRender();
	

	
	ImGui::SetCursorPos(pos);
	ImGui::PushItemWidth(size.x);
	ImGui::PushID(this);

	ImGui::Text("Loc: %d", default_link_outputs[0].opengl_id);
	ImGui::SetCursorPos(pos + ImVec2(0, 20));
	ImGui::InputText("attrib", attrib, sizeof attrib);

	ImGui::PopID();
	ImGui::PopItemWidth();

	Op::PostRender();
}

void OpGLAttrib::Update() {

	if (cache_ingoing_connections > 0) {
		default_link_outputs[0].opengl_id = qglGetAttribLocation(default_link_inputs[0].opengl_id, attrib);
		default_link_outputs[0].changed++;
	}
}

void OpGLAttrib::RenderEditor() {
	Op::RenderEditor();
	//Mesh *mesh = default_link_inputs[0].mesh;
	//ImGui::Text("Mesh: %x", default_link_inputs[0].mesh);


}

std::string OpGLAttrib::WriteExtraData() {
	char buf[1024];
	snprintf(buf, sizeof buf, "attrib %s",
		attrib
	);
	return std::string(buf);
}

void OpGLAttrib::ReadExtraData(char *line) {
	sscanf(line, "attrib %s",
		&attrib
	);
}

OpGLAttrib::OpGLAttrib() {
	Init();
}