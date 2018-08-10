#pragma once

#include <SDL_Surface.h>

struct Player {
	SDL_Surface* sprite;
	SDL_Rect rect;
};

int player_init(struct Player* player);