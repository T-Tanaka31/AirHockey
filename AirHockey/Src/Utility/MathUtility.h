#pragma once
#include <cmath>

class MathUtility {
public:
	//	2点間の角度
	static float AngleBetweenPoints(float x1, float y1, float x2, float y2);

	//	角度の正規化
	static float NormalizeAngle(float angle);

	//	fromからtoへのへ回転する際の最短角度( -180°～ 180°)
	static float ShortestAngle(float from, float to);

	//	2点間の距離
	static float Distance(float x1, float y1, float x2, float y2);

	//	ベクトルの長さ
	static float Length(float x, float y);

	//	ベクトルの正規化
	static void Normalize(float& x, float& y);

	//	内積s
	static float Dot(float ax, float ay, float bx, float by);

	//	反射ベクトル
	static void Reflect(float vx, float vy, float nx, float ny, float& outX, float& outY);

	// 値を min〜max に収める
	static float Clamp(float value, float min, float max);

	// 線形補間（0〜1）
	static float Lerp(float a, float b, float t);

	//	値 t は length より大きくはならず 0 より小さくはならず、その間をループ
	static float Repeat(float t, float length);

	//	だんだん加速
	static float EaseIn(float t);

	//	だんだん遅く
	static float EaseOut(float t);

	//	加速してから減速
	static float EasInOut(float t);
};

