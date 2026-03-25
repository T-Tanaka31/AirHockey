#pragma once
#include <vector>

struct Particle {
    float x, y;
    float vx, vy;
    int life;      // 現在の寿命（フレーム数）
    int maxLife;   // 初期寿命（透明度計算用）
    unsigned int color;
};

class EffectManager {
#pragma region シングルトンのデータ構造
private:
	static EffectManager* pInstance;

private:
	EffectManager();

	~EffectManager() = default;

public:
	EffectManager(const EffectManager&) = delete;
	EffectManager& operator = (const EffectManager&) = delete;
	EffectManager(EffectManager&&) = delete;
	EffectManager& operator = (EffectManager&&) = delete;

private:
	static void CreateInstance();

public:
	static EffectManager* GetInstance();

	static void DestroyInstance();
#pragma endregion

private:
    static std::vector<Particle> particles;

public:
    static void AddSparks(float _x, float _y, unsigned int _color);

    static void Update();

    static void Render();
};

