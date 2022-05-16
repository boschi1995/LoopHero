#pragma once
class Image
{
public:
	enum IMAGE_LOAD_KIND { IMAGE_RESOURCE, IMAGE_FILE, IMAGE_EMPTY, IMAGE_END };

	typedef struct tagImage
	{
		DWORD		resID;	
		HDC			hMemDC;		
		HBITMAP		hBit, hOBit;	
		float currentFrameX, currentFrameY;
		float maxFrameX, maxFrameY;
		float frameWidth, frameHeight;
		int	width, height;	
		BYTE		LoadType;

		tagImage()
		{
			hMemDC = NULL;
			hBit = hOBit = NULL;
			resID = currentFrameX = currentFrameY = maxFrameX = maxFrameY = frameWidth = frameHeight = width = height = 0;
			LoadType = IMAGE_RESOURCE;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO		_imageInfo;	
	CHAR*				_fileName;		
	BOOL					_isTrans;	
	COLORREF			_transColor;	
	BLENDFUNCTION	_blendFunc;
	LPIMAGE_INFO		_blendImage;

public:

	#pragma region Initialization
			
		Image() : _imageInfo(NULL), _fileName(NULL), _isTrans(FALSE), _transColor(RGB(0, 0, 0)), _blendImage(NULL) { }	
		HRESULT init(int width, int height);
		HRESULT init(const DWORD resID, int width, int heigth, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
		HRESULT init(const char* fileName, int width, int heigth, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
		HRESULT init(const char* fileName, int width, int heigth, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
		HRESULT initAlphaBlend(void);

	#pragma endregion
	
	void release(void); ~Image() { }

	#pragma region reder

		void render(HDC hdc);
		void render(HDC hdc, int destX, int destY);
		void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

		void alphaRender(HDC hdc, BYTE alpha);
		void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
		void alphaRender(HDC hdc, int destX, int destY, int sourX, int SourY, int sourWidth, int sourHeight, BYTE alpha);
		void frameRender(HDC hdc, int destX, int destY);
		void frameRender(HDC hdc, int destX, int destY, int currenFrameX, int currenFrameY);
		void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
		void loopAlpha(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	#pragma endregion

	#pragma region get~

		inline HDC getMemDC(void) { return _imageInfo->hMemDC; }
		inline int getWidth() { return _imageInfo->width; }
		inline int getHeight() { return _imageInfo->height; }
		inline int getFrameX() { return _imageInfo->currentFrameX; }
		inline int getFrameY() { return _imageInfo->currentFrameY; }
		inline int getFrameWidth() { return _imageInfo->frameWidth; }
		inline int getFrameHeight() { return _imageInfo->frameHeight; }
		inline int getMaxFramX() { return _imageInfo->maxFrameX; }
		inline int getMaxFramY() { return _imageInfo->maxFrameY; }

	#pragma endregion

	#pragma region  set~

		void setColor(BOOL isTrans, COLORREF transColor)
		{ _isTrans = isTrans; _transColor = transColor; }

		inline void setFramX(int frameX)
		{
			_imageInfo->currentFrameX = frameX;
			if (frameX > _imageInfo->maxFrameX) { _imageInfo->currentFrameX = _imageInfo->maxFrameX; }
		}


		inline void setFramY(int frameY)
		{
			_imageInfo->currentFrameY = frameY;
			if (frameY > _imageInfo->maxFrameY) { _imageInfo->currentFrameY = _imageInfo->maxFrameY; }
		}

	#pragma endregion

};
