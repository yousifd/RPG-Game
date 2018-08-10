#include <SDL.h>
#include <stdlib.h>
#include <string.h>

#include "Game.h"
#include "Event.h"
#include "Const.h"
#include "Collider.h"
#include "Log.h"

int game_init(struct Game* game) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		log_error("SDL initialization failed. SDL Error: %s", SDL_GetError());
		return -1;
	}
	log_info("SDL initialization succeeded!");

	game->game_over = false;

	game->window = SDL_CreateWindow("RPG Game",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WIDTH,
		HEIGHT,
		SDL_WINDOW_OPENGL);
	if (game->window == NULL) {
		log_error("Could not create window: %s", SDL_GetError());
		return -1;
	}
	log_info("Window initialization succeeded!");

	game->renderer = SDL_CreateRenderer(game->window,
		-1,
		SDL_RENDERER_ACCELERATED);
	if (game->renderer == NULL) {
		log_error("Could not create renderer: %s", SDL_GetError());
		return -1;
	}
	log_info("Renderer initialization succeeded!");

	game->screen = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0, 0, 0, 0);
	if (game->screen == NULL) {
		log_error("Could not create the screen surface: %s", SDL_GetError());
		return -1;
	}
	log_info("Create screen surface was successful!");

	if (level_init(&game->level, "Test", "resources/level/test.bmp") < 0) {
		log_error("Failed to create level!");
		return -1;
	}
	log_info("Create level succeeded!");

	if (player_init(&game->player) < 0) {
		log_error("Failed to initalize player!");
		return -1;
	}
	log_info("Player initialization succeeded!");

	return 0;
}

void game_free(struct Game* game) {
	player_free(&game->player);
	if (game->renderer != NULL) {
		SDL_DestroyRenderer(game->renderer);
	}
	if (game->window != NULL) {
		SDL_DestroyWindow(game->window);
	}
}

void game_run() {
	struct Game game;
	SDL_Texture* screen = NULL;

	if (game_init(&game) < 0) {
		log_error("Failed to initialize Game!");
		game.game_over = true;
		getchar();
	}

	screen = SDL_CreateTexture(game.renderer,
		SDL_PIXELFORMAT_BGRA32,
		SDL_TEXTUREACCESS_STREAMING,
		WIDTH,
		HEIGHT);
	if (screen == NULL) {
		log_error("Failed to create screen texture: %s", SDL_GetError());
		game.game_over = true;
		getchar();
	}

	while (!game.game_over) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				event_keyboard_down(&event.key, &game);
				break;
			case SDL_KEYUP:
				event_keyboard_up(&event.key, &game);
				break;
			case SDL_QUIT:
				game.game_over = true;
				break;
			}
		}

		// TODO: Animate Player
		// TODO: Work on Making Tileset Levels
		// TODO: Improve collision to cover everything

		game.player.collider.colliding = collider_check(&game.player.collider, &game.level.collider);
		if (game.player.collider.colliding) {
			log_info("Player collided with level!");
		}

		player_update(&game.player);
		
		SDL_LockTexture(screen, NULL, &game.screen->pixels, &game.screen->pitch);
		// Clear Screen
		SDL_FillRect(game.screen, NULL, SDL_MapRGB(game.screen->format, 0, 0, 0));
		if (SDL_BlitSurface(game.level.bitmap, NULL, game.screen, &game.level.rect) < 0) {
			log_error("Level Surface blit failed: %s", SDL_GetError());
			game.game_over = true;
		}
		if (SDL_BlitSurface(game.player.sprite, NULL, game.screen, &game.player.rect) < 0) {
			log_error("Player Surface blit failed: %s", SDL_GetError());
			game.game_over = true;
		}
		SDL_UnlockTexture(screen);

		SDL_RenderClear(game.renderer);
		SDL_RenderCopy(game.renderer, screen, NULL, NULL);
		SDL_RenderPresent(game.renderer);
	}

	log_info("Game Over!");
	game_free(&game);
	SDL_Quit();
}