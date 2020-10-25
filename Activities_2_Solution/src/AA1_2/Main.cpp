 // Always needs to be included for an SDL app
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <exception>
#include <iostream>
#include <string>

#include "Collisions.h"
#include "SpritesHandler.h"
//Game general information


Rect RectSDL2My(SDL_Rect r) { return Rect(r.x, r.y, r.w, r.h); }

int main(int, char* [])
{
	// --- INIT SDL ---
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		throw "No es pot inicialitzar SDL subsystems";

	// --- WINDOW ---
	SDL_Window* m_window = SDL_CreateWindow("SDL...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (m_window == nullptr)
		throw "No es pot inicialitzar SDL_Window";

	// --- RENDERER ---
	SDL_Renderer* m_renderer{ SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) };
	if (m_renderer == nullptr)
		throw "No es pot inicialitzar SDL_Renderer";

	//Initialize renderer color
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);


	//-->SDL_Image
	const Uint8 imgFlags{ IMG_INIT_PNG | IMG_INIT_JPG };
	if (!(IMG_Init(imgFlags) & imgFlags))
		throw "Error: SDL_image init";

	//-->SDL_TTF
	if (TTF_Init()) throw "No es pot inicialitzar SDL_ttf";

	//-->SDL_Mix
	const Uint8 mixFlags{ MIX_INIT_MP3 | MIX_INIT_OGG };
	if (!(Mix_Init(mixFlags) & mixFlags)) throw "Error: SDL_Mixer init";

	// --- SPRITES ---
	//Background
	SDL_Texture* bgTexture{ IMG_LoadTexture(m_renderer, "../../res/img/bg.jpg") };
	if (bgTexture == nullptr)
		throw "Error: bgTexture init";
	SDL_Rect bgRect{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	//Cursor
	SDL_Texture* cursorTexture{ IMG_LoadTexture(m_renderer, "../../res/img/kintoun.png") };
	if (cursorTexture == nullptr) throw "No s'han pogut crear les textures";
	SDL_Rect cursorRect{ 0, 0, 100, 50 };

	SDL_Point mousePos{ 0,0 };
	//-->Animated Sprite ---

	SDL_Texture* playerTexture = IMG_LoadTexture(m_renderer, "../../res/img/spCastle.png");
	if (playerTexture == nullptr) throw "No s'han pogut crear les textures";
	
	SpritesHandler Player1Sprite( playerTexture, 12, 8, 4, 0);
	SpritesHandler Player2Sprite(playerTexture, 12, 8, 7, 4);
	Player2Sprite.SetSpritePos(200,200);

	// --- TEXT ---
#pragma region Text
  //Load fonts
	TTF_Font* font = TTF_OpenFont("../../res/ttf/saiyan.ttf", 80);
	if (!font) throw "No s'ha pogut crear la font.";

	//Generate font textures 
	SDL_Surface* tmpSurf{ TTF_RenderText_Blended(font, "Play", SDL_Color {0,255,0,255}) };
	if (!tmpSurf) throw "No s'ha pogut crear la surface.";
	SDL_Texture* playtextNormal = SDL_CreateTextureFromSurface(m_renderer, tmpSurf);
	SDL_FreeSurface(tmpSurf);

	tmpSurf = TTF_RenderText_Blended(font, "Play", SDL_Color{ 255,0,0,255 });
	if (!tmpSurf) throw "No s'ha pogut crear la surface.";
	SDL_Texture* playtextHover = SDL_CreateTextureFromSurface(m_renderer, tmpSurf);

	SDL_Rect playtextRect{ (SCREEN_WIDTH / 2 - tmpSurf->w / 2), 100, tmpSurf->w, tmpSurf->h };

	SDL_FreeSurface(tmpSurf);

	SDL_Texture* playtextTexture = playtextNormal;

	tmpSurf = TTF_RenderText_Blended(font, "Quit", SDL_Color { 0,255,0,255 });
	if (!tmpSurf) throw "No s'ha pogut crear la surface.";
	SDL_Texture* quittextNormal = SDL_CreateTextureFromSurface(m_renderer, tmpSurf);
	SDL_FreeSurface(tmpSurf);

	tmpSurf = TTF_RenderText_Blended(font, "Quit", SDL_Color{ 255,0,0,255 });
	if (!tmpSurf) throw "No s'ha pogut crear la surface.";
	SDL_Texture* quittextHover = SDL_CreateTextureFromSurface(m_renderer, tmpSurf);

	SDL_Rect quittextRect{ (SCREEN_WIDTH / 2 - tmpSurf->w / 2), 250, tmpSurf->w, tmpSurf->h };

	SDL_FreeSurface(tmpSurf);

	SDL_Texture* quittextTexture = quittextNormal;

	tmpSurf = TTF_RenderText_Blended(font, "Sound On", SDL_Color{ 255,140,0,255 });
	if (!tmpSurf) throw "No s'ha pogut crear la surface.";
	SDL_Texture* SoundtextOn = SDL_CreateTextureFromSurface(m_renderer, tmpSurf);
	SDL_FreeSurface(tmpSurf);

	tmpSurf = TTF_RenderText_Blended(font, "Sound Off", SDL_Color{ 255,69,0,255 });
	if (!tmpSurf) throw "No s'ha pogut crear la surface.";
	SDL_Texture* SoundtextOff = SDL_CreateTextureFromSurface(m_renderer, tmpSurf);

	SDL_Rect soundtextRect{ (SCREEN_WIDTH / 4 - tmpSurf->w / 2), 500, tmpSurf->w, tmpSurf->h };

	SDL_FreeSurface(tmpSurf);

	SDL_Texture* soundtextTexture = SoundtextOn;

	TTF_CloseFont(font);
#pragma endregion

	// --- AUDIO ---
#pragma region Audio
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		throw "No s'ha pogut inicialitzar SDL_Mixer";
	}

	Mix_Music* soundtrack{ Mix_LoadMUS("../../res/au/mainTheme.mp3") };
	if (!soundtrack) throw "No s'ha pogut carregar l'audio";
	Mix_PlayMusic(soundtrack, -1);
	Mix_VolumeMusic(/*MIX_MAX_VOLUME / 4*/ 0);

#pragma endregion
	// --- GAME VARIABLES ---

	bool isKeySPressed = false;
	bool rightmousePressed = false;
	InputData input;

	// --- GAME LOOP ---
	SDL_Event event;
	bool isRunning = true;

	while (isRunning)
	{
		input.SetFalseKeyDown();
		// HANDLE EVENTS
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				isRunning = false;
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) 
				{
				case SDLK_ESCAPE:
					isRunning = false;
					break;
				case SDLK_w:
					input.SetKeyValue(InputKeys::W, true);
					break;
				case SDLK_d:
					input.SetKeyValue(InputKeys::D, true);
					break;
				case SDLK_a:
					input.SetKeyValue(InputKeys::A, true);
					break;
				case SDLK_s:
					input.SetKeyValue(InputKeys::S, true);
					break;
				case SDLK_UP:
					input.SetKeyValue(InputKeys::UPARROW, true);
					break;
				case SDLK_LEFT:
					input.SetKeyValue(InputKeys::LEFTARROW, true);
					break;
				case SDLK_RIGHT:
					input.SetKeyValue(InputKeys::RIGHTARROW, true);
					break;
				case SDLK_DOWN:
					input.SetKeyValue(InputKeys::DOWNARROW, true);
					break;
				default:
					break;
				}
				break;
			case SDL_KEYUP:
				switch (event.key.keysym.sym)
				{
				case SDLK_w:
					input.SetKeyValue(InputKeys::W, false);
					break;
				case SDLK_d:
					input.SetKeyValue(InputKeys::D, false);
					break;
				case SDLK_a:
					input.SetKeyValue(InputKeys::A, false);
					break;
				case SDLK_s:
					input.SetKeyValue(InputKeys::S, false);
					break;
				case SDLK_UP:
					input.SetKeyValue(InputKeys::UPARROW, false);
					break;
				case SDLK_LEFT:
					input.SetKeyValue(InputKeys::LEFTARROW, false);
					break;
				case SDLK_RIGHT:
					input.SetKeyValue(InputKeys::RIGHTARROW, false);
					break;
				case SDLK_DOWN:
					input.SetKeyValue(InputKeys::DOWNARROW, false);
					break;
				}
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

		//*-*-*-*-*-*UPDATE
		cursorRect.x += (((input.GetMouseCoords().x - (cursorRect.w / 2)) - cursorRect.x) / 10);
		cursorRect.y += (((input.GetMouseCoords().y - (cursorRect.h / 2)) - cursorRect.y) / 10);

		//Play Button
		if (Collisions::ConfirmCollision(input.GetMouseCoords(), RectSDL2My(playtextRect))) {
			playtextTexture = playtextHover;
			if (input.JustPressed(InputKeys::MOUSE_LEFT)) { /*Play Logic*/ }
		}
		else playtextTexture = playtextNormal;

		//Exit Button
		if (Collisions::ConfirmCollision(input.GetMouseCoords(), RectSDL2My(quittextRect))) {
			quittextTexture = quittextHover;
			if (input.JustPressed(InputKeys::MOUSE_LEFT)) { isRunning = false; }
		}
		else quittextTexture = quittextNormal;
		//Sound Button
		if (Collisions::ConfirmCollision(input.GetMouseCoords(), RectSDL2My(soundtextRect))) {
			if (input.JustPressed(InputKeys::MOUSE_LEFT)) {
				if (!Mix_PausedMusic()) Mix_PauseMusic();
				else Mix_PlayMusic(soundtrack, -1);
			}
			soundtextTexture = Mix_PausedMusic() ? SoundtextOff : SoundtextOn;
		}
		else soundtextTexture = !Mix_PausedMusic() ? SoundtextOn : SoundtextOff;
#pragma region SpritesLogic
		if(input.IsPressed(InputKeys::W)) {
			Player1Sprite.AnimatePlayer(InputKeys::W);
			Player1Sprite.MoveSprite(InputKeys::W);
		}
		else if (input.IsPressed(InputKeys::D)) {
			Player1Sprite.AnimatePlayer(InputKeys::D);
			Player1Sprite.MoveSprite(InputKeys::D);
		}
		else if (input.IsPressed(InputKeys::A)) {
			Player1Sprite.AnimatePlayer(InputKeys::A);
			Player1Sprite.MoveSprite(InputKeys::A);
		}
		else if (input.IsPressed(InputKeys::S)) {
			Player1Sprite.AnimatePlayer(InputKeys::S);
			Player1Sprite.MoveSprite(InputKeys::S);
		}
		else
			Player1Sprite.ResetToIdle();

		if (input.IsPressed(InputKeys::UPARROW)) {
			Player2Sprite.AnimatePlayer(InputKeys::UPARROW);
			Player2Sprite.MoveSprite(InputKeys::UPARROW);
		}
		else if (input.IsPressed(InputKeys::LEFTARROW)) {
			Player2Sprite.AnimatePlayer(InputKeys::LEFTARROW);
			Player2Sprite.MoveSprite(InputKeys::LEFTARROW);
		}
		else if (input.IsPressed(InputKeys::RIGHTARROW)) {
			Player2Sprite.AnimatePlayer(InputKeys::RIGHTARROW);
			Player2Sprite.MoveSprite(InputKeys::RIGHTARROW);
		}
		else if (input.IsPressed(InputKeys::DOWNARROW)) {
			Player2Sprite.AnimatePlayer(InputKeys::DOWNARROW);
			Player2Sprite.MoveSprite(InputKeys::DOWNARROW);
		}
		else
			Player2Sprite.ResetToIdle();

#pragma endregion
		//*-*-*-*-*-*DRAW (no logic)
		SDL_RenderClear(m_renderer);

		//Background
		SDL_RenderCopy(m_renderer, bgTexture, nullptr, &bgRect);

		//Text
		SDL_RenderCopy(m_renderer, playtextTexture, nullptr, &playtextRect);
		SDL_RenderCopy(m_renderer, quittextTexture, nullptr, &quittextRect);
		SDL_RenderCopy(m_renderer, soundtextTexture, nullptr, &soundtextRect);
		//Players
		SDL_RenderCopy(m_renderer, playerTexture, &Player1Sprite.GetSpriteRect(), &Player1Sprite.GetSpritePos());
		SDL_RenderCopy(m_renderer, playerTexture, &Player2Sprite.GetSpriteRect(), &Player2Sprite.GetSpritePos());
		//Cursor
		SDL_RenderCopy(m_renderer, cursorTexture, nullptr, &cursorRect);

		SDL_RenderPresent(m_renderer);
	}
	// END *-*-*-*-*---- GAME LOOP ---


	// --- DESTROY ---
	SDL_DestroyTexture(playerTexture);
	SDL_DestroyTexture(playtextHover);
	SDL_DestroyTexture(playtextTexture);
	SDL_DestroyTexture(playtextNormal);
	SDL_DestroyTexture(quittextHover);
	SDL_DestroyTexture(quittextTexture);
	SDL_DestroyTexture(SoundtextOff);
	SDL_DestroyTexture(SoundtextOn);
	SDL_DestroyTexture(quittextTexture);
	SDL_DestroyTexture(quittextNormal);
	SDL_DestroyTexture(bgTexture);
	SDL_DestroyTexture(cursorTexture);
	Mix_CloseAudio();
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);

	// --- QUIT ---
	SDL_Quit();

	return 0;
}