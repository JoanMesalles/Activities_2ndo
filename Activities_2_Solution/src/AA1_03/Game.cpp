#include "Game.h"

Game::Game()
{
	srand(time(NULL));
	//m_window = nullptr;
	//m_renderer = nullptr;


	timeDown = totalGameTime = 80.f;

	_gameState = GameState::MENU;

	//InitSDL();

	//Music
	//-->SDL_Mix


	input = InputData();
	input.SetScreenSize(Vec2D(SCREEN_WIDTH, SCREEN_HEIGHT));

}

Game::~Game()
{
	//renderer.~Renderer();
	//SDL_FreeSurface(surfTimer);
	//TTF_CloseFont(font_timmer);
	//DestroyAllTextures();
	//CloseSDL();
}

void Game::Run()
{
	InitMenu();
	InitGame();

	while (_gameState != GameState::EXIT)
	{

		UpdateInput();
		switch (_gameState)
		{
		case GameState::PLAYING:
			UpdateGame();
			RenderGame();
			break;
		case GameState::MENU:
			UpdateMenu();
			RenderMenu();
			break;
		default:
			break;
		}
	}
}

void Game::InitMenu()
{

	//Background

	renderer.LoadTexture(Txtr_BG_Menu, "../../res/img/bg.jpg");

	renderer.LoadRect(Txtr_BG_Menu, Rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));

	renderer.LoadTexture(Txtr_BG_Game, "../../res/img/bgCastle.jpg");

	renderer.LoadRect(Txtr_BG_Game, Rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));

	//Cursor

	renderer.LoadTexture(Txtr_Cursor, "../../res/img/kintoun.png");

	renderer.LoadRect(Txtr_Cursor, Rect(0, 0, 100, 50));

	//Buttons

	//Load fonts
	renderer.LoadFont(Font(F_Sayian,"../../res/ttf/saiyan.ttf",80));
	
	//Play

	renderer.LoadTextureText(F_Sayian, Text(Txtr_BTN_Play, "Play", Color(0, 255, 0, 255)));

	renderer.SetTextureFromTexture(Txtr_BTN_Play_N, Txtr_BTN_Play);

	renderer.LoadTextureText(F_Sayian, Text(Txtr_BTN_Play_H, "Play", Color(255, 0, 0, 255)));

	renderer.LoadRect(Txtr_BTN_Play, Rect((SCREEN_WIDTH / 2 - renderer.GetTextureSize(Txtr_BTN_Play).x / 2), 100, renderer.GetTextureSize(Txtr_BTN_Play).x, renderer.GetTextureSize(Txtr_BTN_Play).y));

	//Quit

	renderer.LoadTextureText(F_Sayian, Text(Txtr_BTN_Quit, "Quit", Color(0, 255, 0, 255)));

	renderer.LoadTextureText(F_Sayian, Text(Txtr_BTN_Quit_H, "Quit", Color(255, 0, 0, 255)));

	renderer.SetTextureFromTexture(Txtr_BTN_Quit_N, Txtr_BTN_Quit);

	renderer.LoadRect(Txtr_BTN_Quit, Rect((SCREEN_WIDTH / 2 - renderer.GetTextureSize(Txtr_BTN_Quit).x / 2), 250, renderer.GetTextureSize(Txtr_BTN_Quit).x, renderer.GetTextureSize(Txtr_BTN_Quit).y));

	//Sound

	renderer.LoadTextureText(F_Sayian, Text(Txtr_BTN_Sound_On, "Sound On", Color(255, 140, 0, 255)));

	renderer.LoadTextureText(F_Sayian, Text(Txtr_BTN_Sound_Off, "Sound Off", Color(255, 69, 0, 255)));

	renderer.SetTextureFromTexture(Txtr_BTN_Sound, Txtr_BTN_Sound_On);

	renderer.LoadRect(Txtr_BTN_Sound, Rect((SCREEN_WIDTH / 4 - renderer.GetTextureSize(Txtr_BTN_Sound).x / 2), 500, renderer.GetTextureSize(Txtr_BTN_Sound).x, renderer.GetTextureSize(Txtr_BTN_Sound).y));

}

void Game::InitGame()
{
	//Players

	renderer.LoadTexture(Txtr_Players, "../../res/img/spCastle.png");

	AddPlayer(renderer.GetTextureSize(Txtr_Players).x, renderer.GetTextureSize(Txtr_Players).y,Player::PlayerType::PL1);
	AddPlayer(renderer.GetTextureSize(Txtr_Players).x, renderer.GetTextureSize(Txtr_Players).y, Player::PlayerType::PL2);

	// Sacks

	renderer.LoadTexture(Txtr_Sacks, "../../res/img/gold.png");

	for (int i = 0; i < 10; i++) {
		AddSacks();
	}

	//Score

	renderer.LoadTexture(Txtr_SC, "../../res/img/num.png");

	renderer.LoadRect(Txtr_SC, Rect(50, 5, (renderer.GetTextureSize(Txtr_SC).x/10)/2, renderer.GetTextureSize(Txtr_SC).y/2));
	renderer.LoadRect(F_Txtr_SC, Rect(0, 0, renderer.GetTextureSize(Txtr_SC).x/10, renderer.GetTextureSize(Txtr_SC).y));


#pragma endregion
	//Timmer
	renderer.LoadFont(Font(F_Timmer, "../../res/ttf/mono.ttf", 25));

	renderer.LoadTextureText(F_Timmer, Text(Txtr_Time, "Time: ", Color(0, 0, 0, 255)));

	renderer.LoadRect(Txtr_Time, Rect(SCREEN_WIDTH - 150, 10, renderer.GetTextureSize(Txtr_Time).x, renderer.GetTextureSize(Txtr_Time).y));

	//UI

	renderer.LoadTextureText(F_Timmer, Text(Txtr_Text_SC_P1, "P1: ", Color(0, 0, 0, 255)));

	renderer.LoadRect(Txtr_Text_SC_P1, Rect(10, 10, renderer.GetTextureSize(Txtr_Text_SC_P1).x, renderer.GetTextureSize(Txtr_Text_SC_P1).y));

	renderer.LoadTextureText(F_Timmer, Text(Txtr_Text_SC_P2, "P2: ", Color(0, 0, 0, 255)));

	renderer.LoadRect(Txtr_Text_SC_P2, Rect(10, 50, renderer.GetTextureSize(Txtr_Text_SC_P2).x, renderer.GetTextureSize(Txtr_Text_SC_P2).y));


}

void Game::UpdateInput()
{
	input.UpdateDeltaTime();
	input.SetFalseKeyDown();
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{

		switch (event.type)
		{
		case SDL_QUIT:
			input.SetKeyValue(InputKeys::QUIT, true);
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) input.SetKeyValue(InputKeys::ESC, true);

			if (event.key.keysym.sym == SDLK_w) input.SetKeyValue(InputKeys::W, true);
			if (event.key.keysym.sym == SDLK_s) input.SetKeyValue(InputKeys::S, true);
			if (event.key.keysym.sym == SDLK_d) input.SetKeyValue(InputKeys::D, true);
			if (event.key.keysym.sym == SDLK_a) input.SetKeyValue(InputKeys::A, true);

			if (event.key.keysym.sym == SDLK_UP)    input.SetKeyValue(InputKeys::UPARROW, true);
			if (event.key.keysym.sym == SDLK_DOWN)  input.SetKeyValue(InputKeys::DOWNARROW, true);
			if (event.key.keysym.sym == SDLK_RIGHT) input.SetKeyValue(InputKeys::RIGHTARROW, true);
			if (event.key.keysym.sym == SDLK_LEFT)  input.SetKeyValue(InputKeys::LEFTARROW, true);

			break;
		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_ESCAPE) input.SetKeyValue(InputKeys::ESC, false);

			if (event.key.keysym.sym == SDLK_w) input.SetKeyValue(InputKeys::W, false);
			if (event.key.keysym.sym == SDLK_s) input.SetKeyValue(InputKeys::S, false);
			if (event.key.keysym.sym == SDLK_d) input.SetKeyValue(InputKeys::D, false);
			if (event.key.keysym.sym == SDLK_a) input.SetKeyValue(InputKeys::A, false);

			if (event.key.keysym.sym == SDLK_UP)    input.SetKeyValue(InputKeys::UPARROW, false);
			if (event.key.keysym.sym == SDLK_DOWN)  input.SetKeyValue(InputKeys::DOWNARROW, false);
			if (event.key.keysym.sym == SDLK_RIGHT) input.SetKeyValue(InputKeys::RIGHTARROW, false);
			if (event.key.keysym.sym == SDLK_LEFT)  input.SetKeyValue(InputKeys::LEFTARROW, false);
			break;
		case SDL_MOUSEMOTION:
			input.SetMouseCoords(event.motion.x, event.motion.y);
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) input.SetKeyValue(InputKeys::MOUSE_LEFT, true);
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT) input.SetKeyValue(InputKeys::MOUSE_LEFT, false);
			break;
		default:;
		}
	}
}

void Game::UpdateMenu()
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
			_gameState = GameState::PLAYING; };
	}
	else{ 
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
			if (!audioManager.GetMusicPaused()) audioManager.PauseMusic();
			else audioManager.PlayMusic();
		}

		if (audioManager.GetMusicPaused()) {
			renderer.SetTextureFromTexture(Txtr_BTN_Sound, Txtr_BTN_Sound_Off);
		}else renderer.SetTextureFromTexture(Txtr_BTN_Sound, Txtr_BTN_Sound_On);

	}
	else {
		if (!Mix_PausedMusic()) {
			renderer.SetTextureFromTexture(Txtr_BTN_Sound, Txtr_BTN_Sound_On);
		}
		else renderer.SetTextureFromTexture(Txtr_BTN_Sound, Txtr_BTN_Sound_Off);

	}

	input.UpdateDeltaTime();

}

void Game::UpdateGame()
{

	if (input.JustPressed(InputKeys::QUIT) == true) {
		_gameState = GameState::EXIT;
	}

	if (input.JustPressed(InputKeys::ESC)) {
		ResetGame();
		_gameState = GameState::MENU;
	}
	for (Player* pi : players) {
		pi->Update(&input, sacks,players);
	}

	//Update Timer
	if (_gameState == GameState::PLAYING) {

		timeDown -= *input.GetDeltaTime();

	}
	if (timeDown <= 0.f) _gameState = GameState::MENU;
	else {
		std::string s = F2StrFormat(timeDown, 0);

		renderer.LoadTextureText(F_Timmer, Text(Txtr_Time, s.c_str(), Color(0, 0, 0, 255)));

		renderer.LoadRect(Txtr_Time, Rect(SCREEN_WIDTH - 100, 10, renderer.GetTextureSize(Txtr_Time).x, renderer.GetTextureSize(Txtr_Time).y));
	}
}

void Game::RenderMenu()
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

void Game::RenderGame()
{
	renderer.Clear();

	//BG
	renderer.PushImage(Txtr_BG_Game, Txtr_BG_Game);

	//Players 
	for (Player* p : players) {
		renderer.PushSprite(Txtr_Players, p->GetFrame(), p->GetPosition());

	}

	for (int i = 0; i < players.size(); i++) {

		Player* pl = players.at(i);

		renderer.PushSprite(Txtr_SC, &Rect(trunc((pl->GetScore()) * 0.1) * renderer.GetRect(F_Txtr_SC).w, 0, renderer.GetRect(F_Txtr_SC).w, renderer.GetRect(F_Txtr_SC).h),
			&Rect(renderer.GetRect(Txtr_SC).x, renderer.GetRect(Txtr_SC).y + (renderer.GetRect(Txtr_SC).h * i), renderer.GetRect(Txtr_SC).w, renderer.GetRect(Txtr_SC).h));

		renderer.PushSprite(Txtr_SC, &Rect(trunc((pl->GetScore()) % 10) * renderer.GetRect(F_Txtr_SC).w, 0, renderer.GetRect(F_Txtr_SC).w, renderer.GetRect(F_Txtr_SC).h),
			&Rect(renderer.GetRect(Txtr_SC).x + (renderer.GetRect(Txtr_SC).w * 1), renderer.GetRect(Txtr_SC).y + (renderer.GetRect(Txtr_SC).h * i), renderer.GetRect(Txtr_SC).w, renderer.GetRect(Txtr_SC).h));
	}

	//Sacks
	for (Sack* sack : sacks) {
		renderer.PushImage(Txtr_Sacks, sack->GetPosition());
	}

	//UI

	renderer.PushImage(Txtr_Time, Txtr_Time);

	renderer.PushImage(Txtr_Text_SC_P1, Txtr_Text_SC_P1);

	renderer.PushImage(Txtr_Text_SC_P2, Txtr_Text_SC_P2);

	renderer.Render();
}


void Game::ResetGame()
{
	for (Player* pi : players) {
		pi->SetScore(0);
		//pi->reset
	}
	timeDown = totalGameTime;


}

void Game::AddPlayer(int texWidth, int texHeight, Player::PlayerType type)
{
	Player* p = new Player();
	p->SetPlayerValues(texWidth, texHeight, 12, 8, type);
	players.push_back(std::move(p));
}

void Game::AddSacks()
{
	Vec2D randomPos = Vec2D::randomVec(150, SCREEN_WIDTH < SCREEN_HEIGHT ? SCREEN_WIDTH - 100 : SCREEN_HEIGHT - 100);
	Sack* s = new Sack(40, 30, randomPos.x, randomPos.y);
	sacks.push_back(std::move(s));
}


