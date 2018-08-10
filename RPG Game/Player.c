#include <stdio.h>

#include "Player.h"
#include "Const.h"

const int SPRITE_WIDTH = 37;
const int SPRITE_HEIGHT = 50;

int player_init(struct Player* player) {
	player->sprite = SDL_LoadBMP("resources/player/idle-00.bmp");
	if (player->sprite == NULL) {
		printf("Failed to load player image: %s\n", SDL_GetError());
		return -1;
	}
	printf("Load player image succeeded");

	player->rect.x = WIDTH / 2;
	player->rect.y = HEIGHT / 2;
	player->rect.w = WIDTH;
	player->rect.h = HEIGHT;

	return 0;
}