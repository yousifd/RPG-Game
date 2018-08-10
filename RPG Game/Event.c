#include <stdio.h>

#include "Event.h"

void event_keyboard_down(SDL_KeyboardEvent* event, struct Game* game) {
	switch (event->keysym.sym) {
	case SDLK_ESCAPE:
	case SDLK_q:
		game->game_over = true;
		break;
	case SDLK_RIGHT:
	case SDLK_d:
		game->player.xvel = 2;
		break;
	case SDLK_LEFT:
	case SDLK_a:
		game->player.xvel = -2;
		break;
	case SDLK_UP:
	case SDLK_SPACE:
	case SDLK_w:
		game->player.yvel = -2;
		break;
	case SDLK_DOWN:
	case SDLK_s:
		game->player.yvel = 2;
		break;
	}
}

void event_keyboard_up(SDL_KeyboardEvent* event, struct Game* game) {
	switch (event->keysym.sym) {
	case SDLK_RIGHT:
	case SDLK_d:
		if (game->player.xvel > 0) {
			game->player.xvel = 0;
		}
		break;
	case SDLK_LEFT:
	case SDLK_a:
		if (game->player.xvel < 0) {
			game->player.xvel = 0;
		}
		break;
	case SDLK_UP:
	case SDLK_SPACE:
	case SDLK_w:
		if (game->player.yvel < 0) {
			game->player.yvel = 0;
		}
		break;
	case SDLK_DOWN:
	case SDLK_s:
		if (game->player.yvel > 0) {
			game->player.yvel = 0;
		}
		break;
	}
}