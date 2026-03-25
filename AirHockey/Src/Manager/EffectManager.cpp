#include "EffectManager.h"
#include <DxLib.h>

EffectManager* EffectManager::pInstance = nullptr;
std::vector<Particle> EffectManager::particles;

void EffectManager::CreateInstance() {
	pInstance = new EffectManager();
}

EffectManager* EffectManager::GetInstance() {
	if (pInstance == nullptr)
		CreateInstance();
	return pInstance;
}

void EffectManager::DestroyInstance() {
	if (pInstance) {
		particles.clear();
		delete pInstance;
		pInstance = nullptr;
	}
}

EffectManager::EffectManager() {

}

void EffectManager::AddSparks(float _x, float _y, unsigned int _color) {
	for (int i = 0; i < 15; i++) { // 一度に15個生成
		Particle p;
		p.x = _x;
		p.y = _y;

		// 全方向にランダムに飛ばす
		float angle = (float)(rand() % 360) * (3.14159f / 180.0f);
		float speed = (float)(rand() % 8 + 2);
		p.vx = cos(angle) * speed;
		p.vy = sin(angle) * speed;

		p.maxLife = 10 + rand() % 20; // 10〜30フレームで消える
		p.life = p.maxLife;
		p.color = _color;

		particles.push_back(p);
	}
}

void EffectManager::Update() {
	auto it = particles.begin();
	while (it != particles.end()) {
		it->x += it->vx;
		it->y += it->vy;
		it->vx *= 0.95f; // 空気抵抗で少しずつ減速
		it->vy *= 0.95f;
		it->life--;

		if (it->life <= 0) {
			it = particles.erase(it);
		}
		else {
			++it;
		}
	}
}

void EffectManager::Render() {
	for (const auto& p : particles) {
		int alpha = (255 * p.life) / p.maxLife;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		// 速度方向に少し伸びた線を描くと「火花」っぽくなる
		DrawLine((int)p.x, (int)p.y, (int)(p.x + p.vx * 5), (int)(p.y + p.vy * 5), p.color);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
