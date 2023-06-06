/*
 GameStage() ­¶­±¥D¬yµ{
 SetData() ³]©wªì©l­È
 AddData(int RoW) ±À¸ê®Æ
 Stop(int sleep)³B²z¼È°±
  Print(int countdown_sec) ³B²z¿é¥X
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
		game_map[0] = {"------------------------------------"};
		game_map[1] = {"                                    "};
		game_map[2] = {"                                    "};
		game_map[3] = {"===================================="};
		game_map[4] = {"                  ¡õ                 "};
		game_map[5] = {"                                    "};
		game_map[6] = {"===================================="};
		game_map[7] = {"                                    "};
		game_map[8] = {"                                    "};
		game_map[9] = {"------------------------------------"};
		CountDown();
		SetData();
		Print(countdown_sec);
		while (countdown_sec > 0 && !(gamecountdown_score < -998 || gamecountdown_score > 998))
		{
			start = clock();
			Print(countdown_sec);
			while ((clock() - start) < 1000)
			{
				SetWindowsSize(35, 11);
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
		cout << "    ùþùþùþùþùþ   ùþùþ    ùþ   ùþùþùþùþ     ùþ  | " << endl;
		cout << "    ùþ       ùþ ùþ   ùþ   ùþ   ùþ    ùþ  | " << endl;
		cout << "    ùþùþùþùþùþ   ùþ  ùþ  ùþ   ùþ   ùþ    ùþ  | " << endl;
		cout << "    ùþ       ùþ   ùþ ùþ   ùþ   ùþ       | " << endl;
		cout << "    ùþùþùþùþùþ   ùþ    ùþùþ   ùþùþùþùþ     ùþ  | " << endl;
		cout << "                                  | " << endl;
		cout << "------------------------------------" << endl;
		SetColor(7);
		end(interface_cx, interface_cy);
		return 5;
	}

private:
	int gamecountdown_score = 0;
	int color_change[35] = {0};
	char map_char[18];
	string game_map[10] = {{"------------------------------------"},
						   {"                                    "},
						   {"                                    "},
						   {"===================================="},
						   {"                  ¡õ                 "},
						   {"                                    "},
						   {"===================================="},
						   {"                                    "},
						   {"                                    "},
						   {"------------------------------------"}};
	string stop[10] = {{"------------------------------------"},
					   {"                                    "},
					   {"                                    "},
					   {"                                    "},
					   {"                stop                "},
					   {"                                    "},
					   {"        ¦A«ö¤@¦¸ESC¥i¥HÄ~Äò!          "},
					   {"       «öBackspace¥i¥H¦^­º­¶        "},
					   {"                                    "},
					   {"------------------------------------"}};
	string s[9] = {"\0"};
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
		for (int i = 0; i <= 17; i++) // ±À°Ê¦r¤¸
		{
			for (int j = 1; j <= 8; j++)
			{
				if (j < 3 || j > 6)
				{
					game_map[j][36 - (i * 2)] = game_map[j][34 - (i * 2)];
				}
			}
			map_char[i] = map_char[i + 1];
			color_change[y] = color_change[y - 2]; // ±À°ÊÃC¦â
			y -= 2;
		}

		for (int i = 1; i <= 8; i++)
		{
			if (countdown_sec < 30)
			{
				if ((i < 3 || i > 6) && rand() % 25 == 0 && s[i].size() == 0)
				{
					int num = rand() % 3;
					if (num == 0)
					{
						s[i] = "     Hurry up!";
					}
					else if (num == 1)
					{
						s[i] = "    HO NO!";
					}
					else if (num == 2)
					{
						s[i] = "    Eazy!";
					}
				}
				if ((i < 3 || i > 6) && s[i].size() > 0)
				{
					game_map[i][0] = s[i][s[i].size() - 1];
					s[i].pop_back();
				}
				else if (i < 3 || i > 6)
				{
					game_map[i][0] = ' ';
				}
			}
		}
		map_char[17] = (char)(rand() % 26) + 97;
		color_change[0] = 0;
		int j = 0;
		for (int i = 34; i >= 0; i -= 2) // ±N¸ê®Æ¶K¨ìmap¸Ì
		{
			game_map[5][i] = map_char[j];
			j++;
		}
		return;
	}
	void CountDown()
	{
		int time = clock();
		gotoxy(0, 0);
		SetColor(12);
		PlaySound(TEXT("musics/di.wav"), NULL, SND_ASYNC);
		cout << "------------------------------------" << endl;
		cout << "                                    " << endl;
		cout << "            ùþùþùþùþùþùþùþùþùþ               " << endl;
		cout << "                   ùþùþ               " << endl;
		cout << "                   ùþùþ               " << endl;
		cout << "              ùþùþùþùþùþùþùþ               " << endl;
		cout << "                   ùþùþ               " << endl;
		cout << "                   ùþùþ               " << endl;
		cout << "            ùþùþùþùþùþùþùþùþùþ               " << endl;
		cout << "------------------------------------" << endl;
		SetColor(7);
		while (clock() - time < 1000)
		{
			SetWindowsSize(35, 11);
		}
		PlaySound(TEXT("musics/di.wav"), NULL, SND_ASYNC);
		gotoxy(0, 0);
		SetColor(12);
		cout << "------------------------------------" << endl;
		cout << "                                    " << endl;
		cout << "             ùþùþùþùþùþùþùþùþùþ              " << endl;
		cout << "                    ùþùþ              " << endl;
		cout << "                    ùþùþ              " << endl;
		cout << "             ùþùþùþùþùþùþùþùþùþ              " << endl;
		cout << "             ùþùþ                     " << endl;
		cout << "             ùþùþ                     " << endl;
		cout << "             ùþùþùþùþùþùþùþùþùþ              " << endl;
		cout << "------------------------------------" << endl;
		SetColor(7);
		while (clock() - time < 2000)
		{
			SetWindowsSize(35, 11);
		}
		PlaySound(TEXT("musics/di.wav"), NULL, SND_ASYNC);
		gotoxy(0, 0);
		SetColor(10);
		cout << "------------------------------------" << endl;
		cout << "                                    " << endl;
		cout << "                ùþùþ                  " << endl;
		cout << "               ùþùþùþ                  " << endl;
		cout << "                ùþùþ                  " << endl;
		cout << "                ùþùþ                  " << endl;
		cout << "                ùþùþ                  " << endl;
		cout << "                ùþùþ                  " << endl;
		cout << "              ùþùþùþùþùþùþ                " << endl;
		cout << "------------------------------------" << endl;
		SetColor(7);
		while (clock() - time < 3000)
		{
			SetWindowsSize(35, 11);
			if (_kbhit())
				_getch();
		}
		PlaySound(TEXT("musics/di1.wav"), NULL, SND_ASYNC);
	}

	int Stop(int sleep)
	{
		system("cls");
		SetColor(9);
		int stop_time = clock();
		for (int i = 0; i < 10; i++)
		{
			SetColor(3);
			cout << stop[i] << endl;
		}
		SetColor(7);
		char ch;
		while (sleep == 1)
		{
			SetWindowsSize(35, 11);
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
			}
			else
			{
				if (((i < 3 && i > 0) || (i > 6 && i < 9)))
				{
					SetColor(4);
				}
				else
				{
					SetColor(7);
					;
				}
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
		cout << "ÁÙ³Ñ " << countdown_sec << " ¬í¡Ascore: " << to_string(gamecountdown_score) + " " << endl;
		SetColor(7);
		return;
	}
};
#endif