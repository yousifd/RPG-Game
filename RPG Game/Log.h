#pragma once

#include <SDL_log.h>
#include <string.h>

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#define log_info(fmt, ...) SDL_Log("%s:%d " fmt, __FILENAME__, __LINE__, __VA_ARGS__);
#define log_debug(fmt, ...) SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "%s:%d " fmt, __FILE__, __LINE__, __VA_ARGS__);
#define log_error(fmt, ...) SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s:%d " fmt, __FILE__, __LINE__, __VA_ARGS__);