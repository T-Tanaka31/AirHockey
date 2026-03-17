#include "Puck.h"
#include "../../Utility/MathUtility.h"
#include "../../Manager/CollisionManager.h"

Puck::Puck(VECTOR _startPos, float _r, float _friction, std::string _tag)
    : GameObject(_startPos, _tag)
    , radius(_r)
    , friction(friction) {
    velocity = VZero;
}

void Puck::Start() {
}

void Puck::Update() {
    // --- –€ŽC‚É‚æ‚éŒ¸‘¬ ---
    velocity.x *= friction;
    velocity.y *= friction;

    // --- ˆÊ’uXV ---
    position.x += velocity.x;
    position.y += velocity.y;

    // --- •Ç‚Æ‚ÌÕ“Ë”»’è ---
    CollisionManager::GetInstance()->CheckAndReflectWall(
        position.x, position.y,
        velocity.x, velocity.y,
        radius,
        0.0f, WINDOW_WIDTH,
        0.0f, WINDOW_HEIGHT
    );

}

void Puck::Render() {
    DrawCircle((int)position.x, (int)position.y, radius, GetColor(255, 208, 16), TRUE);
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
    CollisionManager::GetInstance()->CheckAndReflectWall(
        position.x, position.y,
        velocity.x, velocity.y,
        radius,
        _minX, _maxX,
        _minY, _maxY
    );

}
