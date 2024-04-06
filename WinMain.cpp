#include<windows.h>
#include<stdio.h>

void CollisionDetection(int charaX, int charaY, int* gamenSeniFlg) {
	if (charaX < 0 || charaX > 100 || charaY < 0 || charaY > 100) {
		*gamenSeniFlg = 2;
	}
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
	HDC hdc;
	HFONT font;
	PAINTSTRUCT ps;
	HGDIOBJ hgdi;
	static RECT rect;
	static PCTSTR ctStrTitle = TEXT("�C���x�[�_�[�Q�[��");
	static PCTSTR ctStrStart = TEXT("Start");
	static PCTSTR ctStrQuit = TEXT("Quit");
	static PCTSTR ctStrChara = TEXT("�L����");
	static PCTSTR ctStrResult = TEXT("GameOver");

	// 0: start, 1: quit
	static int titleButtonFlg = 0;


	static int x = 10;
	static int y = 10;

	// 0: title, 1: game, 2: result
	static int gamenSeniFlg = 0;

	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		switch (gamenSeniFlg)
		{
		case 0:  // title
			GetClientRect(hwnd, &rect);

			// title
			font = CreateFont(
				30, 0,					//����, ��
				0, 0,					//�p�x1, �p�x2
				FW_DONTCARE,			//����
				FALSE, FALSE, FALSE,	//�Α�, ����, �ŏ�����
				SHIFTJIS_CHARSET,		//�����Z�b�g
				OUT_DEFAULT_PRECIS,		//���x
				CLIP_DEFAULT_PRECIS,	//���x
				DEFAULT_QUALITY,		//�i��
				DEFAULT_PITCH | FF_DONTCARE, //�s�b�`�ƃt�@�~��
				L"���C���I");			//�t�H���g��
			hgdi = SelectObject(hdc, font);
			rect.top += DrawText(hdc, ctStrTitle, -1, &rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
			rect.top += 20;

			// button
			int height;
			if (titleButtonFlg == 0) {
				height = 20;
			}
			else {
				height = 10;
			}
			font = CreateFont(
				height, 0,					//����, ��
				0, 0,					//�p�x1, �p�x2
				FW_DONTCARE,			//����
				FALSE, FALSE, FALSE,	//�Α�, ����, �ŏ�����
				SHIFTJIS_CHARSET,		//�����Z�b�g
				OUT_DEFAULT_PRECIS,		//���x
				CLIP_DEFAULT_PRECIS,	//���x
				DEFAULT_QUALITY,		//�i��
				DEFAULT_PITCH | FF_DONTCARE, //�s�b�`�ƃt�@�~��
				L"���C���I");			//�t�H���g��
			hgdi = SelectObject(hdc, font);
			rect.top += DrawText(hdc, ctStrStart, -1, &rect, DT_CENTER);
			// TextOut(hdc, (rect.left + rect.right) / 2, rect.bottom - 150, ctStrStart, lstrlen(ctStrStart));

			if (titleButtonFlg != 0) {
				height = 20;
			}
			else {
				height = 10;
			}
			font = CreateFont(
				height, 0,					//����, ��
				0, 0,					//�p�x1, �p�x2
				FW_DONTCARE,			//����
				FALSE, FALSE, FALSE,	//�Α�, ����, �ŏ�����
				SHIFTJIS_CHARSET,		//�����Z�b�g
				OUT_DEFAULT_PRECIS,		//���x
				CLIP_DEFAULT_PRECIS,	//���x
				DEFAULT_QUALITY,		//�i��
				DEFAULT_PITCH | FF_DONTCARE, //�s�b�`�ƃt�@�~��
				L"���C���I");			//�t�H���g��
			hgdi = SelectObject(hdc, font);
			rect.top += DrawText(hdc, ctStrQuit, -1, &rect, DT_CENTER);

			break;
		case 1:  // game
			MoveToEx(hdc, 10, 10, NULL);
			LineTo(hdc, 110, 10);
			LineTo(hdc, 110, 110);
			TextOut(hdc, x, y, ctStrChara, lstrlen(ctStrChara));
			break;
		case 2:  // result
			// result
			font = CreateFont(
				30, 0,					//����, ��
				0, 0,					//�p�x1, �p�x2
				FW_DONTCARE,			//����
				FALSE, FALSE, FALSE,	//�Α�, ����, �ŏ�����
				SHIFTJIS_CHARSET,		//�����Z�b�g
				OUT_DEFAULT_PRECIS,		//���x
				CLIP_DEFAULT_PRECIS,	//���x
				DEFAULT_QUALITY,		//�i��
				DEFAULT_PITCH | FF_DONTCARE, //�s�b�`�ƃt�@�~��
				L"���C���I");			//�t�H���g��
			hgdi = SelectObject(hdc, font);
			DrawText(hdc, ctStrResult, -1, &rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
			break;
		default:
			break;
		}
		
		EndPaint(hwnd, &ps);
		return 0;
	case WM_KEYDOWN:

		switch (wp)
		{
		case VK_LEFT:
			x -= 10;
			CollisionDetection(x, y, &gamenSeniFlg);
			InvalidateRect(hwnd, NULL, TRUE);
			return 0;
		case VK_RIGHT:
			x += 10;
			CollisionDetection(x, y, &gamenSeniFlg);
			InvalidateRect(hwnd, NULL, TRUE);
			return 0;
		case VK_UP:
			switch (gamenSeniFlg)
			{
			case 0:  // title
				titleButtonFlg = 0;
				break;
			case 1:
				y -= 10;
				break;
			default:
				break;
			}
			CollisionDetection(x, y, &gamenSeniFlg);
			InvalidateRect(hwnd, NULL, TRUE);
			return 0;
		case VK_DOWN:
			switch (gamenSeniFlg)
			{
			case 0:  // title
				titleButtonFlg = 1;
				break;
			case 1:
				y += 10;
				break;
			default:
				break;
			}
			CollisionDetection(x, y, &gamenSeniFlg);
			InvalidateRect(hwnd, NULL, TRUE);
			return 0;
		case VK_RETURN:
			switch (gamenSeniFlg)
			{
			case 0:  // title
				if (titleButtonFlg == 0) {
					gamenSeniFlg = 1;
				}
				else {
					DestroyWindow(hwnd);
					PostQuitMessage(0);
					return 0;
				}
				break;
			case 2:  // result
				gamenSeniFlg = 0;
				break;
			default:
				break;
			}
			InvalidateRect(hwnd, NULL, TRUE);
			return 0;
		}
	}
	return DefWindowProc(hwnd, msg, wp, lp);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR pCmdLine, int nCmdShow) {
	HWND hwnd;
	WNDCLASS winc;
	MSG msg;

	winc.style = CS_HREDRAW | CS_VREDRAW;
	winc.lpfnWndProc = WndProc;
	winc.cbClsExtra = winc.cbWndExtra = 0;
	winc.hInstance = hInstance;
	winc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winc.hCursor = LoadCursor(NULL, IDC_ARROW);
	winc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	winc.lpszMenuName = NULL;
	winc.lpszClassName = TEXT("KITTY");

	if (!RegisterClass(&winc)) return 0;

	hwnd = CreateWindow(
		TEXT("KITTY"), TEXT("Kitty on your lap"),
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 400,
		NULL, NULL, hInstance, NULL
	);

	if (hwnd == NULL) return 0;

	while (GetMessage(&msg, NULL, 0, 0)) DispatchMessage(&msg);
	return msg.wParam;
}