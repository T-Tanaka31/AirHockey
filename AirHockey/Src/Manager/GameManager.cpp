#include "GameManager.h"
#include "ScoreManager.h"
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
	if (pInstance != nullptr) {
		delete pInstance;
		pInstance = nullptr;
	}
}

GameManager::GameManager()
	: isWin(false)
	, modelHandle(){

}

void GameManager::Start() {
}

void GameManager::Update() {
	if ((ScoreManager::GetInstance()->GetPlayer1Score() >= GC::Score::WinScore || ScoreManager::GetInstance()->GetPlayer2Score() >= GC::Score::WinScore) && !isWin)
		isWin = true;
}

void GameManager::Render() {
	modelHandle = LoadGraph("Res/keke.png");
	if(isWin)
		DrawExtendGraph(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, modelHandle, true);
}

void GameManager::WinGame() {

}
