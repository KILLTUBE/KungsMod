#include "../include_gl.h"
#include "op.h"
#include "op_soil.h"

#include "../include_imgui.h"

//#include "G:/libs/Simple OpenGL Image Library/src/SOIL.h"

//#include "G:/libs/DevIL-master/DevIL/include/IL/il.h"
//#include "G:/libs/DevIL-master/DevIL/include/IL/ilu.h"
//#include "G:/libs/DevIL-master/DevIL/include/IL/ilut.h"

void OpSOIL::MakeCheckImage()
{
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

void OpSOIL::GenerateTexture() {
   if ( ! checkImage)
	   return;
	qglPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	qglGenTextures(1, (GLuint *)&textureid);
	//glBindTexture(GL_TEXTURE_2D, 0); // unbind the texture
	qglBindTexture(GL_TEXTURE_2D, textureid);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,  GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,  GL_NEAREST);
	qglTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,  GL_LINEAR);
	qglTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,  GL_LINEAR);
	qglTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);

}

void OpSOIL::Init() {

	Op::Init();
	size = ImVec2(256, 256);
	pos = ImVec2(250, 250);
	strcpy( name, "OpSOIL" );
	checkImage = NULL;

	InitLink(0, "Width" , OP_TYPE_INT );
	InitLink(1, "Height", OP_TYPE_INT );
	InitLink(2, "And I" , OP_TYPE_INT );
	InitLink(3, "And J" , OP_TYPE_INT );

	number_of_inputs = 4;

	number_of_outputs = 1;
	InitLinkOutput(0, "texid", OP_TYPE_GLBUFFER);

	width  = 64;
	height = 64;
	and_i  =  8;
	and_j  =  8;

	//		textureid = SOIL_load_OGL_texture
	//	(
	//		"baseq3/textures/maila_body_1024.jpg",
	//		SOIL_LOAD_AUTO,
	//		textureid,
	//		SOIL_FLAG_DDS_LOAD_DIRECT
	//	);	
			default_link_outputs[0].changed++;

}

void OpSOIL::Render() {
	Op::PreRender();
	
	ImGui::SetCursorPos(pos);
	ImGui::Image((ImTextureID)textureid, size/* + ImVec2(-20,-20)*/);


	Op::PostRender();
}

void OpSOIL::Update() {
	if ( ! DidInputsChange() )
		return;

	//if (checkImage)
	//	free(checkImage);
	//checkImage = (GLubyte *)malloc(width * height * 4);
	//MakeCheckImage();
	//glDeleteTextures(1, (const GLuint *)&textureid);
	//GenerateTexture();

	SetInputsUnchanged();
}

void OpSOIL::RenderEditor() {
	Op::RenderEditor();
	ImGui::Text("address: %x", checkImage);
	ImGui::Text("textureid: %u", textureid);
	
	//if (ImGui::Button("Make DDS")) {
	//	/* load another image, but into the same texture ID, overwriting the last one */
	//	textureid = SOIL_load_OGL_texture
	//	(
	//		"baseq3/textures/maila_body_1024.jpg",
	//		SOIL_LOAD_AUTO,
	//		textureid,
	//		SOIL_FLAG_DDS_LOAD_DIRECT
	//	);	
	//}


	if (ImGui::Button("Make .iwi")) {

		//ILuint devilError;
		//ilInit();
		//devilError = ilGetError();
		////if (devilError != IL_NO_ERROR) { printf ("Devil Error (ilInit: %s\n", iluGetErrorString (devilError)); exit (2); }
		//
		//
		//ILuint devilID;
		//ilGenImages(1, &devilID);
		//ilBindImage(devilID);
		//ilLoadImage("baseq3/textures/maila_body_1024.jpg"); // Loads into the current bound image devilError = ilGetError();
		//
		//iluFlipImage();
		//
		////if (devilError != IL_NO_ERROR) { printf ("Devil Error (ilLoadImage: %s\n", iluGetErrorString (devilError)); exit (2); }
		//
		////IL_OPENGL
		//ilutRenderer(ILUT_OPENGL); // Switch the renderer
		//ilugeterr

		//GLuint openglID, openglError;

		//textureid = ilutGLBindTexImage(); // This generates the texture for you devilError = ilGetError();

		//if (devilError != IL_NO_ERROR) { printf ("Error: %s\n", iluGetErrorString (devilError)); exit (2); }

		//if (openglError != GL_NO_ERROR) { printf ("Opengl Error (ilutGLBindTexImage): %s\n", gluGetErrorString (openglError)); exit (2); }

		// Make sure to close the image when you are done with it (though DevIL // automatically deletes them when the program exits):

		//glDeleteTextures(1, &openglID); ilDeleteImages (1, &devilID);


	}

}

std::string OpSOIL::WriteExtraData() {
	char buf[1024];
	snprintf(buf, sizeof buf, "width %d height %d and_i %d and_j %d",
		width,
		height,
		and_i,
		and_j
	);
	return std::string(buf);
}

void OpSOIL::ReadExtraData(char *line) {
	sscanf(line, "width %d height %d and_i %d and_j %d",
		&width,
		&height,
		&and_i,
		&and_j
	);
}

OpSOIL::OpSOIL() {
	Init();
}