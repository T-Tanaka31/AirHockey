#pragma once 
#include <DxLib.h>
#include "../GameObject/GameObject.h"
#include <vector>

enum ColliderType {
	Circle,
	Box
};

//	“–‚½‚è”»’è‚ÌŠî’êƒNƒ‰ƒX
class Collider {
protected:
	bool isEnable;
	GameObject* pGameObject;
	VECTOR offset;

public:
	Collider(GameObject* _pObj);

	virtual ~Collider();

public:
	virtual void Update() = 0;
	virtual void Render() = 0;

public:
	inline bool IsEnable() const { return isEnable; }
	inline void SetEnable(bool _v) { isEnable = _v; }

	inline GameObject* GetGameObject() const { return pGameObject; }

	inline void SetOffset(VECTOR _o) { offset = _o; }

	virtual ColliderType GetType() const = 0;
};

class CircleCollider : public Collider {
private:
	float radius;
	VECTOR center;
public:
	CircleCollider(GameObject* _pObj, float _r);
	~CircleCollider() = default;

public:
	void Update() override;
	void Render() override;

public:
	inline VECTOR GetCenter() const { return center; }
	inline float GetRadius() const { return radius; }

	inline ColliderType GetType() const override { return ColliderType::Box; }
};


class BoxCollider : public Collider {
private:
	VECTOR minPoint;
	VECTOR maxPoint;

public:
	BoxCollider(GameObject* _pObj, VECTOR _min, VECTOR _max);
	~BoxCollider() = default;

public:
	void Update() override;
	void Render() override;

public:
	inline VECTOR GetMaxPoint() const { return maxPoint; }
	inline VECTOR GetMinPoint() const { return minPoint; }

	inline ColliderType GetType() const override { return ColliderType::Circle; }
};