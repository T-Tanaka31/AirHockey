#pragma once
class CollisionUtility {
public:
	//	円の衝突判定
	static bool CheckCircleCollision(float x1, float y1, float r1, float x2, float y2, float r2);

	//	めり込みを防ぐ
	static void ResolveCircleCollision(float& x1, float& y1, float r1, float& x2, float& y2, float r2);

	//	反射処理
	// nx, ny は正規化された法線ベクトル
	static void ReflectVelocity(float& vx, float& vy, float nx, float ny);

	//	壁との反射用
	static void CheckAndReflectWall(
		float& px, float& py,
		float& vx, float& vy,
		float radius,
		float minX, float maxX,
		float minY, float maxY);

	static bool CheckAndHandleMalletPuckCollision(
		float mx, float my, float mr,
		float& px, float& py, float pr,
		float mvx, float mvy,
		float& pvx, float& pvy
	);
};

