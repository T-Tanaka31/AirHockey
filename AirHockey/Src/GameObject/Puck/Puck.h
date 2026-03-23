#pragma once
#include "../GameObject.h"
class Puck : public GameObject {
private:
	float radius;
	VECTOR velocity;
	float friction;
	VECTOR startPos;

	bool isReturning;
	float elapsed;

	bool waitingAfterReturn = false;
	float waitTimer = 0.0f;
	float waitDuration = 0.5f;

	VECTOR returnStartPos;
	VECTOR targetPos;

	VECTOR impulseDir;
public:
	Puck(VECTOR _startPos, float _r, float _friction = GameConfig::Puck::Friction, std::string _tag = "Puck");

	void Start() override;
	void Update() override;
	void Render() override;

	void AddVelocity(float _vx, float _vy);
	void SetVelocity(float _vx, float _vy);

	void CheckWallCollision(float _minX, float _maxX, float _minY, float _maxY);

	void StartReturn(const VECTOR& _spawnPos, const VECTOR& _targetPos, VECTOR _impulseDir);

	void UpdateReturn();
	void AddSmallImpulse();

	inline float GetRadius() const { return radius; }

	inline VECTOR GetVelocity() const { return velocity; }

	inline VECTOR& GetVelocityRef() { return velocity; }
	inline VECTOR& GetPositionRef() { return position; }

	void ResetPuck();

};

