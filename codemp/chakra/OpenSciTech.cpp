#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <SDL.h>
#undef main // sdl faggotery



#include "C:/OpenSciTech/codemp/include_ccall.h"

CCALL int __cdecl kungsmod_main ( int argc, char* argv[] );
CCALL void __cdecl win_present();



CCALL void __cdecl Sys_PlatformInit( void );

#define MAX_STRING_CHARS 1024
CCALL char *argsToString(int argc, char *argv[]) {
	static char commandLine[ MAX_STRING_CHARS ] = { 0 };
	for (int i = 1; i < argc; i++ )
	{
		const bool containsSpaces = (strchr(argv[i], ' ') != NULL);
		if (containsSpaces)
			strncat( commandLine, "\"", sizeof( commandLine ) );

		strncat( commandLine, argv[ i ], sizeof( commandLine ) );

		if (containsSpaces)
			strncat( commandLine, "\"", sizeof( commandLine ) );

		strncat( commandLine, " ", sizeof( commandLine ) );
	}
	return commandLine;
}

//CCALL void __cdecl Sys_HelloWorld( void );

CCALL void __cdecl win_present();
CCALL void __cdecl Sys_PlatformInit( void );
CCALL int __cdecl Sys_Milliseconds (bool baseTime = false);
CCALL char *__cdecl Sys_SetBinaryPath(const char *path);
CCALL void __cdecl Sys_SetDefaultInstallPath(const char *path);
CCALL void __cdecl Com_Init( char *commandLine );
CCALL void __cdecl NET_Init( void );
CCALL void __cdecl Com_BusyWait();
CCALL char *__cdecl Sys_BinaryPath(void);
CCALL void __cdecl Com_Frame( void );

#include "C:/OpenSciTech/codemp/imgui/imgui_api.h"

CCALL void __cdecl imgui_openjk_start();
CCALL void __cdecl imgui_openjk_end();

CCALL void __cdecl imgui_init();
CCALL void __cdecl imgui_new_frame();
CCALL void __cdecl imgui_end_frame();
CCALL void __cdecl imgui_render();

int mainads(/*int argc, char *argv[]*/) {

	//Sys_HelloWorld();

#if 0
	printf("k\n");

	Sys_PlatformInit();
	Sys_Milliseconds(); // get the initial time base
	Sys_SetBinaryPath( "" );
	Sys_SetDefaultInstallPath( Sys_BinaryPath() );
	char *startString = argsToString(argc, argv);
	Com_Init(startString);

	NET_Init();

	imgui_openjk_start();
	imgui_init();
	imgui_openjk_end();

	while (1) {
		Com_BusyWait();
		imgui_new_frame();
		Com_Frame();

		imgui_openjk_start();
		imgui_end_frame();
		imgui_openjk_end();

		win_present();
	}
#endif
	// never gets here
	return 0;

	//getchar();
	//return 0;
}


int openscitech_init() {
	//printf("k\n");

#if 1
	Sys_PlatformInit();
	Sys_Milliseconds(); // get the initial time base
	Sys_SetBinaryPath( "" );
	Sys_SetDefaultInstallPath( Sys_BinaryPath() );
	//char *startString = argsToString(argc, argv);
	Com_Init((char *)"");

	NET_Init();

	imgui_openjk_start();
	imgui_init();
	imgui_openjk_end();

	while (1) {
		Com_BusyWait();
		imgui_new_frame();
		Com_Frame();

		imgui_openjk_start();
		imgui_end_frame();
		imgui_openjk_end();

		win_present();
	}

#endif
	// never gets here
	return 0;

	//getchar();
	//return 0;
}