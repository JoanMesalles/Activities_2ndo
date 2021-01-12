#pragma once

#include "Constants.h"

enum class ESceneState { NONE = -1, RUNNING, GO_PLAY, GO_MENU, GO_EXIT };

struct Vec2D
{
	int x, y;

	Vec2D() : x(0), y(0) {};
	Vec2D(int _x, int _y) : x(_x), y(_y) {};
	Vec2D(int _xy) : x(_xy), y(_xy) {};


	inline bool operator== (const Vec2D& v)const { return (x == v.x && y == v.y); };
	const Vec2D operator- (const Vec2D& v) { return Vec2D(x - v.x, y - v.y); };
	const Vec2D operator+ (const Vec2D& v) { return Vec2D(x + v.x, y + v.y); };
	Vec2D operator+= (const Vec2D& v) { x += v.x, y += v.y; return *this; };
	const Vec2D operator/ (const Vec2D& v) { return Vec2D(x / v.x, y / v.y); };
	const Vec2D operator/ (float a) const { return Vec2D(static_cast<int>(x) / a, static_cast<int>(y) / a); };
	const Vec2D operator* (const Vec2D& v) { return Vec2D(x * v.x, y * v.y); };
	const Vec2D operator* (float a) const { return Vec2D(static_cast<int>(x) * a, static_cast<int>(y) * a); };
	const Vec2D operator* (int a) const { return Vec2D(x * a, y * a); };
	const Vec2D operator*= (const Vec2D& v) { return Vec2D(x * v.x, y * v.y); };
	const Vec2D operator*= (const int& i) { return Vec2D(x * i, y * i); };


	float mod() { return sqrt(x ^ 2 + y ^ 2); }
	void setPoints(Vec2D v) { x = v.x; y = v.y;}
	static Vec2D randomVec(int min, int max) { return Vec2D(rand() % ((max + 1) - min) + min, rand() % ((max + 1) - min) + min);};
};

struct Rect
{
	int x, y, w, h;

	Rect() : x(0), y(0), w(0), h(0) {};
	Rect(int _x, int _y, int _w, int _h) : x(_x), y(_y), w(_w), h(_h) {};
public:


};

struct Font {
	const std::string id;
	std::string path;
	int size;

	Font(std::string _id, std::string _path, int _size) : id(_id), path(_path), size(_size) {};
};

struct Color {
	Uint8 r, g, b, a;

	Color(Uint8 _r, Uint8 _g, Uint8 _b, Uint8 _a) : r(_r), g(_g), b(_b), a(_a) {};

};

struct Text {
	std::string id;
	std::string text;
	Color color;

	Text(std::string _id, std::string _text, Color _color) : id(_id), text(_text), color(_color) {};

};
