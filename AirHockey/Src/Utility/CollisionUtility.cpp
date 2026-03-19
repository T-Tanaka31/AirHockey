#include "CollisionUtility.h"
#include "MathUtility.h"
#include "../Definition/Definition.h"

bool CollisionUtility::CheckCircleCollision(float x1, float y1, float r1, float x2, float y2, float r2) {
	float dist = MathUtility::Distance(x1, y1, x2, y2);
	return dist < (r1 + r2);
}

void CollisionUtility::ResolveCircleCollision(float& x1, float& y1, float r1, float& x2, float& y2, float r2) {
	float dx = x2 - x1;
	float dy = y2 - y1;

	float dist = MathUtility::Length(dx, dy);
	if (dist == 0.0f) return;

	float overlap = (r1 + r2) - dist;
	if (overlap <= 0.0f) return;

	MathUtility::Normalize(dx, dy);
	x2 += dx * overlap;
	y2 += dy * overlap;


}

void CollisionUtility::ReflectVelocity(float& vx, float& vy, float nx, float ny) {
	MathUtility::Reflect(vx, vy, nx, ny, vx, vy);
}

void CollisionUtility::CheckAndReflectWall(float& px, float& py, float& vx, float& vy, float radius, float minX, float maxX, float minY, float maxY) {
	const float goalMinY = GameConfig::Goal::Top;
	const float goalMaxY = GameConfig::Goal::Bottom;

	bool inGoalY = (py > goalMinY && py < goalMaxY);

	// ç∂âE
	if (!inGoalY) {
		if (px - radius < minX) {
			px = minX + radius;
			vx = -vx;
		}
	}

	if (!inGoalY) {
		if (px + radius > maxX) {
			px = maxX - radius;
			vx = -vx;
		}
	}


	// è„â∫
	if (py - radius < minY) {
		py = minY + radius;
		vy = -vy;
	}
	else if (py + radius > maxY) {
		py = maxY - radius;
		vy = -vy;
	}
}

void CollisionUtility::CheckMalletPuckCollision(
	float mx, float my, float mr,
	float& px, float& py, float pr,
	float mvx, float mvy,
	float& pvx, float& pvy
) {
	float nx = px - mx;
	float ny = py - my;
	MathUtility::Normalize(nx, ny);

	MathUtility::Reflect(pvx, pvy, nx, ny, pvx, pvy);

	pvx += mvx * 0.8f;
	pvy += mvy * 0.8f;

	pvx *= 1.25f;
	pvy *= 1.25f;
}

