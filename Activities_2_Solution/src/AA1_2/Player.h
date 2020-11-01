#pragma once
#include "Collisions.h"

class Sack;

class Player
{
public:
	enum class PlayerType {NONE = -1, PL1, PL2, COUNT};
private:
	Rect position;
	Rect frame;
	PlayerType type;
	EDirection dir = EDirection::NONE;
	int score = 0;

	int initCol, lastCol;
	int initRow, lastRow;
	float frameCount = 0;
public:
	Player();
	void Update(InputData* input, std::vector<Sack*>& sacks);
	const Rect* GetPosition() { return &position; };
	const Rect* GetFrame() { return &frame; };
	void SetPlayerValues(int textWidth, int textHeight, int nCol, int nRow, PlayerType _type);
	int GetScore() { return score; };
	void SetScore(int sc);

private:
	bool Move(InputData* input);
	void UpdateSprite();
	void UpdateCollisions(std::vector<Sack*>& sacks, InputData* input);
};

