#include "Stdafx.h"
#include "MainGame.h"

HRESULT MainGame::init(void)
{
	GameNode::init(true);
	_gameScene = new GameScene();
	_presentScene = _gameScene;
	SceneChage = false;
	IMAGEMANAGER->addImage("LOBBY", "Resource/LOBBY.bmp", WINSIZE_X, WINSIZE_Y);
	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
	if (SceneChage) { _presentScene->release(); }
}

void MainGame::update(void)
{
	GameNode::update();
	if (SceneChage) { _presentScene->update(); return; }
	if (KEYMANAGER->isKeyDown(VK_SPACE)) { SceneChage = true; }
}


void MainGame::render(void)
{
	if (SceneChage) { _presentScene->render(); }
	else { IMAGEMANAGER->render("LOBBY", getMemDC()); }
	backBuffer->render(getHDC(),0,0);
}
	