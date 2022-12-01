#pragma once
#include <Novice.h>

class Key {

private:
	static constexpr int kKeyDataNum = 256;

	static char mKeys[kKeyDataNum];
	static char mPreKeys[kKeyDataNum];
	static bool mIsInput;

public:

	// �L�[���͂��󂯎��
	static void SetState() {
		mIsInput = false;
		memcpy(mPreKeys, mKeys, kKeyDataNum);
		Novice::GetHitKeyStateAll(mKeys);
		for (int i = 0; i < kKeyDataNum; i++) {
			if ((mKeys[i] != 0)) {
				mIsInput = true;
				break;
			}
		}
	}

	// �L�[�������ꂽ��
	static bool IsTrigger(char keycode) {
		return mPreKeys[keycode] == 0 && mKeys[keycode] != 0;
	}
	// �L�[�������Ă���Ƃ�
	static bool IsPressed(char keycode) {
		return mKeys[keycode] != 0;
	}
	// �L�[�𗣂����Ƃ�
	static bool IsRelease(char keycode) {
		return mPreKeys[keycode] != 0 && mKeys[keycode] == 0;
	}

	static bool isInput() {
		return mIsInput;
	}

private:
	Key() = default;
	~Key() = default;
	Key(const Key&) = delete;
	const Key& operator=(const Key&) = delete;
};

