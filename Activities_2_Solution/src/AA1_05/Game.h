#pragma once

#include "Player.h"
#include "Sack.h" 
#include "Renderer.h"
#include "AudioManager.h"

class Game
{
private:
	GameState _gameState;
	InputData input;

	Renderer renderer;

	std::vector<Player*> players;
	std::vector<Sack*> sacks;
	float timeDown, totalGameTime;

	std::string s  = F2StrFormat(timeDown, 0);

public:
	Game();
	~Game();

	void Run();

private:

	void InitMenu();
	void InitGame();

	void UpdateInput();
	void UpdateMenu();
	void UpdateGame();

	void RenderMenu();
	void RenderGame();

	void ResetGame();
	void AddPlayer(int texWidth, int texHeight, Player::PlayerType type);
	void AddSacks();
};

