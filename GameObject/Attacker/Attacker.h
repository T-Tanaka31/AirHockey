#pragma once
#include "../Definition.h"
#include "../GameObject/GameObject.h"
#include "../GameObject/Pack/Pack.h"
	


/*
 *	@breif	アタッカークラス
 */
class Attacker : public GameObject {
public:	//	メンバ変数
	float x1, y1, x2, y2;
	char String[64];
	int move;
	int move2;
	float stickX1, stickY1, stickX2, stickY2;
	int InputX1, InputY1,  InputX2, InputY2;

	int radius;

	float vx, vy;

	bool wasColliding;  // 前回衝突していたか
	bool wasColliding2;  // 前回衝突していたか

	bool isColliding;   // 現在衝突しているか
	bool isColliding2;   // 現在衝突しているか

	float collisionAngle;
	float collisionAngle2;

	float time;


public:		//	コンストラクタとデストラクタ
	/*
	 *	@breif		コンストラクタ
	 *	@param[in]	Vector _pos		初期化する座標
	 */
	Attacker();

	/*
	 *	@breif		デストラクタ
	 */
	~Attacker();

public:		//	メンバ関数
	/*
	 *	@function	Start
	 *	@breif		初期化処理
	 */
	void Start();

	/*
	 *	@function	Update
	 *	@breif		更新処理
	 */
	void Update(Pack* _pack);

	/*
	 *	@function	Render
	 *	@breif		描画処理
	 */
	void Render();

	

public:		//	Getter と Setter
	
	/*inline void SetPosition1(float _x1, float _y1) { x1 = _x1, y1 = _y1; }

	inline void SetPosition2(float _x2, float _y2) { x2 = _x2, y2 = _y2; }*/

	inline float GetPositionX1() const { return x1; }
	inline float GetPositionY1() const { return y1; }

	inline float GetPositionX2() const { return x2; }
	inline float GetPositionY2() const { return y2; }

	inline float GetRadius() const { return radius; }

	inline int GetInputX1() const { return InputX1; }

	inline int GetInputY1() const { return InputY1; }

	inline int GetInputX2() const { return InputX2; }

	inline int GetInputY2() const { return InputY2; }

	inline void SetPos1(float _x, float _y, float _x2, float _y2) { x1 = _x, y1 = _y, x2 = _x2, y2 = _y2; }
public:
	

	inline bool CircleCollision(Pack* _pPack);

	inline  bool CircleCollision2(Pack* _pPack);

};

