#pragma once
#include"GameNode.h"
#include "MainGame.h"
#include "GameScene.h"

class MainGame : public GameNode
{
	private:
		GameNode* _presentScene;
		GameScene* _gameScene;
		bool SceneChage;
	public:
		HRESULT init(void); 
		void release(void);
		void update(void);
		void render(void);
		MainGame() { };
		~MainGame() { };

};
