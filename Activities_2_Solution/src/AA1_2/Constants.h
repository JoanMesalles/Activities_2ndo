#pragma once
#include <math.h>
#include <SDL.h>
#include <time.h>
#include <vector>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <exception>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <unordered_map>

static const int FPS = 60;
static int minutes = 0;
static int seconds = 0;
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
static float timeDown = 0;
static int linelimit = 175;


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


