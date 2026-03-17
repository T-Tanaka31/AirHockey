#pragma once
#include <Windows.h>
#include "DxLib.h"
#include <cmath>
#include <string>
#include <array>

class InputManager {
#pragma region シングルトンのデータ構造
private:	// 静的メンバ変数
	static InputManager* pInstance;	// 自身のインスタンスのアドレスを格納


private:	// コンストラクタとデストラクタ
	/*
	 * @brief	コンストラクタ
	 * @tip		外部で生成されないようにアクセス指定子をprivateにする
	 */
	InputManager();

	/*
	 * @brief	デストラクタ
	 */
	~InputManager() = default;

public:	//コピーと譲渡禁止
	InputManager(const InputManager&) = delete;
	InputManager& operator = (const InputManager&) = delete;
	InputManager(InputManager&&) = delete;
	InputManager& operator = (InputManager&&) = delete;

private:	// 静的メンバ関数
	/*
	 * @function	CreateInstance
	 * @brief		自信のインスタンスを生成する
	 */
	static void CreateInstance();

public:	// 静的メンバ関数
	/*
	 * @function	GetInstance
	 * @brief		自信のインスタンスを取得する唯一の手段
	 * @return		InputManager*	自身のインスタンスのアドレス
	 */
	static InputManager* GetInstance();

	/*
	 * @function	DestroyInstance
	 * @brief		自信のインスタンスを破棄する唯一の手段
	 */
	static void DestroyInstance();
#pragma endregion
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
	inline bool IsButtonDown(int _padID, int _button) const { return !(prevPadState[_padID].Buttons[_button]) && (padState[_padID].Buttons[_button]); }

	//	ボタンが押されているか
	inline bool IsButton(int _padID, int _button) const { return padState[_padID].Buttons[_button]; }

	//	ボタンが離されたか
	inline bool IsButtonUp(int _padID, int _button) const { return (prevPadState[_padID].Buttons[_button]) && !(padState[_padID].Buttons[_button]); }

public:	//	スティックの移動処理
	float IsJoypadSthick(int _padID, std::string _SthickName);
};

