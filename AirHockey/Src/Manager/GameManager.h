#pragma once
#include "../GameSystem/GameState.h"
#include "../GameObject/Mallet/Mallet.h"
#include "../GameObject/Puck/Puck.h"
#include "../GameSystem/Goal.h"

class GameManager {
#pragma region シングルトンのデータ構造
private:
	static GameManager* pInstance;

private:
	GameManager();

	~GameManager() = default;

public:
	GameManager(const GameManager&) = delete;
	GameManager& operator = (const GameManager&) = delete;
	GameManager(GameManager&&) = delete;
	GameManager& operator = (GameManager&&) = delete;

private:
	static void CreateInstance();

public:
	static GameManager* GetInstance();

	static void DestroyInstance();
#pragma endregion

private:
	int modelHandle;

	//	ゲーム状態
	GameState state;

	//	ゲームオブジェクト
	Mallet* player1;
	Mallet* player2;
	Puck* puck;

	//	ゴール
	Goal* leftGoal;
	Goal* rightGoal;

	int winnerID = 0;

	bool changeResult = false;

	int color = 0;

public:
	void Init();
	void Update();
	void Render();

	void Delete();

private:
	//	内部処理
	void UpdateGamePlay();
	void UpdateResult();

	void CheckGoal();
	void ResetRound();

	void ResetGame();

	void HandleMalletCollision(Mallet* _mallet, unsigned int _sparkColor);

	void CheckWinCondition(int _playerID, int _score);
};

