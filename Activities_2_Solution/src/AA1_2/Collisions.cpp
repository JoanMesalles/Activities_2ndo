#include "Collisions.h"

bool Collisions::ConfirmCollision(Vec2D v1, Vec2D v2, float offset)
{
	return abs((long) (Vec2D(v2 - v1).mod()) < offset);
}

bool Collisions::ConfirmCollision(Vec2D v, Rect r)
{
	return (v.x > r.x && v.x < r.x + r.w) && (v.y > r.y && v.y < r.y + r.h);
}

bool Collisions::ConfirmCollision(Rect rect1, Rect rect2)
{
	return (rect1.x < rect2.x + rect2.w && rect1.x + rect1.w > rect2.x && rect1.y < rect2.y + rect2.h && rect1.y + rect1.h > rect2.y);
}

bool Collisions::ConfirmCollision(const Rect* rect1, const Rect* rect2)
{
	return (rect1->x < rect2->x + rect2->w && rect1->x + rect1->w > rect2->x && rect1->y < rect2->y + rect2->h && rect1->y + rect1->h > rect2->y);

}

bool Collisions::ConfirmCollision(Rect rect1, const Rect* rect2)
{
	return (rect1.x < rect2->x + rect2->w && rect1.x + rect1.w > rect2->x && rect1.y < rect2->y + rect2->h && rect1.y + rect1.h > rect2->y);;
}
