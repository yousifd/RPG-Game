#pragma once

#include <SDL_surface.h>

#include "Collider.h"

struct Level {
	int id;
	char* name;
	SDL_Surface* bitmap;
	SDL_Rect rect;

	struct Collider collider;
};

int level_init(struct Level* level, char* name, const SDL_Surface* bitmap);

void level_free(struct Level* level);