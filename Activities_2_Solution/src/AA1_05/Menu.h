#pragma once
#include "Scene.h"
class Menu : public Scene
{
	ESceneState sceneState;

public:
	Menu();
	virtual void Draw();
	virtual void Update();


};

