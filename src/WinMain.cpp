#include <windows.h>
#include <stdio.h>
#include "Constants.h"
#include "DrawManager.h"
#include "GameManager.h"


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (msg)
	{
	case WM_CREATE:
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

/// <summary>
/// ���C���֐�
/// </summary>
/// <param name="hInstance"></param>
/// <param name="hPrevInstance"></param>
/// <param name="pCmdLine"></param>
/// <param name="nCmdShow"></param>
/// <returns></returns>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
{
	HWND hwnd;
	WNDCLASS winc{};
	MSG msg;

	// �E�B���h�E�N���X�쐬
	winc.style = CS_HREDRAW | CS_VREDRAW;
	winc.lpfnWndProc = WndProc;
	winc.cbClsExtra = winc.cbWndExtra = 0;
	winc.hInstance = hInstance;
	winc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winc.hCursor = LoadCursor(NULL, IDC_ARROW);
	winc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	winc.lpszMenuName = NULL;
	winc.lpszClassName = WND_CLASS_NAME;
	// �E�B���h�E�N���X�o�^
	if (!RegisterClass(&winc)) return 0;

	// �E�B���h�E�쐬�E�\��
	hwnd = CreateWindow(
		WND_CLASS_NAME, WND_TITLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, WND_SIZE.x, WND_SIZE.y,
		NULL, NULL, hInstance, NULL
	);
	if (hwnd == NULL) return 0;

	// �Q�[���̏�Ԃ�l�X�Ȓl���Ǘ�����N���X
	GameManager* gm = new GameManager();
	// �`���S������N���X
	DrawManager* dm = new DrawManager(gm, hwnd);

	HDC hdc;

	// ���Ԍv��
	int fps = 240;
	int loop;
	int nowFrame;
	int beforeFrame = 0;
	LARGE_INTEGER cpuFreq;  // CPU���g��
	QueryPerformanceFrequency(&cpuFreq);
	LARGE_INTEGER startCount;
	LARGE_INTEGER nowCount;
	QueryPerformanceCounter(&startCount);

	// ���b�Z�[�W���[�v�iWM_QUIT���̂݃��[�v�𔲂���j
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {

			// �G�X�P�[�v�L�[���� or State��Quit �̏ꍇ�ɏI��
			if(KEYDOWN(VK_ESCAPE) || gm->getCurrentGameState() == STATE_QUIT)
				SendMessage(hwnd, WM_CLOSE, 0, 0);

			// �L�[����
			// TODO: ������key��������邽�тɓ����̒l��ς��Ă��܂��ƁA���[�v�̃X�s�[�h����ŕς���Ă��܂�
			// TODO: �܂�ACPU�̐��\���ǂ��قǑ���������
			// TODO: ���Ƃ����āAkeyPress��for�̒��ɂ����ƁAfor�ɓ����Ă���Ԃ���key�����Ȃ�
			// TODO: �����ŁAkeyPress�͎�葱���A���ۂɒl�������̂�for�ɓ������Ƃ������ɂ����ق�������
			// TODO: keyPress�ɓ��邽�тɌ��݉�����Ă���Key���X�V���Â���
			// TODO: for�ɓ������Ƃ��ɁA���݉�����Ă���Key���擾���Ď��s����
			gm->keyPress();

			// �t���[�����[�g�v�Z
			QueryPerformanceCounter(&nowCount);
			nowFrame = (int)((nowCount.QuadPart - startCount.QuadPart) / (cpuFreq.QuadPart / fps));
			if (nowFrame != beforeFrame) {
				loop = nowFrame - beforeFrame;
				beforeFrame = nowFrame;
			}
			else {
				loop = 0;
			}

			// ���C������
			for (int i = 0; i < loop; i++)
			{
				// TODO: �L�[���͂̏������������ōs��
				// TODO: �J�[�\���̑��x�������Ȃ肷����̂ŁA��O�̃t���[���Ɠ����L�[��������Ă����疳������悤�ɂ����ق�������
				hdc = GetDC(hwnd);
				dm->paint(hdc);
				ReleaseDC(hwnd, hdc);
			}

			Sleep(3);
		}
	}
	delete gm;
	delete dm;

	return msg.wParam;
}