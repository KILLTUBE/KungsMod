#ifndef INCLUDE_GL_H
#define INCLUDE_GL_H

// this file needs to be included first, otherwise there es always this fuckin error caused by GLEW/GL whatever

//#include <Windows.h>
//#include <kung/imgui/examples/libs/gl3w/GL/gl3w_.h>
#ifdef EMSCRIPTEN
//#include <SDL_opengles2.h>
//#include <GLES2/gl2.h>
//#include <GLES2/gl2ext.h>
//#include <SDL_opengl.h>
#else
//#include <F:\etlegacy\deps\glew-2.0.0\include\GL/glew.h>
//#include <SDL_opengl.h>
#endif
//#include <SDL_opengl.h>
//#include "glfw\include\GLFW/glfw3.h"


#include "rd-rend2/qgl.h"

#endif