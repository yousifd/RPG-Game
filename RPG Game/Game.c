#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "Game.h"
#include "Event.h"
#include "Const.h"

int WIDTH = 1240;
int HEIGHT = 720;

int game_init(struct Game* game) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("SDL initialization failed. SDL Error: %s\n", SDL_GetError());
		return -1;
	}
	printf("SDL initialization succeeded!\n");

	game->game_over = false;

	game->window = SDL_CreateWindow("RPG Game",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WIDTH,
		HEIGHT,
		SDL_WINDOW_OPENGL);
	if (game->window == NULL) {
		printf("Could not create window: %s\n", SDL_GetError());
		return -1;
	}
	printf("Window initialization succeeded!\n");

	game->renderer = SDL_CreateRenderer(game->window,
		-1,
		SDL_RENDERER_ACCELERATED);
	if (game->renderer == NULL) {
		printf("Could not create renderer: %s\n", SDL_GetError());
		return -1;
	}
	printf("Renderer initialization succeeded!\n");

	game->screen = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0, 0, 0, 0);
	if (game->screen == NULL) {
		printf("Could not create the screen surface: %s\n", SDL_GetError());
		return -1;
	}
	printf("Create screen surface was successful!\n");

	if (player_init(&game->player) < 0) {
		printf("Failed to initalize player!\n");
		return -1;
	}
	printf("Player initialization succeeded!\n");

	return 0;
}

void game_free(struct Game* game) {
	if (game->player.sprite != NULL) {
		SDL_FreeSurface(game->player.sprite);
	}
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
		printf("Failed to initialize Game!\n");
		game.game_over = true;
		getchar();
	}

	while (!game.game_over) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				event_keyboard(&event.key, &game);
				break;
			case SDL_QUIT:
				game.game_over = true;
				break;
			}
		}

		// TODO: Animate Player

		SDL_FillRect(game.screen, NULL, SDL_MapRGB(game.screen->format, 0, 0, 0));
		if (SDL_BlitSurface(game.player.sprite, NULL, game.screen, &game.player.rect) < 0) {
			printf("Surface blit failed: %s", SDL_GetError());
			game.game_over = true;
		}
		screen = SDL_CreateTextureFromSurface(game.renderer, game.screen);
		SDL_RenderClear(game.renderer);
		SDL_RenderCopy(game.renderer, screen, NULL, NULL);
		SDL_RenderPresent(game.renderer);
		SDL_DestroyTexture(screen);
	}

	printf("Game Over!");
	game_free(&game);
	SDL_Quit();
}