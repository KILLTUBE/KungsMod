#include "../include_gl.h"

#include "../opsys/opsys_opengl.h"
#include "../include_console.h"
#include "stdio.h"
#include "stdlib.h"

int openglstarted;

int fs_readfile(const char *path, char **buffer, size_t *out_filesize);
char *load_file(const char *path) {
	
	char *buf = NULL;
	size_t file_size=0;

	//DebugBreak(); // cba atm, fix when occurs

	// fucking shit is this confusing, return 0 == success
	//if (!fs_readfile(path, (char**)&buf, &file_size)) {
	//	return buf;
	//}
	return NULL;
}
GLuint opengl_make_shader(GLenum type, const char *source, int *out_error) {
	GLuint shader = qglCreateShader(type);
	qglShaderSource(shader, 1, &source, NULL);
	qglCompileShader(shader);
	GLint status;
	qglGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		GLint length;
		qglGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		GLchar *info = (GLchar *)calloc(length, sizeof(GLchar));
		qglGetShaderInfoLog(shader, length, NULL, info);
		imgui_log("glCompileShader failed:\n%s\n", info);
		free(info);
		*out_error = 1;
		qglDeleteShader(shader);
		return 0;
	} else {
		*out_error = 0;
	}
	return shader;
}


GLuint opengl_load_shader(GLenum type, const char *path, int *out_error) {
	//__asm int 3; // meh
	//return 0;

	// todo implement
	char *data = load_file(path);
	GLuint result = opengl_make_shader(type, data, out_error);
	free(data);
	return result;
}

GLuint opengl_make_program(GLuint shader1, GLuint shader2, int *out_error) {
	GLuint program = qglCreateProgram();
	qglAttachShader(program, shader1);
	qglAttachShader(program, shader2);
	qglLinkProgram(program);
	GLint status;
	qglGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		GLint length;
		qglGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		GLchar *info = (GLchar *)calloc(length, sizeof(GLchar));
		qglGetProgramInfoLog(program, length, NULL, info);
		imgui_log("glLinkProgram failed: %s\n", info);
		free(info);
		*out_error = 1;
		qglDeleteProgram(program);
		return 0;
	} else {
		*out_error = 0;
	}
	qglDetachShader(program, shader1);
	qglDetachShader(program, shader2);
	//glDeleteShader(shader1);
	//glDeleteShader(shader2);
	return program;
}