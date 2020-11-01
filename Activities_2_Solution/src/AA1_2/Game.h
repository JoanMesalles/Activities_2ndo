#pragma once

#include "Player.h"
#include "Sack.h"
//#include "Constants.h"

class Game
{
private:
	GameState _gameState;
	InputData input;

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	std::vector<Player*> players;
	std::vector<Sack*> sacks;
	float timeDown, totalGameTime;

	MTextures _Textures;
	MRects _Rects;
	TTF_Font* font_timmer = nullptr;
	SDL_Surface* surfTimer = nullptr;
	Mix_Music* soundtrack = nullptr;

public:
	Game();
	~Game();

	void Run();

private:

	void InitSDL();
	void InitMenu();
	void InitGame();

	void UpdateInput();
	void UpdateMenu();
	void UpdateGame();

	void RenderMenu();
	void RenderGame();

	void CloseSDL();
	void DestroyAllTextures();

	void ResetGame();
	void AddPlayer(int texWidth, int texHeight, Player::PlayerType type);
	void AddSacks();
};

