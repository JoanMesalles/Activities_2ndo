#include "Player.h"
#include "Sack.h"

Player::Player()
{
	position.x = 0;
	position.y = 0;
	frame.x = 0;
	frame.y = 0;
	type = PlayerType::NONE;
	dir = EDirection::NONE;
	score = 0;
	initCol = lastCol = initRow = lastRow =  0;
	frameCount = 0;

}

void Player::Update(InputData* input, std::vector<Sack*>& sacks, std::vector<Player*> players)
{
	Move(input, players);
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
		position.w = initialPositionP1.w = frame.w * 1.5;
		position.h = initialPositionP1.h = frame.h * 1.5;
		position.x = initialPositionP1.x = 50;
		position.y = initialPositionP1.y = 200;
		break;
	case Player::PlayerType::PL2:
		initCol = 6;
		lastCol = initCol + 3;
		initRow = 4;
		lastRow = initRow + 4;
		frame.x = frame.w * initCol;
		frame.y = frame.y * initRow;
		position.w = initialPositionP2.w = frame.w * 1.5;
		position.h = initialPositionP2.h = frame.h * 1.5;
		position.x = initialPositionP2.x = 700;
		position.y = initialPositionP2.y = 200;
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

void Player::Reset()
{
	switch (type)
	{
	case Player::PlayerType::PL1:
		position = initialPositionP1;
		break;
	case Player::PlayerType::PL2:
		position = initialPositionP2;
		break;
	default:
		break;
	}
}

bool Player::Move(InputData* input, std::vector<Player*> players)
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
	if (newposition.y < linelimit) newposition.y = position.y;

	for (Player* pi : players) {
		if(pi->GetType() != type){
			if (Collisions::ConfirmCollision(Rect(newposition.x, newposition.y, position.w, position.h), pi->GetPosition())) {
				if(pi->GetPosition()->x + pi->GetPosition()->w > newposition.x || pi->GetPosition()->x < newposition.x + position.w)
					newposition.x = position.x;
				if (pi->GetPosition()->y + pi->GetPosition()->h > newposition.y || pi->GetPosition()->y < newposition.y + position.h)
					newposition.y = position.y;
			}
		}
	}


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
