#include "Stdafx.h"
#include "RoadTap.h"
#include "GameScene.h"
 
HRESULT RoadTap::init(void)
{
	GameNode::init(false);
	worldInit();
	setLoopCallback(RoadTap::slimeLoop);
	return S_OK;
}

void RoadTap::release(void)
{
	GameNode::release();
}

void RoadTap::update(void)
{
	static int anInt;
	static bool loopCheck = true;
	GameNode::update();
	choisePoint.clear();
	isCardfalse();
	isItemDrag();

	anInt++;
	if (anInt >= 20)
	{
		anInt = IMAGEMANAGER->findImage("MONSTERS")->getFrameX() + 1;
		if (anInt == IMAGEMANAGER->findImage("MONSTERS")->getMaxFramX() + 1) { anInt = 0; }
		IMAGEMANAGER->findImage("MONSTERS")->setFramX(anInt);
		anInt = 0;
		loopCheck = true;
	}

	POINT camp = worldPoint(worldBlock(Camp)[0].point);
	if (GameScene::_player.point.x == camp.x && GameScene::_player.point.y == camp.y && loopCheck)
	{
		loop++; _monster.clear(); loopCheck = false;
		for (int i = 0; i < loopCallback.size(); i++) { loopCallback[i](*this); }
	}
}

void RoadTap::render(void)
{
	for (int i = 0; i < _world.size(); i++)
	{
		if (_world[i].first == Road)
		{ IMAGEMANAGER->frameRender("BLOCK", getMemDC(), worldPoint(_world[i].second.point).x - 30, worldPoint(_world[i].second.point).y - 30, _world[i].second.build, 1); }
		if (_world[i].second.build != Null)
		{ IMAGEMANAGER->frameRender("BLOCK", getMemDC(), worldPoint(_world[i].second.point).x - 30, worldPoint(_world[i].second.point).y - 30, _world[i].second.build, 1); }
	}

	for (int i = 0; i < _monster.size(); i++)
	{
		if (_monster[i].state == 0)
		{ IMAGEMANAGER->frameRender("MONSTERS", getMemDC(), worldPoint(_monster[i].point).x - 9, worldPoint(_monster[i].point).y - 9, IMAGEMANAGER->findImage("MONSTERS")->getFrameX(), _monster[i].character - 1); }

	}

	for (int i = 0; i < choisePoint.size(); i++)
	{ IMAGEMANAGER->render("CHOISE", getMemDC(), worldPoint(choisePoint[i]).x - 30, worldPoint(choisePoint[i]).y - 30); }

}

void RoadTap::slimeLoop(RoadTap& data)
{
	int rand;
	vector<POINT> road = data.worldForm(Road);
	for (int i = 0; i < road.size(); i++)
	{
		if (i != 0)
		{
			rand = RND->getFromInt(0, 100);
			if (rand <= 10) { data._monster.push_back(BaseData(Slime, road[i])); }
		}
	}
}

POINT RoadTap::worldPoint(POINT point)
{ return POINT{ point.x*BLOCK, (point.y*BLOCK) + BLOCK }; }

vector<POINT> RoadTap::worldForm(WorldTerms trem)
{
	vector<POINT> result;
	for (int i = 0; i < _world.size(); i++)
	{
		if (_world[i].first == trem && _world[i].second.build == Null) { result.push_back(_world[i].second.point); }
	}
	return result;
}

vector<BlockData> RoadTap::worldBlock(BuildTerms trem)
{
	vector<BlockData> result;
	for (int i = 0; i < _world.size(); i++)
	{
		if (_world[i].second.build == trem) { result.push_back(_world[i].second); }
	}
	return result;
}

void RoadTap::battleInit(BaseData& player)
{
	for (int i = 0; i < _monster.size(); i++)
	{
		if (player.point.x == worldPoint(_monster[i].point).x && player.point.y == worldPoint(_monster[i].point).y)
		{ _monster[i].state = 1; }
	}
	matching.clear();
}

void RoadTap::worldInit()
{
	int height, wide, x, y, s , i ;
	POINT rand;
	vector<pair<WorldTerms, BlockData>> road;
	vector<pair<WorldTerms, BlockData>> sideRoad;
	pair<WorldTerms, BlockData> subBlock;
	_world.push_back(pair <WorldTerms, BlockData> { Standard, BlockData() } );
	_world[0].second.point = POINT{ (FIELDWINDOW_X / 60) / 2, ((FIELDWINDOW_Y - 60) / 60) / 2 };
	for (s = 0; s < 4; s++)
	{
		rand.x = RND->getFromInt(3, 5);
		rand.y = RND->getFromInt(2, 3);
		if (s % 2 == 0) wide = -1; else wide = 1;
		if (s < 2) height = -1; else height = 1;
		for (x = 0; x < rand.x; x++)
		{
			for (y = 0; y < rand.y; y++)
			{
				subBlock.first = Standard; subBlock.second.point = { _world[0].second.point.x + (wide * x), _world[0].second.point.y + (height * y) };
				_world.push_back( pair<WorldTerms, BlockData>{ subBlock.first, subBlock.second} );
			}
		}
	}
	for (i = 0; i < _world.size(); i++)
	{
		for (s = 0; s < _world.size(); s++)
		{
			if (i != s && _world[i].second.point.x == _world[s].second.point.x && _world[i].second.point.y == _world[s].second.point.y)
			{
				_world.erase(_world.begin() + s);
			}
		}
	}
	for (height = 0; height < 12; height++)
	{
		for (wide = 0; wide < 21; wide++)
		{
			for (i = 0; i< _world.size(); i++)
			{
				rand = { 1 * wide,1 * height };
				if (rand.x == _world[i].second.point.x && rand.y == _world[i].second.point.y)
				{
					for (s = 0; s < 8; s++)
					{
						switch (s)
						{
							case 0: rand.x = 1; rand.y = 0; break;
							case 1: rand.x = 1; rand.y = 1; break;
							case 2: rand.x = 0; rand.y = 1; break;
							case 3: rand.x = -1; rand.y = 1; break;
							case 4: rand.x = -1; rand.y = 0; break;
							case 5: rand.x = -1; rand.y = -1; break;
							case 6: rand.x = 0; rand.y = -1; break;
							case 7: rand.x = 1; rand.y = -1; break;
						}
						subBlock.first = Road; subBlock.second.point = POINT{ (1 * wide) + (rand.x), (1 * height) + (rand.y) };
						road.push_back(subBlock);
					}
				}
			}
		}
	}
	for (i = 0; i < road.size(); i++)
	{
		for ( s = 0; s < road.size(); s++)
		{
			if (i != s && road[i].second.point.x == road[s].second.point.x && road[i].second.point.y == road[s].second.point.y)
			{ road.erase(road.begin() + s); }
		}
	}
	for (i = 0; i < _world.size(); i++)
	{
		for (s = 0; s < road.size(); s++)
		{
			if (road[s].second.point.x == _world[i].second.point.x && road[s].second.point.y == _world[i].second.point.y)
			{ road.erase(road.begin() + s); }
		}
	}
	_world.clear();
	subBlock.second.build = Null;
	subBlock.first = Standard;
	for (height = 0; height < 12; height++)
	{
		for (wide = 0; wide < 21; wide++)
		{
			subBlock.second.point = POINT{ 1 + wide, 1 + height };
			_world.push_back(subBlock);
		}
	}
	height = 0;
	for (int i = 0; i < _world.size(); i++)
	{
		for (int j = 0; j < road.size(); j++)
		{
			if (_world[i].second.point.x == road[j].second.point.x && _world[i].second.point.y == road[j].second.point.y)
			{
				_world[i].first = Road;
				if (height == 0) { _world[i].second.build = Camp; height++; }
				else { _world[i].second.build = Null; }
			}
		}
	}
	for (i = 0; i < road.size(); i++)
	{
		for (s = 0; s < 4; s++)
		{
			switch (s)
			{
				case 0: subBlock.second.point = { road[i].second.point.x - 1, road[i].second.point.y }; break;
				case 1: subBlock.second.point = { road[i].second.point.x, road[i].second.point.y - 1 }; break;
				case 2: subBlock.second.point = { road[i].second.point.x + 1, road[i].second.point.y }; break;
				case 3: subBlock.second.point = { road[i].second.point.x, road[i].second.point.y + 1 }; break;
			}
			sideRoad.push_back(subBlock);
		}
	}
	
	for (i = 0; i < road.size(); i++)
	{
		for (s = 0; s < sideRoad.size(); s++)
		{
			if (sideRoad[s].second.point.x == road[i].second.point.x && sideRoad[s].second.point.y == road[i].second.point.y)
			{ sideRoad.erase(sideRoad.begin() + s); }
		}
	}

	for (int i = 0; i < _world.size(); i++)
	{
		for (s = 0; s < sideRoad.size(); s++)
		{
			if (_world[i].second.point.x == sideRoad[s].second.point.x && _world[i].second.point.y == sideRoad[s].second.point.y)
			{ _world[i].first = UnderRoad; }
		}
	}
}

POINT RoadTap::playerPoint()
{
	POINT result;
	for (int s = 0; s < _world.size(); s++)
	{ if (_world[s].second.build == Camp) { result = worldPoint(_world[s].second.point); break; } }
	return result;
}

void RoadTap::playerPoint(BaseData& player)
{
	POINT result;
	RECT temp[3] = { {0,0,0,0}, RectMakeCenter(player.point.x, player.point.y, 60, 60), {0,0,0,0} };

	vector<POINT> freePoint;
	for (int i = 0; i < _world.size(); i++)
	{ if (_world[i].first == UnderRoad) { freePoint.push_back(_world[i].second.point); } }

	POINT mid = worldPoint(POINT{ 10,6 });
	switch (player.state)
	{
		case 0: player.point.x++; break;
		case 1: player.point.x--;  break;
		case 2: player.point.y++; break;
		case 3: player.point.y--; break;
	}
	for (int i = 0; i < freePoint.size(); i++)
	{
		temp[2] = RectMakeCenter(worldPoint(freePoint[i]).x, worldPoint(freePoint[i]).y, 60, 60);

		if (IntersectRect(&temp[0], &temp[1], &temp[2]))
		{
			switch (player.state)
			{
				case 0:
				{
					player.point.x -= 2;
					if (player.point.x > mid.x) { player.state = 2; } else { player.state = 3; }
				}break;
				case 1:
				{
					player.point.x += 2;
					if (player.point.x > mid.x)
					{ player.state = 2; }
					else { player.state = 3; }
				}break;
				case 2:
				{
					player.point.y -= 2;
					if (player.point.y < mid.y) { player.state = 0; } else { player.state = 1; }
				}break;
				case 3:
				{
					player.point.y += 2;
					if (player.point.y < mid.y) { player.state = 0; } else { player.state = 1; }
				}break;
			}
		}
	}
}

vector<BaseData> RoadTap::playerCollision(BaseData& player)
{
	matching.clear();
	for (int i = 0; i < _monster.size(); i++)
	{
		if (_monster[i].state == 0)
		{
			if (player.point.x == worldPoint(_monster[i].point).x && player.point.y == worldPoint(_monster[i].point).y)
			{
				matching.push_back(player);
				int matchingState = 0;
				for (int j = 0; j < _monster.size(); j++)
				{
					if (matchingState == 5) break;
					if (player.point.x == worldPoint(_monster[j].point).x && player.point.y == worldPoint(_monster[j].point).y)
					{
						for (int c = 0; c < matcingCallback.size(); c++) { matcingCallback[c](*this); }
						matchingState++;
						matching.push_back(_monster[j]);
					}
				}
				return matching;
			}
		}
	}
	return matching;
}

void RoadTap::isCardfalse()
{
	vector<BlockData> card = GameScene::_card;
	for (int i = 0; i < card.size(); i++)
	{
		if (card[i].isCard == false)
		{
			RECT temp;
			choisePoint = worldForm(card[i].world);
			GameScene::_card[i].point = _ptMouse;
			for (int s = 0; s < choisePoint.size(); s++)
			{
				temp = RectMakeCenter(worldPoint(choisePoint[s]).x, worldPoint(choisePoint[s]).y, 60, 60);
				if (PtInRect(&temp, _ptMouse))
				{ 
					GameScene::_card[i].point = worldPoint(choisePoint[s]);
					card[i].point = choisePoint[s];
					break; 
				}
			}
			//card[i] = GameScene::_card[i];
			if (KEYMANAGER->inKeyUp(MK_LBUTTON))
			{
				for (int c = 0; c < _world.size(); c++)
				{
					if (_world[c].first == card[i].world && _world[c].second.point.x == card[i].point.x && _world[c].second.point.y == card[i].point.y)
					{
						_world[c].second = card[i];
						if (card[i].build == spiderCocoon) { setLoopCallback(RoadTap::spiderLoop); }
						else if (card[i].build == Cemetery) { setLoopCallback(RoadTap::cemeteryLoop); }
						GameScene::_card[i].isCard = true;
						GameScene::_card.erase(GameScene::_card.begin() + i);
						GameScene::_updataStop = false;
						return;
					}
				}
				GameScene::_card[i].isCard = true;
				GameScene::_updataStop = false;
			}
		}
	}
}

void RoadTap::isItemDrag()
{
	for (int i = 0; i < GameScene::_item.size(); i++)
	{
		if (GameScene::_item[i].isDrag == true)
		{
			RECT temp;
			GameScene::_item[i].point = _ptMouse;
			int j = 0;
			for ( j = 0; j < GameScene::_equipment.size()-1; j++) { if (GameScene::_equipment[j].state == GameScene::_item[i].state) { break; } }
			choisePoint.push_back(GameScene::_equipment[j].point);
			temp = RectMakeCenter(choisePoint[0].x, choisePoint[0].y, 60, 60);
			if (PtInRect(&temp, _ptMouse))
			{ GameScene::_item[i].point = choisePoint[0]; GameScene::_item[i].point = choisePoint[0]; }
			
			if (KEYMANAGER->inKeyUp(MK_LBUTTON))
			{
				if (GameScene::_item[i].point.x == choisePoint[0].x && GameScene::_item[i].point.y == choisePoint[0].y)
				{
					for(int s = 0; s < GameScene::_equipment[i].outCallback.size(); s++)
					{ GameScene::_equipment[i].outCallback[s](GameScene::_player); }
					for (int s = 0; s < GameScene::_item[i].setCallback.size(); s++)
					{ GameScene::_item[i].setCallback[s](GameScene::_player); }
					GameScene::_equipment[j] = GameScene::_item[i];
					//`1 item[i] Æã¼Ç ÀÔ·Â 
					GameScene::_item[i].isDrag = false;
					GameScene::_updataStop = false;
					GameScene::_item.erase(GameScene::_item.begin() + i);
					break;
				}
				else
				{
					GameScene::_item[i].isDrag = false;
					GameScene::_updataStop = false;
				}
			}
		}
	}
}

void RoadTap::spiderLoop(RoadTap& data)
{
	bool stop = false; 
	POINT sub[4];
	vector<BlockData> Cocoon = data.worldBlock(spiderCocoon);
	vector<POINT> road = data.worldForm(Road);

	for (int i = 0; i < Cocoon.size(); i++)
	{
		for (int s = 0; s < 4; s++)
		{
			switch (s)
			{
			case 0: sub[s] = { Cocoon[i].point.x - 1, Cocoon[i].point.y }; break;
			case 1: sub[s] = { Cocoon[i].point.x, Cocoon[i].point.y - 1 }; break;
			case 2: sub[s] = { Cocoon[i].point.x + 1, Cocoon[i].point.y }; break;
			case 3: sub[s] = { Cocoon[i].point.x, Cocoon[i].point.y + 1 }; break;
			}
		}

		for (int s = 0; s < road.size(); s++)
		{
			for (int g = 0; g < 4; g++)
			{
				if (road[s].x == sub[g].x && road[s].y == sub[g].y)
				{
					data.setmonster(BaseData(Spider, road[s]));
					stop = true;
					break;
				}
			}
			if (stop) break;
		}
	}
}

void RoadTap::cemeteryLoop(RoadTap & data)
{
	int rand;
	vector<BlockData> road = data.worldBlock(Cemetery);
	for (int i = 0; i < road.size(); i++)
	{
		data._monster.push_back(BaseData(Skeleton, road[i].point));
	}
}



