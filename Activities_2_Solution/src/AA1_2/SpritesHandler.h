#pragma once
#include "Types.h"

class SpritesHandler {

	SDL_Rect sprtRect, sprtPos;
	int textureWidth, textureHeight, frameWidht, frameHeight, frameTime = 0,frameSpeed, initialX, initialY;

public:
	SpritesHandler();
	SpritesHandler(SDL_Texture* texture, int frameColumns, int frameRows, int x, int y);
	SDL_Rect GetSpritePos();
	SDL_Rect GetSpriteRect();
	void AnimatePlayer(InputKeys key);
	void ResetToIdle();
	void SetSpritePos(int y, int x);
	void SetFrameSpeed(int fs);
	void MoveSprite(InputKeys key);
};