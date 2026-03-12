#pragma once
#include "../Definition.h"
//#include "../Component/Collider.h"
//	循環参照になってしまう！ -> 前方宣言で回避！

/*
 *	@breif	ゲームオブジェクトクラス
 *	@tips	ゲーム中に存在するモノのほぼ全ての基底クラス
 */
class GameObject {
#pragma region メンバ変数
protected:	//	メンバ変数
	bool isVisible;		//	表示、非表示フラグ
	VECTOR position;	//	座標
	VECTOR rotation;	//	回転 ( オイラー角 )
	VECTOR scale;		//	拡縮

	MATRIX matrix;		//	座標, 回転(ベクトル), 拡縮を併せ持つ4x4行列

	std::string tag;	//	タグ

#pragma endregion

#pragma region コンストラクタとデストラクタ
public:		//	コンストラクタとデストラクタ
	/*
	 *	@breif		コンストラクタ
	 *	@param[in]	VECTOR _pos = VZero		初期化する座標
	 *	@param[in]	std;;string _tag = ""	タグ
	 */
	GameObject(VECTOR _pos = VZero, std:: string _tag = "");

	/*
	 *	@breif		デストラクタ
	 *	@tips		基底クラスなので仮想関数で実装する
	 */
	virtual ~GameObject();
#pragma endregion

#pragma region メンバ関数
public:		//	メンバ関数
	/*
	 *	@function	Start
	 *	@breif		初期化処理
	 *	@tips		純粋仮想関数で実装する
	 */
	virtual void Start() = 0;

	/*
	 *	@function	Update
	 *	@breif		更新処理
	 */
	virtual void Update();

	/*
	 *	@function	Render
	 *	@breif		描画処理
	 *	@tips		純粋仮想関数で実装する
	 */
	virtual void Render() = 0;
#pragma endregion

public:		//	衝突検知関数
	/*
	 *	@function	OnTriggerEnter
	 *	@breif		当たった瞬間
	 *	@param[in]	collider* _pOther	当たった相手
	 */
	virtual void OnTriggerEnter(class Collider* _pOther);

	/*
	 *	@function	OnTriggerStay
	 *	@breif		当たっている間
	 *	@param[in]	collider* _pOther	当たった相手
	 */
	virtual void OnTriggerStay(class Collider* _pOther);

	/*
	 *	@function	OnTriggerExit
	 *	@breif		離れた瞬間
	 *	@param[in]	collider* _pOther	当たった相手
	 */
	virtual void OnTriggerExit(class Collider* _pOther);


#pragma region Getter と Setter
public:		//	Getter と Setter
#pragma region IsVisible
	/*
	 *	@function	IsVisible
	 *	@breif		表示フラグの取得
	 *	@return		bool
	 */
	inline bool IsVisible() const { return isVisible; }

	/*
	 *	@function	SetVisible
	 *	@breif		表示フラグの変更
	 *	@param[in]	bool _v		初期化する値
	 */
	inline void SetVisible(bool _v) { isVisible = _v; }
#pragma endregion


#pragma region Position
	/*
	 *	@function	GetPositipn
	 *	@breif		座標の取得
	 *	@return		VECTOR
	 */
	inline VECTOR GetPosition() const { return position; }

	/*
	 *	@function	SetPosition
	 *	@breif		座標の変更
	 *	@param[in]	VECTOR _v		初期化する値
	 */
	inline void SetPosition(VECTOR _v) { position = _v; }

	/*
	 *	@function	SetPosition
	 *	@breif		座標の変更
	 *	@param[in]	float _x		初期化するxの成分
	 *	@param[in]	float _y		初期化するyの成分
	 *	@param[in]	float _z		初期化するzの成分
	 */
	inline void SetPosition(float _x, float _y, float _z) { position = VGet(_x, _y, _z); }
#pragma endregion

#pragma region Ratation
	/*
	 *	@function	GetRotation
	 *	@breif		回転 ( オイラー角 )の取得
	 *	@return		VECTOR
	 */
	inline VECTOR GetRotation() const { return rotation; }

	/*
	 *	@function	SetRotation
	 *	@breif		回転 ( オイラー角 )の変更
	 *	@param[in]	VECTOR _v		初期化する回転 ( オイラー角 )
	 */
	inline void SetRoatation(VECTOR _v) { rotation = _v; }

	/*
	 *	@function	SetRotation
	 *	@breif		回転 ( オイラー角 )の変更
	 *	@param[in]	float _roll		初期化するx軸の回転
	 *	@param[in]	float _pitch	初期化するy軸の回転
	 *	@param[in]	float _yaw		初期化するz軸の回転
	 */
	inline void SetRotation(float _roll, float _pitch, float _yaw) { rotation = VGet(_roll, _pitch, _yaw); }
#pragma endregion

	/*
	 *	@function	GetMatrix
	 *	@brief		座標の変更
	 *	@param[in]	float _x	初期化するx成分
	 *	@param[in]	float _y	初期化するy成分
	 *	@param[in]	float _z	初期化するz成分
	 */
	inline MATRIX GetMatrix() const { return matrix; }

#pragma region Scale
	/*
	 *	@function	GetScale
	 *	@breif		拡縮の取得
	 *	@return		VECTOR
	 */
	inline VECTOR GetScale() const { return scale; }

	/*
	 *	@function	SetScale
	 *	@breif		拡縮の変更
	 *	@param[in]	VECTOR _v		初期化する拡縮
	 */
	inline void SetScale(VECTOR _v) { scale = _v; }

	/*
	 *	@function	SetScale
	 *	@breif		拡縮の変更
	 *	@param[in]	float _x		初期化するxの成分
	 *	@param[in]	float _y		初期化するyの成分
	 *	@param[in]	float _z		初期化するzの成分
	 */
	inline void SetScale(float _x, float _y, float _z) { scale = VGet(_x, _y, _z); }

	///*
	// *	@function	GetCollider
	// *	@brief		当たり判定の取得
	// *	@return		Collider*
	// */
	//inline Collider* GetCollider() const { return pCollider; }

	///*
	// *	@function	SetCollider
	// *  @brief		当たり判定の変更
	// *  @param[in]	Collider* _pCol
	// */
	//inline void SetCollider(Collider* _pCol) { pCollider = _pCol; }

	/*
	 *	@function	GetTag
	 *	@brief		タグの取得
	 *	@return		std::stiring
	 */
	inline std::string GetTag() const { return tag; };
#pragma endregion
#pragma endregion
};
