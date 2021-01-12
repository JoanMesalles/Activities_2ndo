#include "Play.h"

Play::Play()
{
	//Players

	renderer.LoadTexture(Txtr_Players, "../../res/img/spCastle.png");

	AddPlayer(renderer.GetTextureSize(Txtr_Players).x, renderer.GetTextureSize(Txtr_Players).y, Player::PlayerType::PL1);
	AddPlayer(renderer.GetTextureSize(Txtr_Players).x, renderer.GetTextureSize(Txtr_Players).y, Player::PlayerType::PL2);

	// Sacks

	renderer.LoadTexture(Txtr_Sacks, "../../res/img/gold.png");

	for (int i = 0; i < 10; i++) {
		AddSacks();
	}

	//Score

	renderer.LoadTexture(Txtr_SC, "../../res/img/num.png");

	renderer.LoadRect(Txtr_SC, Rect(50, 5, (renderer.GetTextureSize(Txtr_SC).x / 10) / 2, renderer.GetTextureSize(Txtr_SC).y / 2));
	renderer.LoadRect(F_Txtr_SC, Rect(0, 0, renderer.GetTextureSize(Txtr_SC).x / 10, renderer.GetTextureSize(Txtr_SC).y));


#pragma endregion
	//Timmer
	renderer.LoadFont(Font(F_Timmer, "../../res/ttf/mono.ttf", 25));

	renderer.LoadTextureText(F_Timmer, Text(Txtr_Time, "Time: ", Color(0, 0, 0, 255)));

	renderer.LoadRect(Txtr_Time, Rect(SCREEN_WIDTH - 150, 10, renderer.GetTextureSize(Txtr_Time).x, renderer.GetTextureSize(Txtr_Time).y));

	//Timer



	renderer.LoadRect(Txtr_Time, Rect(SCREEN_WIDTH - 100, 10, renderer.GetTextureSize(Txtr_Time).x, renderer.GetTextureSize(Txtr_Time).y));


	//UI

	renderer.LoadTextureText(F_Timmer, Text(Txtr_Text_SC_P1, "P1: ", Color(0, 0, 0, 255)));

	renderer.LoadRect(Txtr_Text_SC_P1, Rect(10, 10, renderer.GetTextureSize(Txtr_Text_SC_P1).x, renderer.GetTextureSize(Txtr_Text_SC_P1).y));

	renderer.LoadTextureText(F_Timmer, Text(Txtr_Text_SC_P2, "P2: ", Color(0, 0, 0, 255)));

	renderer.LoadRect(Txtr_Text_SC_P2, Rect(10, 50, renderer.GetTextureSize(Txtr_Text_SC_P2).x, renderer.GetTextureSize(Txtr_Text_SC_P2).y));

}

void Play::Draw() {
	renderer.Clear();

	//BG
	renderer.PushImage(Txtr_BG_Game, Txtr_BG_Game);

	//Players 
	for (Player* p : players) {
		renderer.PushSprite(Txtr_Players, p->GetFrame(), p->GetPosition());

	}

	for (int i = 0; i < players.size(); i++) {

		Player* pl = players.at(i);

		renderer.PushSprite(Txtr_SC, &Rect(trunc((pl->GetScore()) * 0.1) * renderer.GetRect(F_Txtr_SC).w, 0, renderer.GetRect(F_Txtr_SC).w, renderer.GetRect(F_Txtr_SC).h),
			&Rect(renderer.GetRect(Txtr_SC).x, renderer.GetRect(Txtr_SC).y + (renderer.GetRect(Txtr_SC).h * i), renderer.GetRect(Txtr_SC).w, renderer.GetRect(Txtr_SC).h));

		renderer.PushSprite(Txtr_SC, &Rect(trunc((pl->GetScore()) % 10) * renderer.GetRect(F_Txtr_SC).w, 0, renderer.GetRect(F_Txtr_SC).w, renderer.GetRect(F_Txtr_SC).h),
			&Rect(renderer.GetRect(Txtr_SC).x + (renderer.GetRect(Txtr_SC).w * 1), renderer.GetRect(Txtr_SC).y + (renderer.GetRect(Txtr_SC).h * i), renderer.GetRect(Txtr_SC).w, renderer.GetRect(Txtr_SC).h));
	}

	//Sacks
	for (Sack* sack : sacks) {
		renderer.PushImage(Txtr_Sacks, sack->GetPosition());
	}

	//UI

	renderer.PushImage(Txtr_Time, Txtr_Time);

	renderer.PushImage(Txtr_Text_SC_P1, Txtr_Text_SC_P1);

	renderer.PushImage(Txtr_Text_SC_P2, Txtr_Text_SC_P2);

	renderer.Render();



}

void Play::Update()
{
	for (Player* pi : players) {
		pi->Update(&input, sacks, players);
	}

	timeDown -= *input.GetDeltaTime();

	s = F2StrFormat(timeDown, 0);

	renderer.LoadTextureText(F_Timmer, Text(Txtr_Time, s.c_str(), Color(0, 0, 0, 255)));

}

void Play::AddSacks()
{
	Vec2D randomPos = Vec2D::randomVec(150, SCREEN_WIDTH < SCREEN_HEIGHT ? SCREEN_WIDTH - 100 : SCREEN_HEIGHT - 100);
	Sack* s = new Sack(40, 30, randomPos.x, randomPos.y);
	sacks.push_back(std::move(s));
}

void Play::AddPlayer(int texWidth, int texHeight, Player::PlayerType type)
{
	Player* p = new Player();
	p->SetPlayerValues(texWidth, texHeight, 12, 8, type);
	players.push_back(std::move(p));
}