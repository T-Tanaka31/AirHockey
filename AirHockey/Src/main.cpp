//	============================================================
//		ヘッダーをインクルードする場所
//	============================================================
#include "Definition/Definition.h"
#include "Manager/InputManager.h"
#include "Manager/CollisionManager.h"
#include "GameObject/Mallet/Mallet.h"
#include "GameObject/Puck/Puck.h"
#include "Component/Goal.h"

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

	Mallet* player1 = new Mallet(PLAYER1_START_POS, MALLET_RADIUS, MALLET_SPEED, P1_MIN_X, P1_MAX_X, P1_MIN_Y, P1_MAX_Y, "Player1");
	Mallet* player2 = new Mallet(PLAYER2_START_POS, MALLET_RADIUS, MALLET_SPEED, P2_MIN_X, P2_MAX_X, P2_MIN_Y, P2_MAX_Y,"Player2");

	Goal leftGoal(0, GOAL_TOP, GOAL_WIDTH, GOAL_BOTTOM);
	Goal rightGoal(WINDOW_WIDTH - GOAL_WIDTH, GOAL_TOP, WINDOW_WIDTH, GOAL_BOTTOM);

	Puck* puck = new Puck(PUCK_START_POS, PUCK_RADIUS, PUCK_FRICTION, "Puck");

	player1->SetPuck(puck);
	player2->SetPuck(puck);


	//CollisionManager::GetInstance()->Register(eAtt->GetCollider());
	//	============================================================
	//		ゲームのメインループ
	//	============================================================
	while (1) {
		//	ウィンドウのメッセージを処理する
		if (ProcessMessage() == -1)
			break;

		//	FPSの調整
		time = GetNowCount();

		//	エスケープキーでウィンドウを閉じる
	/*	if (InputManager::GetInstance()->IsKeyDown(KEY_INPUT_ESCAPE))
			break;*/

			//	============================================================
			//		ゲームの更新処理
			//	============================================================
			 // 描画先画面を裏画面にする
		SetDrawScreen(DX_SCREEN_BACK);

		player1->UpdateByGamepad(0);
		player2->UpdateByGamepad(1);
		
		player1->Update();
		player2->Update();
		puck->Update();

		// 左ゴール
		if (puck->GetPosition().x + puck->GetRadius() < leftGoal.x2) {
			puck->ResetPuck();
		}

		// 右ゴール
		if (puck->GetPosition().x - puck->GetRadius() > WINDOW_WIDTH) {
			puck->ResetPuck();
		}


		InputManager::GetInstance()->Update();
		//	画面をクリアする
		ClearDrawScreen();

		//	============================================================
		//		ゲームの描画処理	処理順に注意
		//	============================================================
		DrawExtendGraph(0, 0,WINDOW_WIDTH, WINDOW_HEIGHT,  CourtHandle, true);

		player1->Render();
		player2->Render();
		puck->Render();

		DrawBox(0, GOAL_TOP, -GOAL_WIDTH, GOAL_BOTTOM, COLOR_BLACK, FALSE);
		DrawBox(WINDOW_WIDTH, GOAL_TOP, WINDOW_WIDTH + GOAL_WIDTH, GOAL_BOTTOM, COLOR_BLACK, FALSE);


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
	CollisionManager::DestroyInstance();



	//	============================================================
	//		DxLibの解放処理
	//	============================================================
	//	DxLibの終了

	DxLib_End();

	return 0;
}