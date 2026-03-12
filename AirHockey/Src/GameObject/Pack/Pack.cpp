#include "Pack.h"
#include "../../Definition/Definition.h"
#include <cmath>

Pack::Pack()
	: x()
	, y()
	, radius2(50)
	, vx()
	, vy()
	, x1()
	, y1()
	, friction(0.98f)
	, pScore(0)
	, eScore(0)
	, Str()
	, chisato(false)
	, keke(false) {
}

Pack::~Pack() {
}

void Pack::Start() {
	x = WINDOW_WIDTH / 2;
	y = WINDOW_HEIGHT / 2;
}

void Pack::Update() {

	int Haikei;

	if (WINDOW_HEIGHT - radius2 <= y) {
		vy *= -1.06;

	}
	if (radius2 >= y) {
		vy *= -1.06;

	}
	if (WINDOW_WIDTH - radius2 <= x || radius2 >= x) {
		vx *= -1.06;

	}

	if (x >= WINDOW_WIDTH - radius2 && y + radius2 > WINDOW_HEIGHT / 3 && y - radius2 < WINDOW_HEIGHT / 3 * 2) {
		pScore++;
		x = WINDOW_WIDTH / 4 * 3;
		y = WINDOW_HEIGHT / 2;
		vx = 0;
		vy = 0;
		WaitTimer(500);
	}
	if (radius2 >= x && y + radius2 > WINDOW_HEIGHT / 3 && y - radius2 < WINDOW_HEIGHT / 3 * 2) {
		eScore++;
		x = WINDOW_WIDTH / 4;
		y = WINDOW_HEIGHT / 2;
		vx = 0;
		vy = 0;
		WaitTimer(500);
	}

#if _DEBUG
	if (keke == true) {
		Haikei = LoadGraph("../../Res/keke.jpg");
	}
	if (chisato == true) {
		Haikei = LoadGraph("../../Res/chisato.jpg");
	}
#endif
	vx *= friction;
	x += vx;
	vy *= friction;
	y += vy;

}

void Pack::Render() {
	int r = GetRand(255);
	int g = GetRand(255);
	int b = GetRand(255);

	SetFontSize(64);

	const unsigned int rainbow = GetColor(r, g, b);		//	äD

	bool i = DrawCircle(x, y, radius2, GetColor(255, 208, 16), TRUE); // ê‘Ç¢â~Ç≈ÉLÉÉÉâÉNÉ^Å[Çï`âÊ

	wsprintf(Str, "%d - %d", pScore, eScore);
	DrawString(WINDOW_WIDTH / 2 - 90, 10, Str, COLOR_RED);

	if (pScore >= 7) {
		wsprintf(Str, "1PÇÃèüóò");
		DrawString(WINDOW_WIDTH / 2 - 90, WINDOW_HEIGHT / 2, Str, COLOR_RED);
#if _DEBUG
		keke = true;
#endif
	}
	else if (eScore >= 7) {
		wsprintf(Str, "2PÇÃèüóò");
		DrawString(WINDOW_WIDTH / 2 - 90, WINDOW_HEIGHT / 2, Str, COLOR_RED);
#if _DEBUG
		chisato = true;
#endif
	}


}

