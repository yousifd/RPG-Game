#pragma once

#include <SDL_Surface.h>

#include "Collider.h"

struct Player {
	SDL_Surface* sprite;
	SDL_Rect rect;

	int xvel;
	int yvel;

	struct Collider collider;
};

int player_init(struct Player* player);

void player_free(struct Player* player);

void player_update(struct Player* player);