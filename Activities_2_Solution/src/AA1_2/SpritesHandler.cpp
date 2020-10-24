#pragma once
#include "SpritesHandler.h"


SpritesHandler::SpritesHandler()
{
}

SpritesHandler::SpritesHandler(SDL_Texture* texture, int frameColumns, int frameRows, int x, int y) {
	SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);
	frameWidht = textureWidth / frameColumns;
	frameHeight = textureHeight / frameRows;
	sprtRect.x = initialX = frameWidht * x;
	sprtRect.y = initialY = frameHeight * y;
	sprtPos.h = sprtRect.h = frameHeight;
	sprtPos.w = sprtRect.w = frameWidht;
	sprtPos.x = 100;
	sprtPos.y = 200;
	frameSpeed = 8;
}

SDL_Rect SpritesHandler::GetSpritePos()
{
	return sprtPos;
}
SDL_Rect SpritesHandler::GetSpriteRect()
{
	return sprtRect;
}
void SpritesHandler::AnimatePlayer(InputKeys key)
{
	switch (key)
	{
	case InputKeys::W:
		frameTime++;
		sprtRect.y = initialY + frameHeight * 3;

		if (FPS / frameTime <= frameSpeed)
		{
			frameTime = 0;
			sprtRect.x -= frameWidht;
			if (sprtRect.x < initialX - frameWidht) {
				sprtRect.x = initialX + frameWidht;
			}
		}
		break;
	case InputKeys::A:
		frameTime++;
		sprtRect.y = initialY + frameHeight;
		if (FPS / frameTime <= frameSpeed)
		{
			frameTime = 0;
			sprtRect.x -= frameWidht;
			if (sprtRect.x < initialX - frameWidht) {
				sprtRect.x = initialX + frameWidht;
			}
		}
		break;
	case InputKeys::S:
		sprtRect.y = initialY;
		frameTime++;
		if (FPS / frameTime <= frameSpeed)
		{
			frameTime = 0;
			sprtRect.x += frameWidht;
			if (sprtRect.x > initialX + frameWidht) {
				sprtRect.x = initialX - frameWidht;
			}
		}
		break;
	case InputKeys::D:
		frameTime++;
		sprtRect.y = initialY + frameHeight * 2;
		if (FPS / frameTime <= frameSpeed)
		{
			frameTime = 0;
			sprtRect.x -= frameWidht;
			if (sprtRect.x < initialX - frameWidht) {
				sprtRect.x = initialX + frameWidht;
			}
		}
		break;
	case InputKeys::UPARROW:
		frameTime++;
		sprtRect.y = initialY + frameHeight * 3;

		if (FPS / frameTime <= frameSpeed)
		{
			frameTime = 0;
			sprtRect.x -= frameWidht;
			if (sprtRect.x < initialX - frameWidht) {
				sprtRect.x = initialX + frameWidht;
			}
		}
		break;
	case InputKeys::DOWNARROW:
		sprtRect.y = initialY;
		frameTime++;
		if (FPS / frameTime <= frameSpeed)
		{
			frameTime = 0;
			sprtRect.x += frameWidht;
			if (sprtRect.x > initialX + frameWidht) {
				sprtRect.x = initialX - frameWidht;
			}
		}
		break;
	case InputKeys::LEFTARROW:
		frameTime++;
		sprtRect.y = initialY + frameHeight;

		if (FPS / frameTime <= frameSpeed)
		{
			frameTime = 0;
			sprtRect.x -= frameWidht;
			if (sprtRect.x < initialX - frameWidht) {
				sprtRect.x = initialX + frameWidht;
			}
		}
		break;
	case InputKeys::RIGHTARROW:
		frameTime++;
		sprtRect.y = initialY + frameHeight * 2;
		if (FPS / frameTime <= frameSpeed)
		{
			frameTime = 0;
			sprtRect.x -= frameWidht;
			if (sprtRect.x < initialX - frameWidht) {
				sprtRect.x = initialX + frameWidht;
			}
		}
		break;
	default:
		break;

	}
}

void SpritesHandler::ResetToIdle()
{
	sprtRect.x = initialX;
	sprtRect.y = initialY;
}
void SpritesHandler::SetSpritePos(int x, int y)
{
	sprtPos.x = x;
	sprtPos.y = y;
}
void SpritesHandler::SetFrameSpeed(int fs)
{
	frameSpeed = fs;
}
;

