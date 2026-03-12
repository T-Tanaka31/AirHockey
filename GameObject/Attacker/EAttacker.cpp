//#include "EAttacker.h"
//
//EAttacker::EAttacker(VECTOR _pos)
//	: x()
//	, y()
//	, move(5)
//	, String()
//	, stickX()
//	, stickY()
//	, InputX()
//	, InputY() 
//	, GameObject(_pos, "eAttacker") {
//}
//
//EAttacker::~EAttacker() {
//}
//
//void EAttacker::Start() {
//	x = 1080, y = 240;
//}
//
//void EAttacker::Update() {
//	// ＥＳＣキーが押されるまでループ
//
//
//		// パッド１の入力を取得
//	GetJoypadAnalogInput(&InputX, &InputY, DX_INPUT_PAD2);
//
//
//	// 画面に入力状態を表示する
//	{
//		ClearDrawScreen();
//	}
//
//	//// ジョイスティックの状態を取得
//	//GetJoypadAnalogInput(&x, &y, DX_INPUT_KEY_PAD1);
//
//// スティックの状態を取得
//	stickX = (InputX / 100); // X軸の値
//	stickY = (InputY / 100); // Y軸の値
//	// アタッカー
//	x += stickX * move; // X軸の移動
//	y += stickY * move; // Y軸の移動
//
//}
//
//void EAttacker::Render() {
//
//	// キャラクターの描画処理
//	DrawCircle(x, y, 50, blue, TRUE); // 赤い円でキャラクターを描画
//}
//
//void EAttacker::MoveAttacler() {
//
//	// キャラクターの位置を更新する処理
//	// ここでは仮にキャラクターの位置を (x, y) とする
//	//x = 320, y = 240; // 初期位置
//	//if (!(x <= 730 && x >= 70 && y <= 530 && y >= 70)) {
//	//	move = 1;
//	//}
//
//}
//
///*
// *	@function	OnTriggerEnter
// *	@brief		当たった瞬間
// *	@param[in]	Collider* _pCol
// */
//void EAttacker::OnTriggerEnter(Collider* _pCol) {
//}
//
///*
// *	@function	OnTriggerEnter
// *	@brief		当たっている間
// *	@param[in]	Collider* _pCol
// */
//void EAttacker::OnTriggerStay(Collider* _pCol) {
//}
//
///*
// *	@function	OnTriggerEnter
// *	@brief		離れた瞬間
// *	@param[in]	Collider* _pCol
// */
//void EAttacker::OnTriggerExit(Collider* _pCol) {
//}
