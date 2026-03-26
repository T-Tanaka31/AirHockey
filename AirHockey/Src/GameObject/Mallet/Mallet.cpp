#include "Mallet.h"
#include "../../Utility/MathUtility.h"
#include "../../Utility/CollisionUtility.h"
#include "../../Utility/ColorUtility.h"
#include "../../Manager/TimeManager.h"
#include "../../Manager/EffectManager.h"
#include "../../Manager/AudioManager.h"

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
	, startColor(_color)
	, padID(){
	Start();
}

void Mallet::Start() {
}

void Mallet::Update() {
	
	// レインボー演出（既存）
	if (isRainbow) {
		color = ColorUtility::ToRainbowColor(color);
	}

	// 帰還中なら専用の更新をして終了
	if (isReturning) {
		UpdateReturn();
		return;
	}

	// ゲームパッド入力による移動と速度(velocity)の計算
	UpdateByGamepad(padID);

	// パックがいなければ衝突判定は不要
	if (!puck) return;

	// --- ここが重要：判定・押し出し・反射を一括で行う ---
	// 引数に自分(Mallet)の速度と、パックの速度(参照)を渡す
	bool nowColliding = CollisionUtility::CheckAndHandleMalletPuckCollision(
		position.x, position.y, radius,
		puck->GetPositionRef().x, puck->GetPositionRef().y, puck->GetRadius(),
		velocity.x, velocity.y,
		puck->GetVelocityRef().x, puck->GetVelocityRef().y
	);

	// --- 当たった瞬間(1フレーム目)だけの演出 ---
	if (nowColliding && !isCollidingWithPuck) {

		// 1. サウンド再生（Excelの"名前"で指定）
		AudioManager::GetInstance()->PlayOneShot("Hit");

		// 2. エフェクト発生
		// パックの座標にスパークを出す
		EffectManager::GetInstance()->AddSparks(puck->GetPosition().x, puck->GetPosition().y, COLOR_ORANGE);
	}

	// 衝突状態を保存（チャタリング・連続ヒット防止用）
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

	float t = elapsed / GameConfig::Mallet::ReturnDuration;
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
