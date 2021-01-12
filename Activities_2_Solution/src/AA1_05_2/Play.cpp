#include "Play.h"

Play::Play()
{
	//Players

	Renderer::getInstance()->LoadTexture(Txtr_Players, "../../res/img/spCastle.png");

	AddPlayer(Renderer::getInstance()->GetTextureSize(Txtr_Players).x, Renderer::getInstance()->GetTextureSize(Txtr_Players).y, Player::PlayerType::PL1);
	AddPlayer(Renderer::getInstance()->GetTextureSize(Txtr_Players).x, Renderer::getInstance()->GetTextureSize(Txtr_Players).y, Player::PlayerType::PL2);

	// Sacks

	Renderer::getInstance()->LoadTexture(Txtr_Sacks, "../../res/img/gold.png");

	for (int i = 0; i < 10; i++) {
		AddSacks();
	}

	//Score

	Renderer::getInstance()->LoadTexture(Txtr_SC, "../../res/img/num.png");

	Renderer::getInstance()->LoadRect(Txtr_SC, Rect(50, 5, (Renderer::getInstance()->GetTextureSize(Txtr_SC).x / 10) / 2, Renderer::getInstance()->GetTextureSize(Txtr_SC).y / 2));
	Renderer::getInstance()->LoadRect(F_Txtr_SC, Rect(0, 0, Renderer::getInstance()->GetTextureSize(Txtr_SC).x / 10, Renderer::getInstance()->GetTextureSize(Txtr_SC).y));


#pragma endregion
	//Timmer
	Renderer::getInstance()->LoadFont(Font(F_Timmer, "../../res/ttf/mono.ttf", 25));

	Renderer::getInstance()->LoadTextureText(F_Timmer, Text(Txtr_Time, "Time: ", Color(0, 0, 0, 255)));

	Renderer::getInstance()->LoadRect(Txtr_Time, Rect(SCREEN_WIDTH - 150, 10, Renderer::getInstance()->GetTextureSize(Txtr_Time).x, Renderer::getInstance()->GetTextureSize(Txtr_Time).y));

	//Timer



	Renderer::getInstance()->LoadRect(Txtr_Time, Rect(SCREEN_WIDTH - 100, 10, Renderer::getInstance()->GetTextureSize(Txtr_Time).x, Renderer::getInstance()->GetTextureSize(Txtr_Time).y));


	//UI

	Renderer::getInstance()->LoadTextureText(F_Timmer, Text(Txtr_Text_SC_P1, "P1: ", Color(0, 0, 0, 255)));

	Renderer::getInstance()->LoadRect(Txtr_Text_SC_P1, Rect(10, 10, Renderer::getInstance()->GetTextureSize(Txtr_Text_SC_P1).x, Renderer::getInstance()->GetTextureSize(Txtr_Text_SC_P1).y));

	Renderer::getInstance()->LoadTextureText(F_Timmer, Text(Txtr_Text_SC_P2, "P2: ", Color(0, 0, 0, 255)));

	Renderer::getInstance()->LoadRect(Txtr_Text_SC_P2, Rect(10, 50, Renderer::getInstance()->GetTextureSize(Txtr_Text_SC_P2).x, Renderer::getInstance()->GetTextureSize(Txtr_Text_SC_P2).y));

	Renderer::getInstance()->LoadTextureText(F_Timmer, Text(Txtr_Time, s.c_str(), Color(0, 0, 0, 255)));

}

void Play::Draw() {
	Renderer::getInstance()->Clear();

	//BG
	Renderer::getInstance()->PushImage(Txtr_BG_Game, Txtr_BG_Game);

	//Players 
	for (Player* p : players) {
		Renderer::getInstance()->PushSprite(Txtr_Players, p->GetFrame(), p->GetPosition());

	}

	for (int i = 0; i < players.size(); i++) {

		Player* pl = players.at(i);

		Renderer::getInstance()->PushSprite(Txtr_SC, &Rect(trunc((pl->GetScore()) * 0.1) * Renderer::getInstance()->GetRect(F_Txtr_SC).w, 0, Renderer::getInstance()->GetRect(F_Txtr_SC).w, Renderer::getInstance()->GetRect(F_Txtr_SC).h),
			&Rect(Renderer::getInstance()->GetRect(Txtr_SC).x, Renderer::getInstance()->GetRect(Txtr_SC).y + (Renderer::getInstance()->GetRect(Txtr_SC).h * i), Renderer::getInstance()->GetRect(Txtr_SC).w, Renderer::getInstance()->GetRect(Txtr_SC).h));

		Renderer::getInstance()->PushSprite(Txtr_SC, &Rect(trunc((pl->GetScore()) % 10) * Renderer::getInstance()->GetRect(F_Txtr_SC).w, 0, Renderer::getInstance()->GetRect(F_Txtr_SC).w, Renderer::getInstance()->GetRect(F_Txtr_SC).h),
			&Rect(Renderer::getInstance()->GetRect(Txtr_SC).x + (Renderer::getInstance()->GetRect(Txtr_SC).w * 1), Renderer::getInstance()->GetRect(Txtr_SC).y + (Renderer::getInstance()->GetRect(Txtr_SC).h * i), Renderer::getInstance()->GetRect(Txtr_SC).w, Renderer::getInstance()->GetRect(Txtr_SC).h));
	}

	//Sacks
	for (Sack* sack : sacks) {
		Renderer::getInstance()->PushImage(Txtr_Sacks, sack->GetPosition());
	}

	//UI

	Renderer::getInstance()->PushImage(Txtr_Time, Txtr_Time);

	Renderer::getInstance()->PushImage(Txtr_Text_SC_P1, Txtr_Text_SC_P1);

	Renderer::getInstance()->PushImage(Txtr_Text_SC_P2, Txtr_Text_SC_P2);

	Renderer::getInstance()->Render();

}

void Play::Update()
{
	InputManager::getInstance()->Update();

	if (InputManager::getInstance()->JustPressed(InputKeys::QUIT) == true) {
		sceneState = ESceneState::GO_EXIT;
	}

	for (Player* pi : players) {
		pi->Update(sacks, players);
	}

	if (InputManager::getInstance()->IsPressed(InputKeys::ESC)) {
		sceneState = ESceneState::GO_MENU;
	}

	timeDown -= *InputManager::getInstance()->GetDeltaTime();

	s = F2StrFormat(timeDown, 0);
	
	if (timeDown <= 0) {
		sceneState = ESceneState::GO_MENU;
	}


}

Play::~Play()
{
	for (Player* pi : players) {
		delete pi;
		pi = nullptr;
	}

	players.clear();
	for (Sack* s : sacks) {
		delete s;
		s = nullptr;
	}
	sacks.clear();
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