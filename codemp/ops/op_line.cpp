#include "op.h"
#include "op_line.h"
#include "../imgui/imgui_fixedarea.h"

#include "../utils_opengl/debuglines.h"

void OpLine::Init() {
	Op::Init();
	size = ImVec2(200, 90);
	pos = ImVec2(250, 300);
	
	number_of_inputs = 4;
	InitLink(0, "a",    OP_TYPE_VECTOR4);
	InitLink(1, "acol", OP_TYPE_VECTOR4);
	InitLink(2, "b",    OP_TYPE_VECTOR4);
	InitLink(3, "bcol", OP_TYPE_VECTOR4);
	number_of_outputs = 0;
}

void OpLine::Render() {
	Op::PreRender();
	//FixedArea fa(pos, size, 4);
	//if (ImGui::PrintVector4(&fa, default_link_inputs[0].matrix))
	//	default_link_inputs[0].changed++;
	Op::PostRender();
}

void OpLine::Update() {
	glm::vec3 a    = glm::vec3(line_from    [0], line_from    [1], line_from    [2]);
	glm::vec3 acol = glm::vec3(line_from_col[0], line_from_col[1], line_from_col[2]);
	glm::vec3 b    = glm::vec3(line_to    [0], line_to    [1], line_to    [2]);
	glm::vec3 bcol = glm::vec3(line_to_col[0], line_to_col[1], line_to_col[2]);
	kungdebuglines.AddLine(a, acol, b, bcol);
}

void OpLine::RenderEditor() {
	Op::RenderEditor();
}

std::string OpLine::WriteExtraData() {
	char buf[1024];
	snprintf(buf, sizeof buf, "values %f %f %f %f",
		line_from[0],
		line_from[1],
		line_from[2],
		line_from[3]
	);
	return std::string(buf);
}

void OpLine::ReadExtraData(char *line) {
	sscanf(line, "values %f %f %f %f",
		&line_from[0],
		&line_from[1],
		&line_from[2],
		&line_from[3]
	);
}

OpLine::OpLine() {
	Init();
}