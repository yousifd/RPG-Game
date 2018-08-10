#include <stdio.h>

#include "Event.h"

void event_keyboard(SDL_KeyboardEvent* event, struct Game* game) {
	// TODO: Make this more responsive by checking when a key is up and doing other things
	// TODO: Use if statements to allow for multiple keys at the same time
	switch (event->keysym.sym) {
	case SDLK_ESCAPE:
	case SDLK_q:
		game->game_over = true;
		break;
	case SDLK_RIGHT:
	case SDLK_d:
		game->player.rect.x += 2;
		break;
	case SDLK_LEFT:
	case SDLK_a:
		game->player.rect.x -= 2;
		break;
	case SDLK_SPACE:
		game->player.rect.y -= 2;
		// TODO: Slowly fall down?
		break;
	}

	return;
}