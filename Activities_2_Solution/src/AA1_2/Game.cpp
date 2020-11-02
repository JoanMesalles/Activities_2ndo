#include "Game.h"

Game::Game()
{
	srand(time(NULL));
	m_window = nullptr;
	m_renderer = nullptr;


	timeDown = totalGameTime = 80.f;

	_gameState = GameState::MENU;

	InitSDL();

	//Music
	soundtrack = { Mix_LoadMUS("../../res/au/mainTheme.mp3") };
	if (!soundtrack) throw "No s'ha pogut carregar l'audio";
	Mix_PlayMusic(soundtrack, -1);
	Mix_VolumeMusic(100);

	input = InputData();
	input.SetScreenSize(Vec2D(SCREEN_WIDTH, SCREEN_HEIGHT));

}

Game::~Game()
{
	SDL_FreeSurface(surfTimer);
	TTF_CloseFont(font_timmer);
	DestroyAllTextures();
	CloseSDL();
}

void Game::Run()
{
	InitMenu();
	InitGame();

	// --- GAME VARIABLES ---
	bool isKeySPressed = false;
	bool rightmousePressed = false;
	// --- GAME LOOP ---
	SDL_Event event;
	bool isRunning = true;

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

void Game::InitSDL()
{


	// --- INIT SDL ---
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		throw "No es pot inicialitzar SDL subsystems";

	// --- WINDOW ---
	m_window = SDL_CreateWindow("SDL...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (m_window == nullptr)
		throw "No es pot inicialitzar SDL_Window";

	// --- RENDERER ---
	m_renderer = { SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) };
	if (m_renderer == nullptr)
		throw "No es pot inicialitzar SDL_Renderer";

	//Initialize renderer color
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);

	//Music

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		throw "No s'ha pogut inicialitzar SDL_Mixer";
	}


	//-->SDL_Image
	const Uint8 imgFlags{ IMG_INIT_PNG | IMG_INIT_JPG };
	if (!(IMG_Init(imgFlags) & imgFlags))
		throw "Error: SDL_image init";

	//-->SDL_TTF
	if (TTF_Init()) throw "No es pot inicialitzar SDL_ttf";

	//-->SDL_Mix
	const Uint8 mixFlags{ MIX_INIT_MP3 | MIX_INIT_OGG };
	if (!(Mix_Init(mixFlags) & mixFlags)) throw "Error: SDL_Mixer init";
}

void Game::InitMenu()
{

	//Background
	_Textures[Txtr_BG_Menu] = { IMG_LoadTexture(m_renderer, "../../res/img/bg.jpg") };
	_Rects[Txtr_BG_Menu] = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	_Textures[Txtr_BG_Game] = { IMG_LoadTexture(m_renderer, "../../res/img/bgCastle.jpg") };
	_Rects[Txtr_BG_Game] = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	//Cursor
	_Textures[Txtr_Cursor] = { IMG_LoadTexture(m_renderer, "../../res/img/kintoun.png") };
	_Rects[Txtr_Cursor] = { 0, 0, 100, 50 };

	//Buttons

	//Load fonts
	TTF_Font* font = TTF_OpenFont("../../res/ttf/saiyan.ttf", 80);
	if (!font) throw "No s'ha pogut crear la font.";
	
	//Play

	SDL_Surface* tmpSurf{ TTF_RenderText_Blended(font, "Play", SDL_Color {0,255,0,255}) };
	if (!tmpSurf) throw "No s'ha pogut crear la surface.";
	_Textures[Txtr_BTN_Play] = SDL_CreateTextureFromSurface(m_renderer, tmpSurf);
	SDL_FreeSurface(tmpSurf);
	_Textures[Txtr_BTN_Play_N] = _Textures[Txtr_BTN_Play];

	tmpSurf = TTF_RenderText_Blended(font, "Play", SDL_Color{ 255,0,0,255 });
	if (!tmpSurf) throw "No s'ha pogut crear la surface.";
	_Textures[Txtr_BTN_Play_H] = SDL_CreateTextureFromSurface(m_renderer, tmpSurf);

	_Rects[Txtr_BTN_Play] ={ (SCREEN_WIDTH / 2 - tmpSurf->w / 2), 100, tmpSurf->w, tmpSurf->h };

	//Quit

	tmpSurf = TTF_RenderText_Blended(font, "Quit", SDL_Color{ 0,255,0,255 });
	if (!tmpSurf) throw "No s'ha pogut crear la surface.";
	_Textures[Txtr_BTN_Quit] = SDL_CreateTextureFromSurface(m_renderer, tmpSurf);

	tmpSurf = TTF_RenderText_Blended(font, "Quit", SDL_Color{ 255,0,0,255 });
	if (!tmpSurf) throw "No s'ha pogut crear la surface.";
	_Textures[Txtr_BTN_Quit_H] = SDL_CreateTextureFromSurface(m_renderer, tmpSurf);

	_Textures[Txtr_BTN_Quit_N] = _Textures[Txtr_BTN_Quit];
	_Rects[Txtr_BTN_Quit] = { (SCREEN_WIDTH / 2 - tmpSurf->w / 2), 250, tmpSurf->w, tmpSurf->h };

	//Sound

	tmpSurf = TTF_RenderText_Blended(font, "Sound On", SDL_Color{ 255,140,0,255 });
	if (!tmpSurf) throw "No s'ha pogut crear la surface.";

	_Textures[Txtr_BTN_Sound_On] = SDL_CreateTextureFromSurface(m_renderer, tmpSurf);

	tmpSurf = TTF_RenderText_Blended(font, "Sound Off", SDL_Color{ 255,69,0,255 });
	if (!tmpSurf) throw "No s'ha pogut crear la surface.";

	_Textures[Txtr_BTN_Sound_Off] = SDL_CreateTextureFromSurface(m_renderer, tmpSurf);

	_Rects[Txtr_BTN_Sound] = { (SCREEN_WIDTH / 4 - tmpSurf->w / 2), 500, tmpSurf->w, tmpSurf->h };

	SDL_FreeSurface(tmpSurf);

	_Textures[Txtr_BTN_Sound] = _Textures[Txtr_BTN_Sound_On];



	TTF_CloseFont(font);




}

void Game::InitGame()
{
	int textWidth, textHeight;

	_Textures[Txtr_Players] = IMG_LoadTexture(m_renderer, "../../res/img/spCastle.png");
	if (_Textures[Txtr_Players] == nullptr) throw "No s'han pogut crear les textures";

	SDL_QueryTexture(_Textures[Txtr_Players], NULL, NULL, &textWidth, &textHeight);

	AddPlayer(textWidth,textHeight,Player::PlayerType::PL1);
	AddPlayer(textWidth, textHeight, Player::PlayerType::PL2);

	// No Animated Sprites
	_Textures[Txtr_Sacks] = IMG_LoadTexture(m_renderer, "../../res/img/gold.png");
	if (_Textures[Txtr_Sacks] == nullptr) throw "No s'han pogut crear les textures";
	SDL_QueryTexture(_Textures[Txtr_Sacks], NULL, NULL, &textWidth, &textHeight);

	_Textures[Txtr_SC] = IMG_LoadTexture(m_renderer, "../../res/img/num.png");
	if (_Textures[Txtr_SC] == nullptr) throw "No s'han pogut crear les textures";
	SDL_QueryTexture(_Textures[Txtr_SC], NULL, NULL, &textWidth, &textHeight);
	_Rects[Txtr_SC] = { 50, 5, (textWidth/10)/ 2,textHeight/2 };
	_Rects[F_Txtr_SC] = { 0,0, textWidth/10,textHeight};

#pragma endregion
	font_timmer = TTF_OpenFont("../../res/ttf/mono.ttf", 25);
	std::string textTime = "Time: ";
	surfTimer = { TTF_RenderText_Blended(font_timmer, textTime.c_str(), SDL_Color{0,0,0,255}) };
	_Textures[Txtr_Time] = SDL_CreateTextureFromSurface(m_renderer, surfTimer);
	_Rects[Txtr_Time] = { SCREEN_WIDTH - 150, 10, surfTimer->w, surfTimer->h };

	std::string player1ScoreText = "P1: ";
	SDL_Surface* surfPlayersScoreText{ TTF_RenderText_Blended(font_timmer, player1ScoreText.c_str(), SDL_Color{0,0,0,255}) };
	_Textures[Txtr_Text_SC_P1] = SDL_CreateTextureFromSurface(m_renderer, surfPlayersScoreText);
	_Rects[Txtr_Text_SC_P1] = { 10, 10, surfPlayersScoreText->w, surfPlayersScoreText->h };

	std::string player2ScoreText = "P2: ";
	surfPlayersScoreText = { TTF_RenderText_Blended(font_timmer, player2ScoreText.c_str(), SDL_Color{0,0,0,255}) };
	_Textures[Txtr_Text_SC_P2] = SDL_CreateTextureFromSurface(m_renderer, surfPlayersScoreText);
	_Rects[Txtr_Text_SC_P2] = { 10, 50, surfPlayersScoreText->w, surfPlayersScoreText->h };

	SDL_FreeSurface(surfPlayersScoreText);

	for (int i = 0; i < 10; i++) {
		AddSacks();
	}
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

	_Rects[Txtr_Cursor].x += (((input.GetMouseCoords().x - (_Rects[Txtr_Cursor].w / 2)) - _Rects[Txtr_Cursor].x) / 10);
	_Rects[Txtr_Cursor].y += (((input.GetMouseCoords().y - (_Rects[Txtr_Cursor].h / 2)) - _Rects[Txtr_Cursor].y) / 10);

	//Play Button
	if (Collisions::ConfirmCollision(input.GetMouseCoords(), RectSDL2My(_Rects[Txtr_BTN_Play]))) {
		_Textures[Txtr_BTN_Play] = _Textures[Txtr_BTN_Play_H];
		if (input.JustPressed(InputKeys::MOUSE_LEFT)) { 
			_gameState = GameState::PLAYING; };
	}
	else _Textures[Txtr_BTN_Play] = _Textures[Txtr_BTN_Play_N];

	//Exit Button
	if (Collisions::ConfirmCollision(input.GetMouseCoords(), RectSDL2My(_Rects[Txtr_BTN_Quit]))) {
		_Textures[Txtr_BTN_Quit] = _Textures[Txtr_BTN_Quit_H];
		if (input.JustPressed(InputKeys::MOUSE_LEFT)) { _gameState = GameState::EXIT; }
	}
	else _Textures[Txtr_BTN_Quit] = _Textures[Txtr_BTN_Quit_N];
	//Sound Button
	if (Collisions::ConfirmCollision(input.GetMouseCoords(), RectSDL2My(_Rects[Txtr_BTN_Sound]))) {
		if (input.JustPressed(InputKeys::MOUSE_LEFT)) {
			if (!Mix_PausedMusic()) Mix_PauseMusic();
			else Mix_PlayMusic(soundtrack, -1);
		}
		_Textures[Txtr_BTN_Sound] = Mix_PausedMusic() ? _Textures[Txtr_BTN_Sound_Off] : _Textures[Txtr_BTN_Sound_On];
	}
	else _Textures[Txtr_BTN_Sound] = !Mix_PausedMusic() ? _Textures[Txtr_BTN_Sound_On] : _Textures[Txtr_BTN_Sound_Off];

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
		surfTimer = TTF_RenderText_Blended(font_timmer, s.c_str(), SDL_Color{ 0,0,0,255 });
		_Textures[Txtr_Time] = SDL_CreateTextureFromSurface(m_renderer, surfTimer);
		_Rects[Txtr_Time] = { SCREEN_WIDTH - 100, 10, surfTimer->w, surfTimer->h };
	}
}

void Game::RenderMenu()
{
	SDL_RenderClear(m_renderer);

	//Background
	SDL_RenderCopy(m_renderer, _Textures[Txtr_BG_Menu], nullptr, &_Rects[Txtr_BG_Menu]);
	//Text
	
	SDL_RenderCopy(m_renderer, _Textures[Txtr_BTN_Play], nullptr, &_Rects[Txtr_BTN_Play]);
	SDL_RenderCopy(m_renderer, _Textures[Txtr_BTN_Quit], nullptr, &_Rects[Txtr_BTN_Quit]);
	SDL_RenderCopy(m_renderer, _Textures[Txtr_BTN_Sound], nullptr, &_Rects[Txtr_BTN_Sound]);
	//Cursor
	SDL_RenderCopy(m_renderer, _Textures[Txtr_Cursor], nullptr, &_Rects[Txtr_Cursor]);
	
	SDL_RenderPresent(m_renderer);

}

void Game::RenderGame()
{
	SDL_RenderClear(m_renderer);

	SDL_RenderCopy(m_renderer, _Textures[Txtr_BG_Game], nullptr, &_Rects[Txtr_BG_Game]);


	//Players 
	for (Player* p : players) {
		SDL_RenderCopy(m_renderer, _Textures[Txtr_Players], &MyRect2SDL(p->GetFrame()), &MyRect2SDL(p->GetPosition()));
	}

	for (int i = 0; i < players.size(); i++) {

		Player* pl = players.at(i);

		SDL_RenderCopy(m_renderer, _Textures[Txtr_SC],
			&MyRect2SDL(&Rect(trunc((pl->GetScore()) * 0.1) * _Rects[F_Txtr_SC].w, 0, _Rects[F_Txtr_SC].w, _Rects[F_Txtr_SC].h)),
			&MyRect2SDL(&Rect(_Rects[Txtr_SC].x, _Rects[Txtr_SC].y + (_Rects[Txtr_SC].h * i), _Rects[Txtr_SC].w, _Rects[Txtr_SC].h)));

		SDL_RenderCopy(m_renderer, _Textures[Txtr_SC],
			&MyRect2SDL(&Rect(trunc((pl->GetScore()) % 10) * _Rects[F_Txtr_SC].w, 0, _Rects[F_Txtr_SC].w, _Rects[F_Txtr_SC].h)),
			&MyRect2SDL(&Rect(_Rects[Txtr_SC].x + (_Rects[Txtr_SC].w * 1), _Rects[Txtr_SC].y + (_Rects[Txtr_SC].h * i), _Rects[Txtr_SC].w, _Rects[Txtr_SC].h)));
	}


	for (Sack* sack : sacks) {
		SDL_RenderCopy(m_renderer, _Textures[Txtr_Sacks], nullptr, &MyRect2SDL(sack->GetPosition()));
	}

	SDL_RenderCopy(m_renderer, _Textures[Txtr_Time], nullptr, &_Rects[Txtr_Time]);
	SDL_RenderCopy(m_renderer, _Textures[Txtr_Text_SC_P1], nullptr, &_Rects[Txtr_Text_SC_P1]);
	SDL_RenderCopy(m_renderer, _Textures[Txtr_Text_SC_P2], nullptr, &_Rects[Txtr_Text_SC_P2]);

	SDL_RenderPresent(m_renderer);
}

void Game::CloseSDL()
{
	Mix_CloseAudio();
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	m_renderer = nullptr;
	m_window = nullptr;
	SDL_Quit();
}

void Game::DestroyAllTextures()
{
	SDL_DestroyTexture(_Textures[Txtr_Players]);
	SDL_DestroyTexture(_Textures[Txtr_Sacks]);
	SDL_DestroyTexture(_Textures[Txtr_Cursor]);
	SDL_DestroyTexture(_Textures[Txtr_BG_Menu]);
	SDL_DestroyTexture(_Textures[Txtr_BG_Game]);
	SDL_DestroyTexture(_Textures[Txtr_BTN_Play]);
	SDL_DestroyTexture(_Textures[Txtr_BTN_Play_N]);
	SDL_DestroyTexture(_Textures[Txtr_BTN_Play_H]);
	SDL_DestroyTexture(_Textures[Txtr_BTN_Quit]);
	SDL_DestroyTexture(_Textures[Txtr_BTN_Quit_N]);
	SDL_DestroyTexture(_Textures[Txtr_BTN_Quit_H]);
	SDL_DestroyTexture(_Textures[Txtr_BTN_Exit]);
	SDL_DestroyTexture(_Textures[Txtr_BTN_Sound_On]);
	SDL_DestroyTexture(_Textures[Txtr_BTN_Sound_Off]);
	SDL_DestroyTexture(_Textures[Txtr_BTN_Sound]);
	SDL_DestroyTexture(_Textures[Txtr_Time]);
	SDL_DestroyTexture(_Textures[Txtr_Text_SC_P1]);
	SDL_DestroyTexture(_Textures[Txtr_Text_SC_P2]);
	SDL_DestroyTexture(_Textures[Txtr_SC]);
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);

	font_timmer = nullptr;
	surfTimer = nullptr;

	SDL_FreeSurface(surfTimer);
	TTF_CloseFont(font_timmer);

}

void Game::ResetGame()
{
	for (Player* pi : players) {
		pi->SetScore(0);
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


