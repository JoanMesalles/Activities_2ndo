#pragma once
#include "Collisions.h"
class Score
{
	Rect position;
	Rect frame;

public:
	Score(int textWidth, int textHeight, int posx, int posy);
	void PlusScore();
	const Rect* GetPosition() { return &position; };
	const Rect* GetFrame() { return &frame; };

};

