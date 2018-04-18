#include <stdio.h>
#include <string.h>
#include <SDL.h>
#undef main // sdl faggotery



#include "../codemp/include_ccall.h"

CCALL int kungsmod_main ( int argc, char* argv[] );
CCALL void win_present();



CCALL void Sys_PlatformInit( void );

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



CCALL void win_present();
CCALL void Sys_PlatformInit( void );
CCALL int Sys_Milliseconds (bool baseTime = false);
CCALL char *Sys_SetBinaryPath(const char *path);
CCALL void Sys_SetDefaultInstallPath(const char *path);
CCALL void Com_Init( char *commandLine );
CCALL void NET_Init( void );
CCALL void Com_BusyWait();
CCALL char *Sys_BinaryPath(void);
CCALL void Com_Frame( void );

#include "../codemp/imgui/imgui_api.h"

CCALL void imgui_openjk_start();
CCALL void imgui_openjk_end();

int main(int argc, char *argv[]) {
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

	// never gets here
	return 0;

	getchar();
	return 0;
}