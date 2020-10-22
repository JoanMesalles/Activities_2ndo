#include <SDL.h> // Always needs to be included for an SDL app
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <exception>
#include <iostream>
#include <string>

//Game general information
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(int, char* [])
{
	// --- INIT SDL ---
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		throw "No es pot inicialitzar SDL subsystems";

	// --- WINDOW ---
	//SDL_Window* m_window { SDL_CreateWindow("SDL...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
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
	SDL_FreeSurface(tmpSurf);

	SDL_Rect playtextRect{ (SCREEN_WIDTH / 2 - tmpSurf->w / 2), 100, tmpSurf->w, tmpSurf->h };

	SDL_Texture* playtextTexture = playtextNormal;

	tmpSurf = TTF_RenderText_Blended(font, "Quit", SDL_Color { 255,0,0,255 });
	if (!tmpSurf) throw "No s'ha pogut crear la surface.";
	SDL_Texture* quittextNormal = SDL_CreateTextureFromSurface(m_renderer, tmpSurf);
	SDL_FreeSurface(tmpSurf);

	tmpSurf = TTF_RenderText_Blended(font, "Quit", SDL_Color{ 0,255,0,255 });
	if (!tmpSurf) throw "No s'ha pogut crear la surface.";
	SDL_Texture* quittextHover = SDL_CreateTextureFromSurface(m_renderer, tmpSurf);
	SDL_FreeSurface(tmpSurf);

	SDL_Rect quittextRect{ (SCREEN_WIDTH / 2 - tmpSurf->w / 2), 250, tmpSurf->w, tmpSurf->h };

	SDL_Texture* quittextTexture = quittextNormal;

	tmpSurf = TTF_RenderText_Blended(font, "Sound On", SDL_Color{ 255,140,0,255 });
	if (!tmpSurf) throw "No s'ha pogut crear la surface.";
	SDL_Texture* SoundtextOn = SDL_CreateTextureFromSurface(m_renderer, tmpSurf);
	SDL_FreeSurface(tmpSurf);

	tmpSurf = TTF_RenderText_Blended(font, "Sound Off", SDL_Color{ 255,69,0,255 });
	if (!tmpSurf) throw "No s'ha pogut crear la surface.";
	SDL_Texture* SoundtextOff = SDL_CreateTextureFromSurface(m_renderer, tmpSurf);
	SDL_FreeSurface(tmpSurf);

	SDL_Rect soundtextRect{ (SCREEN_WIDTH / 4 - tmpSurf->w / 2), 500, tmpSurf->w, tmpSurf->h };

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
	Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
	//Mix_PlayingMusic();
	//Mix_PauseMusic();
	//Mix_PausedMusic();

#pragma endregion
	bool isKeySPressed = false;
	bool rightmousePressed = false;
	// --- GAME LOOP ---
	SDL_Event event;
	bool isRunning = true;

	while (isRunning)
	{
		// HANDLE EVENTS
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
					isRunning = false;
				if (event.key.keysym.sym == SDLK_s)
					isKeySPressed = true;
				break;
			case SDL_MOUSEMOTION:
				mousePos.x = event.motion.x;
				mousePos.y = event.motion.y;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (SDL_BUTTON_RIGHT) {
					rightmousePressed = true;
				}
				break;
			default:
				rightmousePressed = false;
			}
		}
		//*-*-*-*-*-*UPDATE
		cursorRect.x += (mousePos.x - (cursorRect.w / 2) - cursorRect.x) / 10;
		cursorRect.y += (mousePos.y - (cursorRect.h / 2) - cursorRect.y) / 10;

		//if (isKeySPressed) playtextTexture = playtextHover;

		if (mousePos.x > playtextRect.x && mousePos.x < (playtextRect.x + playtextRect.w) && mousePos.y > playtextRect.y && mousePos.y < (playtextRect.y + playtextRect.h) && rightmousePressed)
		{
			playtextTexture = playtextHover;
		}
		else playtextTexture = playtextNormal;

		if (mousePos.x > quittextRect.x && mousePos.x < (quittextRect.x + quittextRect.w) && mousePos.y > quittextRect.y && mousePos.y < (quittextRect.y + quittextRect.h))
		{
			quittextTexture = quittextHover;

			if (rightmousePressed) {
				isRunning = false;
			}
		}
		else quittextTexture = quittextNormal;

		if (mousePos.x > soundtextRect.x && mousePos.x < (soundtextRect.x + soundtextRect.w) && mousePos.y > soundtextRect.y && mousePos.y < (soundtextRect.y + soundtextRect.h) && rightmousePressed )
		{
			if (Mix_PausedMusic()) {
				Mix_PlayMusic(soundtrack, -1);
				soundtextTexture = SoundtextOn;
			}
			else {
				Mix_PauseMusic();
				soundtextTexture = SoundtextOff;
			}
		}

		//*-*-*-*-*-*DRAW (no logic)
		SDL_RenderClear(m_renderer);

		//Background
		SDL_RenderCopy(m_renderer, bgTexture, nullptr, &bgRect);

		//Text
		SDL_RenderCopy(m_renderer, playtextTexture, nullptr, &playtextRect);
		SDL_RenderCopy(m_renderer, quittextTexture, nullptr, &quittextRect);
		SDL_RenderCopy(m_renderer, soundtextTexture, nullptr, &soundtextRect);
		//Cursor
		SDL_RenderCopy(m_renderer, cursorTexture, nullptr, &cursorRect);

		SDL_RenderPresent(m_renderer);
	}
	// END *-*-*-*-*---- GAME LOOP ---


	// --- DESTROY ---
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