#include "../include_gl.h"
#include "op.h"
#include "op_file.h"

#include "../include_imgui.h"
//#include <include_soil.h>
//#include <include_devil.h>
//#include <include_physfs.h>

#include "op_prefab.h"
#include "../opsys/opsys.h"
//#include <format_cod2_xmodel.h>


void OpFile::GenerateTexture() {
	
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
	//qglTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WIDTH, HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);

}

void OpFile::Init() {

	Op::Init();
	size = ImVec2(256, 256);
	pos = ImVec2(250, 250);
	strcpy( name, "OpFile" );
	checkImage = NULL;

	InitLink(0, "Width" , OP_TYPE_INT );
	InitLink(1, "Height", OP_TYPE_INT );
	InitLink(2, "And I" , OP_TYPE_INT );
	InitLink(3, "And J" , OP_TYPE_INT );

	number_of_inputs = 0;

	type = OpType::OP_TYPE_SENDER;
}

void OpFile::Render() {
	Op::PreRender();
	
	ImGui::SetCursorPos(pos);
	ImGui::Image((ImTextureID)textureid, size/* + ImVec2(-20,-20)*/);
	
	Op::PostRender();
}

void OpFile::Update() {
	if ( ! DidInputsChange() )
		return;

	//if (checkImage)
	//	free(checkImage);
	//checkImage = (GLubyte *)malloc(WIDTH * HEIGHT * 4);
	//makeCheckImage)(op);
	//qglDeleteTextures(1, (const GLuint *)&textureid);
	//generate_texture)(op);

	SetInputsUnchanged();
}

void OpFile::RenderEditor() {
	Op::RenderEditor();
	ImGui::Text("address: %x", checkImage);
	ImGui::Text("textureid: %x", textureid);
	
	//if (ImGui::Button("Make DDS")) {
	//	/* load another image, but into the same texture ID, overwriting the last one */
	//	textureid = SOIL_load_OGL_texture
	//	(
	//		"assets/head.iwi_out.dds",
	//		SOIL_LOAD_AUTO,
	//		textureid,
	//		SOIL_FLAG_DDS_LOAD_DIRECT
	//	);	
	//}


	//if (ImGui::Button("Make .iwi")) {
	//
	//	ILuint devilError;
	//	//ilInit();
	//	devilError = ilGetError();
	//	//if (devilError != IL_NO_ERROR) { printf ("Devil Error (ilInit: %s\n", iluGetErrorString (devilError)); exit (2); }
	//
	//
	//	
	//	ilGenImages(1, &devilID);
	//	ilBindImage(devilID);
	//	//ilLoadImage("assets/head.iwi"); // Loads into the current bound image devilError = ilGetError();
	//	ilLoadL(IL_IWI, file_buffer, file_length);
	//
	//	iluFlipImage();
	//
	//	//if (devilError != IL_NO_ERROR) { printf ("Devil Error (ilLoadImage: %s\n", iluGetErrorString (devilError)); exit (2); }
	//
	//	//IL_OPENGL
	//	ilutRenderer(ILUT_OPENGL); // Switch the renderer
	//	//ilugeterr
	//
	//	//GLuint openglID, openglError;
	//
	//	textureid = ilutGLBindTexImage(); // This generates the texture for you devilError = ilGetError();
	//
	//	//if (devilError != IL_NO_ERROR) { printf ("Error: %s\n", iluGetErrorString (devilError)); exit (2); }
	//
	//	//if (openglError != GL_NO_ERROR) { printf ("Opengl Error (ilutGLBindTexImage): %s\n", gluGetErrorString (openglError)); exit (2); }
	//
	//	// Make sure to close the image when you are done with it (though DevIL // automatically deletes them when the program exits):
	//
	//	//qglDeleteTextures(1, &openglID); ilDeleteImages (1, &devilID);
	//
	//
	//}

	
	ImGui::Text("opengl textureid: %d", textureid);
	//ImGui::Text("devilID: %d", devilID);
	ImGui::Text("filename: %s", filename);
	//ImGui::Text("file_handle: %d", file_handle);
	ImGui::Text("file_buffer: %d", file_buffer);
	ImGui::Text("file_length: %d", file_length);
	ImGui::Text("file_length_read: %d", file_length_read);
}

std::string OpFile::WriteExtraData() {
	char buf[1024];
	snprintf(buf, sizeof buf, "filename %s",
		filename
	);
	return std::string(buf);
}

// http://stackoverflow.com/questions/5309471/getting-file-extension-in-c
const char *get_filename_ext(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}



void OpFile::ReadExtraData(char *line) {
	//sscanf(line, "filename %s",
	//	filename
	//);
	//log("Create file: %s\n", line);
	//
	//file_handle = PHYSFS_openRead(filename);
	//if (file_handle == NULL) {
	//	imgui_log("physfs cant open %s\n", filename);
	//	return;
	//}
	//file_buffer = (char *)malloc(PHYSFS_fileLength(file_handle));
	//file_length = PHYSFS_fileLength(file_handle);
	//file_length_read = PHYSFS_read (file_handle, file_buffer, 1, file_length);
	//log("Read file %s length=%d length_read=%d\n", filename, file_length, file_length_read);
	//
	//
	//const char *extension = get_filename_ext(filename);
	//if (strcmp(extension, "iwi") == 0) {
	//	format_iwi = FormatIWI::getByFilename(filename);
	//	textureid = format_iwi->textureid;
	//}
	//
	//
	//if (strcmp(extension, "opsys") == 0) {
	//
	//	OpPrefab *prefab = new OpPrefab();
	//	char buf[128];
	//	sprintf(buf, "filename %s", filename);
	//	prefab->ReadExtraData(buf);
	//	cursys->add((Op *)prefab);
	//	cursys->regenerateCallGraphs();
	//	prefab->pos = pos;
	//	system->deleteOp((Op *)this);
	//}
	//
	//
	//
	//if (strcmp(extension, "mat4") == 0) {
	//	int number_of_matrices = file_length / (16 * sizeof(float));
	//	imgui_log("insert %d matrices\n", number_of_matrices);
	//
	//	ImVec2 startpos = cursys->editor.mousepos;
	//
	//	for (int i=0; i<number_of_matrices; i++) {
	//
	//		char buf[64];
	//		sprintf(buf, "%s[%d]", filename, i);
	//		auto tmpmat = cursys->createMatrix(buf, 0);
	//		tmpmat->size = ImVec2(200, 90);
	//		tmpmat->pos = startpos;
	//		memcpy(tmpmat->default_link_inputs[0].matrix, file_buffer + (16 * 4 * i), 16*4);
	//
	//		startpos += ImVec2(0, 110); // put every matrix 110 pixels below prev one, thats 20 pixel padding
	//		
	//
	//
	//	}
	//	// delete the OpFile op, dont need it anymore
	//	system->deleteOp((Op *)this);
	//}

}

OpFile::OpFile() {
	Init();
}