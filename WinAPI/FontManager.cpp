#include "Stdafx.h"
#include "FontManager.h"

void FontManager::drawText(HDC hdc, int x, int y, char* fontname, char * filetname, int fontSize, int fontW, char * pint, int length, COLORREF color)
{

}

void FontManager::drawText(HDC hdc, int x, int y, char* fontname, int fontSize, int fontW, char * pint, int length, COLORREF color)
{

}

void FontManager::drawText(HDC hdc, int x, int y, char* fontname, int fontSize, int fontW, LPCWSTR pint, int length, COLORREF color)
{

	SetBkMode(hdc, TRANSPARENT);

	HFONT hFont = CreateFont
	(
		fontSize, 0, 0, 5, fontW,
		0, 0, 0,
		HANGUL_CHARSET, 0, 0, 0,
		VARIABLE_PITCH | FF_ROMAN, TEXT(fontname)
	);

	auto oldFont = (HFONT)SelectObject(hdc, hFont);
	auto oldColor = GetTextColor(hdc);

	SetTextColor(hdc, color);
	TextOutW(hdc, x, y, pint, length);

	SetTextColor(hdc, oldColor);
}

void FontManager::drawText(HDC hdc, int x, int y, char* fontname, int fontSize, int fontW, LPCWSTR * pint, int length, COLORREF color)
{
	///int arraySize = sizeof() 

}
