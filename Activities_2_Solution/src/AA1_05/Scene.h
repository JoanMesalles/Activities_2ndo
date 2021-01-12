#pragma once
#include "Types.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "Renderer.h"
#include "Collisions.h"

class Scene
{
	ESceneState sceneState; 

public:
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual ESceneState GetState() = 0;
	virtual ~Scene();

};

