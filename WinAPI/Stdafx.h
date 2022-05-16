#pragma once

#pragma region Windows API

	#include <sdkddkver.h>
	#include "targetver.h"

	#define WIN32_LEAN_AND_MEAN   
	#include <windows.h>

	extern HINSTANCE	_hInstance;
	extern HWND			_hWnd;
	extern POINT		_ptMouse;

	#pragma region Windows Macro

	#define WINSTART_X				0
	#define WINSTART_Y				0
	#define WINSIZE_X					1600
	#define WINSIZE_Y					900
	#define WINSTYLE					WS_CAPTION | WS_SYSMENU 
	#define WINNAME					(LPSTR)(TEXT("WindowsAPI"))

	#pragma endregion

#pragma endregion

#pragma region  C / C++ 

	#include <stdlib.h>
	#include <time.h>
	#include <assert.h>
	#include <stdio.h>
	#include <tchar.h>
	#include <iostream>
	#include <random>
	#include <bitset>
	#include <vector>
	#include <map>
	#include <functional>

using namespace std;

#pragma endregion

#pragma region  My Code

	#include "MakeFunction.h"
	#include "RandomFunction.h"
	#include "KeyManager.h"
	#include "ImageManager.h"
	#include "FontManager.h"

	#define RND RandomFunction::getSingleton()
	#define KEYMANAGER KeyManager::getSingleton()
	#define IMAGEMANAGER ImageManager::getSingleton()
	#define FONTMANAGER FontManager::getSingleton()

	#define SAFE_DELETE(p)			{if(p) {delete(p);      (p) = nullptr;}} 
	#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p);   (p) = nullptr;}}
	#define SAFE_RELEASE(p)			{if(p) {(p)->release(); (p) = nullptr;}}  

	#define BLOCK 60
	#define FIELDWINDOW_STARTX	0
	#define FIELDWINDOW_X			1260 
	#define FIELDWINDOW_STARTY	60
	#define FIELDWINDOW_Y			780 

	#define CARDWINDOW_STARTX	0
	#define CARDWINDOW_X			1260
	#define CARDWINDOW_STARTY	780
	#define CARDWINDOW_Y			WINSIZE_Y

	#define ABILITYWINDOW_STARTX	1320
	#define ABILITYWINDOW_X			WINSIZE_X
	#define ABILITYWINDOW_STARTY	0
	#define ABILITYWINDOW_Y			WINSIZE_Y

	#define BattleField_X ( FIELDWINDOW_X - 300 )
	#define BattleField_Y ( FIELDWINDOW_Y - 200 )

	#define ERASER  RGB (255,0,255)

	enum CharacterSit { Player, Slime, Spider, Skeleton };

	enum WorldTerms { Standard, Road, UnderRoad };

	enum BuildTerms
	{
		Null, Camp,
		Pasture, Mountain, Rock,
		Cemetery, Forest,
		spiderCocoon, VampireMansion, StreetLamp
	};


	enum ItemSit
	{
		Necklace, Armor, Shoes, HeadGear, Ring, Shield, Weapon, ItemSitEnd, slot
	};

	enum ItemOption
	{
		Critical, Absorption, Evasion, IdieRecovery, ItemOptionEnd
	};

	#include "BlockData.h"
	#include "BaseData.h"
	#include "CardData.h"
	#include "ItemData.h"

#pragma endregion
