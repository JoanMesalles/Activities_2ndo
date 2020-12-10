#pragma once
#include <SDL_mixer.h>
class AudioManager
{

	Mix_Music* soundtrack = nullptr;
	const Uint8 mixFlags{ MIX_INIT_MP3 | MIX_INIT_OGG };
	static AudioManager* audioManager;
	AudioManager();


public:

	~AudioManager();
	static AudioManager* getInstance();
	void PauseMusic();
	bool GetMusicPaused();
	void PlayMusic();
};
