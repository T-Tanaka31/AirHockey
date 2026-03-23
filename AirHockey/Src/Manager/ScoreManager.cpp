#include "ScoreManager.h"
#include "../Definition/Definition.h"
#include <DxLib.h>
#include "../Utility/ColorUtility.h"

namespace GC = GameConfig;

//	静的メンバ変数の初期化
ScoreManager* ScoreManager::pInstance = nullptr;

void ScoreManager::CreateInstance() {
	pInstance = new ScoreManager();
}

ScoreManager* ScoreManager::GetInstance() {
	if (pInstance == nullptr)
		CreateInstance();

	return pInstance;
}

void ScoreManager::DestroyInstance() {
	if (pInstance != nullptr) {
		delete pInstance;
		pInstance = nullptr;
	}
}

ScoreManager::ScoreManager()
	: leftGoal(0, GC::Goal::Top, GC::Goal::Width, GC::Goal::Bottom)
	, rightGoal(WINDOW_WIDTH - GC::Goal::Width, GC::Goal::Top, WINDOW_WIDTH, GC::Goal::Bottom)
	, puck(nullptr)
	, player1Mallet(nullptr)
	, player2Mallet(nullptr)
	, p1Color(COLOR_RED)
	, p2Color(COLOR_RED)
	, scorePosY(50){
}

void ScoreManager::Update() {
	const auto pos = puck->GetPosition();
	const auto r = puck->GetRadius();

	// 左ゴール
	if (puck->GetPosition().x + puck->GetRadius() < leftGoal.x2) {
		player2.Add(1);
		player2Mallet->SetRainbow(true);
		puck->StartReturn(GC::PuckSpawn::LeftSpawn(), GC::PuckSpawn::LeftTarget(), VGet(-0.5f, 1.5f, 0));
		ResetRound();
	}

	// 右ゴール
	if (puck->GetPosition().x - puck->GetRadius() > WINDOW_WIDTH) {
		player1.Add(1);
		player1Mallet->SetRainbow(true);
		puck->StartReturn(GC::PuckSpawn::RightSpawn(), GC::PuckSpawn::RightTarget(), VGet(0.5f, 1.5f, 0));
		ResetRound();
	}

	if (player2Mallet->GetIsRainbow()) {
		p2Color = ColorUtility::ToRainbowColor(p2Color);
		SetFontSize(120);
		scorePosY = GC::Court::HalfCourt.y - 50;
		return;
	}
	else if (player1Mallet->GetIsRainbow()) {
		p1Color = ColorUtility::ToRainbowColor(p1Color);
		SetFontSize(120);
		scorePosY = GC::Court::HalfCourt.y - 50;
		return;
	}
	else {
		p2Color = COLOR_RED;
		p1Color = COLOR_RED;
		SetFontSize(60);
		scorePosY = 50;
	}
}

void ScoreManager::Draw() const {
	DrawFormatString(GC::Court::HalfCourt.x - 200, scorePosY, p1Color, "%d", player1.GetValue());
	DrawFormatString(GC::Court::HalfCourt.x + 140, scorePosY, p2Color, "%d", player2.GetValue());
}

void ScoreManager::ResetRound() {
	player1Mallet->StartReturn();
	player2Mallet->StartReturn();
}