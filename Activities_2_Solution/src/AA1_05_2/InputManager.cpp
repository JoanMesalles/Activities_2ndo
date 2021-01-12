#include "InputManager.h"
InputManager* InputManager::inputManager = nullptr;

void InputManager::Update()
{
	UpdateDeltaTime();
	SetFalseKeyDown();
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			SetKeyValue(InputKeys::QUIT, true);
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) SetKeyValue(InputKeys::ESC, true);

			if (event.key.keysym.sym == SDLK_w) SetKeyValue(InputKeys::W, true);
			if (event.key.keysym.sym == SDLK_s) SetKeyValue(InputKeys::S, true);
			if (event.key.keysym.sym == SDLK_d) SetKeyValue(InputKeys::D, true);
			if (event.key.keysym.sym == SDLK_a) SetKeyValue(InputKeys::A, true);

			if (event.key.keysym.sym == SDLK_UP)    SetKeyValue(InputKeys::UPARROW, true);
			if (event.key.keysym.sym == SDLK_DOWN)  SetKeyValue(InputKeys::DOWNARROW, true);
			if (event.key.keysym.sym == SDLK_RIGHT) SetKeyValue(InputKeys::RIGHTARROW, true);
			if (event.key.keysym.sym == SDLK_LEFT)  SetKeyValue(InputKeys::LEFTARROW, true);

			break;
		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_ESCAPE) SetKeyValue(InputKeys::ESC, false);

			if (event.key.keysym.sym == SDLK_w) SetKeyValue(InputKeys::W, false);
			if (event.key.keysym.sym == SDLK_s) SetKeyValue(InputKeys::S, false);
			if (event.key.keysym.sym == SDLK_d) SetKeyValue(InputKeys::D, false);
			if (event.key.keysym.sym == SDLK_a) SetKeyValue(InputKeys::A, false);

			if (event.key.keysym.sym == SDLK_UP)    SetKeyValue(InputKeys::UPARROW, false);
			if (event.key.keysym.sym == SDLK_DOWN)  SetKeyValue(InputKeys::DOWNARROW, false);
			if (event.key.keysym.sym == SDLK_RIGHT) SetKeyValue(InputKeys::RIGHTARROW, false);
			if (event.key.keysym.sym == SDLK_LEFT)  SetKeyValue(InputKeys::LEFTARROW, false);
			break;
		case SDL_MOUSEMOTION:
			SetMouseCoords(event.motion.x, event.motion.y);
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) SetKeyValue(InputKeys::MOUSE_LEFT, true);
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT) SetKeyValue(InputKeys::MOUSE_LEFT, false);
			break;
		default:;
		}
	}
}

InputManager::InputManager() {

	SetScreenSize(Vec2D(SCREEN_WIDTH, SCREEN_HEIGHT));
}

void InputManager::UpdateDeltaTime()
{
	deltaTime = (clock() - lastTime);
	lastTime = clock();
	deltaTime /= CLOCKS_PER_SEC;
}

void InputManager::SetFalseKeyDown()
{
	for (int i = 0; i < (int)InputKeys::COUNT; i++)
	{
		keyboardDown[i] = false;
	};
}

void InputManager::SetKeyValue(InputKeys key, bool value)
{
	if (!keyboardPressed[(int)key]) {
		keyboardDown[(int)key] = value;
	}
	else {
		keyboardDown[(int)key] = false;
	}
	keyboardPressed[(int)key] = value;
}

InputManager::~InputManager()
{



}

InputManager* InputManager::getInstance()
{
	if (inputManager == nullptr) {
		inputManager = new InputManager;
	}
	return inputManager;
}
