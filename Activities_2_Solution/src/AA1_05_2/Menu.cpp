#include "Menu.h"

Menu::Menu()
{

	//Background

	Renderer::getInstance()->LoadTexture(Txtr_BG_Menu, "../../res/img/bg.jpg");

	Renderer::getInstance()->LoadRect(Txtr_BG_Menu, Rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));

	Renderer::getInstance()->LoadTexture(Txtr_BG_Game, "../../res/img/bgCastle.jpg");

	Renderer::getInstance()->LoadRect(Txtr_BG_Game, Rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
		//Cursor

	Renderer::getInstance()->LoadTexture(Txtr_Cursor, "../../res/img/kintoun.png");

	Renderer::getInstance()->LoadRect(Txtr_Cursor, Rect(0, 0, 100, 50));

		//Buttons

		//Load fonts

	Renderer::getInstance()->LoadFont(Font(F_Sayian, "../../res/ttf/saiyan.ttf", 80));

		//Play

	Renderer::getInstance()->LoadTextureText(F_Sayian, Text(Txtr_BTN_Play, "Play", Color(0, 255, 0, 255)));

	Renderer::getInstance()->SetTextureFromTexture(Txtr_BTN_Play_N, Txtr_BTN_Play);

	Renderer::getInstance()->LoadTextureText(F_Sayian, Text(Txtr_BTN_Play_H, "Play", Color(255, 0, 0, 255)));

	Renderer::getInstance()->LoadRect(Txtr_BTN_Play, Rect((SCREEN_WIDTH / 2 - Renderer::getInstance()->GetTextureSize(Txtr_BTN_Play).x / 2), 100, Renderer::getInstance()->GetTextureSize(Txtr_BTN_Play).x, Renderer::getInstance()->GetTextureSize(Txtr_BTN_Play).y));
		
		//Quit

	Renderer::getInstance()->LoadTextureText(F_Sayian, Text(Txtr_BTN_Quit, "Quit", Color(0, 255, 0, 255)));

	Renderer::getInstance()->LoadTextureText(F_Sayian, Text(Txtr_BTN_Quit_H, "Quit", Color(255, 0, 0, 255)));

	Renderer::getInstance()->SetTextureFromTexture(Txtr_BTN_Quit_N, Txtr_BTN_Quit);

	Renderer::getInstance()->LoadRect(Txtr_BTN_Quit, Rect((SCREEN_WIDTH / 2 - Renderer::getInstance()->GetTextureSize(Txtr_BTN_Quit).x / 2), 250, Renderer::getInstance()->GetTextureSize(Txtr_BTN_Quit).x, Renderer::getInstance()->GetTextureSize(Txtr_BTN_Quit).y));

		//Sound

	Renderer::getInstance()->LoadTextureText(F_Sayian, Text(Txtr_BTN_Sound_On, "Sound On", Color(255, 140, 0, 255)));

	Renderer::getInstance()->LoadTextureText(F_Sayian, Text(Txtr_BTN_Sound_Off, "Sound Off", Color(255, 69, 0, 255)));

	Renderer::getInstance()->SetTextureFromTexture(Txtr_BTN_Sound, Txtr_BTN_Sound_On);

	Renderer::getInstance()->LoadRect(Txtr_BTN_Sound, Rect((SCREEN_WIDTH / 4 - Renderer::getInstance()->GetTextureSize(Txtr_BTN_Sound).x / 2), 500, Renderer::getInstance()->GetTextureSize(Txtr_BTN_Sound).x, Renderer::getInstance()->GetTextureSize(Txtr_BTN_Sound).y));

	AudioManager::getInstance()->PlayMusic();

}

void Menu::Draw()
{
	Renderer::getInstance()->Clear();

	//Background

	Renderer::getInstance()->PushImage(Txtr_BG_Menu, Txtr_BG_Menu);

	//Text

	Renderer::getInstance()->PushImage(Txtr_BTN_Play, Txtr_BTN_Play);

	Renderer::getInstance()->PushImage(Txtr_BTN_Quit, Txtr_BTN_Quit);

	Renderer::getInstance()->PushImage(Txtr_BTN_Sound, Txtr_BTN_Sound);

	//Cursor
	Renderer::getInstance()->PushImage(Txtr_Cursor, Txtr_Cursor);

	Renderer::getInstance()->Render();

}

void Menu::Update()
{
	InputManager::getInstance()->Update();

	if (InputManager::getInstance()->JustPressed(InputKeys::QUIT) == true) {
		sceneState = ESceneState::GO_EXIT;
	}
	

	Renderer::getInstance()->PlusRectPosition(Txtr_Cursor, (((InputManager::getInstance()->GetMouseCoords().x - (Renderer::getInstance()->GetRect(Txtr_Cursor).w / 2)) - Renderer::getInstance()->GetRect(Txtr_Cursor).x) / 10),
		(((InputManager::getInstance()->GetMouseCoords().y - (Renderer::getInstance()->GetRect(Txtr_Cursor).h / 2)) - Renderer::getInstance()->GetRect(Txtr_Cursor).y) / 10));

	//Play Button
	if (Collisions::ConfirmCollision(InputManager::getInstance()->GetMouseCoords(), Renderer::getInstance()->GetRect(Txtr_BTN_Play))) {
		Renderer::getInstance()->SetTextureFromTexture(Txtr_BTN_Play, Txtr_BTN_Play_H);
		if (InputManager::getInstance()->JustPressed(InputKeys::MOUSE_LEFT)) {
			sceneState = ESceneState::GO_PLAY;
		};
	}
	else {
		Renderer::getInstance()->SetTextureFromTexture(Txtr_BTN_Play, Txtr_BTN_Play_N);
	}

	//Exit Button
	if (Collisions::ConfirmCollision(InputManager::getInstance()->GetMouseCoords(), Renderer::getInstance()->GetRect(Txtr_BTN_Quit))) {
		Renderer::getInstance()->SetTextureFromTexture(Txtr_BTN_Quit, Txtr_BTN_Quit_H);
		if (InputManager::getInstance()->JustPressed(InputKeys::MOUSE_LEFT)) { sceneState = ESceneState::GO_EXIT; }
	}
	else {
		Renderer::getInstance()->SetTextureFromTexture(Txtr_BTN_Quit, Txtr_BTN_Quit_N);
	}

	//Sound Button
	if (Collisions::ConfirmCollision(InputManager::getInstance()->GetMouseCoords(), Renderer::getInstance()->GetRect(Txtr_BTN_Sound))) {

		if (InputManager::getInstance()->JustPressed(InputKeys::MOUSE_LEFT)) {
			if (!AudioManager::getInstance()->GetMusicPaused()) AudioManager::getInstance()->PauseMusic();
			else AudioManager::getInstance()->PlayMusic();
		}

		if (!AudioManager::getInstance()->GetMusicPaused()) {
			Renderer::getInstance()->SetTextureFromTexture(Txtr_BTN_Sound, Txtr_BTN_Sound_On);
		}
		else Renderer::getInstance()->SetTextureFromTexture(Txtr_BTN_Sound, Txtr_BTN_Sound_Off);

	}
	else {
		if (!AudioManager::getInstance()->GetMusicPaused()) {
			Renderer::getInstance()->SetTextureFromTexture(Txtr_BTN_Sound, Txtr_BTN_Sound_On);
		}
		else Renderer::getInstance()->SetTextureFromTexture(Txtr_BTN_Sound, Txtr_BTN_Sound_Off);

	}

	InputManager::getInstance()->UpdateDeltaTime();
}
