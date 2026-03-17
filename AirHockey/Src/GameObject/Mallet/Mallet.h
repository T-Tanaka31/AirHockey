#pragma once
#include "../../Manager/InputManager.h"
#include "../GameObject.h"

class Mallet : public GameObject {
private:
	float radius;
	float moveSpeed;

	//	ˆÚ“®§ŒÀ
	float minX, maxX;
	float minY, maxY;

public:
	Mallet(VECTOR startPos, float r, float _speed, float _minX, float _maxX, float _minY, float _maxY, std::string _tag = "Mallet");

	void Start() override;
	void Update() override;
	void Render() override;

	void UpdateByGamepad(int _padID);

	void ClampPosition();

	inline float GetRadius() const { return radius; }
};

