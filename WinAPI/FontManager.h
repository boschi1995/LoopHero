#pragma once
#include "SingletonBase.h"
class FontManager : public SingletonBase < FontManager >
{
public:
	void drawText(HDC hdc, int x, int y, char* fontname, char* filetname, int fontSize, int fontW, char* pint, int length, COLORREF color);

	void drawText(HDC hdc, int x, int y, char* fontname, int fontSize, int fontW, char* pint, int length, COLORREF color);

	void drawText(HDC hdc, int x, int y, char* fontname, int fontSize, int fontW, LPCWSTR pint, int length, COLORREF color);

	void drawText(HDC hdc, int x, int y, char* fontname, int fontSize, int fontW, LPCWSTR* pint, int length, COLORREF color);

};

