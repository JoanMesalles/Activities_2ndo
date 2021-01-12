#pragma once
#include "Scene.h"
#include "Player.h"
#include "Sack.h"

class Play : public Scene
{
	ESceneState sceneState;
	std::vector<Player*> players;
	std::vector<Sack*> sacks;
	void AddSacks();
	void AddPlayer(int texWidth, int texHeight, Player::PlayerType type);

public:
	Play();
	virtual void Draw();
	virtual void Update();
};

