#include "DrawImageInfo.h"

DrawImageInfo::DrawImageInfo(POINT pos, ResourceData* resourceData, LPDWORD backPixelBits)
{
	this->pos = {pos.x, pos.y};

	this->resourceData = resourceData;
	this->backPixelBits = backPixelBits;
}

void DrawImageInfo::render(HDC hdc)
{
	int backPixelBitsIndex;
	// backPixelBits��pixelBits�����i�A���t�@��0�̃s�N�Z���̓X�L�b�v�j
	for (int i = 0; i < this->resourceData->width; i++)
	{
		for (int j = 0; j < this->resourceData->height; j++)
		{
			// resourceData��index�ii, j�j��backBMP��PixelBits��index�ɕϊ�
			backPixelBitsIndex = i + this->pos.x + (j + this->pos.y) * WND_SIZE.x;

			// backPixelBitsIndex��backPixelBits�͈̔͂��͂ݏo���Ƃ��̓X�L�b�v
			if (backPixelBitsIndex < 0 || backPixelBitsIndex >= WND_SIZE.x * WND_SIZE.y)
				continue;
			
			// alpha��0x00�̂Ƃ��̓X�L�b�v�i�}�X�N�����j
			if ((this->resourceData->pixelBits[i + j * this->resourceData->width] & 0x11000000) >> 24 == 0x00)
				continue;

			this->backPixelBits[backPixelBitsIndex] = this->resourceData->pixelBits[i + j * this->resourceData->width];
		}
	}
}

