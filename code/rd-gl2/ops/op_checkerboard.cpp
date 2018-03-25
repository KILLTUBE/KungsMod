#include "op.h"
#include "op_checkerboard.h"

#include "../include_imgui.h"

#include "../include_gl.h"

void OpCheckerboard::MakeCheckImage() {
	int i, j, c;
	if ( ! checkImage)
		return;
	GLubyte *img = checkImage;
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			c = ((((i & and_i)==0)^((j & and_j))==0))*255;
			*img++ = (GLubyte) c;
			*img++ = (GLubyte) c;
			*img++ = (GLubyte) c;
			*img++ = (GLubyte) 255;
		}
	}
}

void OpCheckerboard::GenerateTexture() {
	if ( ! checkImage)
		return;
	qglPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	qglGenTextures(1, (GLuint *)&textureid);
	//qglBindTexture(GL_TEXTURE_2D, 0); // unbind the texture
	qglBindTexture(GL_TEXTURE_2D, textureid);
	//qglTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//qglTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//qglTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,  GL_NEAREST);
	//qglTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,  GL_NEAREST);
	qglTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,  GL_LINEAR);
	qglTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,  GL_LINEAR);
	qglTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);
}

void OpCheckerboard::Init() {
	Op::Init();
	size = ImVec2(256, 256);
	pos = ImVec2(250, 250);
	checkImage = NULL;

	number_of_inputs = 4;
	InitLink(0, "Width" , OP_TYPE_INT );
	InitLink(1, "Height", OP_TYPE_INT );
	InitLink(2, "And I" , OP_TYPE_INT );
	InitLink(3, "And J" , OP_TYPE_INT );
	number_of_outputs = 0;

	width  = 64;
	height = 64;
	and_i  =  8;
	and_j  =  8;
	
	type = OpType::OP_TYPE_SENDER;
}

void OpCheckerboard::Render() {
	Op::PreRender();
	
	ImGui::SetCursorPos(pos);
	ImGui::Image((ImTextureID)textureid, size/* + ImVec2(-20,-20)*/);

	ImGui::SetCursorPos(pos + ImVec2(5,5));
	ImGui::Text("Checkboard texid=%d", textureid);

	Op::PostRender();
}

void OpCheckerboard::Update() {
	if ( ! DidInputsChange() )
		return;

	if (checkImage)
		free(checkImage);
	checkImage = (GLubyte *)malloc(width * height * 4);
	MakeCheckImage();
	qglDeleteTextures(1, (const GLuint *)&textureid);
	GenerateTexture();

	SetInputsUnchanged();
}

void OpCheckerboard::RenderEditor() {
	Op::RenderEditor();
	ImGui::Text("address: %x", checkImage);
	ImGui::Text("textureid: %x", textureid);
}

std::string OpCheckerboard::WriteExtraData() {
	char buf[1024];
	snprintf(buf, sizeof buf, "width %d height %d and_i %d and_j %d",
		width,
		height,
		and_i,
		and_j
	);
	return std::string(buf);
}

void OpCheckerboard::ReadExtraData(char *line) {
	sscanf(line, "width %d height %d and_i %d and_j %d",
		&width,
		&height,
		&and_i,
		&and_j
	);
}

OpCheckerboard::OpCheckerboard() {
	Init();
}
