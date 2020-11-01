#include "Player.h"
#include "Sack.h"

Player::Player()
{
}

void Player::Update(InputData* input, std::vector<Sack*>& sacks)
{
	Move(input);
	UpdateSprite();
	UpdateCollisions(sacks, input);
}

void Player::SetPlayerValues(int textWidth, int textHeight, int nCol, int nRow, PlayerType _type)
{
	type = _type;
	frame.h = textHeight / nRow;
	frame.w = textWidth / nCol;

	switch (_type)
	{
	case Player::PlayerType::PL1:
		initCol = 3;
		lastCol = initCol + 3;
		initRow = 0;
		lastRow = initRow + 4;
		frame.x = frame.w * initCol;
		frame.y = frame.y * initRow;
		position.w = frame.w * 1.5;
		position.h = frame.h * 1.5;
		position.x = 100;
		position.y = 200;
		break;
	case Player::PlayerType::PL2:
		initCol = 6;
		lastCol = initCol + 3;
		initRow = 4;
		lastRow = initRow + 4;
		frame.x = frame.w * initCol;
		frame.y = frame.y * initRow;
		position.w = frame.w * 1.5;
		position.h = frame.h * 1.5;
		position.x = 400;
		position.y = 200;
		break;
	default:
		frame.x = 0;
		frame.y = 0;
		frameCount = 0;
		break;
	}

}

void Player::SetScore(int sc)
{
	score = sc;
}

bool Player::Move(InputData* input)
{
	dir = EDirection::NONE;
	Vec2D newposition = {position.x,position.y};

	switch (type)
	{
	case PlayerType::PL1:
		if (input->IsPressed(InputKeys::D)) {
			newposition.x++;
			dir = EDirection::RIGHT;
		}
		if (input->IsPressed(InputKeys::A)) {
			newposition.x--;
			dir = EDirection::LEFT;
		}
		if (input->IsPressed(InputKeys::W)) {
			newposition.y--;
			dir = EDirection::UP;
		}
		if (input->IsPressed(InputKeys::S)) {
			newposition.y++;
			dir = EDirection::DOWN;
		}
		break;
	case PlayerType::PL2:
		if (input->IsPressed(InputKeys::LEFTARROW)) {
			newposition.x--;
			dir = EDirection::LEFT;
		}
		if (input->IsPressed(InputKeys::RIGHTARROW)) {
			newposition.x++;
			dir = EDirection::RIGHT;
		}
		if (input->IsPressed(InputKeys::UPARROW)) {
			newposition.y--;
			dir = EDirection::UP;
		}
		if (input->IsPressed(InputKeys::DOWNARROW)) {
			newposition.y++;
			dir = EDirection::DOWN;
		}
		break;
	default:
		break;

	}
	if (newposition.x + position.w > input->GetScreenSize()->x || newposition.x < 0) newposition.x = position.x;
	if (newposition.y + position.h > input->GetScreenSize()->y || newposition.y < 0) newposition.y = position.y;
	if  (newposition.y < linelimit) newposition.y = position.y;

	if (newposition.x != position.x || newposition.y != position.y) {
		position.y = newposition.y;
		position.x = newposition.x;
		return true;
	}
	return false;
}

void Player::UpdateSprite()
{
	if (dir != EDirection::NONE) frameCount++;

	if (FPS / frameCount <= 9)
	{
		frameCount = 0;
		frame.x -= frame.w;
		if (frame.x < frame.w * initCol) {
			frame.x = frame.w * (initCol + 2);
		}
	}
	switch (dir)
	{
	case EDirection::NONE:
		frame.y = (initRow + 0) * frame.h;
		frame.x = (frame.w * initCol) + frame.w;
		break;
	case EDirection::RIGHT:
		frame.y = (initRow + 2) * frame.h;
		break;
	case EDirection::LEFT:
		frame.y = (initRow + 1) * frame.h;
		break;
	case EDirection::UP:
		frame.y = (initRow + 3) * frame.h;
		break;
	case EDirection::DOWN:
		frame.y = (initRow + 0) * frame.h;
		break;
	default:
		break;
	}
}

void Player::UpdateCollisions(std::vector<Sack*>& sacks, InputData* input)
{
	for (Sack* s : sacks) {
		if (Collisions::ConfirmCollision(position, *s->GetPosition())) {
			Vec2D randomPos = Vec2D::randomVec(150, SCREEN_WIDTH < SCREEN_HEIGHT ? SCREEN_WIDTH - 150 : SCREEN_HEIGHT - 150);
			s->SetPosition(randomPos);
			score++;
		}
	}
}
