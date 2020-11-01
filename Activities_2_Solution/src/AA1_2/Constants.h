#pragma once
#include <unordered_map>
#include "Types.h"
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
const std::string Txtr_BTN_Sound_0n = "SoundOn";
const std::string Txtr_BTN_Sound_Off = "SoundOff";
const std::string Txtr_BTN_Exit = "Exit";
const std::string Txtr_BTN_Quit_N = "ExitNormal";
const std::string Txtr_BTN_Quit_H = "ExitHover";
//In game
const std::string Txtr_Time = "Time";
const std::string Txtr_Text_SC_P1 = "ScorePlayer1";
const std::string Txtr_Text_SC_P2 = "ScorePlayer2";
const std::string Txtr_SC = "Score";


const std::string Rect_BG_Menu = "BackgroundMenu";
const std::string Rect_BG_Game = "BackgroundGame";
const std::string Rect_Cursor = "Cursor";
const std::string Rect_Players = "Players";
const std::string Rect_Sacks = "Sacks";
//Menu
const std::string Rect_BTN_Play = "Play";
const std::string Rect_BTN_Play_N = "PlayNormal";
const std::string Rect_BTN_Play_H = "PlayHover";
const std::string Rect_BTN_Quit = "Quit";
const std::string Rect_BTN_Quit_N = "QuitNormal";
const std::string Rect_BTN_Quit_H = "QuitHover";
const std::string Rect_BTN_Sound = "Sound";
const std::string Rect_BTN_Sound_0n = "SoundOn";
const std::string Rect_BTN_Sound_Off = "SoundOff";
const std::string Rect_BTN_Exit = "Exit";
const std::string Rect_BTN_Quit_N = "ExitNormal";
const std::string Rect_BTN_Quit_H = "ExitHover";
//In game
const std::string Rect_Time = "Time";
const std::string Rect_Text_SC_P1 = "ScorePlayer1";
const std::string Rect_Text_SC_P2 = "ScorePlayer2";
const std::string Rect_SC = "Score";


