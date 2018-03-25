//#include "craftstructs.h"
#include "../include_gl.h"
#include "../include_imgui.h"

//#include "imgui_impl_glfw.h"
#include <stdio.h>
//#include "libs\glfw\include\GLFW/glfw3.h"
#include <list>

#include "op.h"
#include "op_gl_buffer.h"

#include "../include_console.h"

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




void OpGLBuffer::MakeBuffer() {
	if (default_link_outputs[0].opengl_id)
		qglDeleteBuffers(1, &default_link_outputs[0].opengl_id);
	qglGenBuffers(1, &default_link_outputs[0].opengl_id);
	qglBindBuffer(GL_ARRAY_BUFFER, default_link_outputs[0].opengl_id);
	//float dadata[9];
	//memcpy(dadata, buffercontent.data(), 9  * 4);
	qglBufferData(GL_ARRAY_BUFFER, buffercontent.size() * 4, buffercontent.data(), GL_STATIC_DRAW);
	default_link_outputs[0].changed++;

	// wow, what the fuck, without this, it doesnt work... BUT WHYYYYYYYYYYYYYYYYY
	// well, probably some code after this was messing around with the "current" bound buffer
	qglBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpGLBuffer::Init() {

	Op::Init();
	strcpy( name, "OpGLBuffer" );
	size = ImVec2(256, 256);
	pos = ImVec2(250, 250);
	
	number_of_inputs = 0;
	InitLink(0, "Mesh", OP_TYPE_MESH );
	number_of_outputs = 1;
	InitLinkOutput(0, "Buffer", OP_TYPE_GLBUFFER );

	//for (int i=0; i<10; i++) {
	//	buffercontent.push_back(0.0f); // from x
	//	buffercontent.push_back(0.0f); // from y
	//	buffercontent.push_back(0.0f); // from z
	//	buffercontent.push_back(1.0f); // from w
	//	buffercontent.push_back(0.0f); // to x
	//	buffercontent.push_back(1.0f); // to y
	//	buffercontent.push_back(0.0f); // to z
	//	buffercontent.push_back(1.0f); // to w
	//}
	

	/*
	0.0f,  0.5f,  0.0f,
	0.5f, -0.5f,  0.0f,
	-0.5f, -0.5f,  0.0f	
	*/
	// 1st
	buffercontent.push_back(0.0f);
	buffercontent.push_back(-0.2f);
	buffercontent.push_back(0.0f);
	// 2nd
	buffercontent.push_back(0.5f);
	buffercontent.push_back(-0.5f);
	buffercontent.push_back(0.0f);
	// 3rd
	buffercontent.push_back(-0.5f);
	buffercontent.push_back(-0.5f);
	buffercontent.push_back(0.0f);

	//glGenBuffers(1, &default_link_outputs[0].opengl_id);
	MakeBuffer();
	//buffercontent.set
}

#include "../imgui/imgui_fixedarea.h"

void OpGLBuffer::Render() {
	Op::PreRender();
	
	//if (default_link_inputs[0].mesh)
	{

		int changed = 0;

		int cols = 3;

		//Mesh *mesh = default_link_inputs[0].mesh;
		float *data = buffercontent.data();
		int nvectors = buffercontent.size() / cols;
		FixedArea fa(pos + ImVec2(0.0f, 0.0f), size, cols);
		for (int i=0; i<nvectors; i++) {
			for (int j=0; j<cols; j++) {
				ImVec2 wh = fa.SetPos(i, j);
				ImGui::PushItemWidth(wh.x);
				//ImGui::Text("%d, %d", i, j);
				int offset = i * cols + j;
				float *address = data + offset;
				ImGui::PushID(address);
				changed += (int)ImGui::DragFloat("", address, 0.01f);
				// shit doesnt work
				//if (changed) {
				//	glBindBuffer(GL_ARRAY_BUFFER, mesh->buffer);
				//	glBufferSubData(GL_ARRAY_BUFFER, offset, 4, mesh->data);
				//	glBindBuffer(GL_ARRAY_BUFFER, 0);
				//}
				ImGui::PopID();
				ImGui::PopItemWidth();
			}
		}
		
		
		if (changed) {
			MakeBuffer();
			default_link_outputs[0].changed++;
		}


		//duk_push_global_object(ctx);
		//int ret = duk_get_prop_string(ctx, -1, "test");
		////log("ret: %d", ret);
		//
		//unsigned int size;
		//struct duk_hbufferobject *buf;
		//if (ret) {
		//	buf = duk_to_buffer_kung(ctx, -1, &size, DUK_BUF_MODE_DONTCARE);
		//	
		//	//memcpy(javascript_viewmatrix, (void *)( ((int)buf->buf) + 20 ), 16 * 4);
		//	float *arr = (float *)( ((int)buf->buf) + 20  );
		//	//duk_hbuffer *hbuf = buf->buf;
		//	//log("buf = %d size=%d %.2f %.2f %.2f off=%d llen=%d\n", buf, size, arr[0], arr[1], arr[2], buf->offset, buf->length);
		//
		//	int numfloats =  buf->length / (4 * 3); // 4 bytes per float, vec3 per row
		//	int changed = 0;
		//	
		//	FixedArea fa(pos, size, 3);
		//	for (int i=0; i<numfloats; i++) {
		//		for (int j=0; j<3; j++) {
		//			ImVec2 wh = fa.SetPos(i, j);
		//			ImGui::PushItemWidth(wh.x);
		//			//ImGui::Text("%d, %d", i, j);
		//			int offset = i * 3 + j;
		//			float *address = arr + offset;
		//			ImGui::PushID(address);
		//			changed += (int)ImGui::DragFloat("", address, 0.01f);
		//			// shit doesnt work
		//			//if (changed) {
		//			//	glBindBuffer(GL_ARRAY_BUFFER, mesh->buffer);
		//			//	glBufferSubData(GL_ARRAY_BUFFER, offset, 4, mesh->data);
		//			//	glBindBuffer(GL_ARRAY_BUFFER, 0);
		//			//}
		//			ImGui::PopID();
		//			ImGui::PopItemWidth();
		//		}
		//	}
		//	ImVec2 curpos = ImGui::GetCursorPos();
		//
		//	//ImGui::SetCursorPos(pos);
		//	ImGui::Text("Mesh::count: %d", mesh->count);
		//	ImGui::DragInt("meshcount", &mesh->count);
		//
		//	//if (ImGui::Button("reload array")) {
		//	if (changed || forcereload) {
		//		// length in bytes: 120
		//		// floats: 30
		//		// count for opengl: 10
		//		mesh->count = buf->length / (4 * 3);
		//		glBindBuffer(GL_ARRAY_BUFFER, mesh->buffer);
		//		glBufferData(GL_ARRAY_BUFFER, buf->length, arr, GL_STATIC_DRAW);
		//		glBindBuffer(GL_ARRAY_BUFFER, 0);
		//
		//		forcereload = 0;
		//	}
		//
		//} else {
		//	imgui_log("value does not exist");
		//}
		//duk_pop(ctx); // pop the getpropstring
		//duk_pop(ctx); // i guess I need two? no clue..
		////duk_pop(ctx); // pop the getpropstring
		////duk_pop(ctx); // pop the getpropstring

	
	}

	Op::PostRender();
}

void OpGLBuffer::Update() {
	//auto *ol = default_link_outputs + 0;
	//for (auto il : *ol->inputlinks) {
	//	il->mesh = default_link_inputs[0].mesh;
	//	//if (type == OpType::OP_TYPE_SENDER)
	//	//	il->owner->update(il->owner);
	//}

}

void OpGLBuffer::RenderEditor() {
	Op::RenderEditor();
	//Mesh *mesh = default_link_inputs[0].mesh;
	ImGui::Text("Buffer: %d", default_link_outputs[0].opengl_id);

	// test = new Float32Array(30)
	if (ImGui::Button("Update Buffer Data")) {
		MakeBuffer();
		imgui_log("Update Buffer: num floats=%d\n", buffercontent.size());
	}
	//ImGui::Text("textureid: %x", textureid);
}

OpGLBuffer::OpGLBuffer() {
	Init();
}