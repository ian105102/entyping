/*
¸¨¤U¼Ò¦¡¹CÀ¸ªº­¶­±
GameStage()³B²z­¶­±¬yµ{
Print()³B²z­¶­±¿é¥X
CountDown()°µ¶}©l­p®É
stop(int sleep) ³B²z¼È°±
ResetGameFall() ¦n¹³¤£¤Ó»Ý­n³o­Ó¡A´N¬O³]©wªì©l­È
Cheack(int ch) §PÂ_¿é¤J¬O§_¥¿½T
Move(int x) ²¾°Ê¨Ã·s¼WÃD¥Ø
Print() ¿é¥X
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
		ResetGameFall();
		gamefall_score = 0;
		int speed_time;
		double speed = 1;
		int clock_time = clock();
		int renew_time = clock();
		double page_angle = ((rand() % 50) + 20) * 3.1415926 / 180;
		double page_vx = 3 * (game_difficult + 1) * cos(page_angle), page_vy = 3 * (game_difficult + 1) * sin(page_angle), page_x = 450, page_y = 200;
		SetWindowsSize(35, 11);

		while (map_char[33] == '\0' && gamefall_score > -998 && gamefall_score < 998)
		{
			speed_time = clock();
			int sleep = 0;
			int x = rand() % 7 + 1;
			int ch;

			Move(x);																														// ²¾°Ê¦r¥À
			while (clock() - speed_time <= (500 / speed + 500 / (game_difficult * 2 + 1)) && gamefall_score > -998 && gamefall_score < 998) // ©T©w®É¶¡²¾°Ê
			{

				if (clock() - clock_time >= 1000) // ­p®É¾¹
				{
					clock_time = clock();
					speed = speed + 0.05;
					Print();
				}
				if (clock() - renew_time >= 30 && (clock() - start_time) / 1000 > 30 - game_difficult * 10) // ³B²z¤¶­±²¾°Ê
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
				if (_kbhit()) // ¿é¤J
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
					if (sleep == 1)
					{
						if (stop(sleep))
						{
							return 0;
						}
					}

					sleep = 0;
				}
			}
		}
		system("cls"); // µ²§ô
		SetColor(9);
		cout << "------------------------------------" << endl;
		cout << "                                  ¢iùþ" << endl;
		cout << "                                  ùþ¢i" << endl;
		cout << "    ùþùþùþùþùþ   ùþùþ    ùþ   ùþùþùþùþ     ùþ  ¢iùþ" << endl;
		cout << "    ùþ       ùþ ùþ   ùþ   ùþ   ùþ    ùþ  ùþ¢i" << endl;
		cout << "    ùþùþùþùþùþ   ùþ  ùþ  ùþ   ùþ   ùþ    ùþ  ¢iùþ" << endl;
		cout << "    ùþ       ùþ   ùþ ùþ   ùþ   ùþ       ùþ¢i" << endl;
		cout << "    ùþùþùþùþùþ   ùþ    ùþùþ   ùþùþùþùþ     ùþ  ¢iùþ" << endl;
		cout << "                                  ùþ¢i" << endl;
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
		SetColor(12);
		PlaySound(TEXT("musics/di.wav"), NULL, SND_ASYNC);
		cout << "------------------------------------" << endl;
		cout << "                                  ¢iùþ" << endl;
		cout << "            ùþùþùþùþùþùþùþùþùþ             ùþ¢i" << endl;
		cout << "                   ùþùþ             ¢iùþ" << endl;
		cout << "                   ùþùþ             ùþ¢i" << endl;
		cout << "              ùþùþùþùþùþùþùþ             ¢iùþ" << endl;
		cout << "                   ùþùþ             ùþ¢i" << endl;
		cout << "                   ùþùþ             ¢iùþ" << endl;
		cout << "            ùþùþùþùþùþùþùþùþùþ             ùþ¢i" << endl;
		cout << "------------------------------------" << endl;
		SetColor(7);
		while (clock() - time < 1000)
		{
		}
		PlaySound(TEXT("musics/di.wav"), NULL, SND_ASYNC);
		gotoxy(0, 0);
		SetColor(12);
		cout << "------------------------------------" << endl;
		cout << "                                  ¢iùþ" << endl;
		cout << "             ùþùþùþùþùþùþùþùþùþ            ùþ¢i" << endl;
		cout << "                    ùþùþ            ¢iùþ" << endl;
		cout << "                    ùþùþ            ùþ¢i" << endl;
		cout << "             ùþùþùþùþùþùþùþùþùþ            ¢iùþ" << endl;
		cout << "             ùþùþ                   ùþ¢i" << endl;
		cout << "             ùþùþ                   ¢iùþ" << endl;
		cout << "             ùþùþùþùþùþùþùþùþùþ            ùþ¢i" << endl;
		cout << "------------------------------------" << endl;
		SetColor(7);
		while (clock() - time < 2000)
		{
		}
		PlaySound(TEXT("musics/di.wav"), NULL, SND_ASYNC);
		gotoxy(0, 0);
		SetColor(10);
		cout << "------------------------------------" << endl;
		cout << "                                  ¢iùþ" << endl;
		cout << "                ùþùþ                ùþ¢i" << endl;
		cout << "               ùþùþùþ                ¢iùþ" << endl;
		cout << "                ùþùþ                ùþ¢i" << endl;
		cout << "                ùþùþ                ¢iùþ" << endl;
		cout << "                ùþùþ                ùþ¢i" << endl;
		cout << "                ùþùþ                ¢iùþ" << endl;
		cout << "              ùþùþùþùþùþùþ              ùþ¢i" << endl;
		cout << "------------------------------------" << endl;
		SetColor(7);
		while (clock() - time < 3000)
		{
			if (_kbhit())
				_getch();
		}
		PlaySound(TEXT("musics/di1.wav"), NULL, SND_ASYNC);
	}

	int stop(int sleep)
	{
		system("CLS");
		int timeresit = clock();
		SetColor(9);
		gotoxy(0, 0);
		cout << "------------------------------------" << endl;
		cout << "                                  ¢iùþ" << endl;
		cout << "                                  ùþ¢i" << endl;
		cout << "                                  ¢iùþ" << endl;
		cout << "               stop               ùþ¢i" << endl;
		cout << "       ¦A«ö¤@¦¸ESC¥i¥HÄ~Äò!       ¢iùþ" << endl;
		cout << "      «öBackspace¥i¥H¦^­º­¶       ùþ¢i" << endl;
		cout << "                                  ¢iùþ" << endl;
		cout << "                                  ùþ¢i" << endl;
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
		return 0;
	}
	void ResetGameFall()
	{
		for (int i = 0; i < 34; i++)
		{
			pos_x[i] = 0;
			map_char[i] = '\0';
		}
		total = 0;
		start_time = clock();
		gamefall_map[0] = "------------------------------------";
		gamefall_map[1] = "                                  ¢iùþ";
		gamefall_map[2] = "                                  ùþ¢i";
		gamefall_map[3] = "                                  ¢iùþ";
		gamefall_map[4] = "                                  ùþ¢i";
		gamefall_map[5] = "                                  ¢iùþ";
		gamefall_map[6] = "                                  ùþ¢i";
		gamefall_map[7] = "                                  ¢iùþ";
		gamefall_map[8] = "                                  ùþ¢i";
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
		cout << "score: " << gamefall_score << "    time: " << (clock() - start_time) / 1000 <<"     "<< endl;
	}
};
#endif
