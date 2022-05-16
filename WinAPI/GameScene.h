#pragma once
#include"GameNode.h"
#include "RoadTap.h"
#include "BattleTap.h"

class GameScene : public GameNode
{
	private:

		POINT _playerPoint;
		RoadTap* _RoadScene;
		BattleTap* _BattleScene;
		bool _TransScene;
		bool _oneFrame;
		void cardObtain();
		void cardPoint();
		void itemObtain();
		void itemPoint();
		
		void imageLoad();
		int anInt;
		RECT healthBar;
	public:
		HRESULT init(void);
		void release(void);
		void update(void);
		void render(void);
		GameScene() { init(); };
		~GameScene() { };
		
		
		static bool _updataStop;
		static 	BaseData _player;
		static vector<string> text;
		static vector<BlockData> _card;
		static vector<ItemData> _item;
		static vector<ItemData> _equipment; 
};
