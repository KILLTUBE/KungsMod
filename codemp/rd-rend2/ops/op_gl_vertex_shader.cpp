#include "../include_gl.h"
#include "../opsys/opsys_opengl.h"
#include "op.h"
#include "op_gl_vertex_shader.h"

#include "../include_console.h"

void OpVertexShader::MakeShader() {
	if (vertexshader)
		qglDeleteShader(vertexshader);
	vertexshader = opengl_load_shader(GL_VERTEX_SHADER, filename, &haserror);
	Changed();
	default_link_outputs[0].changed++;
	imgui_log("vert loaded: haserror=%d\n", haserror);
}

void OpVertexShader::Init() {
	Op::Init();
	type = OP_TYPE_DELIVERER;
	size = ImVec2(300, 30);
	pos = ImVec2(250, 300);
	strcpy( name, "OpVertexShader" );
	strcpy( default_link_inputs[0].name, ">");
	strcpy( default_link_inputs[0].val_str, "no value set");
	number_of_inputs = 0;
	number_of_outputs = 1;
	InitLinkOutput(0, "Vert", OP_TYPE_VERTEXSHADER);

	//vertexshader = load_shader(GL_VERTEX_SHADER, filename);
}

void OpVertexShader::Render() {
	Op::PreRender();
	ImGui::SetCursorPos(pos + ImVec2(5,5));
	ImGui::PushItemWidth(size.x - 50);
	ImGui::PushID(this);
	ImGui::InputText("File", filename, sizeof filename);
	ImGui::PopID();
	ImGui::PopItemWidth();
	Op::PostRender();
}

void OpVertexShader::Update() {
	if (/*openglstarted &&*/ vertexshader==0 && haserror==0) {
		MakeShader();
	}

	//auto *ol = default_link_outputs + 0;
	//for (auto il : *ol->inputlinks) {
	//	il->opengl_id = vertexshader;
	//	//if (type == OpType::OP_TYPE_SENDER)
	//	//	il->owner->update(il->owner);
	//}
}

void OpVertexShader::RenderEditor() {
	Op::RenderEditor();
	ImGui::Text("vertexshader: %d", vertexshader);
	if ( ImGui::Button("Reload shader") ) {
		MakeShader();
	}
}

std::string OpVertexShader::WriteExtraData() {
	char buf[1024];
	snprintf(buf, sizeof buf, "filename %s",
		filename
	);
	return std::string(buf);
}

void OpVertexShader::ReadExtraData(char *line) {
	sscanf(line, "filename %[^\n]",
		&filename
	);
}

OpVertexShader::OpVertexShader() {
	Init();
}
