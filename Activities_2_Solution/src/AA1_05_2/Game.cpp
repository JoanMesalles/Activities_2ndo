#include "Game.h"

Game::Game()
{
	srand(time(NULL));

	_gameState = GameState::MENU;
	
	scene = new Menu();

}

Game::~Game()
{
	delete scene;
	scene = nullptr;
}

void Game::Run()
{

	while (_gameState != GameState::EXIT)
	{
		switch (_gameState)
		{
		case GameState::PLAYING:
			switch (scene->GetState())
			{
			case ESceneState::GO_MENU:
				delete scene;
				scene = nullptr;
				scene = new Menu();
				_gameState = GameState::MENU;
				break;
			case ESceneState::GO_EXIT:
				_gameState = GameState::EXIT;
				break;
			default:
				scene->Update();
				scene->Draw();
				break;
			}
		case GameState::MENU:
			switch (scene->GetState())
			{
			case ESceneState::GO_PLAY:
				delete scene;
				scene = nullptr;
				scene = new Play();
				_gameState = GameState::PLAYING;
				break;
			case ESceneState::GO_EXIT:
				_gameState = GameState::EXIT;
				break;
			default:
				scene->Update();
				scene->Draw();
				break;
			}
			break;
		default:
			break;
		}
	}
}

