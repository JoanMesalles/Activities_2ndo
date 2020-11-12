#pragma once

#include "Constants.h"

enum class EDirection {NONE = -1, RIGHT, LEFT, UP, DOWN, COUNT};

enum class GameState { PLAYING, MENU, EXIT };

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

enum class InputKeys
{
	NONE, W, A, S, D , UPARROW, DOWNARROW, LEFTARROW, RIGHTARROW, SPACE, P, ESC,
	MOUSE_LEFT, MOUSE_RIGHT, QUIT, COUNT
};

struct InputData
{
private:
	bool keyboardPressed[(int)InputKeys::COUNT] = {};
	bool keyboardDown[(int)InputKeys::COUNT] = {};
	Vec2D mouseCoords;
	Vec2D screenSize;

public:
	Vec2D GetMouseCoords() { return mouseCoords; };
	void SetMouseCoords(Vec2D v) { mouseCoords.setPoints(v); };
	void SetMouseCoords(int x, int y) { mouseCoords = {x,y} ; };
	bool IsPressed(InputKeys key) { return keyboardPressed[(int)key]; }
	bool JustPressed(InputKeys key) { return keyboardDown[(int)key]; }
	void SetScreenSize(Vec2D size) { screenSize = size; };
	Vec2D* GetScreenSize() { return &screenSize; };
	clock_t lastTime = clock();
	float deltaTime = 0.f;

	void UpdateDeltaTime() {
		deltaTime = (clock() - lastTime);
		lastTime = clock();
		deltaTime /= CLOCKS_PER_SEC;
	}
	inline const float* GetDeltaTime() const { return &deltaTime; };

	void SetFalseKeyDown()
	{ 
		for (int i = 0; i < (int)InputKeys::COUNT; i++) 
		{ 
			keyboardDown[i] = false; 
		}; 
	};
	void SetKeyValue(InputKeys key, bool value) 
	{
		if (!keyboardPressed[(int)key]) {
			keyboardDown[(int)key] = value;
		}
		else {
			keyboardDown[(int)key] = false;
		}
		keyboardPressed[(int)key] = value;
	};
};

struct Font {
	const std::string id;
	std::string path;
	int size;
};

struct Color {
	Uint8 r, g, b, a;
};


struct Text {
	std::string id;
	std::string text;
	Color color;
	int w;
	int h;
};
