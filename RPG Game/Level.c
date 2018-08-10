#include <stdlib.h>

#include "Level.h"
#include "Const.h"
#include "Log.h"

static int id = 0;

int level_init(struct Level* level, char* name, const char* level_bitmap_file) {
	level->id = id++;
	level->name = name;

	level->bitmap = SDL_LoadBMP(level_bitmap_file);
	if (level->bitmap == NULL) {
		log_error("Failed to load level bitmap file: %s", SDL_GetError());
		return -1;
	}

	level->rect.x = 0;
	level->rect.y = (HEIGHT / 2) + 100;
	level->rect.w = level->bitmap->clip_rect.w;
	level->rect.h = level->bitmap->clip_rect.h;

	collider_init(&level->collider, &level->rect);

	return 0;
}

void level_free(struct Level* level) {
	free(level->name);
	SDL_FreeSurface(level->bitmap);
	free(level);
}