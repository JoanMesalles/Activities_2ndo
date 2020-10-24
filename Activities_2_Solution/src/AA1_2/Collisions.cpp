#include "Collisions.h"

bool Collisions::ConfirmCollision(Vec2D v1, Vec2D v2, float offset)
{
	return abs((long) (Vec2D(v2 - v1).mod()) < offset);
}

bool Collisions::ConfirmCollision(Vec2D v, Rect r)
{
	return (v.x > r.x && v.x < r.x + r.w) && (v.y > r.y && v.y < r.y + r.h);
}

bool Collisions::ConfirmCollision(Rect r1, Rect r2)
{
	return ConfirmCollision(Vec2D(r1.x,r1.y),r2) || ConfirmCollision(Vec2D(r1.x + r1.w, r1.w), r2)|| ConfirmCollision(Vec2D(r1.x + r1.w, r1.y + r1.h), r2);
}
