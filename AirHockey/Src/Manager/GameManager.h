#pragma once
class GameManager {
#pragma region シングルトンのデータ構造
private:
	static GameManager* pInstance;

private:
	GameManager();

	~GameManager() = default;

public:
	GameManager(const GameManager&) = delete;
	GameManager& operator = (const GameManager&) = delete;
	GameManager(GameManager&&) = delete;
	GameManager& operator = (GameManager&&) = delete;

private:
	static void CreateInstance();

public:
	static GameManager* GetInstance();

	static void DestroyInstance();
#pragma endregion

private:
	bool isWin;
	int modelHandle;

public:
	void Start();
	void Update();
	void Render();

	void WinGame();

};

