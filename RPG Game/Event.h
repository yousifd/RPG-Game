#pragma once

#include <SDL_events.h>
#include "Game.h"

void event_keyboard_down(SDL_KeyboardEvent* event, struct Game* game);

void event_keyboard_up(SDL_KeyboardEvent* event, struct Game* game);