#pragma once

#include <SDL_rect.h>
#include <stdbool.h>

struct Collider {
	const SDL_Rect* rect;
	bool colliding;
};

int collider_init(struct Collider* collider, const SDL_Rect* rect);

bool collider_check(const struct Collider* a, const struct Collider* b);