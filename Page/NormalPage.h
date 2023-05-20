
/*
共通成員函式、成員變數位置
SetWindowsSize(w,h) 處理視窗位置與大小
*/
#ifndef NORMALPAGE_H
#define NORMALPAGE_H
#define MOUSE_Click(mButton) (GetAsyncKeyState(mButton) & 0x8000 ? 1 : 0) // 處理滑鼠點擊MOUSE_Click()可讀取滑鼠操作
class NormalPage
{
protected:
	int mousex;
	int mousey;
	int mousey_control = 1;
	void SetWindowsSize(int w, int h)
	{
		SetWindowPos(GetConsoleWindow(), HWND_TOP, 450, 200, 0, 0, SWP_NOSIZE);
		POINT mouse;
		GetCursorPos(&mouse);
		mousex = mouse.x;
		mousey = mouse.y;
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SMALL_RECT rc = {0, 0, w, h};
		SetConsoleWindowInfo(hOut, true, &rc);
	}
	void PageShake()
	{
		for (int i = 0; i < 5; i++)
		{
			SetWindowPos(GetConsoleWindow(), HWND_TOP, 450 + rand() % 50 - 25, 200 + rand() % 50 - 25, 0, 0, SWP_NOSIZE);
			int tem_time = clock();
			while (clock() - tem_time < 20)
			{
			}
		}
		SetWindowPos(GetConsoleWindow(), HWND_TOP, 450, 200, 0, 0, SWP_NOSIZE);
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
			cout << x << " " << y << " " << GetDeviceCaps(hdc, DESKTOPHORZRES) << " " << GetDeviceCaps(hdc, DESKTOPVERTRES);
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