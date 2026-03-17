#pragma once

class CollisionManager {
#pragma region シングルトンのデータ構造
private:	// 静的メンバ変数
	static CollisionManager* pInstance;	// 自身のインスタンスのアドレスを格納


private:	// コンストラクタとデストラクタ
	/*
	 * @brief	コンストラクタ
	 * @tip		外部で生成されないようにアクセス指定子をprivateにする
	 */
	CollisionManager();

	/*
	 * @brief	デストラクタ
	 */
	~CollisionManager() = default;

public:	//コピーと譲渡禁止
	CollisionManager(const CollisionManager&) = delete;
	CollisionManager& operator = (const CollisionManager&) = delete;
	CollisionManager(CollisionManager&&) = delete;
	CollisionManager& operator = (CollisionManager&&) = delete;

private:	// 静的メンバ関数
	/*
	 * @function	CreateInstance
	 * @brief		自信のインスタンスを生成する
	 */
	static void CreateInstance();

public:	// 静的メンバ関数
	/*
	 * @function	GetInstance
	 * @brief		自信のインスタンスを取得する唯一の手段
	 * @return		InputManager*	自身のインスタンスのアドレス
	 */
	static CollisionManager* GetInstance();

	/*
	 * @function	DestroyInstance
	 * @brief		自信のインスタンスを破棄する唯一の手段
	 */
	static void DestroyInstance();

private:
	
public:

	//	円の衝突判定
	bool CheckCircleCollision (float x1, float y1, float r1, float x2, float y2, float r2) const;

	//	めり込みを防ぐ
	void ResolveCircleCollision(float& x1, float& y1, float r1, float& x2, float& y2, float r2);

	//	反射処理
	// nx, ny は正規化された法線ベクトル
	void ReflectVelocity(float& vx, float& vy, float nx, float ny);

	//	壁との反射用
	void CheckAndReflectWall(float& px, float& py,
		float& vx, float& vy,
		float radius,
		float minX, float maxX,
		float minY, float maxY);

	void CheckMalletPuckCollision(float mx, float my, float mr,      // マレット
		float& px, float& py, float pr,    // パック
		float mvx, float mvy,              // マレットの速度
		float& pvx, float& pvy             // パックの速度
	);
};

