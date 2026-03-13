#include "InputManager.h"

InputManager::InputManager()
	: rangeOfMotion() {
}

void InputManager::Update() {
	for (int i = 0; i < 2; i++) {
		prevPadState[i] = padState[i];

		DWORD result = XInputGetState(i, &padState[i]);

		if (result != ERROR_SUCCESS)
			padState[i] = {};
	}
}

inline float InputManager::IsJoypadSthick(int _padID, std::string _SthickName) {
	//	“ü—Í’l
	float tmp = 0.0f;
	if (_SthickName == "L_Vertical") {
		if (padState[_padID].Gamepad.sThumbLY > rangeOfMotion) {
			padState[_padID].Gamepad.sThumbLY = rangeOfMotion;
		}
		tmp += padState[_padID].Gamepad.sThumbLY / rangeOfMotion;
	}
	else if (_SthickName == "L_Horizontal") {
		if (padState[_padID].Gamepad.sThumbLX > rangeOfMotion) {
			padState[_padID].Gamepad.sThumbLX = rangeOfMotion;
		}
		tmp += padState[_padID].Gamepad.sThumbLX / rangeOfMotion;
	}
	else if (_SthickName == "R_Vertical") {
		if (padState[_padID].Gamepad.sThumbRY > rangeOfMotion) {
			padState[_padID].Gamepad.sThumbRY = rangeOfMotion;
		}
		tmp += padState[_padID].Gamepad.sThumbRY / rangeOfMotion;
	}
	else if (_SthickName == "R_Horizontal") {
		if (padState[_padID].Gamepad.sThumbRX > rangeOfMotion) {
			padState[_padID].Gamepad.sThumbRX = rangeOfMotion;
		}
		tmp += padState[_padID].Gamepad.sThumbRX / rangeOfMotion;
	}

	if (abs(tmp) <= 0.05f)
		tmp = 0.0f;

	return tmp;
}
