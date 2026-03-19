#include "Mallet.h"
#include "../../Utility/MathUtility.h"
#include "../../Utility/CollisionUtility.h"
#include "../../Manager/TimeManager.h"

Mallet::Mallet(VECTOR _startPos, float r, float speed, float _minX, float _maxX, float _minY, float _maxY, int _color, std::string _tag)
	: GameObject(_startPos, _tag)
	, radius(r)
	, moveSpeed(speed)
	, minX(_minX)
	, maxX(_maxX)
	, minY(_minY)
	, maxY(_maxY)
	, velocity(VZero)
	, puck(nullptr)
	, isReturning(false)
	, elapsed(0.0f)
	, returnStartPos(VZero)
	, startPos(_startPos)
	, color(_color)
	, startColor(_color){
	Start();
}

void Mallet::Start() {
}

void Mallet::Update() {
	
	if (isRainbow) {
		float systemTime = GetNowCount() / 1000.0f;

		float speed = 10.0f; 
		hue = systemTime * speed;

		int r = (int)(128 + 127 * sin(hue));
		int g = (int)(128 + 127 * sin(hue + 2.09f));
		int b = (int)(128 + 127 * sin(hue + 4.18f));

		color = GetColor(r, g, b);
	}
	if (isReturning) {
		UpdateReturn();
		return;
	}

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
	DrawCircle((int)position.x, (int)position.y, (int)radius, color, TRUE);
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

void Mallet::StartReturn() {
	isReturning = true;
	elapsed = 0.0f;

	returnStartPos = position;
}

void Mallet::UpdateReturn() {
	float dt = 1.0f / FPS;

	elapsed += dt;

	float t = elapsed / returnDuration;
	if (t > 1.0f) t = 1.0f;

	position.x = MathUtility::Lerp(returnStartPos.x, startPos.x, t);
	position.y = MathUtility::Lerp(returnStartPos.y, startPos.y, t);

	if (t >= 1.0f) {
		isReturning = false;
		isRainbow = false;
		color = startColor;
	}
}

void Mallet::ClampPosition() {
	position.x = MathUtility::Clamp(position.x, minX + radius, maxX - radius);
	position.y = MathUtility::Clamp(position.y, minY + radius, maxY - radius);

}
