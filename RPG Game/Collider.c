#include "Collider.h"
#include "Log.h"

int collider_init(struct Collider* collider, const SDL_Rect* rect) {
	collider->rect = rect;
	collider->colliding = false;

	log_info("Initializing collider:\nX: %d Y: %d\nWidth: %d, Height: %d", rect->x, rect->y, rect->w, rect->h);

	return 0;
}

bool collider_check(const struct Collider* a, const struct Collider* b) {
	//log_debug("Check collider a:\nX: %d Y: %d\nWidth: %d, Height: %d", a->rect->x, a->rect->y, a->rect->w, a->rect->h);
	//log_debug("Check collider b:\nX: %d Y: %d\nWidth: %d, Height: %d", b->rect->x, b->rect->y, b->rect->w, b->rect->h);
	int leftA = a->rect->x;
	int rightA = leftA + a->rect->w;
	int topA = a->rect->y;
	int bottomA = topA + a->rect->h;
	
	int leftB = b->rect->x;
	int rightB = leftB + b->rect->w;
	int topB = b->rect->y;
	int bottomB = topB + b->rect->h;
	return !(leftB > rightA ||
		rightB < leftA ||
		topB > bottomA ||
		bottomB < topA);
}