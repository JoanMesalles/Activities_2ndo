#pragma once

#include "AudioManager.h"
#include "Types.h"
#include "Scene.h"

enum class GameState { PLAYING, MENU, EXIT };

class Game
{
private:
	GameState _gameState;
	float timeDown, totalGameTime;

	std::string s  = F2StrFormat(timeDown, 0);

public:
	Game();
	~Game();

	void Run();

private:

	void UpdateInput();
	void ResetGame();

};

