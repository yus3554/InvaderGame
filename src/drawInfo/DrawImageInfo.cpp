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
	// backPixelBits��pixelBits�����i�A���t�@��0�̃s�N�Z���̓X�L�b�v�j
	for (int i = 0; i < this->width; i++)
	{
		for (int j = 0; j < this->height; j++)
		{
			// �����ŁA���Ƃ��c�𒴂���������ꍇ�ɖ������鏈�������
			// ����ƁA�A���t�@��0�̂Ƃ��X�L�b�v���鏈�������
			this->backPixelBits[i + this->pos.x + (j + this->pos.y) * WND_SIZE.x] = this->pixelBits[i + j * this->width];
		}
	}
}

