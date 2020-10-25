#pragma once
#include <math.h>
#include <SDL.h>

const int FPS = 60;
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

struct Vec2D
{
	int x, y;

	Vec2D() : x(0), y(0) {};
	Vec2D(int _x, int _y) : x(_x), y(_y) {};
	Vec2D(int _xy) : x(_xy), y(_xy) {};


	const Vec2D operator-(const Vec2D& v) { return Vec2D(x - v.x, y - v.y); };

	//Magnitude
	float mod() { return sqrt(x ^ 2 + y ^ 2); }
	void setPoints(Vec2D v) { x = v.x; y = v.y;}
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
	MOUSE_LEFT, MOUSE_RIGHT, COUNT
};


struct InputData
{
private:
	bool keyboardPressed[(int)InputKeys::COUNT] = {};
	bool keyboardDown[(int)InputKeys::COUNT] = {};
	Vec2D mouseCoords;

public:
	Vec2D GetMouseCoords() { return mouseCoords; };
	void SetMouseCoords(Vec2D v) { mouseCoords.setPoints(v); };
	void SetMouseCoords(int x, int y) { mouseCoords = {x,y} ; };
	bool IsPressed(InputKeys key) { return keyboardPressed[(int)key]; }
	bool JustPressed(InputKeys key) { return keyboardDown[(int)key]; }
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
