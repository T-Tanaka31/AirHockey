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

void CollisionUtility::CheckAndReflectWall(
	float& px, float& py,
	float& vx, float& vy,
	float radius,
	float minX, float maxX,
	float minY, float maxY
) {
	const float goalMinY = GameConfig::Goal::Top;
	const float goalMaxY = GameConfig::Goal::Bottom;

	bool inGoalY = (py > goalMinY && py < goalMaxY);

	// 左右
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


	// 上下
	if (py - radius < minY) {
		py = minY + radius;
		vy = -vy;
	}
	else if (py + radius > maxY) {
		py = maxY - radius;
		vy = -vy;
	}
}

bool CollisionUtility::CheckAndHandleMalletPuckCollision(
	float mx, float my, float mr,
	float& px, float& py, float pr,
	float mvx, float mvy,
	float& pvx, float& pvy
) {
	float dx = px - mx;
	float dy = py - my;
	float dist = MathUtility::Length(dx, dy);
	float rSum = mr + pr;

	// 1. 当たっていなければ終了
	if (dist >= rSum || dist == 0.0f) return false;

	// 法線ベクトル（マレットからパックへの方向）
	float nx = dx / dist;
	float ny = dy / dist;

	// 2. 【吸着防止の核】相対速度の確認
	// パックの速度からマレットの速度を引いた「相対的な動き」を計算
	float rvx = pvx - mvx;
	float rvy = pvy - mvy;

	// 相対速度と法線の内積を計算（0以上なら互いに離れる方向へ動いている）
	if (MathUtility::Dot(rvx, rvy, nx, ny) > 0.0f) {
		return false;																																																																									
	}

	// 3. めり込み補正（ガタつき防止に 0.1f の余裕を追加）
	float overlap = rSum - dist;
	px += nx * (overlap + 0.1f);
	py += ny * (overlap + 0.1f);

	// 4. 反射計算
	// パックの現在の速度をマレットの表面（法線）で反射させる
	MathUtility::Reflect(pvx, pvy, nx, ny, pvx, pvy);

	// 5. マレットの押し出し力を加算
	// マレットがパックの方向へ動いている分だけ、速度を上乗せする
	float mDotN = MathUtility::Dot(mvx, mvy, nx, ny);
	if (mDotN > 0.0f) {
		pvx += nx * mDotN * 1.5f; // 1.5fは弾き飛ばす強さの調整値
		pvy += ny * mDotN * 1.5f;
	}

	// 6. 速度の増幅（ゲーム的な爽快感のため）
	pvx *= 1.1f;
	pvy *= 1.1f;

	return true;

}

