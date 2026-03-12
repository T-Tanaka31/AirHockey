//#pragma once
//#include "../制作其の2/Definition.h"
//#include "../GameObject.h"
//
///*
// *	@breif	アタッカークラス
// */
//class EAttacker : public GameObject{
//private:	//	メンバ変数
//	int x, y;
//	char String[64];
//	int move;
//	int stickX, stickY;
//	int InputX, InputY;
//
//public:		//	コンストラクタとデストラクタ
//	/*
//	 *	@breif		コンストラクタ
//	 *	@param[in]	Vector _pos		初期化する座標
//	 */
//	EAttacker(VECTOR _pos = VZero);
//
//	/*
//	 *	@breif		デストラクタ
//	 */
//	~EAttacker();
//
//public:		//	メンバ関数
//	/*
//	 *	@function	Start
//	 *	@breif		初期化処理
//	 */
//	void Start();
//
//	/*
//	 *	@function	Update
//	 *	@breif		更新処理
//	 */
//	void Update();
//
//	/*
//	 *	@function	Render
//	 *	@breif		描画処理
//	 */
//	void Render();
//
//
//
//public:		//	Getter と Setter
//
//
//public:
//	void MoveAttacler();
//
//public:		//	オーバーライドした衝突検知
//	/*
//	 *	@function	OnTriggerEnter
//	 *	@brief		当たった瞬間
//	 *	@param[in]	Collider* _pCol
//	 */
//	void OnTriggerEnter(Collider* _pCol);
//
//	/*
//	 *	@function	OnTriggerEnter
//	 *	@brief		当たっている間
//	 *	@param[in]	Collider* _pCol
//	 */
//	void OnTriggerStay(Collider* _pCol);
//
//	/*
//	 *	@function	OnTriggerEnter
//	 *	@brief		離れた瞬間
//	 *	@param[in]	Collider* _pCol
//	 */
//	void OnTriggerExit(Collider* _pCol);
//};
