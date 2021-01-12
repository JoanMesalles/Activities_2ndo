#include "AudioManager.h"

AudioManager* AudioManager::audioManager = nullptr;

AudioManager::AudioManager()
{
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		throw "No s'ha pogut inicialitzar SDL_Mixer";
	}

	soundtrack = { Mix_LoadMUS("../../res/au/mainTheme.mp3") };
	if (!soundtrack) throw "No s'ha pogut carregar l'audio";
	Mix_PlayMusic(soundtrack, -1);
	Mix_VolumeMusic(100);


}

AudioManager::~AudioManager()
{
	Mix_CloseAudio();
	Mix_Quit();
}

AudioManager* AudioManager::getInstance()
{
	if (audioManager == nullptr) {
		audioManager = new AudioManager;
	}
	return audioManager;
}



void AudioManager::PauseMusic()
{
	Mix_PauseMusic();

}

bool AudioManager::GetMusicPaused()
{
	return Mix_PausedMusic();
}

void AudioManager::PlayMusic()
{
	Mix_PlayMusic(soundtrack, -1);
}
