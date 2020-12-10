#include "Menu.h"

Menu::Menu()
{

	//Background

	//renderer.LoadTexture(Txtr_BG_Menu, "../../res/img/bg.jpg");
	Renderer::G

	//renderer.LoadRect(Txtr_BG_Menu, Rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));

	//renderer.LoadTexture(Txtr_BG_Game, "../../res/img/bgCastle.jpg");

	//renderer.LoadRect(Txtr_BG_Game, Rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));

	//Cursor

	//renderer.LoadTexture(Txtr_Cursor, "../../res/img/kintoun.png");

	//renderer.LoadRect(Txtr_Cursor, Rect(0, 0, 100, 50));

	//Buttons

	//Load fonts
	//renderer.LoadFont(Font(F_Sayian, "../../res/ttf/saiyan.ttf", 80));

	//Play

	//renderer.LoadTextureText(F_Sayian, Text(Txtr_BTN_Play, "Play", Color(0, 255, 0, 255)));

	//renderer.SetTextureFromTexture(Txtr_BTN_Play_N, Txtr_BTN_Play);

	//renderer.LoadTextureText(F_Sayian, Text(Txtr_BTN_Play_H, "Play", Color(255, 0, 0, 255)));

	//renderer.LoadRect(Txtr_BTN_Play, Rect((SCREEN_WIDTH / 2 - renderer.GetTextureSize(Txtr_BTN_Play).x / 2), 100, renderer.GetTextureSize(Txtr_BTN_Play).x, renderer.GetTextureSize(Txtr_BTN_Play).y));

	//Quit

	//renderer.LoadTextureText(F_Sayian, Text(Txtr_BTN_Quit, "Quit", Color(0, 255, 0, 255)));

	//renderer.LoadTextureText(F_Sayian, Text(Txtr_BTN_Quit_H, "Quit", Color(255, 0, 0, 255)));

	//renderer.SetTextureFromTexture(Txtr_BTN_Quit_N, Txtr_BTN_Quit);

	//renderer.LoadRect(Txtr_BTN_Quit, Rect((SCREEN_WIDTH / 2 - renderer.GetTextureSize(Txtr_BTN_Quit).x / 2), 250, renderer.GetTextureSize(Txtr_BTN_Quit).x, renderer.GetTextureSize(Txtr_BTN_Quit).y));

	//Sound

	//renderer.LoadTextureText(F_Sayian, Text(Txtr_BTN_Sound_On, "Sound On", Color(255, 140, 0, 255)));

	//renderer.LoadTextureText(F_Sayian, Text(Txtr_BTN_Sound_Off, "Sound Off", Color(255, 69, 0, 255)));

	//renderer.SetTextureFromTexture(Txtr_BTN_Sound, Txtr_BTN_Sound_On);

	//renderer.LoadRect(Txtr_BTN_Sound, Rect((SCREEN_WIDTH / 4 - renderer.GetTextureSize(Txtr_BTN_Sound).x / 2), 500, renderer.GetTextureSize(Txtr_BTN_Sound).x, renderer.GetTextureSize(Txtr_BTN_Sound).y));

}

void Menu::Draw()
{
	renderer.Clear();

	//Background

	renderer.PushImage(Txtr_BG_Menu, Txtr_BG_Menu);

	//Text

	renderer.PushImage(Txtr_BTN_Play, Txtr_BTN_Play);

	renderer.PushImage(Txtr_BTN_Quit, Txtr_BTN_Quit);

	renderer.PushImage(Txtr_BTN_Sound, Txtr_BTN_Sound);

	//Cursor
	renderer.PushImage(Txtr_Cursor, Txtr_Cursor);

	renderer.Render();

}

void Menu::Update()
{
	if (input.JustPressed(InputKeys::QUIT) == true) {
		_gameState = GameState::EXIT;
	}

	renderer.PlusRectPosition(Txtr_Cursor, (((input.GetMouseCoords().x - (renderer.GetRect(Txtr_Cursor).w / 2)) - renderer.GetRect(Txtr_Cursor).x) / 10),
		(((input.GetMouseCoords().y - (renderer.GetRect(Txtr_Cursor).h / 2)) - renderer.GetRect(Txtr_Cursor).y) / 10));

	//Play Button
	if (Collisions::ConfirmCollision(input.GetMouseCoords(), renderer.GetRect(Txtr_BTN_Play))) {
		renderer.SetTextureFromTexture(Txtr_BTN_Play, Txtr_BTN_Play_H);
		if (input.JustPressed(InputKeys::MOUSE_LEFT)) {
			_gameState = GameState::PLAYING;
		};
	}
	else {
		renderer.SetTextureFromTexture(Txtr_BTN_Play, Txtr_BTN_Play_N);
	}

	//Exit Button
	if (Collisions::ConfirmCollision(input.GetMouseCoords(), renderer.GetRect(Txtr_BTN_Quit))) {
		renderer.SetTextureFromTexture(Txtr_BTN_Quit, Txtr_BTN_Quit_H);
		if (input.JustPressed(InputKeys::MOUSE_LEFT)) { _gameState = GameState::EXIT; }
	}
	else {
		renderer.SetTextureFromTexture(Txtr_BTN_Quit, Txtr_BTN_Quit_N);
	}
	//Sound Button
	if (Collisions::ConfirmCollision(input.GetMouseCoords(), renderer.GetRect(Txtr_BTN_Sound))) {

		if (input.JustPressed(InputKeys::MOUSE_LEFT)) {
			if (!AudioManager::getInstance()->GetMusicPaused()) AudioManager::getInstance()->PauseMusic();
			else AudioManager::getInstance()->PlayMusic();
		}

		if (!AudioManager::getInstance()->GetMusicPaused()) {
			renderer.SetTextureFromTexture(Txtr_BTN_Sound, Txtr_BTN_Sound_On);
		}
		else renderer.SetTextureFromTexture(Txtr_BTN_Sound, Txtr_BTN_Sound_Off);

	}
	else {
		if (!AudioManager::getInstance()->GetMusicPaused()) {
			renderer.SetTextureFromTexture(Txtr_BTN_Sound, Txtr_BTN_Sound_On);
		}
		else renderer.SetTextureFromTexture(Txtr_BTN_Sound, Txtr_BTN_Sound_Off);

	}

	input.UpdateDeltaTime();
}
