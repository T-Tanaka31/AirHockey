//#pragma once
//#include <vector>
//
///*
// *	@brief	当たり判定の管理
// *	@tips	シングルトン
// */
//class CollisionManager {
//#pragma region シングルトンのデータ構造
//private:	//	静的メンバ変数
//	static CollisionManager* pInstance;		//	自身のインスタンスのアドレスを格納
//
//private:	//	コンストラクタとデストラクタ
//	/*
//	 *	@brief		コンストラクタ
//	 *	@tips		外部で生成されないようにアクセス指定子を private	にする
//	 */
//	CollisionManager();
//
//	/*
//	 *	@brief		デストラクタ
//	 */
//	~CollisionManager();
//
//public:		//	コピーと譲渡の禁止
//	CollisionManager(const CollisionManager&) = delete;
//	CollisionManager(CollisionManager&&) = delete;
//
//	CollisionManager& operator = (const CollisionManager&) = delete;
//	CollisionManager& operator = (CollisionManager&&) = delete;
//
//private:	//	静的メンバ関数
//	/*
//	 *	@function	CreateInstance
//	 *	@brief		自身のインスタンスを生成する
//	 */
//	static void CreateInstance();
//
//public:		//	静的メンバ関数
//	/*
//	 *	@function	GetInstance
//	 *	@brief		自身のインスタンスを取得する唯一の手段
//	 *	@return		InputManager*	自身のインスタンスのアドレス
//	 */
//	static CollisionManager* GetInstance();
//
//	/*
//	 *	@function	DestroyInstance
//	 *	@breif		自身のインスタンスを破棄する唯一の手段
//	 */
//	static void DestroyInstance();
//
//#pragma endregion
//
//
//private:	//	メンバ変数
//	std::vector<class Collider*> pColliderArray;		//	当たり判定の一元管理
//	std::vector<bool> prevs;							//	1フレーム前の衝突結果
//	std::vector<bool> currents;							//	現在の衝突結果
//
//public:		//	メンバ関数
//	/*
//	 *		@function			Update
//	 *		@brief					更新処理
//	 */
//	void Update();
//
//	/*
//	 *		@function			Register
//	 *		@brief					一元管理に登録する
//	 *		@param[in]		Collider* _pCol			登録する当たり判定
//	 */
//	void Register(class Collider* _pCol);
//
//	/*
//	 *		@function			Unregister
//	 *		@brief					一元管理から抹消する
//	 *		@param[in]		Collider		_pCol	　抹消する当たり判定
//	 */
//	void Unregister(class Collider* _pCol);
//
//	/*
//	 *		@function		CheckHit
//	 *		@breif				当たり判定の衝突検知
//	 *		@param[in]	Collider* _pCol	1			当たり判定1
//	 *		@param[in]	Collider* _pCol	2			当たり判定2
//	 *		@return			bool
//	 */
//	bool CheckHit(class Collider* _pcol1, class Collider* pCol2);
//
//
//
//};
//
//
