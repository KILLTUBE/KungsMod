#ifndef OPSYSTEM_OPENGL_H
#define OPSYSTEM_OPENGL_H


//#include "GL/glew.h"
//#include "../include_gl.h"
#include "../rd-rend2/qgl.h"
//#include "glfw\include\GLFW/glfw3.h"

extern int openglstarted;

GLuint opengl_make_shader(GLenum type, const char *source, int *out_error);
GLuint opengl_load_shader(GLenum type, const char *path, int *out_error);
GLuint opengl_make_program(GLuint shader1, GLuint shader2, int *out_error);

#endif