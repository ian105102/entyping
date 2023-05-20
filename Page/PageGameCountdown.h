#pragma once
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
		int countdown_sec = 60, start;
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
						Stop(1);
					}
					else if (ch == map_char[8])
					{
						gamecountdown_score++;
						AddData(1);
					}
					else
					{
						gamecountdown_score--;
						AddData(2);
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
		cout << "                                  | " << endl;
		cout << "                end               | " << endl;
		cout << "                                  | " << endl;
		cout << "                                  | " << endl;
		cout << "                                  | " << endl;
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
					   {"         再按一次ESC可以繼續!         "},
					   {"                                    "},
					   {"                                    "},
					   {"------------------------------------"}};

	void SetData(void)
	{
		for (int i = 0; i < 18; i++)
		{
			if (i < 8)
			{
				map_char[i] = ' ';
			}
			else
			{
				int r = (rand() % 26) + 97;
				map_char[i] = r;
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
	void AddData(int RoW)
	{
		color_change[18] = RoW;
		int y = 34;
		for (int i = 0; i < 17; i++)
		{
			map_char[i] = map_char[i + 1];
			color_change[y] = color_change[y - 2];
			y -= 2;
		}
		int R = (rand() % 26) + 97;
		map_char[17] = R;
		color_change[0] = 0;

		int j = 0;
		for (int i = 34; i >= 0; i -= 2)
		{
			game_map[5][i] = map_char[j];
			j++;
		}
		return;
	}
	void Stop(int sleep)
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
				}
			}
		}
		system("cls");
		return;
	}
};
#endif