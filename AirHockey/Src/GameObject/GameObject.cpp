#include "GameObject.h"
#include "../Component/Collider.h"


/*
 *	@breif		コンストラクタ
 *	@param[in]	VECTOR _pos = VZero	初期化する座標
 */
GameObject::GameObject(VECTOR _pos, std::string _tag)
	: isVisible(true)
	, position(_pos)
	, scale(VOne)
	, rotation(VZero)
	, matrix(MGetIdent())
	, tag(_tag) {
}


/*
 *	@breif		デストラクタ
 */
GameObject::~GameObject() {

}

/*
 *	@function	Update
 *	@breif		更新処理
 */
void GameObject::Update() {
	//	非表示なら更新しない
	if (!isVisible)
		return;

	//	座標、回転、拡縮から行列を求める


	MATRIX mRotX = MGetRotX(Deg2Rad(rotation.x));		//	X軸回転行列
	MATRIX mRotY = MGetRotY(Deg2Rad(rotation.y));		//	Y軸回転行列
	MATRIX mRotZ = MGetRotZ(Deg2Rad(rotation.z));		//	Z軸回転行列

	//	X->Y->Z の順で回転行列を作成する
	MATRIX mRotXYZ = MMult(MMult(mRotX, mRotY), mRotZ);

	//	拡縮行列を取得する
	MATRIX mScale = MGetScale(scale);

	//	平行移動行列を取得する
	MATRIX mTranslate = MGetTranslate(position);

	//	行列の乗算は合成
	//	回転行列 -> 拡縮行列 -> 平行行列 の順に掛け合わせる
	//	(交換法則は成り立たない)
	matrix = MMult(MMult(mRotXYZ, mScale), mTranslate);

}

/*
 *	@function	OnTriggerEnter
 *	@breif		当たった瞬間
 *	@param[in]	collider* _pOther	当たった相手
 */
void GameObject::OnTriggerEnter(Collider* _pOther) {
}

/*
 *	@function	OnTriggerStay
 *	@breif		当たっている間
 *	@param[in]	collider* _pOther	当たった相手
 */
void GameObject::OnTriggerStay(Collider* _pOther) {
}

/*
 *	@function	OnTriggerExit
 *	@breif		離れた瞬間
 *	@param[in]	collider* _pOther	当たった相手
 */
void GameObject::OnTriggerExit(Collider* _pOther) {
}
