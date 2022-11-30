#pragma once
#include <Windows.h>
#include <Xinput.h>
#include <vector>

#pragma comment (lib, "xinput.lib")

// コントローラーボタン
enum ControllerButton {
	kControllerButtonUp			= 0x0001,		// 上
	kControllerButtonDown		= 0x0002,		// 下
	kControllerButtonLeft		= 0x0004,		// 左
	kControllerButtonRight		= 0x0008,		// 右
	kControllerButtonStart		= 0x0010,		// メニュー
	kControllerButtonBack		= 0x0020,		// ビュー
	kControllerLeftThumb		= 0x0040,		// L3
	kControllerRightThumb		= 0x0080,		// R3
	kControllerLeftShoulder		= 0x0100,		// L1
	kControllerRightShoulder	= 0x0200,		// R1
	kControllerButtonA			= 0x1000,		// A
	kControllerButtonB			= 0x2000,		// B
	kControllerButtonX			= 0x4000,		// X
	kControllerButtonY			= 0x8000,		// Y
	kControllerLeftTrigger		= 0x000F0000,	// L2 (適当な数字を割り当て)
	kControllerRightTrigger		= 0x00FF0000,	// R2 (適当な数字を割り当て)
};

// スティックの向き
enum StickDirection {
	kLeftStickDirectionUp,			// LEFT STICK DIRECTION UP
	kLeftStickDirectionDown,		// LEFT STICK DIRECTION DOWN
	kLeftStickDirectionRight,		// LEFT STICK DIRECTION RIGHT
	kLeftStickDirectionLeft,		// LEFT STICK DIRECTION LEFT
	kRightStickDirectionUp,			// RIGHT STICK DIRECTION UP
	kRightStickDirectionDown,		// RIGHT STICK DIRECTION DOWN
	kRightStickDirectionRight,		// RIGHT STICK DIRECTION RIGHT
	kRightStickDirectionLeft		// RIGHT STICK DIRECTION LEFT
};

// Xinputコントローラー
class Controller {

public:
	
	struct StickMagnitude {
		int x;
		int y;
	};

private:
	struct State {
		bool isConnect = false;				// 接続できたか
		XINPUT_STATE state = {};			// 現在の入力状態
		XINPUT_STATE preState = {};		// 前回の入力状態
		BYTE triggerDeadZone = XINPUT_GAMEPAD_TRIGGER_THRESHOLD;		// トリガーのデッドゾーン
		SHORT leftStickDeadZone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;	// 左スティックのデッドゾーン
		SHORT rightStickDeadZone = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;	// 右スティックのデッドゾーン
	};

public:
	static constexpr int kMaxConnectionNum = 4;

private:
	static std::vector<State> mData;
	static bool mIsInput;

public:

	/// <summary>
	/// コントローラーを追加する
	/// </summary>
	/// <returns> 既に４つ接続されている場合 false</returns>
	static bool Add() {
		if (mData.size() < kMaxConnectionNum) {
			mData.emplace_back();
			return true;
		}
		return false;
	}

	static bool isUse(const State& data) ;

	/// <summary>
	/// すべてのコントローラーの状態をセットする
	/// </summary>
	/// <returns>接続数</returns>
	static void SetState();

	/// <summary>
	/// 現在使われているか
	/// </summary>
	static bool isInput() { return mIsInput; }

	static int getConnectnNum() { return (int)mData.size(); }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// トリガーのデッドゾーンを変更する
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	/// <param name="deadzone">デッドゾーン　：　0～255</param>
	/// <returns>成功　or　失敗</returns>
	static bool setTriggerDeadZone(int index, int deadzone);

	/// <summary>
	/// 右スティックのデッドゾーンを変更する
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	/// <param name="deadzone">デッドゾーン　：　0～32768</param>
	/// <returns>成功　or　失敗</returns>
	static bool setRightStickDeadZone(int index, int deadzone);

	/// <summary>
	/// 左スティックのデッドゾーンを変更する
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	/// <param name="deadzone">デッドゾーン　：　0～32768</param>
	/// <returns>成功　or　失敗</returns>
	static bool setLeftStickDeadZone(int index, int deadzone);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// ボタンが押された時
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	/// <param name="button">ボタン番号</param>
	/// <returns></returns>
	static bool isTrigger(int index, ControllerButton button);

	/// <summary>
	/// ボタンが押されている時
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	/// <param name="button">ボタン番号</param>
	/// <returns></returns>
	static bool isPressed(int index, ControllerButton button);

	/// <summary>
	/// ボタンが離された時
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	/// <param name="button">ボタン番号</param>
	/// <returns></returns>
	static bool isRelease(int index, ControllerButton button);

	/// <summary>
	/// スティックが指定の向きに倒された時
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	/// <param name="direction">スティック向き</param>
	/// <returns></returns>
	static bool isStickDirection(int index, StickDirection direction);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// 右トリガー
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	/// <param name="out">0～255</param>
	/// <returns>成功　or　失敗</returns>
	static bool getRightTrigger(int index, int* out);

	/// <summary>
	/// 左トリガー
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	/// <param name="out">0～255</param>
	/// <returns>成功　or　失敗</returns>
	static bool getLeftTrigger(int index, int* out);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// 右スティック
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	/// <param name="outx">X軸</param>
	/// <param name="outy">Y軸</param>
	/// <returns>成功　or　失敗</returns>
	static bool getRightStick(int index, int* outx, int* outy);
	static bool getRightStick(int index, float* outx, float* outy);
	static bool getRightStick(int index, StickMagnitude* out);

	static bool getRightStickNoDeadZone(int index, int* outx, int* outy);
	static bool getRightStickNoDeadZone(int index, float* outx, float* outy);

	/// <summary>
	/// 左スティック
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	/// <param name="outx">X軸</param>
	/// <param name="outy">Y軸</param>
	/// <returns>成功　or　失敗</returns>
	static bool getLeftStick(int index, int* outx, int* outy);
	static bool getLeftStick(int index, float* outx, float* outy);
	static bool getLeftStick(int index, StickMagnitude* out);

	static bool getLeftStickNoDeadZone(int index, int* outx, int* outy);
	static bool getLeftStickNoDeadZone(int index, float* outx, float* outy);
private:

	Controller() { mData.emplace_back(); }
	~Controller() = default;
	Controller(const Controller&) = delete;
	const Controller& operator=(const Controller&) = delete;

};