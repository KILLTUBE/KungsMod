#include "../include_gl.h"
#include "../opsys/opsys_opengl.h"
#include "op.h"
#include "op_gl_fragment_shader.h"

#include "../include_console.h"

void OpFragmentShader::MakeShader() {
	if (fragmentshader)
		qglDeleteShader(fragmentshader);
	fragmentshader = opengl_load_shader(GL_FRAGMENT_SHADER, filename, &haserror);
	Changed();
	default_link_outputs[0].changed++;
	imgui_log("frag loaded: haserror=%d\n", haserror);
}

void OpFragmentShader::Init() {
	Op::Init();
	type = OP_TYPE_DELIVERER;
	size = ImVec2(300, 30);
	pos = ImVec2(250, 300);
	strcpy( name, "OpFragmentShader" );
	strcpy( default_link_inputs[0].name, ">");
	strcpy( default_link_inputs[0].val_str, "no value set");
	number_of_inputs = 0;
	number_of_outputs = 1;
	InitLinkOutput(0, "Frag", OP_TYPE_FRAGMENTSHADER);

	//fragmentshader = load_shader(GL_FRAGMENT_SHADER, filename);
}

void OpFragmentShader::Render() {
	Op::PreRender();
	ImGui::SetCursorPos(pos + ImVec2(5,5));
	ImGui::PushItemWidth(size.x - 50);
	ImGui::PushID(this);
	ImGui::InputText("File", filename, sizeof filename);
	ImGui::PopID();
	ImGui::PopItemWidth();
	Op::PostRender();
}

void OpFragmentShader::Update() {

	if (/*openglstarted &&*/ fragmentshader==0 && haserror==0) {
		MakeShader();
	}

	//auto *ol = default_link_outputs + 0;
	//for (auto il : *ol->inputlinks) {
	//	il->opengl_id = fragmentshader;
	//	//if (type == OpType::OP_TYPE_SENDER)
	//	//	il->owner->update(il->owner);
	//}
}

void OpFragmentShader::RenderEditor() {
	Op::RenderEditor();
	ImGui::Text("fragmentshader: %d", fragmentshader);
	if ( ImGui::Button("Reload shader") )
		MakeShader();
}

std::string OpFragmentShader::WriteExtraData() {
	char buf[1024];
	snprintf(buf, sizeof buf, "filename %s",
		filename
	);
	return std::string(buf);
}

void OpFragmentShader::ReadExtraData(char *line) {
	sscanf(line, "filename %[^\n]",
		&filename
	);
}

OpFragmentShader::OpFragmentShader() {
	Init();
}