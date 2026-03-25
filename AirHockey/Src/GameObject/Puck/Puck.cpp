#include "Puck.h"
#include "../../Utility/MathUtility.h"
#include "../../Utility/CollisionUtility.h"
#include "../../Manager/EffectManager.h"

Puck::Puck(VECTOR _startPos, float _r, float _friction, std::string _tag)
	: GameObject(_startPos, _tag)
	, radius(_r)
	, friction(_friction)
	, startPos(_startPos)
	, isReturning(false)
	, elapsed(0.0f)
	, targetPos(VZero)
	, returnStartPos(VZero)
	, impulseDir(VZero){
	velocity = VZero;
}

void Puck::Start() {
}

void Puck::Update() {
	if (isReturning) {
		UpdateReturn();
		return;
	}

	if (waitingAfterReturn) {
		waitTimer += 1.0f / 60.0f;

		if (waitTimer >= waitDuration) {
			waitingAfterReturn = false;
			AddSmallImpulse(); 
		}

		return;
	}

	VECTOR prevVelocity = velocity;


	// --- 摩擦による減速 ---
	velocity.x *= friction;
	velocity.y *= friction;

	// --- 位置更新 ---
	position.x += velocity.x;
	position.y += velocity.y;

	// --- 壁との衝突判定 ---
	CollisionUtility::CheckAndReflectWall(
		position.x, position.y,
		velocity.x, velocity.y,
		radius,
		0.0f, WINDOW_WIDTH,
		0.0f, WINDOW_HEIGHT
	);

	if (MathUtility::HasImpact(prevVelocity, velocity, 0.5f)) {
		// 火花エフェクトを発生させる
		EffectManager::AddSparks(position.x, position.y, COLOR_YELLOW);
	}

	float maxSpeed = GameConfig::Puck::MaxSpeed;
	float speed = MathUtility::Length(velocity.x, velocity.y);

	if (speed > maxSpeed) {
		float nx = velocity.x / speed;
		float ny = velocity.y / speed;
		velocity.x = nx * maxSpeed;
		velocity.y = ny * maxSpeed;
	}


}

void Puck::Render() {
	DrawCircle((int)position.x, (int)position.y, (int)radius, COLOR_YELLOW, TRUE);
}

void Puck::AddVelocity(float _vx, float _vy) {
	velocity.x += _vx;
	velocity.y += _vy;
}

void Puck::SetVelocity(float _vx, float _vy) {
	velocity.x = _vx;
	velocity.y = _vy;
}

void Puck::CheckWallCollision(float _minX, float _maxX, float _minY, float _maxY) {
	CollisionUtility::CheckAndReflectWall(
		position.x, position.y,
		velocity.x, velocity.y,
		radius,
		_minX, _maxX,
		_minY, _maxY
	);

}

void Puck::StartReturn(const VECTOR& _spawnPos, const VECTOR& _targetPos, VECTOR _impulseDir) {
	isReturning = true;
	elapsed = 0.0f;

	// まず画面外に瞬間移動
	position = _spawnPos;

	returnStartPos = _spawnPos;
	this->targetPos = _targetPos;

	this->impulseDir = _impulseDir;
	velocity = VZero;
}



void Puck::UpdateReturn() {
	float dt = 1.0f / FPS;
	elapsed += dt;

	float t = elapsed / GameConfig::PuckSpawn::ReturnDuration;
	if (t > 1.0f) t = 1.0f;

	position.x = MathUtility::Lerp(returnStartPos.x, targetPos.x, t);
	position.y = MathUtility::Lerp(returnStartPos.y, targetPos.y, t);

	// ★ コート内に入ったら戻り終了
	if (GameConfig::Court::IsInside(position)) {
		isReturning = false;
		waitingAfterReturn = true;
		waitTimer = 0.0f;
	}

	if (t >= 1.0f)
		isReturning = false;

}

void Puck::AddSmallImpulse() {
	float power = GameConfig::Puck::PushPower;

	velocity.x = impulseDir.x * power;
	velocity.y = impulseDir.y * power;

}

void Puck::ResetPuck() {
	position = startPos;
	velocity = VZero;
}

