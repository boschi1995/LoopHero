#pragma once
#include "Stdafx.h"

#pragma region  Line

	inline void LineRander(HDC hdc, int startX, int startY, int endX, int endY)
	{ MoveToEx(hdc, startX, startY, NULL); LineTo(hdc, endX, endY); }

#pragma endregion

#pragma region RECT

	inline RECT RectMake(int x, int y, int width, int height)
	{ return RECT{ x, y, x + width, y + height }; }

	inline RECT RectMakeCenter(int x, int y, int width, int height)
	{ return RECT { x - width / 2, y - height / 2, x + width / 2, y + height / 2 }; }

#pragma endregion

#pragma region Box

	inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
	{ Rectangle(hdc, x, y, x + width, y + height); }

	inline void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height)
	{ Rectangle(hdc, x - width / 2, y - height / 2 , x + width / 2, y + height /2); }

#pragma endregion

#pragma region Circle

	inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
	{ Ellipse(hdc, x, y, x + width, y + height); }

	inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height) 
	{ Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2); }

#pragma endregion