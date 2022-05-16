#include "Stdafx.h"
#include "GameScene.h"

 bool GameScene::_updataStop;
 BaseData GameScene::_player;
 vector<string> GameScene::text;
 vector<BlockData> GameScene::_card;
 vector<ItemData> GameScene::_item;
 vector<ItemData> GameScene::_equipment;

HRESULT GameScene::init(void)
{
	GameNode::init(false);
	imageLoad();
	_RoadScene = new RoadTap();
	_BattleScene = new BattleTap();
	_TransScene = false;
	_player = BaseData(Player,_RoadScene->playerPoint());
	_RoadScene->setLoopCallback(_player.loopCallback);
	POINT point;
	for (int i = 0; i < ItemSitEnd; i++)
	{
		if (i < 4) { point.x = 1370 + ((i % 2) * 62); point.y = 100 + ((i / 2) * 63); }
		else { point.x = 1370 + ((i - 4) * 62); point.y = 100 + 126; }
		_equipment.push_back(ItemData((ItemSit)i,point));
	}
	return S_OK;
}

void GameScene::release(void) { GameNode::release(); }

void GameScene::update(void)
{
	GameNode::update();
	text.clear(); cardPoint(); itemPoint();

	if (_TransScene)
	{
		if (_oneFrame)
		{ 
			_playerPoint = _player.point;
			_BattleScene->setMatching(_RoadScene->playerCollision());
			for (int i = 0; i < _card.size(); i++) { _card[i].isCard = true; }
			for (int i = 0; i < _item.size(); i++) { _item[i].isDrag = false; }
			_oneFrame = _updataStop = false;
			return;
		}
		_BattleScene->update();
		if (_BattleScene->getVictory() == true) { _TransScene = false; _oneFrame = true; }
		else if (_BattleScene->getVictory() == false) { PostQuitMessage(0); }
	}
	else
	{
		if (_oneFrame) 
		{ 
			_oneFrame = false; 
			_player = _BattleScene->getPlayer();
			_player.point = _playerPoint;
			_RoadScene->battleInit(_player);
			if (_card.size() < 10) { cardObtain(); }
			if (_card.size() < 12) { itemObtain(); }
			return;
		}
		_RoadScene->update();
		if (_updataStop == false) { _RoadScene->playerPoint(_player); }
		if (_RoadScene->playerCollision(_player).size() != 0) { _TransScene = _oneFrame = true; }
	}
	anInt ++;
	if (anInt >= 20)
	{
		anInt = IMAGEMANAGER->findImage("PLAYERS")->getFrameX() + 1;
		if (anInt == IMAGEMANAGER->findImage("PLAYERS")->getMaxFramX() + 1) { anInt = 0; }
		IMAGEMANAGER->findImage("PLAYERS")->setFramX(anInt);
		anInt = 0;
	}
}

void GameScene::render(void)
{
	IMAGEMANAGER->render("UI", getMemDC());
	_RoadScene->render();
	IMAGEMANAGER->frameRender("PLAYERS", getMemDC(), _player.point.x - 12.5f, _player.point.y - 12.5f, IMAGEMANAGER->findImage("PLAYERS")->getFrameX(), IMAGEMANAGER->findImage("PLAYERS")->getFrameY());
	if (_TransScene) { _BattleScene->render(); };
	for (int i = 0; i < _card.size(); i++)
	{
		if (_card[i].isCard == true) 
		{ IMAGEMANAGER->frameRender("CARD", getMemDC(), _card[i].point.x, _card[i].point.y, _card[i].build - Pasture, 1); }
		else { IMAGEMANAGER->frameRender("BLOCK", getMemDC(), _card[i].point.x-30, _card[i].point.y-30, _card[i].build, 1); }
	}
	for (int i = 0; i < _equipment.size(); i++)
	{
		if (_equipment[i].isDrag == true) 
		{ IMAGEMANAGER->frameRender("ITEM", getMemDC(), _equipment[i].point.x-30, _equipment[i].point.y-30, _equipment[i].rating, _equipment[i].state); }
	}
	for (int i = 0; i < _item.size(); i++)
	{
		if (_item[i].isDrag == false) 
		{ IMAGEMANAGER->frameRender("ITEM", getMemDC(), _item[i].point.x, _item[i].point.y, _item[i].rating, _item[i].state); }
		else { IMAGEMANAGER->frameRender("ITEM", getMemDC(), _item[i].point.x-30, _item[i].point.y-30 , _item[i].rating, _item[i].state); }
	}
	char str[254];
	SetTextAlign(getMemDC(), TA_CENTER); SetBkMode(getMemDC(), TRANSPARENT); SetTextColor(getMemDC(), RGB(255, 255, 255));
	for (int i = 0; i < text.size(); i++)
	{
		strcpy_s(str, text[i].c_str());
		HFONT  hFont = CreateFont(15, 0, 0, 0, FW_HEAVY, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("±¼¸²"));
		SelectObject(getMemDC(), hFont);
		TextOut(getMemDC(), 1460, 550 + (i*40), str, strlen(str));
	}
	wsprintf(str, "%d", _RoadScene->loop);		
	TextOut(getMemDC(), 1462, 32, str, strlen(str));
}


void GameScene::cardObtain()
{
	BlockData result = BlockData( (BuildTerms)RND->getFromInt(Pasture, StreetLamp), {0,0} );
	_card.push_back(result);
}

void GameScene::cardPoint()
{
	RECT temp;
	for (int i = 0; i < _card.size(); i++)
	{
		_card[i].point = { 40 + (i * 82) , WINSIZE_Y - 60 };
		temp = RectMakeCenter(_card[i].point.x, _card[i].point.y, 80, 100);
		if (PtInRect(&temp, _ptMouse))
		{
			text = _card[i].description;
			_card[i].point.y -= 50;
			if (KEYMANAGER->isKeyDown(MK_LBUTTON) && !_TransScene)
			{ 
				_card[i].isCard = false; 
				_updataStop = true;
			}
		}
	}
}

void GameScene::itemObtain()
{
	ItemData result = ItemData((ItemSit)RND->getFromInt(Necklace, ItemSitEnd), { 0,0 });
	_item.push_back(result);
}

void GameScene::itemPoint()
{
	for (int i = 0; i < _item.size(); i++)
	{
		_item[i].point = { (1370 - 30) + ((i % 4) * 62),  (350 - 30) - (-64 * (i / 4)) };
		RECT temp = RectMakeCenter(_item[i].point.x, _item[i].point.y, 60, 60);
		if (PtInRect(&temp, _ptMouse))
		{
			text = _item[i].description;
			if (KEYMANAGER->isKeyDown(MK_LBUTTON) && !_TransScene)
			{ _item[i].isDrag = _updataStop = true; }
		}
	}
}

void GameScene::imageLoad()
{
	IMAGEMANAGER->addImage("UI", "Resource/UI.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addFrameImage("ITEM", "Resource/ITEM.bmp", 180, 420, 3, 7);
	IMAGEMANAGER->addFrameImage("CARD", "Resource/CARD.bmp", 640, 110, 8, 1,true,ERASER);
	IMAGEMANAGER->addFrameImage("CARDCUT", "Resource/CARDCUT.bmp", 480, 60, 8, 1);
	IMAGEMANAGER->addFrameImage("MONSTERS", "Resource/MONSTERS.bmp", 36, 54, 2, 3, true, ERASER);
	IMAGEMANAGER->addFrameImage("BLOCK", "Resource/BLOCK.bmp", 600, 60, 10, 1);
	IMAGEMANAGER->addImage("CHOISE", "Resource/CHOISE.bmp", 60, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PLAYERS", "Resource/PLAYERS.bmp", 100, 25, 4, 1, true, ERASER);
	IMAGEMANAGER->addImage("BATTLEUI", "Resource/BATTLEUI.bmp", BattleField_X, BattleField_Y,true,ERASER);
	IMAGEMANAGER->addFrameImage("PLAYER", "Resource/PLAYER.bmp", 600, 200, 3, 2);
	IMAGEMANAGER->addFrameImage("SLIME", "Resource/SLIME.bmp", 600, 200, 3, 2);
	IMAGEMANAGER->addFrameImage("SPIDER", "Resource/SPIDER.bmp", 600, 200, 3, 2);
	IMAGEMANAGER->addFrameImage("SKELETON", "Resource/SKELETON.bmp", 600, 200, 3, 2);
}
