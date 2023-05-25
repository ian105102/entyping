/*
 GameStage() 頁面主流程
 SetData() 設定初始值
 AddData(int RoW) 推資料
 Stop(int sleep)處理暫停
  Print(int countdown_sec) 處理輸出
*/
#ifndef PAGEGAMERECOUNTDOWN_H
#define PAGEGAMERECOUNTDOWN_H
class PageGameCountdown : NormalPage
{
public:
	int GameCountdownScore()
	{
		return gamecountdown_score;
	}
	int GameStage()
	{
		PlaySound(NULL, NULL, SND_NODEFAULT);
		int countdown_sec = 60, start;
		gamecountdown_score = 0;
		SetData();
		Print(countdown_sec);
		while (countdown_sec > 0 && !(gamecountdown_score < -998 || gamecountdown_score > 998))
		{
			start = clock();
			Print(countdown_sec);
			while ((clock() - start) < 1000)
			{
				SetWindowsSize(36, 11);
				int ch;
				if (_kbhit())
				{

					ch = _getch();
					if (ch == 27)
					{
						if (Stop(1) == 1)
						{
							return 0;
						}
					}
					else if (ch == map_char[8])
					{
						PlaySound(TEXT("musics/click2.wav"), NULL, SND_ASYNC);
						gamecountdown_score++;
						AddData(1, countdown_sec);
					}
					else
					{
						PlaySound(TEXT("musics/di.wav"), NULL, SND_ASYNC);
						gamecountdown_score--;
						AddData(2, countdown_sec);
						PageShake();
					}

					Print(countdown_sec);
				}
			}
			countdown_sec--;
		}
		system("cls");
		SetColor(9);
		cout << "------------------------------------" << endl;
		cout << "                                  | " << endl;
		cout << "                                  | " << endl;
		cout << "    ▓▓▓▓▓   ▓▓    ▓   ▓▓▓▓     ▓  | " << endl;
		cout << "    ▓       ▓ ▓   ▓   ▓   ▓    ▓  | " << endl;
		cout << "    ▓▓▓▓▓   ▓  ▓  ▓   ▓   ▓    ▓  | " << endl;
		cout << "    ▓       ▓   ▓ ▓   ▓   ▓       | " << endl;
		cout << "    ▓▓▓▓▓   ▓    ▓▓   ▓▓▓▓     ▓  | " << endl;
		cout << "                                  | " << endl;
		cout << "------------------------------------" << endl;
		SetColor(7);
		end(450, 200);
		return 5;
	}

private:
	int gamecountdown_score = 0;
	int color_change[35] = {0};
	char map_char[18];
	string game_map[10] = {{"------------------------------------"},
						   {"                                    "},
						   {"                                    "},
						   {"                                    "},
						   {"                  ↓                 "},
						   {"                                    "},
						   {"                                    "},
						   {"                                    "},
						   {"                                    "},
						   {"------------------------------------"}};
	string stop[10] = {{"------------------------------------"},
					   {"                                    "},
					   {"                                    "},
					   {"                                    "},
					   {"                stop                "},
					   {"                                    "},
					   {"        再按一次ESC可以繼續!          "},
					   {"       按Backspace可以回首頁        "},
					   {"                                    "},
					   {"------------------------------------"}};

	void SetData()
	{
		for (int i = 0; i < 18; i++)
		{
			if (i < 8)
			{
				map_char[i] = ' ';
			}
			else
			{
				map_char[i] = (char)(rand() % 26) + 97;
			}
		}
		int j = 0;
		for (int i = 34; i >= 0; i -= 2)
		{
			game_map[5][i] = map_char[j];
			j++;
		}
		return;
	}
	void AddData(int RoW, int countdown_sec)
	{
		color_change[18] = RoW;
		int y = 34;
		for (int i = 0; i <= 17; i++) // 推動字元
		{
			for (int j = 1; j <= 8; j++)
			{
				if (j != 5 && j != 4)
				{
					game_map[j][36 - (i * 2)] = game_map[j][34 - (i * 2)];
				}
			}
			map_char[i] = map_char[i + 1];
			color_change[y] = color_change[y - 2]; // 推動顏色
			y -= 2;
		}
		for (int i = 1; i <= 8; i++)
		{
			if (countdown_sec < 30)
			{
				int num = rand();
				if (i != 5 && i != 4 && num % 5 == 1)
				{
					game_map[i][0] = '<';
				}
				else if (i != 5 && i != 4 && num % 5 == 2)
				{
					game_map[i][0] = '>';
				}
				else
				{
					game_map[i][0] = ' ';
				}
			}
		}
		map_char[17] = (char)(rand() % 26) + 97;
		color_change[0] = 0;
		int j = 0;
		for (int i = 34; i >= 0; i -= 2) // 將資料貼到map裡
		{
			game_map[5][i] = map_char[j];
			j++;
		}
		return;
	}
	int Stop(int sleep)
	{
		system("cls");
		SetColor(9);
		int stop_time = clock();
		gotoxy(0, 0);
		for (int i = 0; i < 10; i++)
		{
			SetColor(3);
			cout << stop[i] << endl;
		}
		SetColor(7);
		char ch;
		while (sleep == 1)
		{
			if (_kbhit())
			{
				ch = _getch();
				if (ch == 27)
				{
					sleep = 0;
					system("cls");
					return 0;
				}
				if (ch == 8)
				{

					sleep = 0;
					system("cls");
					return 1;
				}
			}
		}
		system("cls");
		return 0;
	}
	void Print(int countdown_sec)
	{
		gotoxy(0, 0);
		for (int i = 0; i < 10; i++)
		{
			if (i == 5)
			{
				for (int j = 0; j < 36; j++)
				{
					if (j > 18)
					{
						if (color_change[j] == 1)
						{
							SetColor(2);
						}
						else if (color_change[j] == 2)
						{
							SetColor(12);
						}
						cout << game_map[i][j];
					}
					else
					{
						SetColor(7);
						cout << game_map[i][j];
					}
				}
				cout << endl;
				SetColor(7);
			}
			else
			{
				cout << game_map[i] << endl;
			}
		}
		if (countdown_sec < 10)
		{
			SetColor(12);
		}
		else
		{
			SetColor(7);
		}
		cout << "還剩 " << countdown_sec << " 秒，score: " << to_string(gamecountdown_score) + " " << endl;
		SetColor(7);
		return;
	}
};
#endif