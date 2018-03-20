#ifndef OP_FILE_H
#define OP_FILE_H

#include "op.h"

//#include <include_devil.h>
//#include <include_physfs.h>

//#include <format_iwi.h>

class OpFile : public Op {
public:
	
	GLubyte *checkImage = NULL;

	char filename[512];
	//PHYSFS_File *file_handle;
	char *file_buffer;
	int file_length;
	int file_length_read;
	GLuint textureid = 0;
	//FormatIWI *format_iwi = NULL;

	OpFile();
	void GenerateTexture();

	void Init();
	void Render();
	void Update();
	void RenderEditor();
	std::string WriteExtraData();
	void ReadExtraData(char * line);

};

#endif