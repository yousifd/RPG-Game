#pragma once

#include <stdbool.h>
#include <SDL_video.h>
#include <SDL_render.h>

#include "Player.h"

struct Game {
	struct Player player;
	bool game_over;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* screen;
};

int game_init(struct Game* game);

void game_free(struct Game* game);

void game_run();
