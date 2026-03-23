#pragma once
#include "../../Manager/InputManager.h"
#include "../GameObject.h"
#include "../Puck/Puck.h"

class Puck;

class Mallet : public GameObject {
private:
	//	半径
	float radius;
	//	速度
	float moveSpeed;

	//	移動制限
	float minX, maxX;
	float minY, maxY;

	//	パックに当たっているか
	bool isCollidingWithPuck = false;

	//	位置を戻すか
	bool isReturning;

	//	経過時間
	float elapsed;

	//	戻す前の位置
	VECTOR returnStartPos;

	//	初期位置
	VECTOR startPos;

	//	速度
	VECTOR velocity;
	//	パック
	Puck* puck;

	//	色
	int color;
	unsigned int startColor;

	float hue = 0.0f;
	bool isRainbow = false;

	int padID;


public:
	Mallet(VECTOR _startPos, float r, float _speed, float _minX, float _maxX, float _minY, float _maxY, int _color, std::string _tag = "Mallet");

	void Start() override;
	void Update() override;
	void Render() override;

	void UpdateByGamepad(int _padID);

	void StartReturn();

	void  UpdateReturn();

	void ClampPosition();

	inline bool GetIsRainbow() const { return isRainbow; }

	inline float GetRadius() const { return radius; }

	inline void SetRainbow(bool _rainbow) { isRainbow = _rainbow; }

	void SetPuck(Puck* p) { puck = p; }
	
	void SetPosition(VECTOR _pos) { position = _pos; }

	inline void SetPadID(int _padID) { padID = _padID; }
};

