#include "Collider.h"

Collider::Collider(GameObject* _pObj)
	: isEnable(true)
	, pGameObject(_pObj)
	, offset(VZero) {
}

Collider::~Collider() {
}

CircleCollider::CircleCollider(GameObject* _pObj, float _r)
	: Collider(_pObj)
	, radius(_r)
	, center() {
}

void CircleCollider::Update() {
	if (!isEnable)
		return;
	VECTOR pos = pGameObject->GetPosition();

	center.x = pos.x + offset.x;
	center.y = pos.y + offset.y;
	center.z = 0;
}

void CircleCollider::Render() {
	DrawCircle(
		(int)center.x,
		(int)center.y,
		(int)radius,
		COLOR_RED,
		FALSE
	);
}

BoxCollider::BoxCollider(GameObject* _pObj, VECTOR _min, VECTOR _max)
	: Collider(_pObj)
	, minPoint(_min)
	, maxPoint(_max) {
}

void BoxCollider::Update() {
	VECTOR pos = pGameObject->GetPosition();

	minPoint.x += pos.x;
	minPoint.y += pos.y;

	maxPoint.x += pos.x;
	maxPoint.y += pos.y;

}

void BoxCollider::Render() {
	DrawBox(
		(int)minPoint.x,
		(int)minPoint.y,
		(int)maxPoint.x,
		(int)maxPoint.y,
		GetColor(0, 255, 0),
		FALSE
	);
}
