#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <unordered_map>
#include "Types.h"

static const int FPS = 60;
static int minutes = 0;
static int seconds = 0;
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

static float timeDown = 0;
static void setTimeDown(float t) { timeDown = t; };

static Rect RectSDL2My(SDL_Rect r) { return Rect(r.x, r.y, r.w, r.h); }

static SDL_Rect MyRect2SDL(const Rect* r) { return { r->x ,r->y,r->w, r->h }; }

static int linelimit = 175;

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

using MTextures = std::unordered_map<std::string, SDL_Texture*>;
using MRects = std::unordered_map<std::string, SDL_Rect>;

const std::string Txtr_BG_Menu = "BackgroundMenu";
const std::string Txtr_BG_Game = "BackgroundGame";
const std::string Txtr_Cursor = "Cursor";
const std::string Txtr_Players = "Players";
const std::string Txtr_Sacks = "Sacks";
//Menu
const std::string Txtr_BTN_Play = "Play";
const std::string Txtr_BTN_Play_N = "PlayNormal";
const std::string Txtr_BTN_Play_H = "PlayHover";
const std::string Txtr_BTN_Quit = "Quit";
const std::string Txtr_BTN_Quit_N = "QuitNormal";
const std::string Txtr_BTN_Quit_H = "QuitHover";
const std::string Txtr_BTN_Sound = "Sound";
const std::string Txtr_BTN_Sound_On = "SoundOn";
const std::string Txtr_BTN_Sound_Off = "SoundOff";
const std::string Txtr_BTN_Exit = "Exit";
const std::string Txtr_BTN_Exit_N = "ExitNormal";
const std::string Txtr_BTN_Exit_H = "ExitHover";
//In game
const std::string Txtr_Time = "Time";
const std::string Txtr_Text_SC_P1 = "ScorePlayer1";
const std::string Txtr_Text_SC_P2 = "ScorePlayer2";
const std::string Txtr_SC = "Score";
const std::string F_Txtr_SC = "F_Score";

