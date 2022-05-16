#pragma once
#include "SingletonBase.h"

#define KEY_MAX 256

class KeyManager:public SingletonBase<KeyManager>
{
private:

	bitset < KEY_MAX>_keyUp;
	bitset < KEY_MAX>_keyDown;

	void setkeyDown(int key, bool state) { _keyDown.set(key, state); }
	void setkeyUp(int key, bool state) { _keyUp.set(key, state); }

public:
	KeyManager() {} ~KeyManager() {}
	HRESULT init(void);

	#pragma region (bool) is~

		bool isKeyDown(int key);
		bool inKeyUp(int key);
		bool isStayKeyDown(int key);
		bool isToggleKey(int key);

	#pragma endregion

	#pragma region (bitset<KEY_MAX>) get~

		bitset<KEY_MAX>getKeyUp(void) { return _keyUp; }
		bitset<KEY_MAX>getKeyDown(void) { return _keyDown; }

	#pragma endregion
};

