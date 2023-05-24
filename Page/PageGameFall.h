/*
落下模式遊戲的頁面
GameStage()處理頁面流程
Print()處理頁面輸出
*/
#ifndef PAGEGAMEFALL_H
#define PAGEGAMEFALL_H

class PageGameFall : NormalPage
{
public:
	int GameFallScore()
	{
		return gamefall_score;
	}
	int GameStage(int game_stage, int game_difficult)
	{
		PlaySound(NULL, NULL, SND_NODEFAULT);
		CountDown();
		ResetGame3();
		gamefall_score = 0;
		int speed_time;
		double speed = 1;
		int clock_time = clock();
		int renew_time = clock();
		HDC hdc = GetDC(NULL);
		double page_angle = ((rand() % 50) + 20) * 3.1415926 / 180;
		double page_vx = 3 * (game_difficult + 1) * cos(page_angle), page_vy = 3 * (game_difficult + 1) * sin(page_angle), page_x = 450, page_y = 200;
		SetWindowsSize(37, 11);

		while (map_char[32] == '\0' && gamefall_score > -998 && gamefall_score < 998)
		{
			speed_time = clock();
			int sleep = 0;
			int x = rand() % 7 + 1;
			int ch;

			Move(x);
			while (clock() - speed_time <= (500 / speed + 500 / (game_difficult * 2 + 1)) && gamefall_score > -998 && gamefall_score < 998)
			{

				if (clock() - clock_time >= 1000)
				{
					clock_time = clock();
					speed = speed + 0.05;
					Print();
				}
				if (clock() - renew_time >= 30 && (clock() - start_time) / 1000 > 30 - game_difficult * 10)
				{
					renew_time = clock();
					page_x += page_vx;
					page_y += page_vy;
					int window_cx = GetSystemMetrics(SM_CXSCREEN);
					int window_cy = GetSystemMetrics(SM_CYSCREEN);
					if (page_x <= 0)
					{
						page_vx *= -1;
					}
					if (page_y <= 0)
					{
						page_vy *= -1;
					}
					if (page_x + 570 >= window_cx)
					{
						page_vx *= -1;
					}
					if (page_y + 370 >= window_cy)
					{
						page_vy *= -1;
					}
					PageMove(page_x, page_y);
				}
				if (_kbhit())
				{
					ch = _getch();
					if (ch == 27)
					{
						sleep = 1;
					}
					else
					{
						Cheack(ch);
					}
					if (sleep == 1) {
						if (stop(sleep)) {
							return 0;
						}
					}
						
					sleep = 0;
				}
			}
		}
		system("cls");
		SetColor(9);
		cout << "------------------------------------" << endl;
		cout << "                                  | " << endl;
		cout << "                                  | " << endl;
		cout << "                                  | " << endl;
		cout << "                end               | " << endl;
		cout << "                                  | " << endl;
		cout << "                                  | " << endl;
		cout << "                                  | " << endl;
		cout << "                                  | " << endl;
		cout << "------------------------------------" << endl;
		SetColor(7);
		end(page_x, page_y);
		return 5;
	}

private:
	int gamefall_score = 0;
	int start_time = 0;
	int pos_x[34] = {};
	int total = 0;
	char map_char[34] = {};
	string gamefall_map[10];
	void CountDown()
	{
		int time = clock();
		gotoxy(0, 0);
			SetColor(11);
			cout << "------------------------------------" << endl;
			cout << "                                  | " << endl;
			cout << "                                  | " << endl;
			cout << "                                  | " << endl;
			cout << "                 3                | " << endl;
			cout << "                                  | " << endl;
			cout << "                                  | " << endl;
			cout << "                                  | " << endl;
			cout << "                                  | " << endl;
			cout << "------------------------------------" << endl;
			SetColor(7);
			while (clock() - time < 1000) {
			}

			gotoxy(0, 0);
			SetColor(11);
			cout << "------------------------------------" << endl;
			cout << "                                  | " << endl;
			cout << "                                  | " << endl;
			cout << "                                  | " << endl;
			cout << "                 2                | " << endl;
			cout << "                                  | " << endl;
			cout << "                                  | " << endl;
			cout << "                                  | " << endl;
			cout << "                                  | " << endl;
			cout << "------------------------------------" << endl;
			SetColor(7);
			while (clock() - time < 2000) {
			}
			gotoxy(0, 0);
			SetColor(11);
			cout << "------------------------------------" << endl;
			cout << "                                  | " << endl;
			cout << "                                  | " << endl;
			cout << "                                  | " << endl;
			cout << "                 1                | " << endl;
			cout << "                                  | " << endl;
			cout << "                                  | " << endl;
			cout << "                                  | " << endl;
			cout << "                                  | " << endl;
			cout << "------------------------------------" << endl;
			SetColor(7);
			while (clock() - time < 3000) {
				if(_kbhit())
				 _getch();
			}
	}

	int stop(int sleep)
	{
		system("CLS");
		int timeresit = clock();
		SetColor(9);
		gotoxy(0, 0);
		cout << "------------------------------------" << endl;
		cout << "                                  | " << endl;
		cout << "                                  | " << endl;
		cout << "                                  | " << endl;
		cout << "               stop               | " << endl;
		cout << "       再按一次ESC可以繼續!       | " << endl;
		cout << "      按Backspace可以回首頁       | " << endl;
		cout << "                                  | " << endl;
		cout << "                                  | " << endl;
		cout << "------------------------------------" << endl;
		cout << "score: " << gamefall_score << "    time: " << (clock() - start_time) / 1000 << endl;
		SetColor(7);
		while (sleep == 1)
		{
			int ch = _getch();
			if (ch == 27)
			{
				start_time += (clock() - timeresit);
				system("CLS");
				Print();
				sleep = 0;
				return 0;
			}
			if (ch == 8)
			{
				start_time += (clock() - timeresit);
				system("CLS");
				sleep = 0;
				return 1;
			}
		}

	}
	void ResetGame3()
	{
		for (int i = 0; i < 34; i++)
		{
			pos_x[i] = 0;
			map_char[i] = '\0';
		}
		total = 0;
		start_time = clock();
		gamefall_map[0] = "------------------------------------";
		gamefall_map[1] = "                                  | ";
		gamefall_map[2] = "                                  | ";
		gamefall_map[3] = "                                  | ";
		gamefall_map[4] = "                                  | ";
		gamefall_map[5] = "                                  | ";
		gamefall_map[6] = "                                  | ";
		gamefall_map[7] = "                                  | ";
		gamefall_map[8] = "                                  | ";
		gamefall_map[9] = "------------------------------------";
	}
	void Cheack(int ch)
	{
		if (ch == map_char[0])
		{
			PlaySound(TEXT("musics/click2.wav"), NULL, SND_ASYNC);
			gamefall_score++;
			gamefall_map[pos_x[0]][total - 1] = ' ';
			total--;
			for (int i = 0; i < 33; i++)
			{
				pos_x[i] = pos_x[i + 1];
				map_char[i] = map_char[i + 1];
			}
		}
		else
		{
			PlaySound(TEXT("musics/di.wav"), NULL, SND_ASYNC);
			SetColor(0xC);
			gamefall_score--;
		}
		Print();
	}
	void Move(int x)
	{

		for (int i = 1; i <= 8; i++)
		{
			for (int j = 33; j >= 1; j--)
			{
				gamefall_map[i][j] = gamefall_map[i][j - 1];
			}
			gamefall_map[i][0] = ' ';
		}
		Print();
		int r = (rand() % 26) + 97;
		gamefall_map[x][0] = r;
		pos_x[total] = x;
		map_char[total] = r;
		total++;
	}
	void Print()
	{
		gotoxy(0, 0);
		for (int i = 0; i < 10; i++)
		{
			cout << gamefall_map[i] << endl;
		}
		SetColor(7);
		cout << "score: " << gamefall_score << "    time: " << (clock() - start_time) / 1000 << endl;
	}
};
#endif