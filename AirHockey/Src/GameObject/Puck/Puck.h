#pragma once
#include "../GameObject.h"
class Puck : public GameObject {
private:
	float radius;
	VECTOR velocity;
	float friction;
	VECTOR startPos;
public:
	Puck(VECTOR _startPos, float _r, float _friction = GameConfig::Puck::Friction, std::string _tag = "Puck");

	void Start() override;
	void Update() override;
	void Render() override;

	void AddVelocity(float _vx, float _vy);
	void SetVelocity(float _vx, float _vy);

	void CheckWallCollision(float _minX, float _maxX, float _minY, float _maxY);

	inline float GetRadius() const { return radius; }

	inline VECTOR GetVelocity() const { return velocity; }

	inline VECTOR& GetVelocityRef() { return velocity; }
	inline VECTOR& GetPositionRef() { return position; }

	void ResetPuck();

};

