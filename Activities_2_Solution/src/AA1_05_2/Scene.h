#pragma once
#include "Types.h"
#include "InputManager.h"
#include "Renderer.h"
#include "Collisions.h"
#include "AudioManager.h"

class Scene
{
	ESceneState sceneState;
	
	
public:
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual ESceneState GetState() { return sceneState; };
	virtual ~Scene();

};
