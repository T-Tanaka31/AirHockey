#pragma once
#include "../../Manager/InputManager.h"
#include "../GameObject.h"
#include "../Puck/Puck.h"

class Puck;

class Mallet : public GameObject {
private:
	float radius;
	float moveSpeed;

	//	à⁄ìÆêßå¿
	float minX, maxX;
	float minY, maxY;

	bool isCollidingWithPuck = false;

	VECTOR velocity;
	Puck* puck;

public:
	Mallet(VECTOR startPos, float r, float _speed, float _minX, float _maxX, float _minY, float _maxY, std::string _tag = "Mallet");

	void Start() override;
	void Update() override;
	void Render() override;

	void UpdateByGamepad(int _padID);

	void ClampPosition();

	inline float GetRadius() const { return radius; }

	void SetPuck(Puck* p) { puck = p; }
	
	void SetPosition(VECTOR _pos) { position = _pos; }
};

