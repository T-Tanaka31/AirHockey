#include "ScoreManager.h"
#include "../Definition/Definition.h"
#include <DxLib.h>
#include "../Utility/ColorUtility.h"

namespace GC = GameConfig;

//	Ã“Iƒƒ“ƒo•Ï”‚Ì‰Šú‰»
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
	: puck(nullptr)
	, player1Mallet(nullptr)
	, player2Mallet(nullptr)
	, p1Color(COLOR_RED)
	, p2Color(COLOR_RED)
	, scorePosY(50){
}

void ScoreManager::Update() {
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
	DrawFormatString((int)GC::Court::HalfCourt.x - 200, (int)scorePosY, p1Color, "%d", player1.GetValue());
	DrawFormatString((int)GC::Court::HalfCourt.x + 140, (int)scorePosY, p2Color, "%d", player2.GetValue());
}

void ScoreManager::AddScore(int playerID) {
	if (playerID == 1) {
		player1.Add(1);
	}
	else if (playerID == 2) {
		player2.Add(1);
	}
}

void ScoreManager::ResetScore() {
	player1.Reset();
	player2.Reset();
}
