#pragma once
#include <Windows.h>
#include <XInput.h>
#include <cmath>
#include <string>
#include <array>

#pragma comment(lib, "xinput.lib")

class InputManager {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	InputManager();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~InputManager() = default;

private:
	std::array<XINPUT_STATE, 2> padState{};
	std::array<XINPUT_STATE, 2> prevPadState{};
	float rangeOfMotion;

public:
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

public:	//	パッド入力
	//	ボタンが押されたか
	inline bool IsButtonDown(int _padID, int _button) const { return !(prevPadState[_padID].Gamepad.wButtons & _button) && (padState[_padID].Gamepad.wButtons & _button); }

	//	ボタンが押されているか
	inline bool IsButton(int _padID, int _button) const { return padState[_padID].Gamepad.wButtons & _button; }

	//	ボタンが離されたか
	inline bool IsButtonUp(int _padID, int _button) const { return (prevPadState[_padID].Gamepad.wButtons & _button) && !(padState[_padID].Gamepad.wButtons & _button); }

public:	//	スティックの移動処理
	inline float IsJoypadSthick(int _padID, std::string _SthickName);
};

