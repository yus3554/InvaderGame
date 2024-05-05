#include "DrawImageInfo.h"

DrawImageInfo::DrawImageInfo(POINT pos, int width, int height, BYTE* pixelBits, LPDWORD backPixelBits)
{
	this->pos = pos;

	this->width = width;
	this->height = height;

	this->pixelBits = pixelBits;
	this->backPixelBits = backPixelBits;
}

void DrawImageInfo::render(HDC hdc)
{
	// backPixelBitsにpixelBitsを代入（アルファが0のピクセルはスキップ）
	for (int i = 0; i < this->width; i++)
	{
		for (int j = 0; j < this->height; j++)
		{
			// ここで、横とか縦を超えちゃった場合に無視する処理いれる
			// それと、アルファが0のときスキップする処理いれる
			this->backPixelBits[i + this->pos.x + (j + this->pos.y) * WND_SIZE.x] = this->pixelBits[i + j * this->width];
		}
	}
}

