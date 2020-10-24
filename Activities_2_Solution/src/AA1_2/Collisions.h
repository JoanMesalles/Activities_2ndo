#pragma once
#include "Types.h"


class Collisions
{
public:
	static bool ConfirmCollision(Vec2D v1, Vec2D v2, float offset);
	static bool ConfirmCollision(Vec2D v, Rect r);
	static bool ConfirmCollision(Rect r1, Rect r2);


};