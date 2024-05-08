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
	// backPixelBits��pixelBits�����i�A���t�@��0�̃s�N�Z���̓X�L�b�v�j
	for (int i = 0; i < this->resourceData->width; i++)
	{
		for (int j = 0; j < this->resourceData->height; j++)
		{
			// resourceData��index�ii, j�j��backBMP��PixelBits��index�ɕϊ�
			backPixelBitsIndex = i + this->pos.x + (j + this->pos.y) * WND_SIZE.x;

			// resource��pixelBitsindex
			resourcePixelBitsIndex = i + j * this->resourceData->width + this->pixelOffset;
			resourcePixelBitsIndex = resourcePixelBitsIndex % (this->resourceData->width * this->resourceData->height);
			resourcePixelBitsIndex = abs(resourcePixelBitsIndex);

			// backPixelBitsIndex��backPixelBits�͈̔͂��͂ݏo���Ƃ��̓X�L�b�v
			if (backPixelBitsIndex < 0 || backPixelBitsIndex >= WND_SIZE.x * WND_SIZE.y)
				continue;
			
			// alpha��0x00�̂Ƃ��̓X�L�b�v�i�}�X�N�����j
			if ((this->resourceData->pixelBits[resourcePixelBitsIndex] & 0x11000000) >> 24 == 0x00)
				continue;

			this->backPixelBits[backPixelBitsIndex] = this->resourceData->pixelBits[resourcePixelBitsIndex];
		}
	}
}

