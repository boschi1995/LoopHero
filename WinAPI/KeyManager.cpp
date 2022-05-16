#include "Stdafx.h"
#include "KeyManager.h"

HRESULT KeyManager::init(void)
{ for (int i = 0; i < KEY_MAX; i++) { this->setkeyDown(i , false); this->setkeyUp(i, false); } return S_OK; }

bool KeyManager::isKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{ 
		if (!this->getKeyDown()[key]) { this->setkeyDown(key, true); return true; }
	} 
	else { this->setkeyDown(key, false); }
	return false;
}

bool KeyManager::inKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) { this->setkeyUp(key, true); }
	else { if (this->getKeyUp()[key]) { this->setkeyUp(key, false); return true; } }
	return false;
}

bool KeyManager::isStayKeyDown(int key)
{ if (GetAsyncKeyState(key) & 0x8000) { return true; } else { return false; } }

bool KeyManager::isToggleKey(int key)
{ if (GetKeyState(key) & 0x0001) { return true; } else { return false; } }