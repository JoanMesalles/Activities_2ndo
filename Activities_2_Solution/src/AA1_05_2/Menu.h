#pragma once
#include "Scene.h"
class Menu : public Scene
{
	ESceneState sceneState = ESceneState::RUNNING;

public:
	Menu();
	virtual void Draw();
	virtual void Update();
	virtual ESceneState GetState() { return sceneState; };


};

