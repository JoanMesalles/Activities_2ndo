#pragma once

#include "Types.h"

static void setTimeDown(float t) { timeDown = t; };

static Rect RectSDL2My(SDL_Rect r) { return Rect(r.x, r.y, r.w, r.h); }

static SDL_Rect MyRect2SDL(const Rect* r) { return { r->x ,r->y,r->w, r->h }; }

static std::string F2StrFormat(int num, int decimals) {

	std::stringstream ss;
	if (num >= 60) {
		minutes = num / 60;
		num = num % 60;
		seconds = num;
	}
	else {
		minutes = 0;
		seconds = num;
	}
	ss << std::fixed << std::setprecision(decimals) << minutes << ":" << seconds;
	return static_cast<std::string>(ss.str());
}


