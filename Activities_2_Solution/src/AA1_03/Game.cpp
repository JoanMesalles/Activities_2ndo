#include "Game.h"

Game::Game()
{
	srand(time(NULL));

	timeDown = totalGameTime = 80.f;

	_gameState = GameState::MENU;

	AudioManager::getInstance()->PlayMusic();
}

Game::~Game()
{
}

void Game::Run()
{

	while (_gameState != GameState::EXIT)
	{

		UpdateInput();
		switch (_gameState)
		{
		case GameState::PLAYING:
			if (timeDown <= 0.f) _gameState = GameState::MENU;
			if (input.JustPressed(InputKeys::QUIT) == true) {
				_gameState = GameState::EXIT;
			}
			if (input.JustPressed(InputKeys::ESC)) {
				ResetGame();
				_gameState = GameState::MENU;
			}
			UpdateGame();
			RenderGame();
			break;
		case GameState::MENU:
			UpdateMenu();
			RenderMenu();
			break;
		default:
			break;
		}
	}
}

void Game::ResetGame()
{
	for (Player* pi : players) {
		pi->SetScore(0);
		pi->Reset();
	}
	timeDown = totalGameTime;


}






