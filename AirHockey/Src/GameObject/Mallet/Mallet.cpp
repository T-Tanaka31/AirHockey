#include "Mallet.h"
#include "../../Utility/MathUtility.h"
#include "../../Utility/CollisionUtility.h"

Mallet::Mallet(VECTOR startPos, float r, float speed, float _minX, float _maxX, float _minY, float _maxY, std::string _tag)
	: GameObject(startPos, _tag)
	, radius(r)
	, moveSpeed(speed)
	, minX(_minX)
	, maxX(_maxX)
	, minY(_minY)
	, maxY(_maxY)
	, velocity(VZero)
	, puck(NULL) {
}

void Mallet::Start() {
}

void Mallet::Update() {
	if (!puck) return;

	// 衝突しているか
	bool nowColliding = CollisionUtility::CheckCircleCollision(
		position.x, position.y, radius,
		puck->GetPositionRef().x, puck->GetPositionRef().y, puck->GetRadius()
	);

	if (nowColliding) {
		CollisionUtility::ResolveCircleCollision(
			position.x, position.y, radius,
			puck->GetPositionRef().x, puck->GetPositionRef().y, puck->GetRadius()
		);
	}

	if (nowColliding && !isCollidingWithPuck) {
		CollisionUtility::CheckMalletPuckCollision(
			position.x, position.y, radius,
			puck->GetPositionRef().x, puck->GetPositionRef().y, puck->GetRadius(),
			velocity.x, velocity.y,
			puck->GetVelocityRef().x, puck->GetVelocityRef().y
		);
	}
	isCollidingWithPuck = nowColliding;
}

void Mallet::Render() {
	DrawCircle((int)position.x, (int)position.y, (int)radius, COLOR_CYAN, TRUE);
}

void Mallet::UpdateByGamepad(int _padID) {
	auto input = InputManager::GetInstance();

	float inputX = input->IsJoypadSthick(_padID, "L_Horizontal");
	float inputY = input->IsJoypadSthick(_padID, "L_Vertical");

	// 前フレームの位置を保存
	VECTOR prevPos = position;

	// 位置更新
	position.x += inputX * moveSpeed;
	position.y -= inputY * moveSpeed;

	// 速度計算（今回のフレームの移動量）
	velocity.x = position.x - prevPos.x;
	velocity.y = position.y - prevPos.y;

	ClampPosition();

}

void Mallet::ClampPosition() {
	position.x = MathUtility::Clamp(position.x, minX + radius, maxX - radius);
	position.y = MathUtility::Clamp(position.y, minY + radius, maxY - radius);

}
