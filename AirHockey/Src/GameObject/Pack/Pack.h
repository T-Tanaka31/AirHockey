#pragma once
#include <vector>
#include <DxLib.h>
#include "../../Definition/Definition.h"

class Pack {
	
private:	//	メンバ変数
	float x, y;
	float radius2;

	float vx, vy;

	float x1, y1;

	float friction;

	int pScore, eScore;

	char Str[64];

	bool chisato;
	bool keke;

public:		//	コンストラクタとデストラクタ
	Pack();

	~Pack();

public:
	void Start();

	void Update();

	void Render();

	inline float GetPositionX() const { return x; }

	inline float GetPositionY() const { return y; }

	inline float GetRadius() const { return radius2; }

	inline void SetPositionVX(float _x) { vx = _x; }

	inline void SetPositionVY(float _y) { vy = _y; }

	inline bool Getkeke() const { return keke; }

	inline bool Getchisato() const { return chisato; }
};

