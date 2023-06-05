
/*
�@�q�����禡�B�����ܼƦ�m

mousey
mousex
���ƹ�xy��m
resetmousesit() �N��s�ƹ���m��mousex�Bmousey
SetWindowsSize(int w,int h) �B�z������m�P�j�p
PageShake()��������
PageMove()���wxy�T�w������m
printsit()�Ω���աA��bView()�BPrint()�̥i�H��X�ƹ���m�H�οù��̤j��m
gotoxy(x, y)�Ndos�������в���xy�A����00�i�H�����л\�e����r
SetColor(int color)��J��X������C��
end(int page_x, int page_y)��J������xy���X�������U���ĪG
*/
#ifndef NORMALPAGE_H
#define NORMALPAGE_H
#define MOUSE_Click(mButton) (GetAsyncKeyState(mButton) & 0x8000 ? 1 : 0) // �B�z�ƹ��I��MOUSE_Click()�iŪ���ƹ��ާ@
class NormalPage
{
protected:
	int mousex;
	int mousey;
	int interface_cx = ((GetSystemMetrics(SM_CXSCREEN)) - 585) / 2;
	int interface_cy = ((GetSystemMetrics(SM_CYSCREEN)) - 375) / 2;
	int mousey_control = 0;
	void resetmousesit()
	{
		POINT mouse;
		GetCursorPos(&mouse);
		mousex = mouse.x;
		mousey = mouse.y;
	}
	void SetWindowsSize(int w, int h)
	{
		POINT mouse;
		GetCursorPos(&mouse);
		mousex = mouse.x;
		mousey = mouse.y;
		SetWindowPos(GetConsoleWindow(), HWND_TOP, interface_cx, interface_cy, 0, 0, SWP_NOSIZE);
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SMALL_RECT rc = {0, 0, w, h};
		SetConsoleWindowInfo(hOut, true, &rc);
	}
	void PageShake()
	{
		for (int i = 0; i < 10; i++)
		{
			SetWindowPos(GetConsoleWindow(), HWND_TOP, interface_cx + rand() % 50 - 25, interface_cy + rand() % 50 - 25, 0, 0, SWP_NOSIZE);
			int tem_time = clock();
			while (clock() - tem_time < 20)
			{
				if (_kbhit())
					_getch();
			}
		}
		SetWindowPos(GetConsoleWindow(), HWND_TOP, interface_cx, interface_cy, 0, 0, SWP_NOSIZE);
	}
	void PageMove(int x, int y)
	{
		SetWindowPos(GetConsoleWindow(), HWND_TOP, x, y, 0, 0, SWP_NOSIZE);
	}
	void printsit()
	{
		POINT cursorPos;
		if (GetCursorPos(&cursorPos))
		{
			int x = cursorPos.x;
			int y = cursorPos.y;
			HDC hdc = GetDC(NULL);
			cout << mousex - interface_cx << " " << mousey - interface_cy << " " << GetSystemMetrics(SM_CXSCREEN) << " " << GetSystemMetrics(SM_CYSCREEN);
		}
	}
	void gotoxy(int x, int y)
	{
		COORD pos = {x, y};
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hOut, pos);
		return;
	}
	void SetColor(int color)
	{
		HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, color);
		return;
	}
	void end(int page_x, int page_y)
	{
		int window_cx = GetSystemMetrics(SM_CXSCREEN);
		int window_cy = GetSystemMetrics(SM_CYSCREEN);
		int page_vy = -25;
		int page_vx = 0;
		int renew_time = clock();
		while (page_y < window_cy)
		{
			if (_kbhit())
				_getch();
			if (clock() - renew_time >= 30)
			{
				renew_time = clock();
				page_x += page_vx;
				page_y += page_vy;
				page_vy += 2;
				PageMove(page_x, page_y);
			}
		}
		system("cls");
	}
};
#endif