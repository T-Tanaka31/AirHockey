//	============================================================
//		ヘッダーをインクルードする場所
//	============================================================
#include "Definition/Definition.h"
#include "Manager/InputManager.h"
#include "Manager/ScoreManager.h"
#include "Manager/TimeManager.h"
#include "Manager/AudioManager.h"
#include "Manager/GameManager.h"
#include "Manager/EffectManager.h"

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
	
#if _DEBUG
	SetOutApplicationLogValidFlag(TRUE);
#else
	SetOutApplicationLogValidFlag(FALSE);
#endif
	
	//	ウィンドウのサイズを変更する
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, FPS);
	//	起動時のウィンドウのモード設定する
	ChangeWindowMode(TRUE);		//	true : Windowモード, false : FullScreen

	SetMainWindowText("AirHockey");

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
	GameManager::GetInstance()->Init();
	//	============================================================
	//		ゲームのメインループ
	//	============================================================
	while (1) {
		//	ウィンドウのメッセージを処理する
		if (ProcessMessage() == -1)
			break;

		if (GameManager::GetInstance()->GetIsEnd()) break;

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
		EffectManager::GetInstance()->Update();
		AudioManager::GetInstance()->Update();
		GameManager::GetInstance()->Update();

		//	画面をクリアする
		ClearDrawScreen();

		//	============================================================
		//		ゲームの描画処理	処理順に注意
		//	============================================================
		GameManager::GetInstance()->Render();

		// 画面の更新
		ScreenFlip();
		// DXライブラリの終了
		if (ProcessMessage() != 0) break;

		//	処理が早すぎた場合に待つ
		/*while (1) {
			if (GetNowCount() - time >= 1000 / FPS)
				break;
		}*/
		while (GetNowCount() - time < 1000 / FPS) {
			Sleep(1);
		}

	}

	//	============================================================
	//		ゲームの解放処理
	//	============================================================ 
	TimeManager::DestroyInstance();
	InputManager::DestroyInstance();
	ScoreManager::DestroyInstance();
	EffectManager::DestroyInstance();
	AudioManager::DestroyInstance();
	GameManager::DestroyInstance();
	//	============================================================
	//		DxLibの解放処理
	//	============================================================
	//	DxLibの終了

	InitSoundMem();
	InitGraph();
	InitFontToHandle();

	DxLib_End();

	return 0;
}