#include "MathUtility.h"

//	2点間の角度
float MathUtility::AngleBetweenPoints(float x1, float y1, float x2, float y2) {
	return atan2(y2 - y1, x2 - x1);
}

//	角度の正規化
float MathUtility::NormalizeAngle(float angle) {
	return Repeat(angle + 180.0f, 360.0f) - 180.0f;
}

//	fromからtoへのへ回転する際の最短角度( -180°～ 180°)
float MathUtility::ShortestAngle(float from, float to) {
	float diff = NormalizeAngle(to - from);
	return diff;
}

//	2点間の距離
float MathUtility::Distance(float x1, float y1, float x2, float y2) {
	float dx = x2 - x1;
	float dy = y2 - y1;
	return sqrt(dx * dx + dy * dy);
}

//	ベクトルの長さ
float MathUtility::Length(float x, float y) {
	return sqrt(x * x + y * y);
}

//	ベクトルの正規化
void MathUtility::Normalize(float& x, float& y) {
	float len = Length(x, y);
	if (len == 0.0f) return;

	x /= len;
	y /= len;
}

//	内積
float MathUtility::Dot(float ax, float ay, float bx, float by) {
	return ax * bx + ay * by;
}

//	反射ベクトル
void MathUtility::Reflect(float vx, float vy, float nx, float ny, float& outX, float& outY) {
	float dot = Dot(vx, vy, nx, ny);

	outX = vx - 2.0f * dot * nx;
	outY = vy - 2.0f * dot * ny;
}

//	値を min〜max に収める
float MathUtility::Clamp(float value, float min, float max) {
	if (value < min) return min;
	if (value > max) return max;
	return value;

}

// 線形補間（0〜1）
float MathUtility::Lerp(float a, float b, float t) {
	return a + (b - a) * t;
}

float MathUtility::Repeat(float t, float length) {
	return t - float(t / length) * length;
}

float MathUtility::EaseIn(float t) {
	return t * t;
}

float MathUtility::EaseOut(float t) {
	return 1.0f - (1.0f - t) * (1.0f - t);
}

float MathUtility::EasInOut(float t) {
	return t < 0.5f
		? 2.0f * t * t
		: 1.0f - powf(-2.0f * t + 2.0f, 2.0f) / 2.0f;

}
