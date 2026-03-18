#include "ScoreManager.h"
#include "../Definition/Definition.h"
#include <DxLib.h>

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
	, player2Mallet(nullptr){
}

void ScoreManager::Update() {
	const auto pos = puck->GetPosition();
	const auto r = puck->GetRadius();

	// 左ゴール
	if (puck->GetPosition().x + puck->GetRadius() < leftGoal.x2) {
		player2.Add(1);
		ResetRound();
	}

	// 右ゴール
	if (puck->GetPosition().x - puck->GetRadius() > WINDOW_WIDTH) {
		player1.Add(1);
		ResetRound();
	}
}

void ScoreManager::Draw() const {
	DrawFormatString(820, 50, COLOR_RED, "%d", player1.GetValue());
	DrawFormatString(1100, 50, COLOR_RED, "%d", player2.GetValue());

}

void ScoreManager::ResetRound() {
	player1Mallet->SetPosition(GC::Mallet::Player1StartPos);
	player2Mallet->SetPosition(GC::Mallet::Player2StartPos);

	puck->ResetPuck();
}