#include "CollisionManager.h"
#include "../Utility/MathUtility.h"
// Ã“Iƒƒ“ƒo•Ï”‚Ì‰Šú‰»
CollisionManager* CollisionManager::pInstance = nullptr;

void CollisionManager::CreateInstance() {
	pInstance = new CollisionManager();
}

CollisionManager* CollisionManager::GetInstance() {
	if (pInstance == nullptr)
		CreateInstance();

	return pInstance;
}

void CollisionManager::DestroyInstance() {
	if (pInstance != nullptr) {
		delete pInstance;
		pInstance = nullptr;
	}
}

CollisionManager::CollisionManager() {

}

bool CollisionManager::CheckCircleCollision(float x1, float y1, float r1, float x2, float y2, float r2) const {
	float dist = MathUtility::Distance(x1, y1, x2, y2);
	return dist < (r1 + r2);
}

void CollisionManager::ResolveCircleCollision(float& x1, float& y1, float r1, float& x2, float& y2, float r2) {
	float dx = x2 - x1;
	float dy = y2 - y1;

	float dist = MathUtility::Length(dx, dy);
	if (dist == 0.0f) return;

	float overlap = (r1 + r2) - dist;
	if (overlap <= 0.0f) return;

	MathUtility::Normalize(dx, dy);

	x1 -= dx * overlap * 0.5f;
	y1 -= dy * overlap * 0.5f;

	x2 += dx * overlap * 0.5f;
	y2 += dy * overlap * 0.5f;
}

void CollisionManager::ReflectVelocity(float& vx, float& vy, float nx, float ny) {
	MathUtility::Reflect(vx, vy, nx, ny, vx, vy);
}

void CollisionManager::CheckAndReflectWall(float& px, float& py, float& vx, float& vy, float radius, float minX, float maxX, float minY, float maxY) {
	// ¶‰E
	if (px - radius < minX) {
		px = minX + radius;
		vx = -vx;
	}
	else if (px + radius > maxX) {
		px = maxX - radius;
		vx = -vx;
	}

	// ã‰º
	if (py - radius < minY) {
		py = minY + radius;
		vy = -vy;
	}
	else if (py + radius > maxY) {
		py = maxY - radius;
		vy = -vy;
	}
}

