//	============================================================
//		ヘッダーをインクルードする場所
//	============================================================
#include "Definition/Definition.h"
#include "Manager/InputManager.h"
#include "GameObject/Mallet/Mallet.h"

/*
 *	@brief		Windowプログラムのエントリーポイント
 *	@param[in]	HINSTANCE	今回は不要
 *	@param[in]	HINSTANCE	今回は不要
 *	@param[in]	LPSTR		今回は不要
 *	@param[in]	int
 *	@return		int
 *	@tips		WINAPI
 */
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
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

	Mallet* player1 = new Mallet(PLAYER1_START_POS, 70.0f, 10.0f, 0, WINDOW_WIDTH / 2, 0, WINDOW_HEIGHT, "Player1");

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

		//pAtt->CheckCircleCollision();

		//pPack->CircleCollision222(pAtt);

		//eAtt->MoveAttacler()


		//	画面をクリアする
		ClearDrawScreen();

		//	============================================================
		//		ゲームの描画処理	処理順に注意
		//	============================================================

#if _DEBUG
		//	キャラクターの位置関係がわかるように地面にラインを描画する
		{
			float x1 = 0;
			float x2 = 0;
			float Xver2 = 1900;
			float y1 = 0;
			float y2 = 1080;
			float Yver2 = 0;

			for (int i = 0; i < 500; i++) {
				DrawLine(x1, y1, x2, y2, COLOR_GREEN);    // 線を描画
				x1 += 10;
				x2 += 10;
			}

			for (int i = 0; i < 500; i++) {
				DrawLine(0, y1, Xver2, Yver2, COLOR_GREEN);
				y1 += 10;
				Yver2 += 10;
			}

			DrawLine(WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT - 400, COLOR_BLUE);

			DrawLine(WINDOW_WIDTH / 2, 400, WINDOW_WIDTH / 2, WINDOW_HEIGHT, COLOR_BLUE);

			DrawCircle(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 100, COLOR_BLUE, FALSE);

			DrawLine(40, 200, 40, 400, COLOR_YELLOW);
			DrawLine(0, (WINDOW_HEIGHT * 2) / 3, 40, (WINDOW_HEIGHT * 2) / 3, COLOR_YELLOW);
			DrawLine(0, 400, 40, 400, COLOR_YELLOW);

			DrawLine(1160, 200, 1160, 400, COLOR_YELLOW);
			DrawLine(1200, 200, 1160, 200, COLOR_YELLOW);
			DrawLine(1200, 400, 1160, 400, COLOR_YELLOW);

		}
#endif
		InputManager::GetInstance()->Update();

		DrawExtendGraph(0, 0,WINDOW_WIDTH, WINDOW_HEIGHT,  CourtHandle, true);

		player1->UpdateByGamepad(0);
		player1->Render();

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

	InputManager::GetInstance()->DestroyInstance();
	//delete eAtt;

	//	============================================================
	//		DxLibの解放処理
	//	============================================================
	//	DxLibの終了
	DxLib_End();

	return 0;
}