#include "Stdafx.h"
#include "GameScene.h"
#include "BattleTap.h"

HRESULT BattleTap::init(void)
{ GameNode::init(false); return S_OK; }

void BattleTap::release(void)
{ GameNode::release(); }

void BattleTap::update(void)
{
	GameNode::update();
	battle();

	if (player.ani == Die && player.Dely >= 20)
	{
		if (player.aniStack < 4)
		{
			player.Dely = 0;
			player.aniStack++;
			IMAGEMANAGER->findImage("PLAYER")->setFramY(1);
			IMAGEMANAGER->findImage("PLAYER")->setFramX(player.aniStack);
		}
	}
	else if (player.ani == Attack && player.Dely >= 20)
	{
		player.Dely = 0;
		IMAGEMANAGER->findImage("PLAYER")->setFramY(0);
		IMAGEMANAGER->findImage("PLAYER")->setFramX(2);
		player.aniStack++;
		if (player.aniStack > 1)
		{
			player.aniStack = 0;
			player.ani = Idle;
			IMAGEMANAGER->findImage("PLAYER")->setFramY(0);
			IMAGEMANAGER->findImage("PLAYER")->setFramX(0);
		}
	}
	else if (player.ani == Hit && player.Dely >= 20)
	{
		player.Dely = 0;
		player.aniStack++;
		IMAGEMANAGER->findImage("PLAYER")->setFramY(0);
		IMAGEMANAGER->findImage("PLAYER")->setFramX(1);
		if (player.aniStack > 1)
		{
			player.aniStack = 0;
			player.ani = Idle;
			IMAGEMANAGER->findImage("PLAYER")->setFramY(0);
			IMAGEMANAGER->findImage("PLAYER")->setFramX(0);
		}
	}
	for (int i = 0; i < _monster.size(); i++)
	{
		if (_monster[i].ani == Die && _monster[i].Dely >= 15)
		{
			_monster[i].Dely = 0;
			IMAGEMANAGER->findImage(EnumToText(_monster[i].character))->setFramY(1);
			IMAGEMANAGER->findImage(EnumToText(_monster[i].character))->setFramX(_monster[i].aniStack);
			_monster[i].aniStack++;
			if (_monster[i].aniStack > 4)
			{
				_monster[i].Dely = 40;
				_monster.erase(_monster.begin() + i);
			}
		}
		else if (_monster[i].ani == Hit && _monster[i].Dely >= 40)
		{
			_monster[i].Dely = 0;
			IMAGEMANAGER->findImage(EnumToText(_monster[i].character))->setFramY(0);
			IMAGEMANAGER->findImage(EnumToText(_monster[i].character))->setFramX(1);
			_monster[i].aniStack++;
			if (_monster[i].aniStack > 1)
			{
				_monster[i].aniStack = 0;
				_monster[i].ani = Idle;
				IMAGEMANAGER->findImage(EnumToText(_monster[i].character))->setFramY(0);
				IMAGEMANAGER->findImage(EnumToText(_monster[i].character))->setFramX(0);
			}
		}

		else if (_monster[i].ani == Attack && _monster[i].Dely >= 20)
		{
			_monster[i].Dely = 0;
			_monster[i].aniStack++;
			IMAGEMANAGER->findImage(EnumToText(_monster[i].character))->setFramY(0);
			IMAGEMANAGER->findImage(EnumToText(_monster[i].character))->setFramX(2);
			if (_monster[i].aniStack > 1)
			{
				_monster[i].aniStack = 0;
				_monster[i].ani = Idle;
				IMAGEMANAGER->findImage(EnumToText(_monster[i].character))->setFramY(0);
				IMAGEMANAGER->findImage(EnumToText(_monster[i].character))->setFramX(0);
			}
		}
	}
	player.Dely++;
	for (int i = 0; i < _monster.size(); i++) { _monster[i].Dely++; }
}

void BattleTap::render(void)
{
	HBRUSH myBrush, oldBrush;
	IMAGEMANAGER->render("BATTLEUI", getMemDC(), 200, 150);
	myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 103, 163));
	oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);
	Rectangle(getMemDC(), player.staminaBar.left, player.staminaBar.top, player.staminaBar.right, player.staminaBar.bottom);
	SelectObject(getMemDC(), oldBrush); DeleteObject(myBrush);
	myBrush = (HBRUSH)CreateSolidBrush(RGB(129, 193, 71));
	oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);
	Rectangle(getMemDC(), player.healthBar.left, player.healthBar.top, player.healthBar.right, player.healthBar.bottom);
	SelectObject(getMemDC(), oldBrush); DeleteObject(myBrush);
	IMAGEMANAGER->frameRender("PLAYER", getMemDC(), player.point.x, player.point.y);
	for (int i = 0; i < _monster.size(); i++)
	{
		IMAGEMANAGER->frameRender(EnumToText(_monster[i].character), getMemDC(), _monster[i].point.x, _monster[i].point.y, IMAGEMANAGER->findImage(EnumToText(_monster[i].character))->getFrameX(), IMAGEMANAGER->findImage(EnumToText(_monster[i].character))->getFrameY());
		myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 103, 163));
		oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);
		Rectangle(getMemDC(), _monster[i].staminaBar.left, _monster[i].staminaBar.top, _monster[i].staminaBar.right, _monster[i].staminaBar.bottom);
		SelectObject(getMemDC(), oldBrush); DeleteObject(myBrush);
		myBrush = (HBRUSH)CreateSolidBrush(RGB(129, 193, 71));
		oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);
		Rectangle(getMemDC(), _monster[i].healthBar.left, _monster[i].healthBar.top, _monster[i].healthBar.right, _monster[i].healthBar.bottom);
		SelectObject(getMemDC(), oldBrush); DeleteObject(myBrush);
	}
}

BaseData BattleTap::getPlayer()
{
	BaseData result;
	result.character = player.character;
	result.health = player.health;
	result.state = player.state;
	result.damage = player.damage;
	result.stamina = player.stamina;
	result.loopCallback = player.loopCallback;
	return result;
}

void BattleTap::setMatching(vector<BaseData> data)
{
	_monster.clear();
	Battledata result; result.ani = Idle;
	for (int i = 0; i < data.size(); i++)
	{
		result.character = data[i].character;
		result.health = data[i].health;
		result.state = data[i].state;
		result.damage = data[i].damage;
		result.stamina = data[i].stamina;
		result.loopCallback = data[i].loopCallback;
		switch (i)
		{
			case 0:  result.point = { 400, 500 }; result.staminaBar = { 450,490,450,500 }; result.healthBar = { 450,480,550,490 }; break;
			case 1:  result.point = { 800, 500 }; result.staminaBar = { 850,490,850,500 }; result.healthBar = { 850,480,850,490 };  break;
			case 2:  result.point = { 900, 400 }; result.staminaBar = { 950,390,950,400 }; result.healthBar = { 950,380,950,390 }; break;
			case 3:  result.point = { 900, 600 };  result.staminaBar = { 950,590,950,600 }; result.healthBar = { 950,580,950,590 }; break;
			case 4:  result.point = { 700, 400 };  result.staminaBar = { 650,390,650,400 }; result.healthBar = { 650,380,650,390 }; break;
			case 5:  result.point = { 700, 600 };  result.staminaBar = { 650,590,650,600 }; result.healthBar = { 650,580,650,590 }; break;
		}
		if (i != 0)
		{
			IMAGEMANAGER->findImage(EnumToText(result.character))->setFramX(0); IMAGEMANAGER->findImage(EnumToText(result.character))->setFramY(0);
			_monster.push_back(result); 
		}
		else 
		{
			IMAGEMANAGER->findImage("PLAYER")->setFramX(0); IMAGEMANAGER->findImage("PLAYER")->setFramY(0);
			player = result; 
		}
	}
	player.point = { 400, 500 }; player.staminaBar = { 450,490,450,500 }; player.healthBar = { 450,480,550,490 };
}

int BattleTap::getVictory()
{ if (_monster.size() == 0) { return true; } else if (player.health["min"] <= 0) { return false; } else return 3; }

void BattleTap::battle()
{
	player.stamina["min"] ++;
	player.staminaBar.right = player.staminaBar.left + (player.stamina["min"] * 100) / player.stamina["max"];
	player.healthBar.right = player.healthBar.left + (player.health["min"] * 100) / player.health["max"];
	if (player.stamina["min"] >= player.stamina["max"])
	{
		player.stamina["min"] = 0;
		for (int i = 0; i < _monster.size(); i++)
		{
			if (_monster[i].health["min"] > 0)
			{
				_monster[i].health["min"] -= RND->getFromInt(player.damage["min"], player.damage["max"]);
				player.ani = Attack; player.Dely = 1000; player.aniStack = 0;
				_monster[i].Dely = 1000; _monster[i].aniStack = 0;
				if (_monster[i].health["min"] <= 0) { _monster[i].ani = Die; } else { _monster[i].ani = Hit; }
			}
		} return;
	}

	for (int i = 0; i < _monster.size(); i++)
	{
		_monster[i].staminaBar.right = _monster[i].staminaBar.left + (_monster[i].stamina["min"] * 100) / _monster[i].stamina["max"];
		_monster[i].healthBar.right = _monster[i].healthBar.left + (_monster[i].health["min"] * 100) / _monster[i].health["max"];
		if (_monster[i].healthBar.right <= 0) { _monster[i].healthBar.right = 0; }
		if (_monster[i].ani != Die)
		{
			_monster[i].stamina["min"] ++;
			if (_monster[i].stamina["min"] >= _monster[i].stamina["max"])
			{
				_monster[i].stamina["min"] = 0;
				player.health["min"] -= RND->getFromInt(_monster[i].damage["min"], _monster[i].damage["max"]);
				if (player.health["min"] >= 0) { player.ani = Hit; } else { player.ani = Die; }
				player.Dely = 1000; player.aniStack = 0;
				for (int i = 0; i < _monster.size(); i++) { _monster[i].ani = Attack; _monster[i].Dely = 1000; _monster[i].aniStack = 0; }
			}
		}
		else { _monster[i].healthBar = _monster[i].staminaBar = { 0,0,0,0 }; } return;
	}
}

string BattleTap::EnumToText(CharacterSit sit)
{
	string result;
	switch (sit)
	{
		case Slime: { result = "SLIME";  }break;
		case Spider: { result = "SPIDER";  }break;
		case Skeleton: { result = "SKELETON";  }break;
	}
	return result;
}
