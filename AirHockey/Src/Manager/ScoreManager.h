#pragma once
#include "../GameSystem/Score.h"
#include "../GameSystem/Goal.h"
#include "../GameObject/Puck/Puck.h"
#include "../GameObject/Mallet/Mallet.h"
class ScoreManager {
#pragma region シングルトンのデータ構造
private:
	static ScoreManager* pInstance;

private:
	/*
	 *	@brief	コンストラクタ
	 *	@tips	外部で生成されないようにアクセス指定子をprivateにする
	 */
	ScoreManager();

	/*
	 *	@brief	デストラクタ
	 */
	~ScoreManager() = default;

public:	
	ScoreManager(const ScoreManager&) = delete;
	ScoreManager& operator = (const ScoreManager&) = delete;
	ScoreManager(ScoreManager&&) = delete;
	ScoreManager& operator = (ScoreManager&&) = delete;

private:	//	静的メンバ関数
	/*
	 *	@function	CreateInstance
	 *	@brief		自身のインスタンスを生成する
	 */
	static void CreateInstance();

public:		//	静的メンバ関数
	/*
	 *	@function	GetInstance
	 *	@brief		自身のインスタンスを取得する唯一の手段
	 *	@return		ScoreManager*	自身のインスタンスのアドレス
	 */
	static ScoreManager* GetInstance();

	/* 
	 *	@function	DestroyInstance
	 *	@brief		自身のインスタンスを破棄する唯一の手段
	 */
	static void DestroyInstance();
#pragma endregion

private:

	Score player1;
	Score player2;

	Goal leftGoal;
	Goal rightGoal;

	Puck* puck;

	Mallet* player1Mallet;
	Mallet* player2Mallet;

	int p1Color;
	int p2Color;

	float scorePosY;

public:

	void Update();
	void Draw() const;

	void ResetRound();

	int GetPlayer1Score() const { return player1.GetValue(); }
	int GetPlayer2Score() const { return player2.GetValue(); }

	void SetPuck(Puck* _puck) { puck = _puck; }
	void SetMallet(Mallet* _p1, Mallet* _p2) { player1Mallet = _p1, player2Mallet = _p2; }

};

