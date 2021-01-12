#pragma once
#include "Collisions.h"

enum class EDirection { NONE = -1, RIGHT, LEFT, UP, DOWN, COUNT };

class Sack;

class Player
{
public:
	enum class PlayerType {NONE = -1, PL1, PL2, COUNT};
private:
	Rect position;
	Rect initialPositionP1, initialPositionP2;
	Rect frame;
	PlayerType type;
	EDirection dir = EDirection::NONE;
	int score = 0;

	int initCol, lastCol;
	int initRow, lastRow;
	float frameCount = 0;
public:
	Player();
	void Update(InputData* input, std::vector<Sack*>& sacks, std::vector<Player*> players);
	const Rect* GetPosition() { return &position; };
	const Rect* GetFrame() { return &frame; };
	void SetPlayerValues(int textWidth, int textHeight, int nCol, int nRow, PlayerType _type);
	int GetScore() { return score; };
	void SetScore(int sc);
	PlayerType GetType() { return type; };
	void Reset();

private:
	bool Move(InputData* input, std::vector<Player*> players);
	void UpdateSprite();
	void UpdateCollisions(std::vector<Sack*>& sacks, InputData* input);
};

