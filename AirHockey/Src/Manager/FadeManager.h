#pragma once
#include "../Definition/Definition.h"
#include "../GameSystem/GameState.h"

class FadeManager {
#pragma region シングルトンのデータ構造
private:
	static FadeManager* pInstance;

private:
	FadeManager();

	~FadeManager() = default;

public:
	FadeManager(const FadeManager&) = delete;
	FadeManager& operator = (const FadeManager&) = delete;
	FadeManager(FadeManager&&) = delete;
	FadeManager& operator = (FadeManager&&) = delete;

private:
	static void CreateInstance();

public:
	static FadeManager* GetInstance();

	static void DestroyInstance();
#pragma endregion
private:
	const int BlendMax = 255;
	float time = 0;
	float alpha = 0;
	FadeState fadeState = FadeState::FadeEnd;
	int screenGraph = -1;
public:
	void Update();
	void Render();
	void FadeStart(FadeState state, float _t = 1.0f);

	void Fade(FadeState state, float _t = 1.0f);
	void FadeIn(float _t);
	void FadeOut(float _t);
public:
	inline FadeState GetFadeState() const { return fadeState; }
	float GetAlpha() const { return alpha; }
};

