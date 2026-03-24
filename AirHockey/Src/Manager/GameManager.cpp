#include "GameManager.h"
#include "ScoreManager.h"
#include "FadeManager.h"
#include "../Definition/Definition.h"

GameManager* GameManager::pInstance = nullptr;

namespace GC = GameConfig;

void GameManager::CreateInstance() {
	pInstance = new GameManager();
}

GameManager* GameManager::GetInstance() {
	if (pInstance == nullptr)
		CreateInstance();
	return pInstance;
}

void GameManager::DestroyInstance() {
	delete pInstance;
	pInstance = nullptr;
}

GameManager::GameManager()
	: state(GameState::Playing)
	, player1(nullptr)
	, player2(nullptr)
	, puck(nullptr)
	, leftGoal(nullptr)
	, rightGoal(nullptr)
	, changeResult(false)
	, modelHandle(0){
}

void GameManager::Init() {

	modelHandle = LoadGraph("Res/”wŒi4.png");

	player1 = new Mallet(
		GC::Mallet::Player1StartPos,
		GC::Mallet::Radius,
		GC::Mallet::Speed,
		GC::Mallet::P1Limit.minX, GC::Mallet::P1Limit.maxX,
		GC::Mallet::P1Limit.minY, GC::Mallet::P1Limit.maxY,
		COLOR_CYAN,
		"Player1"
	);

	player2 = new Mallet(
		GC::Mallet::Player2StartPos,
		GC::Mallet::Radius,
		GC::Mallet::Speed,
		GC::Mallet::P2Limit.minX, GC::Mallet::P2Limit.maxX,
		GC::Mallet::P2Limit.minY, GC::Mallet::P2Limit.maxY,
		COLOR_PINK,
		"Player2"
	);

	puck = new Puck(
		GC::Puck::StartPos,
		GC::Puck::Radius,
		GC::Puck::Friction,
		"Puck"
	);

	leftGoal = new Goal(0, GC::Goal::Top, GC::Goal::Width, GC::Goal::Bottom);
	rightGoal = new Goal(WINDOW_WIDTH - GC::Goal::Width, GC::Goal::Top, WINDOW_WIDTH, GC::Goal::Bottom);

	ScoreManager::GetInstance()->SetPuck(puck);
	ScoreManager::GetInstance()->SetMallet(player1, player2);

	player1->SetPuck(puck);
	player2->SetPuck(puck);
	player1->SetPadID(0);
	player2->SetPadID(1);

	SetFontSize(60);
}

void GameManager::Update() {

	if (changeResult) {
		FadeManager::GetInstance()->Update();

		if (FadeManager::GetInstance()->GetFadeState() == FadeState::FadeEnd) {

			if (state == GameState::Playing && winnerID != 0) {
				state = GameState::Result;
				FadeManager::GetInstance()->FadeIn(1.0f); 
				return;
			}

			if (state == GameState::Result && FadeManager::GetInstance()->GetAlpha() >= 255) {
				ResetGame();
				FadeManager::GetInstance()->FadeIn(1.0f); 
				return;
			}

			changeResult = false;
		}
		return;
	}

	switch (state) {
	case GameState::Playing:
		UpdateGamePlay();
		break;

	case GameState::Result:
		UpdateResult();
		break;
	}
}

void GameManager::Render() {
	if (state == GameState::Result) {
		DrawExtendGraph(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, modelHandle, TRUE);

		if (winnerID == 1)
			DrawString((int)GC::Court::HalfCourt.x - 300, (int)GC::Court::HalfCourt.y, "Player 1 WIN!", GetColor(255, 255, 0));
		else if (winnerID == 2)
			DrawString((int)GC::Court::HalfCourt.x - 300, (int)GC::Court::HalfCourt.y, "Player 2 WIN!", GetColor(255, 255, 0));

		DrawString((int)GC::Court::HalfCourt.x - 600, (int)GC::Court::HalfCourt.y + 200, "Press SPACE to Restart", GetColor(255, 255, 255));

		FadeManager::GetInstance()->Render();
		return;
	}

	puck->Render();
	player1->Render();
	player2->Render();

	DrawBox((int)leftGoal->x1, (int)leftGoal->y1, (int)leftGoal->x2, (int)leftGoal->y2, COLOR_BLACK, FALSE);
	DrawBox((int)rightGoal->x1, (int)rightGoal->y1, (int)rightGoal->x2, (int)rightGoal->y2, COLOR_BLACK, FALSE);

	ScoreManager::GetInstance()->Draw();

	FadeManager::GetInstance()->Render();
}

void GameManager::UpdateGamePlay() {

	player1->Update();
	player2->Update();
	puck->Update();

	CheckGoal();

	if (ScoreManager::GetInstance()->GetPlayer1Score() >= GC::Score::WinScore) {
		winnerID = 1;
		FadeManager::GetInstance()->FadeOut(1.0f);
		changeResult = true;
	}
	else if (ScoreManager::GetInstance()->GetPlayer2Score() >= GC::Score::WinScore) {
		winnerID = 2;
		FadeManager::GetInstance()->FadeOut(1.0f);
		changeResult = true;
	}
}

void GameManager::UpdateResult() {
	static bool lastSpaceState = false;
	bool currentSpaceState = CheckHitKey(KEY_INPUT_SPACE);

	if (currentSpaceState && !lastSpaceState) {
		if (!changeResult) { 
			FadeManager::GetInstance()->FadeOut(1.0f);
			changeResult = true;
		}
	}

	// ó‘Ô‚ðXV
	lastSpaceState = currentSpaceState;
}

void GameManager::CheckGoal() {
	const auto pos = puck->GetPosition();
	const float r = puck->GetRadius();

	if (pos.x + r < leftGoal->x2) {
		ScoreManager::GetInstance()->AddScore(2);
		player2->SetRainbow(true);
		puck->StartReturn(GC::PuckSpawn::LeftSpawn(), GC::PuckSpawn::LeftTarget(), VGet(-0.5f, 1.5f, 0));
		ResetRound();
	}

	if (pos.x - r > rightGoal->x1) {
		ScoreManager::GetInstance()->AddScore(1);
		player1->SetRainbow(true);
		puck->StartReturn(GC::PuckSpawn::RightSpawn(), GC::PuckSpawn::RightTarget(), VGet(0.5f, 1.5f, 0));
		ResetRound();
	}
}

void GameManager::ResetRound() {
	player1->StartReturn();
	player2->StartReturn();
}

void GameManager::ResetGame() {
	Delete();
	Init();
	ScoreManager::GetInstance()->ResetScore();
	state = GameState::Playing;
	winnerID = 0;
}

void GameManager::Delete() {
	delete player1;
	delete player2;
	delete puck;
	delete leftGoal;
	delete rightGoal;

	player1 = nullptr;
	player2 = nullptr;
	puck = nullptr;
	leftGoal = nullptr;
	rightGoal = nullptr;

	DeleteGraph(modelHandle);
	modelHandle = -1;
}