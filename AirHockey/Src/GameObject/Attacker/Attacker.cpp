#include "Attacker.h"
#include "EAttacker.h"
#include <cmath>
#include "../../Manager/TimeManager.h"
#include "../../Definition/Definition.h"
#include "../GameObject.h"
#include "../Pack/Pack.h"


Attacker::Attacker()
	: x1()
	, y1()
	, x2()
	, y2()
	, move()
	, move2()
	, String()
	, stickX1()
	, stickY1()
	, stickX2()
	, stickY2()
	, InputX1()
	, InputY1()
	, InputX2()
	, InputY2()
	, radius(70)
	, vx()
	, vy()
	, wasColliding(false)
	, isColliding(false)
	, isColliding2(false)
	, wasColliding2(false)
	, collisionAngle(0.0f)
	, collisionAngle2(0.0f)
	, time(5) {
}

Attacker::~Attacker() {
}

void Attacker::Start() {
	//	非表示だったら初期化しない
	if (!isVisible)
		return;
	x1 = 320, y1 = 240;
	x2 = 1600, y2 = 240;
}

void Attacker::Update(Pack* _pack) {
	// ＥＳＣキーが押されるまでループ
	time += TimeManager::GetInstance()->deltaTime;


	// パッド１の入力を取得
	GetJoypadAnalogInput(&InputX1, &InputY1, DX_INPUT_KEY_PAD1);

	int PadInput;
	// パッド１の9ボタンの入力待ち
	PadInput = GetJoypadInputState(DX_INPUT_KEY_PAD1);



	GetJoypadAnalogInput(&InputX2, &InputY2, DX_INPUT_PAD2);

	int PadInput2;

	PadInput2 = GetJoypadInputState(DX_INPUT_PAD2);

	if (PadInput & PAD_INPUT_1) {
		move2 = 10;
	}
	else {
		move2 = 20;
	}

	// スティックの状態を取得
	stickX1 = (InputX1 / move2); // X軸の値
	stickY1 = (InputY1 / move2); // Y軸の値

	if (x1 - radius * 1.3f < 0 && stickX1 < 0) {
		stickX1 = 0;
	}
	if (x1 + radius * 1.3f > WINDOW_WIDTH / 2 && stickX1 > 0) {
		stickX1 = 0;
	}
	if (y1 - radius * 1.3f < 0 && stickY1 < 0) {
		stickY1 = 0;
	}
	if (y1 + radius * 1.3f > WINDOW_HEIGHT && stickY1 > 0) {
		stickY1 = 0;
	}
	// アタッカー
	x1 += stickX1; // X軸の移動
	y1 += stickY1; // Y軸の移動

	if ((PadInput2 & PAD_INPUT_1 && PadInput2 & PAD_INPUT_2 && PadInput2 & PAD_INPUT_3)) {
		WaitTimer(100);
	}


	//if (!(PadInput & PAD_INPUT_1 && PadInput & PAD_INPUT_2)) {


	if (PadInput2 & PAD_INPUT_1) {
		move = 10;
	}
	else {
		move = 20;
	}
	// スティックの状態を取得
	stickX2 = (InputX2 / move); // X軸の値
	stickY2 = (InputY2 / move); // Y軸の値

	if (x2 - radius * 1.3f < WINDOW_WIDTH / 2 && stickX2 < 0) {
		stickX2 = 0;
	}
	if (x2 + radius * 1.3f > WINDOW_WIDTH && stickX2 > 0) {
		stickX2 = 0;
	}
	if (y2 - radius * 1.3f < 0 && stickY2 < 0) {
		stickY2 = 0;
	}
	if (y2 + radius * 1.3f > WINDOW_HEIGHT && stickY2 > 0) {
		stickY2 = 0;
	}

	// アタッカー
	x2 += stickX2; // X軸の移動
	y2 += stickY2; // Y軸の移動

	isColliding = CircleCollision(_pack);

	isColliding2 = CircleCollision2(_pack);

	if (!wasColliding && isColliding) {
		if ((CircleCollision(_pack) && InputX1 == 0 && InputY1 == 0)) {
			if (_pack->GetPositionX() > x1) {
				_pack->SetPositionVX(cos(collisionAngle *= 1.2f));
				_pack->SetPositionVY(sin(collisionAngle *= 1.2f));
			}
			else if (_pack->GetPositionX() < x1) {
				_pack->SetPositionVX(-cos(collisionAngle *= 1.2f));
				_pack->SetPositionVY(-sin(collisionAngle *= 1.2f));
			}
		}

		else if (CircleCollision(_pack) && InputX1 >= 0 || CircleCollision(_pack) && InputX1 <= 0 || CircleCollision(_pack) && InputY1 >= 0 || CircleCollision(_pack) && InputY1 <= 0) {
			if (InputX1 >= 0 && InputY1 >= 0) {
				vx = InputX1 / 10;
				vy = InputY1 / 10;
				_pack->SetPositionVX(cos(collisionAngle) * vx);
				_pack->SetPositionVY(sin(collisionAngle) * vy);
			}
			else if (InputX1 <= 0 && InputY1 <= 0) {
				vx = InputX1 / 10;
				vy = InputY1 / 10;
				_pack->SetPositionVX(-cos(collisionAngle) * vx);
				_pack->SetPositionVY(-sin(collisionAngle) * vy);
			}
			else if (InputX1 <= 0 && InputY1 >= 0) {
				vx = InputX1 / 10;
				vy = InputY1 / 10;
				_pack->SetPositionVX(-cos(collisionAngle) * vx);
				_pack->SetPositionVY(sin(collisionAngle) * vy);
			}
			else if (InputX1 >= 0 && InputY1 <= 0) {
				vx = InputX1 / 10;
				vy = InputY1 / 10;
				_pack->SetPositionVX(cos(collisionAngle) * vx);
				_pack->SetPositionVY(-sin(collisionAngle) * vy);
			}
		}
	}


	if (!wasColliding2 && isColliding2) {
		if ((CircleCollision2(_pack) && InputX2 == 0 && InputY2 == 0)) {
			if (_pack->GetPositionX() > x2) {
				_pack->SetPositionVX(cos(collisionAngle *= 1.2f));
				_pack->SetPositionVY(sin(collisionAngle *= 1.2f));
			}
			else if (_pack->GetPositionX() < x2) {
				_pack->SetPositionVX(-cos(collisionAngle *= 1.2f));
				_pack->SetPositionVY(-sin(collisionAngle *= 1.2f));
			}
		}

		else if (CircleCollision2(_pack) && InputX2 >= 0 || CircleCollision2(_pack) && InputX2 <= 0 || CircleCollision2(_pack) && InputY2 >= 0 || CircleCollision2(_pack) && InputY2 <= 0) {
			if (InputX2 >= 0 && InputY2 >= 0) {
				vx = InputX2 / 10;
				vy = InputY2 / 10;
				_pack->SetPositionVX(cos(collisionAngle) * vx);
				_pack->SetPositionVY(sin(collisionAngle) * vy);
			}
			else if (InputX2 <= 0 && InputY2 <= 0) {
				vx = InputX2 / 10;
				vy = InputY2 / 10;
				_pack->SetPositionVX(-cos(collisionAngle) * vx);
				_pack->SetPositionVY(-sin(collisionAngle) * vy);
			}
			else if (InputX2 <= 0 && InputY2 >= 0) {
				vx = InputX2 / 10;
				vy = InputY2 / 10;
				_pack->SetPositionVX(-cos(collisionAngle) * vx);
				_pack->SetPositionVY(sin(collisionAngle) * vy);
			}
			else if (InputX2 >= 0 && InputY2 <= 0) {
				vx = InputX2 / 10;
				vy = InputY2 / 10;
				_pack->SetPositionVX(cos(collisionAngle) * vx);
				_pack->SetPositionVY(-sin(collisionAngle) * vy);
			}
		}
	}


	wasColliding = isColliding;
	wasColliding2 = isColliding2;


}

void Attacker::Render() {

	// キャラクターの描画処理
	DrawCircle(x1, y1, radius, GetColor(102, 192, 255), TRUE); // 赤い円でキャラクターを描画


	// キャラクターの描画処理
	DrawCircle(x2 + move, y2 + move, radius, GetColor(255, 110, 144), TRUE); // 青い円でキャラクターを描画

}


bool Attacker::CircleCollision(Pack* _pPack) {
	// 2つの円の中心の距離を計算
	int dx = _pPack->GetPositionX() - x1;
	int dy = _pPack->GetPositionY() - y1;
	float distance = sqrt(dx * dx + dy * dy);


	if (distance < (radius + _pPack->GetRadius())) {

		collisionAngle = atan2(dy, dx);  // -π〜πの範囲で角度を得る

		return true;
	}

	return false;
}

bool Attacker::CircleCollision2(Pack* _pPack) {
	// 2つの円の中心の距離を計算
	int dx2 = _pPack->GetPositionX() - x2;
	int dy2 = _pPack->GetPositionY() - y2;
	float distance = sqrt(dx2 * dx2 + dy2 * dy2);


	if (distance < (radius + _pPack->GetRadius())) {

		collisionAngle = atan2(dy2, dx2);  // -π〜πの範囲で角度を得る

		return true;
	}

	return false;
}

