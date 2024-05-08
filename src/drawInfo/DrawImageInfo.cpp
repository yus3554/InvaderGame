#include "DrawImageInfo.h"

DrawImageInfo::DrawImageInfo(POINT pos, ResourceData* resourceData, LPDWORD backPixelBits, int pixelOffset)
{
	this->pos = {pos.x, pos.y};

	this->resourceData = resourceData;
	this->backPixelBits = backPixelBits;
	this->pixelOffset = pixelOffset;
}

void DrawImageInfo::render(HDC hdc)
{
	int backPixelBitsIndex;
	int resourcePixelBitsIndex;
	// backPixelBitsにpixelBitsを代入（アルファが0のピクセルはスキップ）
	for (int i = 0; i < this->resourceData->width; i++)
	{
		for (int j = 0; j < this->resourceData->height; j++)
		{
			// resourceDataのindex（i, j）をbackBMPのPixelBitsのindexに変換
			backPixelBitsIndex = i + this->pos.x + (j + this->pos.y) * WND_SIZE.x;

			// resourceのpixelBitsindex
			resourcePixelBitsIndex = i + j * this->resourceData->width + this->pixelOffset;
			resourcePixelBitsIndex = resourcePixelBitsIndex % (this->resourceData->width * this->resourceData->height);
			resourcePixelBitsIndex = abs(resourcePixelBitsIndex);

			// backPixelBitsIndexがbackPixelBitsの範囲をはみ出すときはスキップ
			if (backPixelBitsIndex < 0 || backPixelBitsIndex >= WND_SIZE.x * WND_SIZE.y)
				continue;
			
			// alphaが0x00のときはスキップ（マスク処理）
			if ((this->resourceData->pixelBits[resourcePixelBitsIndex] & 0x11000000) >> 24 == 0x00)
				continue;

			this->backPixelBits[backPixelBitsIndex] = this->resourceData->pixelBits[resourcePixelBitsIndex];
		}
	}
}

