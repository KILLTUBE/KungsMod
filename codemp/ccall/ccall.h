#ifndef CCALL_H
#define CCALL_H

#define ICDECL __cdecl

#ifdef __cplusplus
#	define EXTERNC extern "C"
#else
#	define EXTERNC extern
#endif

#ifdef EMSCRIPTEN
#	include <emscripten.h>
#	define CCALL EXTERNC EMSCRIPTEN_KEEPALIVE
#else
#	if defined(_MSC_VER)
#		define CCALL EXTERNC __declspec(dllexport)
#	else
#		define CCALL EXTERNC __attribute__((visibility("default")))
#	endif
#endif

#define ICAPI CCALL

#endif