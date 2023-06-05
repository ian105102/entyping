
/*
共通成員函式、成員變數位置

mousey
mousex
為滑鼠xy位置
resetmousesit() 將刷新滑鼠位置至mousex、mousey
SetWindowsSize(int w,int h) 處理視窗位置與大小
PageShake()頁面跳動
PageMove()給定xy固定頁面位置
printsit()用於測試，放在View()、Print()裡可以輸出滑鼠位置以及螢幕最大位置
gotoxy(x, y)將dos介面光標移到xy，移到00可以直接覆蓋前面文字
SetColor(int color)輸入色碼後改變顏色
end(int page_x, int page_y)輸入頁面的xy做出頁面落下的效果
*/
#ifndef NORMALPAGE_H
#define NORMALPAGE_H
#define MOUSE_Click(mButton) (GetAsyncKeyState(mButton) & 0x8000 ? 1 : 0) // 處理滑鼠點擊MOUSE_Click()可讀取滑鼠操作
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