//#include "craftstructs.h"
#include "../include_gl.h"
#include "../include_imgui.h"

//#include "imgui_impl_glfw.h"
#include <stdio.h>
//#include "libs\glfw\include\GLFW/glfw3.h"
#include <list>

#include "op.h"
#include "op_mesh_editor.h"


#ifdef USE_DUKTAPE
#include <include_duktape.h>
#include <duktape/dukdebugheaders.h>
#endif

void OpMeshEditor::Init() {

	Op::Init();
	size = ImVec2(256, 256);
	pos = ImVec2(250, 250);
	
	number_of_inputs = 1;
	InitLink(0, "Mesh", OP_TYPE_MESH );
	number_of_outputs = 1;
	InitLinkOutput(0, "Mesh", OP_TYPE_MESH );
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

void OpMeshEditor::Render() {
	Op::PreRender();
#ifdef USE_DUKTAPE
	if (default_link_inputs[0].mesh) {

		int changed = 0;

		Mesh *mesh = default_link_inputs[0].mesh;
		//FixedArea fa(pos, size, 3);
		//for (int i=0; i<10; i++) {
		//	for (int j=0; j<3; j++) {
		//		ImVec2 wh = fa.SetPos(i, j);
		//		ImGui::PushItemWidth(wh.x);
		//		//ImGui::Text("%d, %d", i, j);
		//		int offset = i * 3 + j;
		//		float *address = mesh->data + offset;
		//		ImGui::PushID(address);
		//		changed += (int)ImGui::DragFloat("", address, 0.01f);
		//		// shit doesnt work
		//		//if (changed) {
		//		//	glBindBuffer(GL_ARRAY_BUFFER, mesh->buffer);
		//		//	glBufferSubData(GL_ARRAY_BUFFER, offset, 4, mesh->data);
		//		//	glBindBuffer(GL_ARRAY_BUFFER, 0);
		//		//}
		//		ImGui::PopID();
		//		ImGui::PopItemWidth();
		//	}
		//}
		//
		//
		//if (changed) {
		//	glBindBuffer(GL_ARRAY_BUFFER, mesh->buffer);
		//	glBufferData(GL_ARRAY_BUFFER, sizeof(mesh->data), mesh->data, GL_STATIC_DRAW);
		//	glBindBuffer(GL_ARRAY_BUFFER, 0);
		//}


		duk_push_global_object(ctx);
		int ret = duk_get_prop_string(ctx, -1, "test");
		//log("ret: %d", ret);

		unsigned int size;
		struct duk_hbufferobject *buf;
		if (ret) {
#if 0
			buf = duk_to_buffer_kung(ctx, -1, &size, DUK_BUF_MODE_DONTCARE);
			
			//memcpy(javascript_viewmatrix, (void *)( ((int)buf->buf) + 20 ), 16 * 4);
			float *arr = (float *)( ((int)buf->buf) + 20  );
			//duk_hbuffer *hbuf = buf->buf;
			//log("buf = %d size=%d %.2f %.2f %.2f off=%d llen=%d\n", buf, size, arr[0], arr[1], arr[2], buf->offset, buf->length);

			int numfloats =  buf->length / (4 * 3); // 4 bytes per float, vec3 per row
			int changed = 0;
			
			FixedArea fa(pos, size, 3);
			for (int i=0; i<numfloats; i++) {
				for (int j=0; j<3; j++) {
					ImVec2 wh = fa.SetPos(i, j);
					ImGui::PushItemWidth(wh.x);
					//ImGui::Text("%d, %d", i, j);
					int offset = i * 3 + j;
					float *address = arr + offset;
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
			ImVec2 curpos = ImGui::GetCursorPos();

			//ImGui::SetCursorPos(pos);
			ImGui::Text("Mesh::count: %d", mesh->count);
			ImGui::DragInt("meshcount", &mesh->count);

			//if (ImGui::Button("reload array")) {
			if (changed || forcereload) {
				// length in bytes: 120
				// floats: 30
				// count for opengl: 10
				mesh->count = buf->length / (4 * 3);
				glBindBuffer(GL_ARRAY_BUFFER, mesh->buffer);
				glBufferData(GL_ARRAY_BUFFER, buf->length, arr, GL_STATIC_DRAW);
				glBindBuffer(GL_ARRAY_BUFFER, 0);

				forcereload = 0;
			}
#endif
		} else {
			//log("value does not exist");
		}
		duk_pop(ctx); // pop the getpropstring
		duk_pop(ctx); // i guess I need two? no clue..
		//duk_pop(ctx); // pop the getpropstring
		//duk_pop(ctx); // pop the getpropstring

	
	}
#endif
	Op::PostRender();
}

void OpMeshEditor::Update() {
	auto *ol = default_link_outputs + 0;
	for (auto il : *ol->inputlinks) {
		//il->mesh = default_link_inputs[0].mesh;
		//if (type == OpType::OP_TYPE_SENDER)
		//	il->owner->update(il->owner);
	}

}

void OpMeshEditor::RenderEditor() {
	Op::RenderEditor();
	//Mesh *mesh = default_link_inputs[0].mesh;
	//ImGui::Text("Mesh: %x", default_link_inputs[0].mesh);

	// test = new Float32Array(30)
	//if (ImGui::Button("Reload test")) {
	//	qglBindBuffer(GL_ARRAY_BUFFER, mesh->buffer);
	//	qglBufferData(GL_ARRAY_BUFFER, sizeof(mesh->data), mesh->data, GL_STATIC_DRAW);
	//	qglBindBuffer(GL_ARRAY_BUFFER, 0);
	//}
	//ImGui::Text("textureid: %x", textureid);
}

OpMeshEditor::OpMeshEditor() {
	Init();
}