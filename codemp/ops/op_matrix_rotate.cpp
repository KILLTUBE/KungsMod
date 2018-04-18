#include "op.h"
#include "op_matrix_rotate.h"

#include "rd-rend2/matrix.h"

void OpMatrixRotate::Init() {
	Op::Init();
	size = ImVec2(256, 256);
	pos = ImVec2(250, 300);
	strcpy( name, "OpMatrixRotate" );
	InitLink(0, "X", OP_TYPE_FLOAT);
	InitLink(1, "Y", OP_TYPE_FLOAT);
	InitLink(2, "Z", OP_TYPE_FLOAT);
	InitLink(3, "Angle", OP_TYPE_FLOAT);
	InitLinkOutput(0, "Matrix", OP_TYPE_MATRIX);
	number_of_inputs = 4;
	number_of_outputs = 1;
	ResizeMinimal();
}

void OpMatrixRotate::Render() {
	Op::PreRender();
	
	Op::PostRender();
}

void OpMatrixRotate::Update() {
	if ( ! forcereload)
		return;
	//if (!strcmp(name, "MatRotHurr"))
	//	imgui_log("upddate matrix rotate\n");
	mat_rotate(default_link_outputs[0].matrix, x, y, z, angle);
	default_link_outputs[0].changed++;
}

std::string OpMatrixRotate::WriteExtraData() {
	char buf[1024];
	snprintf(buf, sizeof buf, "x %f y %f z %f angle %f", x, y, z, angle);
	return std::string(buf);
}

void OpMatrixRotate::ReadExtraData(char *line) {
	sscanf(line, "x %f y %f z %f angle %f", &x, &y, &z, &angle);
}

void OpMatrixRotate::RenderEditor() {
	Op::RenderEditor();
}

OpMatrixRotate::OpMatrixRotate() {
	Init();
}