//#include "Collider.h"
//
//Collider::Collider(GameObject* _pObj)
//	: isEnable(true)
//	, pGameObject(_pObj)
//	, matrix(MGetIdent()) {
//}
//
//Collider::~Collider() {
//}
//
//void Collider::Update() {
//}
//
//void Collider::Render() {
//}
//
//CircleCollider::CircleCollider(GameObject* _pAtk, VECTOR _offset, float _radius)
//	: Collider(_pAtk)
//	, worldCenter(VZero)
//	, localCenter(_offset)
//	, radius(_radius){
//}
//
//void CircleCollider::Update() {
//	//	無効であれば処理しない
//	if (!isEnable)
//		return;	
//
//	//	ワールド座標の更新
//	worldCenter = VAdd(pGameObject->GetPosition(), localCenter);
//}
//
//void CircleCollider::Render() {
//}
//
