#pragma once
#include <SDL.h>
#include "Types.h"


class InputManager
{
	static InputManager* inputManager;

	bool keyboardPressed[(int)InputKeys::COUNT] = {};
	bool keyboardDown[(int)InputKeys::COUNT] = {};
	Vec2D mouseCoords;
	Vec2D screenSize;
	InputManager();

public:

	void Update();

	Vec2D GetMouseCoords() { return mouseCoords; };

	void SetMouseCoords(Vec2D v) { mouseCoords.setPoints(v); };

	void SetMouseCoords(int x, int y) { mouseCoords = { x,y }; };

	bool IsPressed(InputKeys key) { return keyboardPressed[(int)key]; }

	bool JustPressed(InputKeys key) { return keyboardDown[(int)key]; }

	void SetScreenSize(Vec2D size) { screenSize = size; };

	Vec2D* GetScreenSize() { return &screenSize; };

	clock_t lastTime = clock();

	float deltaTime = 0.f;

	void UpdateDeltaTime();

	inline const float* GetDeltaTime() const { return &deltaTime; };

	void SetFalseKeyDown();

	void SetKeyValue(InputKeys key, bool value);

	~InputManager();

	static InputManager* getInstance();

};

