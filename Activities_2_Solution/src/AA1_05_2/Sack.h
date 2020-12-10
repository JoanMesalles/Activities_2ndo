#pragma once
#include "Collisions.h"
class Sack
{

	Rect position;
	Rect frame;
public:
	Sack();
	Sack(int textWidth, int textHeight, int posx, int posy);
	const Rect* GetPosition() { return &position; };
	const Rect* GetFrame() { return &frame; };
	Vec2D GetPositionInVect() { return Vec2D(position.x, position.y); };
	void SetPosition(Vec2D v) { position.x = v.x; position.y = v.y; };



};

