#pragma once
#include "Scene.h"
#include "Sack.h"
#include "Player.h"


class Play : public Scene
{
	ESceneState sceneState = ESceneState::RUNNING;
	std::vector<Player*> players;
	std::vector<Sack*> sacks;
	void AddSacks();
	void AddPlayer(int texWidth, int texHeight, Player::PlayerType type);
	float timeDown = 80.f;
	std::string s = F2StrFormat(timeDown, 0);


public:
	Play();
	virtual void Draw();
	virtual void Update();
	virtual ESceneState GetState() { return sceneState; };
	~Play();
};

