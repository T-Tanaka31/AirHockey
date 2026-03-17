#include "InputManager.h"
// 静的メンバ変数の初期化
InputManager* InputManager::pInstance = nullptr;

void InputManager::CreateInstance() {
	pInstance = new InputManager();
}

InputManager* InputManager::GetInstance() {
	if (pInstance == nullptr)
		CreateInstance();

	return pInstance;
}

void InputManager::DestroyInstance() {
	if (pInstance != nullptr) {
		delete pInstance;
		pInstance = nullptr;
	}
}

InputManager::InputManager()
	: rangeOfMotion(32767.0f) {
}

void InputManager::Update() {
	const int padTypes[2] = { DX_INPUT_PAD1, DX_INPUT_PAD2 };

	for (int i = 0; i < 2; i++) {
		prevPadState[i] = padState[i];

		int result = GetJoypadXInputState(padTypes[i], &padState[i]);

		if (result != 0) {
			padState[i] = {};
		}
	}

}

float InputManager::IsJoypadSthick(int _padID, std::string _SthickName) {
	//	入力値
	float tmp = 0.0f;

	if (_SthickName == "L_Vertical") {
		tmp = padState[_padID].ThumbLY / rangeOfMotion;
	}
	else if (_SthickName == "L_Horizontal") {
		tmp = padState[_padID].ThumbLX / rangeOfMotion;
	}
	else if (_SthickName == "R_Vertical") {
		tmp = padState[_padID].ThumbRY / rangeOfMotion;
	}
	else if (_SthickName == "R_Horizontal") {
		tmp = padState[_padID].ThumbRX / rangeOfMotion;
	}

	// デッドゾーン
	if (fabs(tmp) <= 0.05f)
		tmp = 0.0f;

	return tmp;

}
