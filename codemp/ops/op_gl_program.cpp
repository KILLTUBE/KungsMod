
#include "../opsys/opsys_opengl.h"
#include "op.h"
#include "op_gl_program.h"
//#include "util.h"

#include "../include_console.h"

void OpProgram::MakeProgram() {
	if (program)
		qglDeleteProgram(program);
	GLuint program_new = qglCreateProgram();
	if ( ! vertexshader) {
		imgui_log("vertexshader not set for %s\n", name);
		goto error;
	}
	if ( ! fragmentshader) {
		imgui_log("shader2 not set for %s\n", name);
		goto error;
	}
	qglAttachShader(program_new, vertexshader);
	qglAttachShader(program_new, fragmentshader);
	qglLinkProgram(program_new);
	GLint status;
	qglGetProgramiv(program_new, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		GLint length;
		qglGetProgramiv(program_new, GL_INFO_LOG_LENGTH, &length);
		GLchar *info = (GLchar *)calloc(length, sizeof(GLchar));
		qglGetProgramInfoLog(program_new, length, NULL, info);
		imgui_log("glLinkProgram failed: %s\n", info);
		free(info);
		
		goto error;
	} else {
		haserror = 0;
	}
	qglDetachShader(program_new, vertexshader);
	qglDetachShader(program_new, fragmentshader);
	//glDeleteShader(shader1);
	//glDeleteShader(shader2);
	program = program_new;
	imgui_log("update program: old=%d new=%d\n", program, program_new);
	default_link_outputs[0].changed++;
	return;
error:
	if (program)
		qglDeleteProgram(program);
	if (program)
		qglDeleteProgram(program);
	program = 0;
	haserror = 1;
}

void OpProgram::Init() {
	Op::Init();
	type = OP_TYPE_DELIVERER;
	size = ImVec2(300, 30);
	pos = ImVec2(250, 300);
	strcpy( name, "OpProgram" );
	
	fragmentshader = 0;
	vertexshader = 0;

	number_of_inputs = 2;
	InitLink(0, "Frag", OP_TYPE_FRAGMENTSHADER);
	InitLink(1, "Vert", OP_TYPE_VERTEXSHADER);
	number_of_outputs = 1;
	InitLinkOutput(0, "Prog", OP_TYPE_PROGRAM);
	
	ResizeMinimal();	
}

void OpProgram::Render() {
	Op::PreRender();
	ImGui::SetCursorPos(pos + ImVec2(5,5));
	ImGui::Text("%d", program);
	Op::PostRender();
}

void OpProgram::Update() {

	if (fragmentshader && vertexshader && haserror==0 && program==0) {
		MakeProgram();
	}

	//auto *ol = default_link_outputs + 0;
	//for (auto il : *ol->inputlinks) {
	//	il->opengl_id = program;
	//	//if (type == OpType::OP_TYPE_SENDER)
	//	//	il->owner->update(il->owner);
	//}
}

void OpProgram::RenderEditor() {
	Op::RenderEditor();
	ImGui::Text("fragmentshader: %d", fragmentshader);
	ImGui::Text("vertexshader: %d", vertexshader);
	ImGui::Text("program: %d", program);
	if ( ImGui::Button("Make Program") )
		MakeProgram();
}

void OpProgram::OnLinkDisconnect(int id) {
	//log("disconnect id: %d\n", id);
	switch (default_link_inputs[id].type) {
		case OP_TYPE_FRAGMENTSHADER:
			fragmentshader = 0;
			break;
		case OP_TYPE_VERTEXSHADER:
			vertexshader = 0;
			break;
	}
}

void OpProgram::OnLinkUpdate(int id) {
	imgui_log("link changed id: %d\n", id);
	MakeProgram();
	switch (default_link_inputs[id].type) {
		case OP_TYPE_FRAGMENTSHADER:
			//fragmentshader = 0;
			break;
		case OP_TYPE_VERTEXSHADER:
			//vertexshader = 0;
			break;
	}
}

OpProgram::OpProgram() {
	Init();
}