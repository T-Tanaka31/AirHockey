#include "ColorUtility.h"
#include "../Definition/Definition.h"

int ColorUtility::ToRainbowColor(int color) {
	float systemTime = GetNowCount() / 1000.0f;

	float speed = 10.0f;
	float hue = systemTime * speed;

	int r = (int)(128 + 127 * sin(hue));
	int g = (int)(128 + 127 * sin(hue + 2.09f));
	int b = (int)(128 + 127 * sin(hue + 4.18f));

	color = GetColor(r, g, b);
    return color;
}
