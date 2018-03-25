#include "compose_images.h"
#include <string.h>

int images_changed[4096] = {0};

typedef int Image;

//Image ToImage(int id) {
//}

bool hasImageChanged(int id) {
	//qhandle_t ad;
	// todo... an Image type shouldnt be possible to create with an invalid id (0 to 4095)... so if a handle exists, it is ALWAYS valid
	return images_changed[ id ];
}

void markImageChanged(int id) {
	images_changed[id] = 1;
}

void resetImageChanges() {
	memset(images_changed, 0, sizeof(images_changed));
}