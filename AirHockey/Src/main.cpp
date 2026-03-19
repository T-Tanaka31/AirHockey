//	============================================================
//		ヘッダーをインクルードする場所
//	============================================================
#include "Definition/Definition.h"
#include "Manager/InputManager.h"
#include "Manager/ScoreManager.h"
#include "Manager/TimeManager.h"
#include "Manager/GameManager.h"
#include "GameObject/Mallet/Mallet.h"
#include "GameObject/Puck/Puck.h"
#include "GameSystem/Goal.h"

/*
 *	@brief		Windowプログラムのエントリーポイント
 *	@param[in]	HINSTANCE	今回は不要
 *	@param[in]	HINSTANCE	今回は不要
 *	@param[in]	LPSTR		今回は不要
 *	@param[in]	int
 *	@return		int
 *	@tips		WINAPI
 */
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	//	============================================================
	//		DxLibの初期化処理	理解するまで触らない
	//	============================================================
	//	ウィンドウのサイズを変更する
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, FPS);
	//	起動時のウィンドウのモード設定する
	ChangeWindowMode(TRUE);		//	true : Windowモード, false : FullScreen
	//	背景色の設定する
	SetBackgroundColor(196, 196, 196);

	//	DxLibの初期化
	if (DxLib_Init() == -1)
		return 0;

	//	描画する先を設定する	裏画面に変更する
	SetDrawScreen(DX_SCREEN_BACK);

	//	図形描画のZバッファの有効化
	{
		//	Zバッファを使用するかどうか		デフォルト : FALSE
		SetUseZBuffer3D(FALSE);
		//	Zバッファを書き込むかどうか		デフォルト : FALSE
		SetWriteZBuffer3D(FALSE);
	}

	//	ライティング
	{
		//	ライトの計算をするかどうか		デフォルト : TRUE
		SetUseLighting(TRUE);
		//	標準ライトを使用するかどうか	デフォルト : TRUE
		SetLightEnable(TRUE);
		//	グローバル環境光の設定
		SetGlobalAmbientLight(GetColorF(1.0f, 1.0f, 1.0f, 1.0f));	//	ライトの計算で α値は使わない
	}

	//	============================================================
	//		ゲームの初期化処理
	//	============================================================
	//	FPS調整用
	int time;

	int CourtHandle = LoadGraph("Res/court.png");

	namespace GC = GameConfig;

	Mallet* player1 = new Mallet(
		GC::Mallet::Player1StartPos,	//	初期位置
		GC::Mallet::Radius,				//	半径
		GC::Mallet::Speed,				//	速度
		GC::Mallet::P1Limit.minX, GC::Mallet::P1Limit.maxX,	//	移動範囲制限(横)
		GC::Mallet::P1Limit.minY, GC::Mallet::P1Limit.maxY,	//	移動範囲制限(縦)
		COLOR_CYAN,		//	色
		"Player1");		//	タグ

	Mallet* player2 = new Mallet(
		GC::Mallet::Player2StartPos,	//	初期位置
		GC::Mallet::Radius,				//	半径
		GC::Mallet::Speed,				//	速度
		GC::Mallet::P2Limit.minX, GC::Mallet::P2Limit.maxX,	//	移動範囲制限(横)
		GC::Mallet::P2Limit.minY, GC::Mallet::P2Limit.maxY,	//	移動範囲制限(縦)
		COLOR_PINK,	//	色
		"Player3");		//	タグ

	Puck* puck = new Puck(
		GC::Puck::StartPos,	//	初期位置
		GC::Puck::Radius,	//	半径
		GC::Puck::Friction,	//	摩擦抵抗
		"Puck");			//	タグ

	ScoreManager::GetInstance()->SetPuck(puck);
	ScoreManager::GetInstance()->SetMallet(player1, player2);

	player1->SetPuck(puck);
	player2->SetPuck(puck);

	//	============================================================
	//		ゲームのメインループ
	//	============================================================
	while (1) {
		//	ウィンドウのメッセージを処理する
		if (ProcessMessage() == -1)
			break;

		//	FPSの調整
		time = GetNowCount();

		//	============================================================
		//		ゲームの更新処理
		//	============================================================
		// 描画先画面を裏画面にする
		SetDrawScreen(DX_SCREEN_BACK);

		InputManager::GetInstance()->Update();
		ScoreManager::GetInstance()->Update();
		TimeManager::GetInstance()->Update();
		GameManager::GetInstance()->Update();

		player1->Update();
		player2->Update();

		player1->UpdateByGamepad(0);
		player2->UpdateByGamepad(1);
		puck->Update();

		//	画面をクリアする
		ClearDrawScreen();

		//	============================================================
		//		ゲームの描画処理	処理順に注意
		//	============================================================
		DrawExtendGraph(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, CourtHandle, true);

		GameManager::GetInstance()->Render();

		puck->Render();
		player1->Render();
		player2->Render();

		ScoreManager::GetInstance()->Draw();

		DrawBox(0, GC::Goal::Top, -GC::Goal::Width, GC::Goal::Bottom, COLOR_BLACK, FALSE);
		DrawBox(WINDOW_WIDTH, GC::Goal::Top, WINDOW_WIDTH + GC::Goal::Width, GC::Goal::Bottom, COLOR_BLACK, FALSE);


		// 画面の更新
		ScreenFlip();
		// DXライブラリの終了
		if (ProcessMessage() != 0) break;

		//	裏画面と表画面を切り替える
		//ScreenFlip();

		//	処理が早すぎた場合に待つ
		while (1) {
			if (GetNowCount() - time >= 1000 / FPS)
				break;
		}
	}

	//	============================================================
	//		ゲームの解放処理
	//	============================================================

	delete player1;
	delete player2;
	delete puck;

	InputManager::DestroyInstance();
	ScoreManager::DestroyInstance();
	TimeManager::DestroyInstance();
	GameManager::DestroyInstance();
	//	============================================================
	//		DxLibの解放処理
	//	============================================================
	//	DxLibの終了

	DxLib_End();

	return 0;
}