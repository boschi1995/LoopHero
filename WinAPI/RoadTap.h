#pragma once
#include"GameNode.h"
#include "BlockData.h"


class RoadTap : public GameNode
{
	private:
		vector<BaseData> matching;
		vector<BaseData> _monster;
		static void slimeLoop(RoadTap&);
		static void spiderLoop(RoadTap&);
		static void cemeteryLoop(RoadTap&);
		vector<pair<WorldTerms, BlockData>> _world;
		void worldInit();
		vector<function<void(RoadTap&)>> loopCallback;
		vector<function<void(RoadTap&)>> matcingCallback;
		void isCardfalse();
		void isItemDrag();
		vector<POINT> choisePoint;
	public:
		POINT playerPoint();
		void playerPoint(BaseData&);
		vector<BaseData> playerCollision() { return matching; };
		vector<BaseData> playerCollision(BaseData&);
		vector<POINT> worldForm(WorldTerms trem);
		vector<BlockData> worldBlock(BuildTerms trem);
		POINT worldPoint(POINT point);
		void battleInit(BaseData& player);
		void setmonster(BaseData data) { _monster.push_back(data); }
		void setLoopCallback( function<void(RoadTap&)> func) { loopCallback.push_back(func); };
		int loop;

	#pragma region Standard

		public:
			HRESULT init(void);
			void release(void);
			void update(void);
			void render(void);
			RoadTap() { init(); };
			~RoadTap() { };

	#pragma endregion

};