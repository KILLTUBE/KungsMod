#include <stdio.h>
#include <SDL.h>
#undef main // sdl faggotery



#include "../codemp/rd-rend2/include_ccall.h"

CCALL int kungsmod_main ( int argc, char* argv[] );

int main() {
	printf("k\n");


	char *argv[] = {"meh.exe", "map mp/duel1"};

	kungsmod_main(2, argv);

	getchar();
	return 0;
}