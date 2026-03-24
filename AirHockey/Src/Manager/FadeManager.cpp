#include "FadeManager.h"
#include <DxLib.h>


FadeManager* FadeManager::pInstance = nullptr;

void FadeManager::CreateInstance() {
	pInstance = new FadeManager();
}

FadeManager* FadeManager::GetInstance() {
	if (pInstance == nullptr)
		CreateInstance();
	return pInstance;
}

void FadeManager::DestroyInstance() {
	delete pInstance;
	pInstance = nullptr;
}

FadeManager::FadeManager()
	: time(0)
	, alpha(0)
	, fadeState(FadeState::FadeEnd)
	, screenGraph(-1) {
}


void FadeManager::FadeStart(FadeState state, float _t) {
	fadeState = state;
	time = _t;

	alpha = (state == FadeState::FadeIn) ? 255.0f : 0.0f;

	if (screenGraph != -1) DeleteGraph(screenGraph);
	screenGraph = MakeScreen(WINDOW_WIDTH, WINDOW_HEIGHT, TRUE);
	GetDrawScreenGraph(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, screenGraph);
}

void FadeManager::Fade(FadeState state, float _t) {
	FadeStart(state, _t);
}

void FadeManager::FadeIn(float _t) {
	FadeStart(FadeState::FadeIn, _t);
}

void FadeManager::FadeOut(float _t) {
	FadeStart(FadeState::FadeOut, _t);
}

void FadeManager::Update() {
	if (fadeState == FadeState::FadeEnd) return;

	// time Ç™ïbíPà Ç»ÇÁÅA60fpsä∑éZÇ≈åvéZ
	float delta = 255.0f / (time * 60.0f);

	if (fadeState == FadeState::FadeIn) {
		alpha -= delta;
		if (alpha <= 0) {
			alpha = 0;
			fadeState = FadeState::FadeEnd; 
		}
	}
	else if (fadeState == FadeState::FadeOut) {
		alpha += delta;
		if (alpha >= 255) {
			alpha = 255;
			fadeState = FadeState::FadeEnd;
		}
	}
}

void FadeManager::Render() {
	if (fadeState == FadeState::FadeEnd && alpha <= 0) return;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)alpha);
	DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}