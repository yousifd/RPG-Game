#include "Player.h"
#include "Const.h"
#include "Log.h"

#define SPRITE_WIDTH 37
#define SPRITE_HEIGHT 50

int player_init(struct Player* player) {
	player->sprite = SDL_LoadBMP("resources/player/idle-00.bmp");
	if (player->sprite == NULL) {
		log_error("Failed to load player image: %s", SDL_GetError());
		return -1;
	}
	log_info("Load player image succeeded");

	player->rect.x = WIDTH / 2;
	player->rect.y = HEIGHT / 2;
	player->rect.w = SPRITE_WIDTH;
	player->rect.h = SPRITE_HEIGHT;

	collider_init(&player->collider, &player->rect);

	player->xvel = 0;
	player->yvel = 0;

	return 0;
}

void player_free(struct Player* player) {
	if (player->sprite != NULL) {
		SDL_FreeSurface(player->sprite);
	}
}

void player_update(struct Player* player) {
	// TODO: fix player action after collision
	player->rect.x += player->xvel;
	if (player->rect.x < 0) {
		player->rect.x = 0;
	}
	if (player->rect.x > WIDTH - SPRITE_WIDTH) {
		player->rect.x = WIDTH - SPRITE_WIDTH;
	}

	player->rect.y += player->yvel;
	if (player->yvel == 0) {
		player->yvel = 1;
	}

	if (player->collider.colliding) {
		player->yvel = 0;
	}
}