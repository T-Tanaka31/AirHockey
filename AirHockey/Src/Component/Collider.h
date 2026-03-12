//#pragma once
//#include "../GameObject/Attacker/Attacker.h"
//#include "../GameObject/GameObject.h"
//#include "DxLib.h"
//class Collider {
//protected:	//	メンバ変数
//	bool isEnable;				//	当たり判定の有効、無効フラグ
//	GameObject* pGameObject;	//	当たり判定を付けるオブジェクト
//	MATRIX matrix;				//	当たり判定を付けるオブジェクトの行列
//
//public:		//	コンストラクタとデストラクタ
//	/*
//	 *	@brief		コンストラクタ
//	 *	@param[in]	GameObject* _pObj	当たり判定を付けるオブジェクト
//	 */
//	Collider(GameObject* _pObj);
//
//	/*
//	 *	@brief	デストラクタ
//	 *	@tips	基底クラスなので仮想関数で実装
//	 */
//	virtual ~Collider();
//
//public:		//	メンバ関数
//	/*
//	 *	@function	Update
//	 *	@brief		更新処理
//	 *	@tips		純粋仮想関数で実装
//	 */
//	virtual void Update() = 0;
//
//	/*
//	 *	@function	Render
//	 *	@brief		描画処理
//	 *	@tips		純粋仮想関数で実装
//	 */
//	virtual void Render() = 0;
//
//public:		//	Getter と Setter
//	/*
//	 *	@function	IsEnable
//	 *	@brief		有効フラグの取得
//	 *	@return		bool
//	 */
//	inline bool IsEnable() const { return isEnable; }
//
//	/*
//	 *	@function	SetEnable
//	 *	@brief		有効フラグの変更
//	 *	@param[in]	bool _v
//	 */
//	inline void SetEnable(bool _v) { isEnable = _v; }
//
//	/*
//	 *	@function	GetGameObject
//	 *	@brief		当たり判定を付けるオブジェクトの取得
//	 *	@return		GameOBject*
//	 */
//	inline GameObject* GetGameObject() const { return pGameObject; }
//
//	/*
//	 *	@function	SetGameObject
//	 *	@breif		当たり判定を付けるオブジェクトの変更
//	 *	@param[in]	GameObject* _pObj
//	 */
//	inline void SetGameObject(GameObject* _pObj) { pGameObject = _pObj; }
//
//	/*
//	 *	@function	SetMatrix
//	 *	@brief		行列の変更
//	 *	@param[in]	MATRIX _mat
//	 */
//	inline void SetMatrix(MATRIX _mat) { matrix = _mat; }
//};
//
//class CircleCollider : public Collider{
//private:	//	メンバ変数
//	float radius;			//	半径
//	VECTOR worldCenter;		//	中心点
//	VECTOR localCenter;		//	中心点
//
//public:		//	コンストラクタとデストラクタ
//	/*
//	 *	@breif		コンストラクタ
//	 *	@param[in]	Attacker* _pAtk
//	 *	@param[in]	_radius		半径
//	 *	@param[in]	_offset		中心点
//	 */
//	CircleCollider(GameObject* _pAtk, VECTOR _offset, float _radius );
//
//	/*
//	 *	@breif	デストラクタ
//	 */
//	~CircleCollider() = default;
//
//public:		//	オーバーライドしたメンバ変数
//	/*
//	 *	@function	Update
//	 *	@brief		更新処理
//	 */
//	void Update() override;
//
//	/*
//	 *	@function	Render
//	 *	@brief		描画処理
//	 */
//	void Render() override;
//
//public:		//	Getter と Settetr
//	/*
//	 *	@function	GetRadius
//	 *	@brief		半径の取得
//	 *  @return		float
//	 */
//	inline float GetRadius() const { return radius; }
//
//	/*
//	 *	@functionq	GetLocalcenter
//	 *	@brief		中心点の取得
//	 *	@return		VECTOR
//	 */
//	inline VECTOR GetWorldCenter() const { return worldCenter; }
//};
//
