#pragma once
#include "Types.h"
#include "Menu.h"
#include "Play.h"
#include "Scene.h"

enum class GameState { PLAYING, MENU, EXIT };

class Game
{
private:
	GameState _gameState;
	Scene* scene;
public:
	Game();
	~Game();

	void Run();

};


