#include <SDL_log.h>
#include <stdarg.h>

#include "Log.h"

void log_info(const char* fmt, ...) {
	va_list args;
	va_start(args, fmt);

	va_end(args);
}

void log_warn(const char* fmt, ...) {

}

void log_error(const char* fmt, ...) {

}

void log_debug(const char* fmt, ...) {

}